#include "osal.h"

#include <unistd.h>
#include <pthread.h>

osal_task_t osal_posix_task_create(const char *name,
                                   osal_task_func_t func,
                                   void *arg,
                                   void *stack_start,
                                   int stack_size,
                                   int priority)
{
    pthread_t tid;
    pthread_attr_t attr = {0};

    pthread_attr_init(&attr);

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if (stack_size && pthread_attr_setstacksize(&attr, stack_size))
    {

    }

    pthread_create(&tid, &attr, func, arg);

    pthread_attr_destroy(&attr);

    return (osal_task_t)tid;
}

int osal_posix_task_destory(osal_task_t task)
{
    pthread_cancel((pthread_t)task);
}

osal_task_t osal_posix_task_self(void)
{
    return (osal_task_t)pthread_self();
}

int osal_posix_task_yield(void)
{
    return 0;
}

int osal_posix_task_sleep(uint32_t s)
{
    return sleep(s);
}

int osal_posix_task_usleep(uint32_t us)
{
    return usleep(us);
}

int osal_posix_task_suspend(osal_task_t task)
{
    return 0;
}

int osal_posix_task_resume(osal_task_t task)
{
    return 0;
}

int osal_posix_task_get_priority(osal_task_t task, int *priority)
{
    return 0;
}

int osal_posix_task_set_priority(osal_task_t task, int priority)
{
    return 0;
}

osal_mutex_t osal_posix_mutex_create(void)
{
    pthread_mutex_t *mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mutex, NULL);
    return (osal_mutex_t)mutex;
}

int osal_posix_mutex_destory(osal_mutex_t mutex)
{
    pthread_mutex_destroy((pthread_mutex_t *)mutex);
    free(mutex);
    return 0;
}

int osal_posix_mutex_lock(osal_mutex_t mutex, uint32_t timeout)
{
    return pthread_mutex_lock((pthread_mutex_t *)mutex);
}

int osal_posix_mutex_unlock(osal_mutex_t mutex, uint32_t timeout)
{
    return pthread_mutex_unlock((pthread_mutex_t *)mutex);
}

#include <sys/sysinfo.h>

uint64_t osal_posix_uptime(void)
{
    struct sysinfo info;
    sysinfo(&info);
    return info.uptime;
}

osal_api_t osal_api = {
    .task_create = osal_posix_task_create,
    .task_destory = osal_posix_task_destory,
    .task_self = osal_posix_task_self,
    .task_yield = osal_posix_task_yield,
    .task_sleep = osal_posix_task_sleep,
    .task_usleep = osal_posix_task_usleep,
    .task_suspend = osal_posix_task_suspend,
    .task_resume = osal_posix_task_resume,
    .task_get_priority = osal_posix_task_get_priority,
    .task_set_priority = osal_posix_task_set_priority,

    .mutex_create = osal_posix_mutex_create,
    .mutex_destory = osal_posix_mutex_destory,
    .mutex_lock = osal_posix_mutex_lock,
    .mutex_unlock = osal_posix_mutex_unlock,

    .uptime = osal_posix_uptime,
};
