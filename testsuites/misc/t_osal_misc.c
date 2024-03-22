#include "t_osal_misc.h"

static int suite_init(void) { return 0; }
static int suite_clean(void) { return 0; }

void MiscAddTests(void)
{
    CU_CI_DEFINE_SUITE("MISC", suite_init, suite_clean, NULL, NULL);

    t_osal_misc_001();
    t_osal_misc_002();
}
