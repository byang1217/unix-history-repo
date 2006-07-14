/*
 * System call prototypes.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * $FreeBSD$
 * created from FreeBSD: src/sys/i386/ibcs2/syscalls.master,v 1.27 2006/07/14 15:42:21 jhb Exp 
 */

#ifndef _IBCS2_SYSPROTO_H_
#define	_IBCS2_SYSPROTO_H_

#include <sys/signal.h>
#include <sys/acl.h>
#include <sys/thr.h>
#include <sys/umtx.h>
#include <posix4/_semaphore.h>

#include <sys/ucontext.h>

struct proc;

struct thread;

#define	PAD_(t)	(sizeof(register_t) <= sizeof(t) ? \
		0 : sizeof(register_t) - sizeof(t))

#if BYTE_ORDER == LITTLE_ENDIAN
#define	PADL_(t)	0
#define	PADR_(t)	PAD_(t)
#else
#define	PADL_(t)	PAD_(t)
#define	PADR_(t)	0
#endif

struct ibcs2_read_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char buf_l_[PADL_(char *)]; char * buf; char buf_r_[PADR_(char *)];
	char nbytes_l_[PADL_(u_int)]; u_int nbytes; char nbytes_r_[PADR_(u_int)];
};
struct ibcs2_open_args {
	char path_l_[PADL_(char *)]; char * path; char path_r_[PADR_(char *)];
	char flags_l_[PADL_(int)]; int flags; char flags_r_[PADR_(int)];
	char mode_l_[PADL_(int)]; int mode; char mode_r_[PADR_(int)];
};
struct ibcs2_wait_args {
	char a1_l_[PADL_(int)]; int a1; char a1_r_[PADR_(int)];
	char a2_l_[PADL_(int)]; int a2; char a2_r_[PADR_(int)];
	char a3_l_[PADL_(int)]; int a3; char a3_r_[PADR_(int)];
};
struct ibcs2_creat_args {
	char path_l_[PADL_(char *)]; char * path; char path_r_[PADR_(char *)];
	char mode_l_[PADL_(int)]; int mode; char mode_r_[PADR_(int)];
};
struct ibcs2_unlink_args {
	char path_l_[PADL_(char *)]; char * path; char path_r_[PADR_(char *)];
};
struct ibcs2_execv_args {
	char path_l_[PADL_(char *)]; char * path; char path_r_[PADR_(char *)];
	char argp_l_[PADL_(char **)]; char ** argp; char argp_r_[PADR_(char **)];
};
struct ibcs2_chdir_args {
	char path_l_[PADL_(char *)]; char * path; char path_r_[PADR_(char *)];
};
struct ibcs2_time_args {
	char tp_l_[PADL_(ibcs2_time_t *)]; ibcs2_time_t * tp; char tp_r_[PADR_(ibcs2_time_t *)];
};
struct ibcs2_mknod_args {
	char path_l_[PADL_(char *)]; char * path; char path_r_[PADR_(char *)];
	char mode_l_[PADL_(int)]; int mode; char mode_r_[PADR_(int)];
	char dev_l_[PADL_(int)]; int dev; char dev_r_[PADR_(int)];
};
struct ibcs2_chmod_args {
	char path_l_[PADL_(char *)]; char * path; char path_r_[PADR_(char *)];
	char mode_l_[PADL_(int)]; int mode; char mode_r_[PADR_(int)];
};
struct ibcs2_chown_args {
	char path_l_[PADL_(char *)]; char * path; char path_r_[PADR_(char *)];
	char uid_l_[PADL_(int)]; int uid; char uid_r_[PADR_(int)];
	char gid_l_[PADL_(int)]; int gid; char gid_r_[PADR_(int)];
};
struct ibcs2_stat_args {
	char path_l_[PADL_(char *)]; char * path; char path_r_[PADR_(char *)];
	char st_l_[PADL_(struct ibcs2_stat *)]; struct ibcs2_stat * st; char st_r_[PADR_(struct ibcs2_stat *)];
};
struct ibcs2_lseek_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char offset_l_[PADL_(long)]; long offset; char offset_r_[PADR_(long)];
	char whence_l_[PADL_(int)]; int whence; char whence_r_[PADR_(int)];
};
struct ibcs2_mount_args {
	char special_l_[PADL_(char *)]; char * special; char special_r_[PADR_(char *)];
	char dir_l_[PADL_(char *)]; char * dir; char dir_r_[PADR_(char *)];
	char flags_l_[PADL_(int)]; int flags; char flags_r_[PADR_(int)];
	char fstype_l_[PADL_(int)]; int fstype; char fstype_r_[PADR_(int)];
	char data_l_[PADL_(char *)]; char * data; char data_r_[PADR_(char *)];
	char len_l_[PADL_(int)]; int len; char len_r_[PADR_(int)];
};
struct ibcs2_umount_args {
	char name_l_[PADL_(char *)]; char * name; char name_r_[PADR_(char *)];
};
struct ibcs2_setuid_args {
	char uid_l_[PADL_(int)]; int uid; char uid_r_[PADR_(int)];
};
struct ibcs2_stime_args {
	char timep_l_[PADL_(long *)]; long * timep; char timep_r_[PADR_(long *)];
};
struct ibcs2_alarm_args {
	char sec_l_[PADL_(unsigned)]; unsigned sec; char sec_r_[PADR_(unsigned)];
};
struct ibcs2_fstat_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char st_l_[PADL_(struct ibcs2_stat *)]; struct ibcs2_stat * st; char st_r_[PADR_(struct ibcs2_stat *)];
};
struct ibcs2_pause_args {
	register_t dummy;
};
struct ibcs2_utime_args {
	char path_l_[PADL_(char *)]; char * path; char path_r_[PADR_(char *)];
	char buf_l_[PADL_(struct ibcs2_utimbuf *)]; struct ibcs2_utimbuf * buf; char buf_r_[PADR_(struct ibcs2_utimbuf *)];
};
struct ibcs2_stty_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char buf_l_[PADL_(struct sgttyb *)]; struct sgttyb * buf; char buf_r_[PADR_(struct sgttyb *)];
};
struct ibcs2_gtty_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char buf_l_[PADL_(struct sgttyb *)]; struct sgttyb * buf; char buf_r_[PADR_(struct sgttyb *)];
};
struct ibcs2_access_args {
	char path_l_[PADL_(char *)]; char * path; char path_r_[PADR_(char *)];
	char flags_l_[PADL_(int)]; int flags; char flags_r_[PADR_(int)];
};
struct ibcs2_nice_args {
	char incr_l_[PADL_(int)]; int incr; char incr_r_[PADR_(int)];
};
struct ibcs2_statfs_args {
	char path_l_[PADL_(char *)]; char * path; char path_r_[PADR_(char *)];
	char buf_l_[PADL_(struct ibcs2_statfs *)]; struct ibcs2_statfs * buf; char buf_r_[PADR_(struct ibcs2_statfs *)];
	char len_l_[PADL_(int)]; int len; char len_r_[PADR_(int)];
	char fstype_l_[PADL_(int)]; int fstype; char fstype_r_[PADR_(int)];
};
struct ibcs2_kill_args {
	char pid_l_[PADL_(int)]; int pid; char pid_r_[PADR_(int)];
	char signo_l_[PADL_(int)]; int signo; char signo_r_[PADR_(int)];
};
struct ibcs2_fstatfs_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char buf_l_[PADL_(struct ibcs2_statfs *)]; struct ibcs2_statfs * buf; char buf_r_[PADR_(struct ibcs2_statfs *)];
	char len_l_[PADL_(int)]; int len; char len_r_[PADR_(int)];
	char fstype_l_[PADL_(int)]; int fstype; char fstype_r_[PADR_(int)];
};
struct ibcs2_pgrpsys_args {
	char type_l_[PADL_(int)]; int type; char type_r_[PADR_(int)];
	char dummy_l_[PADL_(caddr_t)]; caddr_t dummy; char dummy_r_[PADR_(caddr_t)];
	char pid_l_[PADL_(int)]; int pid; char pid_r_[PADR_(int)];
	char pgid_l_[PADL_(int)]; int pgid; char pgid_r_[PADR_(int)];
};
struct ibcs2_xenix_args {
	char a1_l_[PADL_(int)]; int a1; char a1_r_[PADR_(int)];
	char a2_l_[PADL_(int)]; int a2; char a2_r_[PADR_(int)];
	char a3_l_[PADL_(int)]; int a3; char a3_r_[PADR_(int)];
	char a4_l_[PADL_(int)]; int a4; char a4_r_[PADR_(int)];
	char a5_l_[PADL_(int)]; int a5; char a5_r_[PADR_(int)];
};
struct ibcs2_times_args {
	char tp_l_[PADL_(struct tms *)]; struct tms * tp; char tp_r_[PADR_(struct tms *)];
};
struct ibcs2_plock_args {
	char cmd_l_[PADL_(int)]; int cmd; char cmd_r_[PADR_(int)];
};
struct ibcs2_setgid_args {
	char gid_l_[PADL_(int)]; int gid; char gid_r_[PADR_(int)];
};
struct ibcs2_sigsys_args {
	char sig_l_[PADL_(int)]; int sig; char sig_r_[PADR_(int)];
	char fp_l_[PADL_(ibcs2_sig_t)]; ibcs2_sig_t fp; char fp_r_[PADR_(ibcs2_sig_t)];
};
struct ibcs2_msgsys_args {
	char which_l_[PADL_(int)]; int which; char which_r_[PADR_(int)];
	char a2_l_[PADL_(int)]; int a2; char a2_r_[PADR_(int)];
	char a3_l_[PADL_(int)]; int a3; char a3_r_[PADR_(int)];
	char a4_l_[PADL_(int)]; int a4; char a4_r_[PADR_(int)];
	char a5_l_[PADL_(int)]; int a5; char a5_r_[PADR_(int)];
	char a6_l_[PADL_(int)]; int a6; char a6_r_[PADR_(int)];
};
struct ibcs2_sysi86_args {
	char cmd_l_[PADL_(int)]; int cmd; char cmd_r_[PADR_(int)];
	char arg_l_[PADL_(int *)]; int * arg; char arg_r_[PADR_(int *)];
};
struct ibcs2_shmsys_args {
	char which_l_[PADL_(int)]; int which; char which_r_[PADR_(int)];
	char a2_l_[PADL_(int)]; int a2; char a2_r_[PADR_(int)];
	char a3_l_[PADL_(int)]; int a3; char a3_r_[PADR_(int)];
	char a4_l_[PADL_(int)]; int a4; char a4_r_[PADR_(int)];
};
struct ibcs2_semsys_args {
	char which_l_[PADL_(int)]; int which; char which_r_[PADR_(int)];
	char a2_l_[PADL_(int)]; int a2; char a2_r_[PADR_(int)];
	char a3_l_[PADL_(int)]; int a3; char a3_r_[PADR_(int)];
	char a4_l_[PADL_(int)]; int a4; char a4_r_[PADR_(int)];
	char a5_l_[PADL_(int)]; int a5; char a5_r_[PADR_(int)];
};
struct ibcs2_ioctl_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char cmd_l_[PADL_(int)]; int cmd; char cmd_r_[PADR_(int)];
	char data_l_[PADL_(caddr_t)]; caddr_t data; char data_r_[PADR_(caddr_t)];
};
struct ibcs2_uadmin_args {
	char cmd_l_[PADL_(int)]; int cmd; char cmd_r_[PADR_(int)];
	char func_l_[PADL_(int)]; int func; char func_r_[PADR_(int)];
	char data_l_[PADL_(caddr_t)]; caddr_t data; char data_r_[PADR_(caddr_t)];
};
struct ibcs2_utssys_args {
	char a1_l_[PADL_(int)]; int a1; char a1_r_[PADR_(int)];
	char a2_l_[PADL_(int)]; int a2; char a2_r_[PADR_(int)];
	char flag_l_[PADL_(int)]; int flag; char flag_r_[PADR_(int)];
};
struct ibcs2_execve_args {
	char path_l_[PADL_(char *)]; char * path; char path_r_[PADR_(char *)];
	char argp_l_[PADL_(char **)]; char ** argp; char argp_r_[PADR_(char **)];
	char envp_l_[PADL_(char **)]; char ** envp; char envp_r_[PADR_(char **)];
};
struct ibcs2_fcntl_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char cmd_l_[PADL_(int)]; int cmd; char cmd_r_[PADR_(int)];
	char arg_l_[PADL_(char *)]; char * arg; char arg_r_[PADR_(char *)];
};
struct ibcs2_ulimit_args {
	char cmd_l_[PADL_(int)]; int cmd; char cmd_r_[PADR_(int)];
	char newlimit_l_[PADL_(int)]; int newlimit; char newlimit_r_[PADR_(int)];
};
struct ibcs2_rmdir_args {
	char path_l_[PADL_(char *)]; char * path; char path_r_[PADR_(char *)];
};
struct ibcs2_mkdir_args {
	char path_l_[PADL_(char *)]; char * path; char path_r_[PADR_(char *)];
	char mode_l_[PADL_(int)]; int mode; char mode_r_[PADR_(int)];
};
struct ibcs2_getdents_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char buf_l_[PADL_(char *)]; char * buf; char buf_r_[PADR_(char *)];
	char nbytes_l_[PADL_(int)]; int nbytes; char nbytes_r_[PADR_(int)];
};
struct ibcs2_sysfs_args {
	char cmd_l_[PADL_(int)]; int cmd; char cmd_r_[PADR_(int)];
	char d1_l_[PADL_(caddr_t)]; caddr_t d1; char d1_r_[PADR_(caddr_t)];
	char buf_l_[PADL_(char *)]; char * buf; char buf_r_[PADR_(char *)];
};
struct ibcs2_getmsg_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char ctl_l_[PADL_(struct ibcs2_stropts *)]; struct ibcs2_stropts * ctl; char ctl_r_[PADR_(struct ibcs2_stropts *)];
	char dat_l_[PADL_(struct ibcs2_stropts *)]; struct ibcs2_stropts * dat; char dat_r_[PADR_(struct ibcs2_stropts *)];
	char flags_l_[PADL_(int *)]; int * flags; char flags_r_[PADR_(int *)];
};
struct ibcs2_putmsg_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char ctl_l_[PADL_(struct ibcs2_stropts *)]; struct ibcs2_stropts * ctl; char ctl_r_[PADR_(struct ibcs2_stropts *)];
	char dat_l_[PADL_(struct ibcs2_stropts *)]; struct ibcs2_stropts * dat; char dat_r_[PADR_(struct ibcs2_stropts *)];
	char flags_l_[PADL_(int)]; int flags; char flags_r_[PADR_(int)];
};
struct ibcs2_secure_args {
	char cmd_l_[PADL_(int)]; int cmd; char cmd_r_[PADR_(int)];
	char a1_l_[PADL_(int)]; int a1; char a1_r_[PADR_(int)];
	char a2_l_[PADL_(int)]; int a2; char a2_r_[PADR_(int)];
	char a3_l_[PADL_(int)]; int a3; char a3_r_[PADR_(int)];
	char a4_l_[PADL_(int)]; int a4; char a4_r_[PADR_(int)];
	char a5_l_[PADL_(int)]; int a5; char a5_r_[PADR_(int)];
};
struct ibcs2_symlink_args {
	char path_l_[PADL_(char *)]; char * path; char path_r_[PADR_(char *)];
	char link_l_[PADL_(char *)]; char * link; char link_r_[PADR_(char *)];
};
struct ibcs2_lstat_args {
	char path_l_[PADL_(char *)]; char * path; char path_r_[PADR_(char *)];
	char st_l_[PADL_(struct ibcs2_stat *)]; struct ibcs2_stat * st; char st_r_[PADR_(struct ibcs2_stat *)];
};
struct ibcs2_readlink_args {
	char path_l_[PADL_(char *)]; char * path; char path_r_[PADR_(char *)];
	char buf_l_[PADL_(char *)]; char * buf; char buf_r_[PADR_(char *)];
	char count_l_[PADL_(int)]; int count; char count_r_[PADR_(int)];
};
struct ibcs2_isc_args {
	register_t dummy;
};
int	ibcs2_read(struct thread *, struct ibcs2_read_args *);
int	ibcs2_open(struct thread *, struct ibcs2_open_args *);
int	ibcs2_wait(struct thread *, struct ibcs2_wait_args *);
int	ibcs2_creat(struct thread *, struct ibcs2_creat_args *);
int	ibcs2_unlink(struct thread *, struct ibcs2_unlink_args *);
int	ibcs2_execv(struct thread *, struct ibcs2_execv_args *);
int	ibcs2_chdir(struct thread *, struct ibcs2_chdir_args *);
int	ibcs2_time(struct thread *, struct ibcs2_time_args *);
int	ibcs2_mknod(struct thread *, struct ibcs2_mknod_args *);
int	ibcs2_chmod(struct thread *, struct ibcs2_chmod_args *);
int	ibcs2_chown(struct thread *, struct ibcs2_chown_args *);
int	ibcs2_stat(struct thread *, struct ibcs2_stat_args *);
int	ibcs2_lseek(struct thread *, struct ibcs2_lseek_args *);
int	ibcs2_mount(struct thread *, struct ibcs2_mount_args *);
int	ibcs2_umount(struct thread *, struct ibcs2_umount_args *);
int	ibcs2_setuid(struct thread *, struct ibcs2_setuid_args *);
int	ibcs2_stime(struct thread *, struct ibcs2_stime_args *);
int	ibcs2_alarm(struct thread *, struct ibcs2_alarm_args *);
int	ibcs2_fstat(struct thread *, struct ibcs2_fstat_args *);
int	ibcs2_pause(struct thread *, struct ibcs2_pause_args *);
int	ibcs2_utime(struct thread *, struct ibcs2_utime_args *);
int	ibcs2_stty(struct thread *, struct ibcs2_stty_args *);
int	ibcs2_gtty(struct thread *, struct ibcs2_gtty_args *);
int	ibcs2_access(struct thread *, struct ibcs2_access_args *);
int	ibcs2_nice(struct thread *, struct ibcs2_nice_args *);
int	ibcs2_statfs(struct thread *, struct ibcs2_statfs_args *);
int	ibcs2_kill(struct thread *, struct ibcs2_kill_args *);
int	ibcs2_fstatfs(struct thread *, struct ibcs2_fstatfs_args *);
int	ibcs2_pgrpsys(struct thread *, struct ibcs2_pgrpsys_args *);
int	ibcs2_xenix(struct thread *, struct ibcs2_xenix_args *);
int	ibcs2_times(struct thread *, struct ibcs2_times_args *);
int	ibcs2_plock(struct thread *, struct ibcs2_plock_args *);
int	ibcs2_setgid(struct thread *, struct ibcs2_setgid_args *);
int	ibcs2_sigsys(struct thread *, struct ibcs2_sigsys_args *);
int	ibcs2_msgsys(struct thread *, struct ibcs2_msgsys_args *);
int	ibcs2_sysi86(struct thread *, struct ibcs2_sysi86_args *);
int	ibcs2_shmsys(struct thread *, struct ibcs2_shmsys_args *);
int	ibcs2_semsys(struct thread *, struct ibcs2_semsys_args *);
int	ibcs2_ioctl(struct thread *, struct ibcs2_ioctl_args *);
int	ibcs2_uadmin(struct thread *, struct ibcs2_uadmin_args *);
int	ibcs2_utssys(struct thread *, struct ibcs2_utssys_args *);
int	ibcs2_execve(struct thread *, struct ibcs2_execve_args *);
int	ibcs2_fcntl(struct thread *, struct ibcs2_fcntl_args *);
int	ibcs2_ulimit(struct thread *, struct ibcs2_ulimit_args *);
int	ibcs2_rmdir(struct thread *, struct ibcs2_rmdir_args *);
int	ibcs2_mkdir(struct thread *, struct ibcs2_mkdir_args *);
int	ibcs2_getdents(struct thread *, struct ibcs2_getdents_args *);
int	ibcs2_sysfs(struct thread *, struct ibcs2_sysfs_args *);
int	ibcs2_getmsg(struct thread *, struct ibcs2_getmsg_args *);
int	ibcs2_putmsg(struct thread *, struct ibcs2_putmsg_args *);
int	ibcs2_secure(struct thread *, struct ibcs2_secure_args *);
int	ibcs2_symlink(struct thread *, struct ibcs2_symlink_args *);
int	ibcs2_lstat(struct thread *, struct ibcs2_lstat_args *);
int	ibcs2_readlink(struct thread *, struct ibcs2_readlink_args *);
int	ibcs2_isc(struct thread *, struct ibcs2_isc_args *);

#ifdef COMPAT_43


#endif /* COMPAT_43 */


#ifdef COMPAT_FREEBSD4


#endif /* COMPAT_FREEBSD4 */

#undef PAD_
#undef PADL_
#undef PADR_

#endif /* !_IBCS2_SYSPROTO_H_ */
