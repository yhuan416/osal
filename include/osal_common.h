#ifndef _OSAL_COMMON_H_
#define _OSAL_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

enum {
    OSAL_OK = 0,
    OSAL_ERROR = -1,
    OSAL_TIMEOUT = -2,
    OSAL_NULL_PTR = -3,
    OSAL_MALLOC_FAILED = -4,
};

#define OSAL_NO_WAIT        ((uint32_t)0)
#define OSAL_WAIT_FOREVER   ((uint32_t)-1)

#endif // !_OSAL_COMMON_H_
