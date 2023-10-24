#include "osal.h"

#include <pthread.h>

void *osal_task_create(TaskFunc func, void *arg, TaskAttr *attr)
{
    pthread_t thread;
    int32_t ret = pthread_create(&thread, NULL, func, arg);
    if (ret != 0)
        return NULL;

    return (void *)thread;
}

void osal_task_join(void *task)
{
    pthread_join((pthread_t)task, NULL);
}

int32_t osal_task_self(void)
{
    return (int32_t)pthread_self();
}
