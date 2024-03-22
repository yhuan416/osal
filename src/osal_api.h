#ifndef _OSAL_API_H_
#define _OSAL_API_H_

#if defined(__linux__)
#include "osal_posix.h"
#endif

enum OSAL_API_RET
{
    OSAL_API_OK = 0,
    OSAL_API_FAIL = -1,
    OSAL_API_TIMEOUT = -2,
    OSAL_API_INVALID = -3,
    OSAL_API_MEM_ALLOC_FAIL = -4,
};

#define OSAL_API_WAITFOREVER (-1)

//////////////////////////////////////////////// mem

/**
 * @name osal_malloc
 * 
 * @brief same as malloc
 *
 */
typedef void *(*osal_api_malloc)(size_t size);

/**
 * @name osal_free
 * 
 * @brief same as free
 *
 */
typedef void (*osal_api_free)(void *ptr);

/**
 * @name osal_calloc
 * 
 * @brief same as calloc
 *
 */
typedef void *(*osal_api_calloc)(size_t num, size_t size);

/**
 * @name osal_realloc
 * 
 * @brief same as realloc
 *
 */
typedef void *(*osal_api_realloc)(void *ptr, size_t size);

//////////////////////////////////////////////// task
typedef void *osal_task_t;
typedef void *(*osal_task_func_t)(void *arg);

/**
 * @name osal_task_create
 * 
 * @brief create a task
 *
 * @param name task name, can be NULL
 * @param func task entry, see @osal_task_func_t
 * @param arg task arg
 * @param stack_start stack base address, refer for RTOS
 * @param stack_size stack size
 * @param priority task priority, for RTOS
 *
 * @return
 *      task handle
 *      NULL, create failed.
 *
 */
typedef osal_task_t (*osal_api_task_create)(const char *name,
                                            osal_task_func_t func,
                                            void *arg,
                                            void *stack_start,
                                            int stack_size,
                                            int priority);

/**
 * @name osal_task_destory
 * 
 * @brief destory a task
 *
 * @param task task handle
 *
 * @return
 *      see @OSAL_API_RET
 *
 */
typedef int (*osal_api_task_destory)(osal_task_t task);

/**
 * @name osal_task_self
 * 
 * @brief get current task handle
 *
 * @return
 *      task handle
 *
 */
typedef osal_task_t (*osal_api_task_self)(void);

/**
 * @name osal_task_yield
 * 
 * @brief yield, for RTOS
 * 
 * @return
 *      see @OSAL_API_RET
 * 
 */
typedef int (*osal_api_task_yield)(void);

/**
 * @name osal_task_sleep
 * 
 * @brief task sleep second
 * 
 * @param s sleep time(s)
 * 
 * @return
 *      see @OSAL_API_RET
 * 
 */
typedef int (*osal_api_task_sleep)(uint32_t s);

/**
 * @name osal_task_usleep
 * 
 * @brief task sleep us
 * 
 * @param s sleep time(us)
 * 
 * @return
 *      see @OSAL_API_RET
 * 
 */
typedef int (*osal_api_task_usleep)(uint32_t us);

/**
 * @name osal_task_suspend
 * 
 * @brief task suspend, for RTOS
 * 
 * @param task task handle
 * 
 * @return
 *      see @OSAL_API_RET
 * 
 */
typedef int (*osal_api_task_suspend)(osal_task_t task);

/**
 * @name osal_task_resume
 * 
 * @brief task resume, for RTOS
 * 
 * @param task task handle
 * 
 * @return
 *      see @OSAL_API_RET
 * 
 */
typedef int (*osal_api_task_resume)(osal_task_t task);

/**
 * @name osal_task_get_priority
 * 
 * @brief get task priority, for RTOS
 * 
 * @param task task handle
 * @param priority [out] task priority
 * 
 * @return
 *      see @OSAL_API_RET
 * 
 */
typedef int (*osal_api_task_get_priority)(osal_task_t task, int *priority);

/**
 * @name osal_task_set_priority
 * 
 * @brief set task priority, for RTOS
 * 
 * @param task task handle
 * @param priority task priority
 * 
 * @return
 *      see @OSAL_API_RET
 * 
 */
typedef int (*osal_api_task_set_priority)(osal_task_t task, int priority);

//////////////////////////////////////////////// mutex
typedef void *osal_mutex_t;

typedef osal_mutex_t (*osal_api_mutex_create)(void);

typedef int (*osal_api_mutex_destory)(osal_mutex_t mutex);

typedef int (*osal_api_mutex_lock)(osal_mutex_t mutex);

typedef int (*osal_api_mutex_trylock)(osal_mutex_t mutex);

typedef int (*osal_api_mutex_unlock)(osal_mutex_t mutex);

//////////////////////////////////////////////// sem
typedef void *osal_sem_t;

typedef osal_sem_t (*osal_api_sem_create)(uint32_t init);

typedef int (*osal_api_sem_destory)(osal_sem_t sem);

typedef int (*osal_api_sem_wait)(osal_sem_t sem, uint32_t timeout);

typedef int (*osal_api_sem_post)(osal_sem_t sem);

////////////////////////////////////////////////// shm

//////////////////////////////////////////////// event

//////////////////////////////////////////////// mq

//////////////////////////////////////////////// timer

//////////////////////////////////////////////// time
typedef int (*osal_api_calc_timedwait)(struct timespec *tm, uint32_t s);

//////////////////////////////////////////////// signal

//////////////////////////////////////////////// file

//////////////////////////////////////////////// misc
// reboot system sysinfo...
typedef const char *(*osal_api_get_version)(void);
typedef uint64_t (*osal_api_uptime)(void);

typedef struct osal_api
{
    // mem
    osal_api_malloc malloc;
    osal_api_free free;
    osal_api_calloc calloc;
    osal_api_realloc realloc;

    // task
    osal_api_task_create task_create;
    osal_api_task_destory task_destory;
    osal_api_task_self task_self;
    osal_api_task_yield task_yield;
    osal_api_task_sleep task_sleep;
    osal_api_task_usleep task_usleep;
    osal_api_task_suspend task_suspend;
    osal_api_task_resume task_resume;
    osal_api_task_get_priority task_get_priority;
    osal_api_task_set_priority task_set_priority;

    // mutex
    osal_api_mutex_create mutex_create;
    osal_api_mutex_destory mutex_destory;
    osal_api_mutex_lock mutex_lock;
    osal_api_mutex_trylock mutex_trylock;
    osal_api_mutex_unlock mutex_unlock;

    // sem
    osal_api_sem_create sem_create;
    osal_api_sem_destory sem_destory;
    osal_api_sem_wait sem_wait;
    osal_api_sem_post sem_post;

    // time
    osal_api_calc_timedwait calc_timedwait;

    // misc
    osal_api_uptime uptime;
    osal_api_get_version get_version;
} osal_api_t;

extern osal_api_t osal_api;

#ifndef osal_malloc
#define osal_malloc osal_api.malloc
#define osal_free osal_api.free
#define osal_calloc osal_api.calloc
#define osal_realloc osal_api.realloc
#endif // !osal_malloc

#ifndef osal_task_create
#define osal_task_create osal_api.task_create
#define osal_task_self osal_api.task_self
#define osal_task_sleep osal_api.task_sleep
#define osal_task_usleep osal_api.task_usleep
#define osal_task_destory osal_api.task_destory
#define osal_task_yield osal_api.task_yield
#define osal_task_suspend osal_api.task_suspend
#define osal_task_resume osal_api.task_resume
#define osal_task_get_priority osal_api.task_get_priority
#define osal_task_set_priority osal_api.task_set_priority
#endif // !osal_task_create

#ifndef osal_mutex_create
#define osal_mutex_create osal_api.mutex_create
#define osal_mutex_destory osal_api.mutex_destory
#define osal_mutex_lock osal_api.mutex_lock
#define osal_mutex_trylock osal_api.mutex_trylock
#define osal_mutex_unlock osal_api.mutex_unlock
#endif // !osal_mutex_create

#ifndef osal_sem_create
#define osal_sem_create osal_api.sem_create
#define osal_sem_destory osal_api.sem_destory
#define osal_sem_wait osal_api.sem_wait
#define osal_sem_post osal_api.sem_post
#endif // !osal_sem_create

#ifndef osal_uptime
#define osal_uptime osal_api.uptime
#endif // !osal_uptime

#ifndef osal_get_version
#define osal_get_version osal_api.get_version
#endif // !osal_get_version

#ifndef osal_calc_timedwait
#define osal_calc_timedwait osal_api.calc_timedwait
#endif // !osal_calc_timedwait

#endif // !_OSAL_API_H_
