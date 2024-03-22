#include "t_osal_task.h"

static int i = 0;

static void *taskEntry(void *arg)
{
    CU_ASSERT_EQUAL(i, 0);
    i++;
    return NULL;
}

static void task_02(void)
{
    CU_ASSERT_EQUAL(i, 0);

    osal_task_t task1 = osal_task_create(
        "task1",
        (osal_task_func_t)NULL,
        NULL,
        NULL,
        0,
        0);
    CU_ASSERT_PTR_NULL(task1);// 入参为空, 返回NULL

    osal_task_sleep(1);
    CU_ASSERT_EQUAL(i, 0);// task不执行, i不变
}

void t_osal_task_002(void)
{
    CU_add_test(task_suite, "task_02", task_02);
}
