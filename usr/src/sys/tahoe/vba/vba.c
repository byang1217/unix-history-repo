/*	vba.c	1.7	87/04/06	*/

/*
 * Tahoe VERSAbus adapator support routines.
 */

#include "../tahoe/mtpr.h"
#include "../tahoe/pte.h"

#include "param.h"
#include "buf.h"
#include "cmap.h"
#include "conf.h"
#include "dir.h"
#include "dk.h"
#include "map.h"
#include "systm.h"
#include "user.h"
#include "vmparam.h"
#include "vmmac.h"
#include "proc.h"
#include "syslog.h"

#include "../tahoevba/vbavar.h"

#define	kvtopte(v) (&Sysmap[btop((int)(v) &~ KERNBASE)])

/*
 * Allocate private page map and intermediate buffer
 * for a VERSAbus device, large enough for maximum transfer size.
 * Intermediate buffer 
 * Make intermediate buffer uncacheable.
 */
vbainit(vb, xsize, flags)
	register struct vb_buf *vb;
	int xsize, flags;
{
	register struct pte *pte;
	register n;

	vb->vb_flags = flags;
	vbmapalloc(btoc(xsize) + 1, &vb->vb_map, &vb->vb_utl);
	n = roundup(xsize, NBPG);
	vb->vb_bufsize = n;
	if (vb->vb_rawbuf == 0)
		vb->vb_rawbuf = calloc(n);
	if ((int)vb->vb_rawbuf & PGOFSET)
		panic("vbinit pgoff");
	vb->vb_physbuf = vtoph((struct proc *)0, vb->vb_rawbuf);
	if (flags & VB_20BIT)
		vb->vb_maxphys = btoc(VB_MAXADDR20);
	else if (flags & VB_24BIT)
		vb->vb_maxphys = btoc(VB_MAXADDR24);
	else
		vb->vb_maxphys = btoc(VB_MAXADDR32);
	if (btoc(vb->vb_physbuf + n) > vb->vb_maxphys)
		panic("vbinit physbuf");
	
	/*
	 * Make raw buffer pages uncacheable.
	 */
	pte = kvtopte(vb->vb_rawbuf);
	for (n = btoc(n); n--; pte++)
		pte->pg_nc = 1;
	mtpr(TBIA, 0);
}

/*
 * Check a transfer to see whether it can be done directly
 * to the destination buffer, or whether it must be copied.
 * On Tahoe, the lack of a bus I/O map forces data to be copied
 * to a physically-contiguous buffer whenever one of the following is true:
 *	1) The data length is not a multiple of sector size.
 *	   (The swapping code does this, unfortunately.)
 *	2) The buffer is not physically contiguous and the controller
 *	   does not support scatter-gather operations.
 *	3) The physical address for I/O is higher than addressible
 *	   by the device.
 * This routine is called by the start routine.
 * If copying is necessary, the intermediate buffer is mapped;
 * if the operation is a write, the data is copied into the buffer.
 * It returns the physical address of the first byte for DMA, to
 * be presented to the controller.
 */
u_long
vbasetup(bp, vb, sectsize)
	register struct buf *bp;
	register struct vb_buf *vb;
	int sectsize;
{
	register struct pte *spte, *dpte;
	register int p, i;
	int npf, o, v;

	o = (int)bp->b_un.b_addr & PGOFSET;
	npf = btoc(bp->b_bcount + o);
	vb->vb_iskernel = (((int)bp->b_un.b_addr & KERNBASE) == KERNBASE);
	if (vb->vb_iskernel)
		spte = kvtopte(bp->b_un.b_addr);
	else
		spte = vtopte((bp->b_flags&B_DIRTY) ? &proc[2] : bp->b_proc,
		    btop(bp->b_un.b_addr));
	if (bp->b_bcount % sectsize)
		goto copy;
	else if ((vb->vb_flags & VB_SCATTER) == 0 ||
	    vb->vb_maxphys != VB_MAXADDR32) {
		dpte = spte;
		p = (dpte++)->pg_pfnum;
		for (i = npf; --i > 0; dpte++) {
			if ((v = dpte->pg_pfnum) != p + CLSIZE &&
			    (vb->vb_flags & VB_SCATTER) == 0)
				goto copy;
			if (p >= vb->vb_maxphys)
				goto copy;
			p = v;
		}
		if (p >= vb->vb_maxphys)
			goto copy;
	}
	vb->vb_copy = 0;
	if (vb->vb_iskernel)
		vbastat.k_raw++;
	else
		vbastat.u_raw++;
	return ((spte->pg_pfnum << PGSHIFT) + o);

copy:
	vb->vb_copy = 1;
	if (bp->b_bcount > vb->vb_bufsize)
		panic("vba xfer too large");
	if (vb->vb_iskernel) {
		if ((bp->b_flags & B_READ) == 0)
			bcopy(bp->b_un.b_addr, vb->vb_rawbuf,
			    (unsigned)bp->b_bcount);
		vbastat.k_copy++;
	} else  {
		dpte = vb->vb_map;
		for (i = npf, p = (int)vb->vb_utl; i--; p += NBPG) {
			*(int *)dpte++ = (spte++)->pg_pfnum |
			    PG_V | PG_KW | PG_N;
			mtpr(TBIS, p);
		}
		if ((bp->b_flags & B_READ) == 0)
			bcopy(vb->vb_utl + o, vb->vb_rawbuf,
			    (unsigned)bp->b_bcount);
		vbastat.u_copy++;
	}
	return (vb->vb_physbuf);
}

/*
 * Called by the driver's interrupt routine, after DMA is completed.
 * If the operation was a read, copy data to final buffer if necessary
 * or invalidate data cache for cacheable direct buffers.
 * Similar to the vbastart routine, but in the reverse direction.
 */
vbadone(bp, vb)
	register struct buf *bp;
	register struct vb_buf *vb;
{
	register npf;
	register caddr_t v;
	int o;

	if (bp->b_flags & B_READ) {
		o = (int)bp->b_un.b_addr & PGOFSET;
		if (vb->vb_copy) {
			if (vb->vb_iskernel)
				bcopy(vb->vb_rawbuf, bp->b_un.b_addr,
				    (unsigned)(bp->b_bcount - bp->b_resid));
			else {
				bcopy(vb->vb_rawbuf, vb->vb_utl + o,
				    (unsigned)(bp->b_bcount - bp->b_resid));
				dkeyinval(bp->b_proc);
			}
		} else {
			if (vb->vb_iskernel) {
				npf = btoc(bp->b_bcount + o);
				for (v = bp->b_un.b_addr; npf--; v += NBPG)
					mtpr(P1DC, (int)v);
			} else
				dkeyinval(bp->b_proc);
		}
	}
}

/*
 * Set up a scatter-gather operation for SMD/E controller.
 * This code belongs half-way between vd.c and this file.
 */
#include "vdreg.h"

vba_sgsetup(bp, vb, sg)
	register struct buf *bp;
	struct vb_buf *vb;
	struct trsg *sg;
{
	register struct pte *spte;
	register struct addr_chain *adr;
	register int npf, i;
	int o;

	o = (int)bp->b_un.b_addr & PGOFSET;
	npf = btoc(bp->b_bcount + o);
	vb->vb_iskernel = (((int)bp->b_un.b_addr & KERNBASE) == KERNBASE);
	vb->vb_copy = 0;
	if (vb->vb_iskernel) {
		spte = kvtopte(bp->b_un.b_addr);
		vbastat.k_sg++;
	} else {
		spte = vtopte((bp->b_flags&B_DIRTY) ? &proc[2] : bp->b_proc,
		    btop(bp->b_un.b_addr));
		vbastat.u_sg++;
	}

	i = min(NBPG - o, bp->b_bcount);
	sg->start_addr.wcount = (i + 1) >> 1;
	sg->start_addr.memadr = ((spte++)->pg_pfnum << PGSHIFT) + o;
	i = bp->b_bcount - i;
	if (i > VDMAXPAGES * NBPG)
		panic("vba xfer too large");
	i = (i + 1) >> 1;
	for (adr = sg->addr_chain; i > 0; adr++, i -= NBPG / 2) {
		adr->nxt_addr = (spte++)->pg_pfnum << PGSHIFT;
		adr->nxt_len = min(i, NBPG / 2);
	}
	adr->nxt_addr = 0;
	adr++->nxt_len = 0;
	return ((adr - sg->addr_chain) * sizeof(*adr) / sizeof(long));
}
