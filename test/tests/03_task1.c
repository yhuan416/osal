#include "common.h"

/* run at the start of each suite */
CU_SUITE_SETUP() {
    return CUE_SUCCESS;
}

/* run at the end of the suite */
CU_SUITE_TEARDOWN() {
    return CUE_SUCCESS;
}

/* run at the start of each test */
CU_TEST_SETUP() {

}

/* run at the end of each test */
CU_TEST_TEARDOWN() {

}

int i = 0;

void *taskEntry(void *arg)
{
    i++;

    return NULL;
}

static void task1(void)
{
    osal_task_attr_t attr = { 0 };

    CU_ASSERT_EQUAL(i, 0);

    osal_task_t task = osal_task_create(taskEntry, NULL, &attr);
    CU_ASSERT_PTR_NOT_NULL(task);

    osal_task_delay(1);

    CU_ASSERT_EQUAL(i, 1);
}

CUNIT_CI_RUN(CU_MAIN_EXE_NAME,
             CUNIT_CI_TEST(task1)
);
