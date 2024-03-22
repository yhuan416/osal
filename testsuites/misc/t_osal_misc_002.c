#include "t_osal_misc.h"

static void get_version(void)
{
    const char *version = osal_get_version();
    CU_ASSERT_PTR_NOT_NULL(version);
    CU_PASS(version);
}

void t_osal_misc_002(void)
{
    CUNIT_CI_TEST(get_version);
}
