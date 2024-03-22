#if defined(__linux__)

#include "osal.h"
#include "osal_posix.h"

#include <pthread.h>

void *osal_posix_malloc(size_t size)
{
    if (size == 0) {
        return NULL;
    }

    return malloc(size);
}

void *osal_posix_calloc(size_t num, size_t size)
{
    if (size == 0 || num == 0) {
        return NULL;
    }

    return calloc(num, size);
}

void *osal_posix_realloc(void *ptr, size_t size)
{
    if (ptr == NULL) {
        return osal_malloc(size);
    }

    if (size == 0) {
        osal_free(ptr);
        return NULL;
    }

    return realloc(ptr, size);
}

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

osal_mutex_t osal_posix_mutex_create(void)
{
    pthread_mutex_t *mutex = osal_malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mutex, NULL);
    return (osal_mutex_t)mutex;
}

int osal_posix_mutex_destory(osal_mutex_t mutex)
{
    pthread_mutex_destroy((pthread_mutex_t *)mutex);
    osal_free(mutex);
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
    .malloc = osal_posix_malloc,
    .calloc = osal_posix_calloc,
    .realloc = osal_posix_realloc,

    .task_create = osal_posix_task_create,

    .mutex_create = osal_posix_mutex_create,
    .mutex_destory = osal_posix_mutex_destory,
    .mutex_lock = osal_posix_mutex_lock,
    .mutex_unlock = osal_posix_mutex_unlock,

    .uptime = osal_posix_uptime,
};

#endif
