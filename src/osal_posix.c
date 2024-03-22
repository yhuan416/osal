#if defined(__linux__)

#include "osal_api.h"
#include "osal_posix.h"

void *osal_posix_malloc(size_t size)
{
    if (size == 0)
    {
        return NULL;
    }

    return malloc(size);
}

void *osal_posix_calloc(size_t num, size_t size)
{
    if (size == 0 || num == 0)
    {
        return NULL;
    }

    return calloc(num, size);
}

void *osal_posix_realloc(void *ptr, size_t size)
{
    if (ptr == NULL)
    {
        return osal_malloc(size);
    }

    if (size == 0)
    {
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
    if (mutex == NULL)
    {
        return OSAL_API_INVALID;
    }

    pthread_mutex_destroy((pthread_mutex_t *)mutex);
    osal_free(mutex);
    return OSAL_API_OK;
}

int osal_posix_mutex_lock(osal_mutex_t mutex)
{
    if (mutex == NULL)
    {
        return OSAL_API_INVALID;
    }
    return pthread_mutex_lock((pthread_mutex_t *)mutex);
}

int osal_posix_mutex_trylock(osal_mutex_t mutex)
{
    if (mutex == NULL)
    {
        return OSAL_API_INVALID;
    }
    return pthread_mutex_trylock((pthread_mutex_t *)mutex);
}

int osal_posix_mutex_unlock(osal_mutex_t mutex)
{
    if (mutex == NULL)
    {
        return OSAL_API_INVALID;
    }
    return pthread_mutex_unlock((pthread_mutex_t *)mutex);
}

#include <semaphore.h>

osal_sem_t osal_posix_sem_create(int count, uint32_t init)
{
    int ret;
    sem_t *sem = (sem_t *)osal_malloc(sizeof(sem_t));
    if (sem == NULL)
    {
        return NULL;
    }

    ret = sem_init(sem, 0, init);
    if (ret != 0)
    {
        osal_free(sem);
        return NULL;
    }

    return (osal_sem_t)sem;
}

int osal_posix_sem_destory(osal_sem_t sem)
{
    if (sem == NULL)
    {
        return OSAL_API_INVALID;
    }

    sem_destroy((sem_t *)sem);
    osal_free(sem);
    return OSAL_API_OK;
}

int osal_posix_sem_wait(osal_sem_t sem, uint32_t timeout)
{
    int ret;

    if (sem == NULL)
    {
        return OSAL_API_INVALID;
    }

    if (timeout == 0) {
        ret = sem_trywait((sem_t *)sem);
    } else if (timeout == OSAL_API_WAITFOREVER) {
        ret = sem_wait((sem_t *)sem);
    } else {
        // TODO: implement timeout
    }

    if (ret != 0)
    {
        return OSAL_API_FAIL;
    }

    return OSAL_API_OK;
}

int osal_posix_sem_post(osal_sem_t sem)
{
    int ret;

    if (sem == NULL)
    {
        return OSAL_API_INVALID;
    }

    ret = sem_post((sem_t *)sem);
    if (ret != 0)
    {
        return OSAL_API_FAIL;
    }

    return OSAL_API_OK;
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
    .mutex_trylock = osal_posix_mutex_trylock,
    .mutex_unlock = osal_posix_mutex_unlock,

    .sem_create = osal_posix_sem_create,
    .sem_destory = osal_posix_sem_destory,
    .sem_wait = osal_posix_sem_wait,
    .sem_post = osal_posix_sem_post,

    .uptime = osal_posix_uptime,
};

#endif
