#include "osal.h"

void *osal_malloc(size_t size)
{
    if (size == 0) {
        return NULL;
    }

    return malloc(size);
}

void *osal_calloc(size_t num, size_t size)
{
    if (size == 0 || num == 0) {
        return NULL;
    }

    return calloc(num, size);
}

void osal_free(void *ptr)
{
    if (ptr == NULL) {
        return;
    }

    free(ptr);
}

void *osal_realloc(void *ptr, size_t size)
{
    if (ptr == NULL) {
        return osal_malloc(size);
    }

    if (size == 0) {
        osal_free(ptr);
        return NULL;
    }

    return realloc(ptr, size);
}
