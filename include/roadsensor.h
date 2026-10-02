#ifndef ROADSENSOR_H
#define ROADSENSOR_H
#include <linux/types.h>
#include <linux/ioctl.h>

/* One reading from the simulated vehicle sensor (24 bytes) */
struct rs_sample {
    __u64 ts_ms;       /* wall-clock time, ms */
    __s32 lat_e6;      /* latitude  * 1e6 */
    __s32 lon_e6;      /* longitude * 1e6 */
    __s32 accel_z_mg;  /* vertical acceleration in milli-g (~1000 = flat road) */
    __u32 pad;
};

#define RS_IOC_MAGIC        'R'
#define RS_IOC_SET_SPIKE_PCT _IOW(RS_IOC_MAGIC, 1, __u32) /* % of samples that are bumps */
#define RS_IOC_GET_COUNT     _IOR(RS_IOC_MAGIC, 2, __u64) /* samples served so far */
#define RS_IOC_RESET         _IO(RS_IOC_MAGIC, 3)         /* restart route + counters */

#define RS_DEVICE_PATH "/dev/roadsensor"
#endif
