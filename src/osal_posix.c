#include "osal.h"

#include <unistd.h>
#include <pthread.h>

struct osal_task
{
    pthread_t tid;
};

osal_task_t osal_posix_task_create(const char *name,
                                   osal_task_func_t func,
                                   void *arg,
                                   void *stack_start,
                                   int stack_size,
                                   int priority)
{
    // pthread_t tid;
    // pthread_attr_t attr = {0};

    // pthread_attr_init(&attr);

    // pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // if (stack_size && pthread_attr_setstacksize(&attr, stack_size))
    // {

    // }
}

osal_api_t osal_api = {
    .task_create = osal_posix_task_create,
};
