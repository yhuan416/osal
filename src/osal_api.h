#ifndef _OSAL_API_H_
#define _OSAL_API_H_

#if defined(__linux__)
#include "osal_posix.h"
#endif

enum osal_api_ret
{
    OSAL_API_OK = 0,              /*!< ok */
    OSAL_API_FAIL = -1,           /*!< fail */
    OSAL_API_TIMEOUT = -2,        /*!< time out */
    OSAL_API_INVALID = -3,        /*!< invalid args */
    OSAL_API_MEM_ALLOC_FAIL = -4, /*!< no mem */
};

#define OSAL_API_WAITFOREVER (-1)

//////////////////////////////////////////////// mem

/**
 * @brief malloc
 * 
 * @name osal_malloc
 * 
 * @param[in] size 内存大小
 * 
 * @retval NULL 申请失败
 * @retval other 内存基地址
 */
typedef void *(*osal_api_malloc)(size_t size);

/**
 * @brief free
 * 
 * @name osal_free
 * 
 * @param[in] ptr 要释放的内存地址
 */
typedef void (*osal_api_free)(void *ptr);

/**
 * @brief calloc
 * 
 * @name osal_calloc
 * 
 * @param[in] num 数量
 * @param[in] size 单块内存大小
 * 
 * @retval NULL 申请失败
 * @retval other 内存基地址
 */
typedef void *(*osal_api_calloc)(size_t num, size_t size);

/**
 * @brief realloc
 * 
 * @name osal_realloc
 * 
 * @param[in] ptr 内存基地址, 为 NULL 时, 该函数等同calloc
 * @param[in] size 内存大小, 为 0 时, 该函数等同free
 * 
 * @retval 新申请到的地址
 */
typedef void *(*osal_api_realloc)(void *ptr, size_t size);

//////////////////////////////////////////////// task
typedef void *osal_task_t;
typedef void *(*osal_task_func_t)(void *arg);

/**
 * @brief task_create
 * 
 * @name osal_task_create
 * 
 * @param[in] name 任务名
 * @param[in] func 任务入口
 * @param[in] arg 传递给任务的参数
 * @param[in] stack_start 任务栈起始地址, 为rtos预留
 * @param[in] stack_size 任务栈大小
 * @param[in] priority 任务优先级, 为rtos预留
 * 
 * @retval NULL 任务创建失败
 * @retval other 任务句柄
 */
typedef osal_task_t (*osal_api_task_create)(const char *name,
                                            osal_task_func_t func,
                                            void *arg,
                                            void *stack_start,
                                            int stack_size,
                                            int priority);

/**
 * @brief task_create_pin_to_core
 * 
 * @name osal_task_create_pin_to_core
 * 
 * @param[in] name 任务名
 * @param[in] func 任务入口
 * @param[in] arg 传递给任务的参数
 * @param[in] stack_start 任务栈起始地址, 为rtos预留
 * @param[in] stack_size 任务栈大小
 * @param[in] priority 任务优先级, 为rtos预留
 * @param[in] core_id 任务核心亲和性
 * 
 * @retval NULL 任务创建失败
 * @retval other 任务句柄
 */
typedef osal_task_t (*osal_api_task_create_pin_to_core)(const char *name,
                                                        osal_task_func_t func,
                                                        void *arg,
                                                        void *stack_start,
                                                        int stack_size,
                                                        int priority,
                                                        int core_id);

/**
 * @brief task_destory
 * 
 * @name osal_task_destory
 * 
 * @param[in] task 任务句柄
 * 
 * @retval OSAL_API_OK 成功
 * @retval other 失败
 */
typedef int (*osal_api_task_destory)(osal_task_t task);

typedef osal_task_t (*osal_api_task_self)(void);

typedef int (*osal_api_task_yield)(void);

typedef int (*osal_api_task_sleep)(uint32_t s);

typedef int (*osal_api_task_usleep)(uint32_t us);

typedef int (*osal_api_task_suspend)(osal_task_t task);

typedef int (*osal_api_task_resume)(osal_task_t task);

typedef int (*osal_api_task_get_priority)(osal_task_t task, int *priority);

typedef int (*osal_api_task_set_priority)(osal_task_t task, int priority);

//////////////////////////////////////////////// mutex
typedef void *osal_mutex_t;

typedef osal_mutex_t (*osal_api_mutex_create)(void);

typedef int (*osal_api_mutex_destory)(osal_mutex_t mutex);

typedef int (*osal_api_mutex_lock)(osal_mutex_t mutex, uint32_t timeout_ms);

typedef int (*osal_api_mutex_trylock)(osal_mutex_t mutex);

typedef int (*osal_api_mutex_unlock)(osal_mutex_t mutex);

//////////////////////////////////////////////// sem
typedef void *osal_sem_t;

typedef osal_sem_t (*osal_api_sem_create)(uint32_t init);

typedef int (*osal_api_sem_destory)(osal_sem_t sem);

typedef int (*osal_api_sem_wait)(osal_sem_t sem, uint32_t timeout_ms);

typedef int (*osal_api_sem_post)(osal_sem_t sem);

////////////////////////////////////////////////// shm
typedef void *(*osal_api_shm_create)(const char *key, int size);

typedef int (*osal_api_shm_destory)(void *shm);

//////////////////////////////////////////////// event
typedef void *osal_event_t;

typedef osal_event_t (*osal_api_event_create)(void);

typedef void (*osal_api_event_destory)(osal_event_t event);

typedef int (*osal_api_event_wait)(osal_event_t event, uint32_t set, uint32_t option, uint32_t timeout_ms);

typedef int (*osal_api_event_set)(osal_event_t event, uint32_t set);

//////////////////////////////////////////////// mq

//////////////////////////////////////////////// timer

//////////////////////////////////////////////// time
typedef int (*osal_api_calc_timedwait)(struct timespec *tm, uint32_t ms);

//////////////////////////////////////////////// signal

//////////////////////////////////////////////// file

//////////////////////////////////////////////// misc
// reboot system sysinfo random env...
typedef void (*osal_api_reboot)(void);

typedef const char *(*osal_api_get_version)(void);

typedef uint64_t (*osal_api_uptime)(void);

typedef unsigned long (*osal_api_random)(void);

typedef struct osal_api
{
    // mem
    osal_api_malloc malloc;
    osal_api_free free;
    osal_api_calloc calloc;
    osal_api_realloc realloc;

    // task
    osal_api_task_create task_create;
    osal_api_task_create_pin_to_core task_create_pin_to_core;
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

    // shm
    osal_api_shm_create shm_create;
    osal_api_shm_destory shm_destory;

    // event
    osal_api_event_create event_create;
    osal_api_event_destory event_destory;
    osal_api_event_wait event_wait;
    osal_api_event_set event_set;

    // time
    osal_api_calc_timedwait calc_timedwait;

    // misc
    osal_api_reboot reboot;
    osal_api_uptime uptime;
    osal_api_get_version get_version;
    osal_api_random random;
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
#define osal_task_create_pin_to_core osal_api.task_create_pin_to_core
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

#ifndef osal_shm_create
#define osal_shm_create osal_api.shm_create
#define osal_shm_destory osal_api.shm_destory
#endif // !osal_shm_create

#ifndef osal_event_create
#define osal_event_create osal_api.event_create
#define osal_event_destory osal_api.event_destory
#define osal_event_wait osal_api.event_wait
#define osal_event_set osal_api.event_set
#endif // !osal_event_create

#ifndef osal_uptime
#define osal_uptime osal_api.uptime
#endif // !osal_uptime

#ifndef osal_get_version
#define osal_get_version osal_api.get_version
#endif // !osal_get_version

#ifndef osal_calc_timedwait
#define osal_calc_timedwait osal_api.calc_timedwait
#endif // !osal_calc_timedwait

#ifndef osal_random
#define osal_random osal_api.random
#endif // !osal_random

#ifndef osal_reboot
#define osal_reboot osal_api.reboot
#endif // !osal_reboot

#endif // !_OSAL_API_H_
