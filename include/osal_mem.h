#ifndef _OSAL_MEM_H_
#define _OSAL_MEM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void *osal_malloc(size_t size);

void *osal_calloc(size_t num, size_t size);

void *osal_realloc(void *ptr, size_t size);

void osal_free(void *ptr);

#endif // !_OSAL_MEM_H_
