#include "t_osal_mem.h"

void malloc_01(void)
{
    void *buff = osal_malloc(1024);
    CU_ASSERT_PTR_NOT_NULL(buff);
    osal_free(buff);
}
