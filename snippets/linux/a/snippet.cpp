#include <stdint.h>
#include <stddef.h>
#include <errno.h>

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)
#define u64 uint64_t

// https://github.com/torvalds/linux/blob/3d7cb6b0/arch/sparc/include/asm/vvar.h#L14

struct vvar_data {
	unsigned int seq;

	int vclock_mode;
	struct { /* extract of a clocksource struct */
		u64	cycle_last;
		u64	mask;
		int	mult;
		int	shift;
	} clock;
	/* open coded 'struct timespec' */
	u64		wall_time_sec;
	u64		wall_time_snsec;
	u64		monotonic_time_snsec;
	u64		monotonic_time_sec;
	u64		monotonic_time_coarse_sec;
	u64		monotonic_time_coarse_nsec;
	u64		wall_time_coarse_sec;
	u64		wall_time_coarse_nsec;

	int		tz_minuteswest;
	int		tz_dsttime;
};

extern struct vvar_data *vvar_data;


// https://github.com/torvalds/linux/blob/3d7cb6b0/include/uapi/linux/time.h#L33

struct timezone {
	int	tz_minuteswest;	/* minutes west of Greenwich */
	int	tz_dsttime;	/* type of dst correction */
};

extern struct timezone sys_tz;


// Modified from
// https://github.com/torvalds/linux/blob/3d7cb6b0/arch/sparc/kernel/vdso.c#L17

int update_vsyscall_tz(void)
{
	if (vvar_data == NULL)
		return -ENOMEM;

	vvar_data->tz_minuteswest = sys_tz.tz_minuteswest;
	vvar_data->tz_dsttime = sys_tz.tz_dsttime;
    return 0;
}
