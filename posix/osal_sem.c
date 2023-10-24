#include "osal.h"

#include <semaphore.h>

osal_sem_t osal_sem_create(uint32_t count, uint32_t init)
{
    int ret;
    sem_t *sem = (sem_t *)osal_malloc(sizeof(sem_t));
    if (sem == NULL) { return NULL; }

    ret = sem_init(sem, 0, init);
    if (ret != 0) {
        osal_free(sem);
        return NULL;
    }

    return (osal_sem_t)sem;
}

void osal_sem_destroy(osal_sem_t sem)
{
    if (sem == NULL) { return; }

    sem_destroy((sem_t *)sem);
    osal_free(sem);
}

int32_t osal_sem_give(osal_sem_t sem, uint32_t timeout)
{
    int ret;

    if (sem == NULL) { return OSAL_NULL_PTR; }

    ret = sem_post((sem_t *)sem);
    if (ret != 0) {
        return OSAL_ERROR;
    }

    return OSAL_OK;
}

int32_t osal_sem_take(osal_sem_t sem, uint32_t timeout)
{
    int ret;

    if (sem == NULL) { return OSAL_NULL_PTR; }

    ret = sem_wait((sem_t *)sem);
    if (ret != 0) {
        return OSAL_ERROR;
    }

    return OSAL_OK;
}
