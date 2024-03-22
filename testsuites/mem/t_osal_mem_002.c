#include "t_osal_mem.h"

static void calloc_01(void)
{
    void *buff = osal_calloc(1024, 1);
    CU_ASSERT_PTR_NOT_NULL(buff);
    osal_free(buff);
}

static void calloc_02(void)
{
    void *buff = osal_calloc(0, 1);
    CU_ASSERT_PTR_NULL(buff);
    osal_free(buff);
}

void t_osal_mem_002(void)
{
    CUNIT_CI_TEST(calloc_01);
    CUNIT_CI_TEST(calloc_02);
}
