#ifndef _OSAL_POSIX_H_
#define _OSAL_POSIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifndef osal_malloc
#define osal_malloc malloc
#define osal_free free
#define osal_calloc calloc
#define osal_realloc realloc
#endif // !osal_malloc

#ifndef osal_get_version
#define osal_get_version() "1.0.0"
#endif // !osal_get_version

#endif
