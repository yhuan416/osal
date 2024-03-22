#include "t_osal_mem.h"

static int suite_init(void) { return 0; }
static int suite_clean(void) { return 0; }

void MemAddTests(void)
{
    CU_CI_DEFINE_SUITE("MEM", suite_init, suite_clean, NULL, NULL);

    t_osal_mem_001();
    t_osal_mem_002();
    t_osal_mem_003();
}
