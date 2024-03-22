#if defined(__linux__)

#include "osal_api.h"
#include "osal_posix.h"

#define mmodule_name "osal"

#if !defined(pr_fatal)

#if !defined(print_level)
#define print_level 2
#endif

#define pr_fatal(fmt, ...)          \
    if (print_level >= 1)           \
    {                               \
        printf(fmt, ##__VA_ARGS__); \
    }
#define pr_error(fmt, ...)          \
    if (print_level >= 2)           \
    {                               \
        printf(fmt, ##__VA_ARGS__); \
    }
#define pr_warn(fmt, ...)           \
    if (print_level >= 3)           \
    {                               \
        printf(fmt, ##__VA_ARGS__); \
    }
#define pr_info(fmt, ...)           \
    if (print_level >= 4)           \
    {                               \
        printf(fmt, ##__VA_ARGS__); \
    }
#define pr_debug(fmt, ...)          \
    if (print_level >= 5)           \
    {                               \
        printf(fmt, ##__VA_ARGS__); \
    }
#define pr_trace(fmt, ...)          \
    if (print_level >= 6)           \
    {                               \
        printf(fmt, ##__VA_ARGS__); \
    }
#endif

void *osal_posix_malloc(size_t size)
{
    if (size == 0)
    {
        pr_warn("size is 0.\n");
        return NULL;
    }

    return malloc(size);
}

void *osal_posix_calloc(size_t num, size_t size)
{
    if (size == 0 || num == 0)
    {
        pr_warn("size or num is 0.\n");
        return NULL;
    }

    return calloc(num, size);
}

void *osal_posix_realloc(void *ptr, size_t size)
{
    if (ptr == NULL)
    {
        pr_warn("ptr is NULL.\n");
        return osal_malloc(size);
    }

    if (size == 0)
    {
        pr_warn("size is 0.\n");
        osal_free(ptr);
        return NULL;
    }

    return realloc(ptr, size);
}

#define DEFAULT_STACK_NAME "osal_task"

osal_task_t osal_posix_task_create(const char *name,
                                   osal_task_func_t func,
                                   void *arg,
                                   void *stack_start,
                                   int stack_size,
                                   int priority)
{
    int ret;
    pthread_t tid;
    pthread_attr_t attr = {0};

    // posix平台不关注这两个参数
    (void)stack_start;
    (void)stack_size;
    (void)priority;

    if (func == NULL)
    {
        pr_error("func is NULL.\n");
        return NULL;
    }

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if ((ret = pthread_create(&tid, &attr, func, arg)))
    {
        pr_error("pthread_create failed, ret = %d.\n", ret);
        pthread_attr_destroy(&attr);
        return NULL;
    }

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
        pr_error("mutex is NULL.\n");
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
        pr_error("mutex is NULL.\n");
        return OSAL_API_INVALID;
    }
    return pthread_mutex_lock((pthread_mutex_t *)mutex);
}

int osal_posix_mutex_trylock(osal_mutex_t mutex)
{
    if (mutex == NULL)
    {
        pr_error("mutex is NULL.\n");
        return OSAL_API_INVALID;
    }
    return pthread_mutex_trylock((pthread_mutex_t *)mutex);
}

int osal_posix_mutex_unlock(osal_mutex_t mutex)
{
    if (mutex == NULL)
    {
        pr_error("mutex is NULL.\n");
        return OSAL_API_INVALID;
    }
    return pthread_mutex_unlock((pthread_mutex_t *)mutex);
}

#include <semaphore.h>

osal_sem_t osal_posix_sem_create(uint32_t init)
{
    sem_t *sem = (sem_t *)osal_calloc(1, sizeof(sem_t));
    if (sem == NULL)
    {
        pr_error("sem malloc failed.\n");
        return NULL;
    }
    sem_init(sem, 0, init);
    return (osal_sem_t)sem;
}

int osal_posix_sem_destory(osal_sem_t sem)
{
    if (sem == NULL)
    {
        pr_error("sem is NULL.\n");
        return OSAL_API_INVALID;
    }

    sem_destroy((sem_t *)sem);
    osal_free(sem);
    return OSAL_API_OK;
}

int osal_posix_sem_wait(osal_sem_t sem, uint32_t timeout)
{
    struct timespec tm = {0};

    if (sem == NULL)
    {
        pr_error("sem is NULL.\n");
        return OSAL_API_INVALID;
    }

    if (timeout == 0)
    {
        return sem_trywait((sem_t *)sem);
    }
    else if (timeout == OSAL_API_WAITFOREVER)
    {
        return sem_wait((sem_t *)sem);
    }
    else
    {
        // TODO: implement timeout
        osal_calc_timedwait(&tm, timeout);
        return sem_timedwait((sem_t *)sem, &tm);
    }

    return OSAL_API_OK;
}

int osal_posix_sem_post(osal_sem_t sem)
{
    if (sem == NULL)
    {
        pr_error("sem is NULL.\n");
        return OSAL_API_INVALID;
    }

    return sem_post((sem_t *)sem);
}

int osal_posix_calc_timedwait(struct timespec *tm, uint32_t s)
{
    struct timeval tv;

    if (tm == NULL)
    {
        pr_error("tm is NULL.\n");
        return OSAL_API_INVALID;
    }

    gettimeofday(&tv, NULL);
    tv.tv_sec += s / 1000;
    tv.tv_usec += (s % 1000) * 1000;
    if (tv.tv_usec >= 1000000)
    {
        tv.tv_usec -= 1000000;
        tv.tv_sec++;
    }
    tm->tv_sec = tv.tv_sec;
    tm->tv_nsec = tv.tv_usec * 1000;

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
