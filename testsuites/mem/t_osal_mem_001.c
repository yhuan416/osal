#include "t_osal_mem.h"

static void malloc_01(void)
{
    void *buff = osal_malloc(1024);
    CU_ASSERT_PTR_NOT_NULL(buff);
    osal_free(buff);
}

void t_osal_mem_001(void)
{
    CU_add_test(mem_suite, "malloc_01", malloc_01);
}
