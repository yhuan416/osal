#include "osal.h"

void *osal_malloc(size_t size)
{
    return malloc(size);
}

void *osal_calloc(size_t num, size_t size)
{
    return calloc(num, size);
}

void *osal_realloc(void *ptr, size_t size)
{
    return realloc(ptr, size);
}

void osal_free(void *ptr)
{
    free(ptr);
}
