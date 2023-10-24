#include "osal.h"

#include <sys/sysinfo.h>

uint64_t osal_uptime(void)
{
    struct sysinfo info;
    sysinfo(&info);
    return info.uptime;
}
