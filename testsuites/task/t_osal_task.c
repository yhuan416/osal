#include "t_osal_task.h"

static int suite_init(void) { return 0; }
static int suite_clean(void) { return 0; }

void TaskAddTests(void)
{
    CU_CI_DEFINE_SUITE("TASK", suite_init, suite_clean, NULL, NULL);

    t_osal_task_001();
    t_osal_task_002();
    t_osal_task_003();
}
