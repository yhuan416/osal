#include "common.h"

void MemAddTests(void);

void AddTests(void)
{
    MemAddTests();
}

void *osal_test_entry(void *arg)
{
    if (CU_initialize_registry())
    {
        printf("\nInitialization of Test Registry failed.");
    }
    else
    {
        AddTests();
        CU_basic_set_mode(CU_BRM_VERBOSE);
        CU_set_error_action(CUEA_FAIL);
        printf("\nTests completed with return value %d.\n", CU_basic_run_tests());
        CU_cleanup_registry();
    }
    return 0;
}

#if defined(__linux__)
int main(int argc, char const *argv[])
{
    osal_test_entry(NULL);
    return 0;
}
#endif
