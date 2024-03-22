#include "t_osal_sem.h"

static void sem_02(void)
{
    osal_sem_t sem1;
    osal_sem_t sem2;

    // 创建sem1
    sem1 = osal_sem_create(0);
    CU_ASSERT_PTR_NOT_NULL(sem1);

    // 尝试获取
    CU_ASSERT_NOT_EQUAL(osal_sem_wait(sem1, 0), OSAL_API_OK);

    // 销毁
    CU_ASSERT_EQUAL(osal_sem_destory(sem1), OSAL_API_OK);

    // 创建sem2
    sem2 = osal_sem_create(1);
    CU_ASSERT_PTR_NOT_NULL(sem2);

    // 获取
    CU_ASSERT_EQUAL(osal_sem_wait(sem1, 0), OSAL_API_OK);

    // 销毁
    CU_ASSERT_EQUAL(osal_sem_destory(sem2), OSAL_API_OK);
}

void t_osal_sem_002(void)
{
    CU_add_test(sem_suite, "sem_02", sem_02);
}
