#ifndef _OSAL_H_
#define _OSAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// task
#include "osal_task.h"

// mem
#include "osal_mem.h"

// mutex
#include "osal_mutex.h"

// sem

// mq(msg queue)

// timer

// uptime
uint64_t osal_uptime(void);

// reboot

// get_version
const char *osal_get_version(void);

#endif // !_OSAL_H_
