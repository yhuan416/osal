#include "t_osal_mem.h"

int suite_init(void) { return 0; }
int suite_clean(void) { return 0; }

static CU_TestInfo tests[] = {
    {"malloc_01", malloc_01},
    CU_TEST_INFO_NULL,
};

static CU_SuiteInfo suites[] = {
    {"mem", suite_init, suite_clean, NULL, NULL, tests},
    CU_SUITE_INFO_NULL,
};

void MemAddTests(void)
{
    assert(NULL != CU_get_registry());
    assert(!CU_is_test_running());

    /* Register suites. */
    if (CU_register_suites(suites) != CUE_SUCCESS)
    {
        fprintf(stderr, "suite registration failed - %s\n",
                CU_get_error_msg());
        exit(EXIT_FAILURE);
    }
}
