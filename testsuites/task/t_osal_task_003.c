#include "t_osal_task.h"

#include <unistd.h>

static int i = 0;

static void *taskEntry(void *arg)
{
    CU_ASSERT_EQUAL(i, 0);
    i++;
    return NULL;
}

static void task_03(void)
{
    CU_ASSERT_EQUAL(i, 0);

    osal_task_t task1 = osal_task_create(
        NULL,
        (osal_task_func_t)taskEntry,
        NULL,
        NULL,
        0,
        0);
    CU_ASSERT_PTR_NOT_NULL(task1);// name可以为空, 返回task句柄

    sleep(1);
    CU_ASSERT_EQUAL(i, 1);// task执行, i加1
}

void t_osal_task_003(void)
{
    CUNIT_CI_TEST(task_03);
}
