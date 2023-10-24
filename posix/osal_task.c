#include "osal.h"

#include <unistd.h>
#include <pthread.h>

osal_task_t osal_task_create(osal_task_func_t func, void *arg, osal_task_attr_t *attr)
{
    pthread_t thread;
    int32_t ret = pthread_create(&thread, NULL, func, arg);
    if (ret != 0) { return NULL; }

    return (osal_task_t)thread;
}

void osal_task_join(osal_task_t task)
{
    pthread_join((pthread_t)task, NULL);
}

int32_t osal_task_self(void)
{
    return (int32_t)pthread_self();
}

void osal_task_delay_ms(uint32_t ms)
{
    usleep(ms * 1000);
}

void osal_task_delay(uint32_t s)
{
    sleep(s);
}
