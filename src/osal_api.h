/**
 * @file osal_api.h
 * @author yhuan (yhuan416@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2024-03-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _OSAL_API_H_
#define _OSAL_API_H_

#if defined(__linux__)
#include "osal_posix.h"
#endif

enum osal_api_ret
{
    OSAL_API_OK = 0,   /*!< ok */
    OSAL_API_FAIL,     /*!< fail */
    OSAL_API_TIMEDOUT, /*!< time out */
    OSAL_API_INVAL,  /*!< invalid args */
    OSAL_API_NOMEM,    /*!< no mem */
    OSAL_API_OVERFLOW, /*!< overflow */

    OSAL_API_RET_MAX,
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
 * @brief 创建一个任务
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
 * @brief 创建一个任务并制定其亲核性, 一般用于rtos
 *
 * @name osal_task_create_pin_to_core
 *
 * @param[in] name 任务名
 * @param[in] func 任务入口
 * @param[in] arg 传递给任务的参数
 * @param[in] stack_start 任务栈起始地址, 为rtos预留
 * @param[in] stack_size 任务栈大小
 * @param[in] priority 任务优先级, 为rtos预留
 * @param[in] core_id 任务核心亲核性
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
 * @brief 销毁一个任务
 *
 * @name osal_task_destory
 *
 * @param[in] task 任务句柄
 *
 * @retval OSAL_API_OK 成功
 * @retval other 失败
 */
typedef int (*osal_api_task_destory)(osal_task_t task);

/**
 * @brief 获取当前任务句柄
 *
 * @name osal_task_self
 *
 * @retval 任务句柄
 */
typedef osal_task_t (*osal_api_task_self)(void);

/**
 * @brief 任务调度, 一般用于rtos
 *
 * @name osal_task_tield
 *
 * @retval OSAL_API_OK 成功
 * @retval other 失败
 */
typedef int (*osal_api_task_yield)(void);

/**
 * @brief 任务睡眠
 *
 * @name osal_task_sleep
 *
 * @param[in] s 秒数
 *
 * @retval OSAL_API_OK 成功
 * @retval other 失败
 */
typedef int (*osal_api_task_sleep)(uint32_t s);

/**
 * @brief 任务微秒级睡眠
 *
 * @name osal_task_usleep
 *
 * @param[in] us 微秒秒数
 *
 * @retval OSAL_API_OK 成功
 * @retval other 失败
 */
typedef int (*osal_api_task_usleep)(uint32_t us);

/**
 * @brief 任务挂起, 一般用于rtos
 *
 * @name osal_task_suspend
 *
 * @param[in] task 任务句柄
 *
 * @retval OSAL_API_OK 成功
 * @retval other 失败
 */
typedef int (*osal_api_task_suspend)(osal_task_t task);

/**
 * @brief 任务恢复, 一般用于rtos
 *
 * @name osal_task_resume
 *
 * @param[in] task 任务句柄
 *
 * @retval OSAL_API_OK 成功
 * @retval other 失败
 */
typedef int (*osal_api_task_resume)(osal_task_t task);

/**
 * @brief 获取任务优先级, 一般用于rtos
 *
 * @name osal_task_get_priority
 *
 * @param[in] task 任务句柄
 * @param[out] priority 任务优先级
 *
 * @retval OSAL_API_OK 成功
 * @retval other 失败
 */
typedef int (*osal_api_task_get_priority)(osal_task_t task, int *priority);

/**
 * @brief 设置任务优先级, 一般用于rtos
 *
 * @name osal_task_set_priority
 *
 * @param[in] task 任务句柄
 * @param[in] priority 任务优先级
 *
 * @retval OSAL_API_OK 成功
 * @retval other 失败
 */
typedef int (*osal_api_task_set_priority)(osal_task_t task, int priority);

//////////////////////////////////////////////// mutex
typedef void *osal_mutex_t;

/**
 * @brief 创建一个互斥锁
 *
 * @name osal_mutex_create
 *
 * @retval NULL 失败
 * @retval other mutex句柄
 */
typedef osal_mutex_t (*osal_api_mutex_create)(void);

/**
 * @brief 销毁互斥锁
 *
 * @name osal_mutex_destory
 *
 * @param[in] mutex mutex句柄
 *
 * @retval OSAL_API_OK 成功
 * @retval other 失败
 */
typedef int (*osal_api_mutex_destory)(osal_mutex_t mutex);

/**
 * @brief 持有互斥锁
 *
 * @name osal_mutex_lock
 *
 * @param[in] mutex mutex句柄
 * @param[in] timeout_ms 超时时间 ms
 *
 * @retval OSAL_API_OK 成功
 * @retval other 失败
 */
typedef int (*osal_api_mutex_lock)(osal_mutex_t mutex, uint32_t timeout_ms);

/**
 * @brief 尝试持有互斥锁
 *
 * @name osal_mutex_trylock
 *
 * @param[in] mutex mutex句柄
 *
 * @retval OSAL_API_OK 成功
 * @retval other 失败
 */
typedef int (*osal_api_mutex_trylock)(osal_mutex_t mutex);

/**
 * @brief 释放互斥锁
 *
 * @name osal_mutex_unlock
 *
 * @param[in] mutex mutex句柄
 *
 * @retval OSAL_API_OK 成功
 * @retval other 失败
 */
typedef int (*osal_api_mutex_unlock)(osal_mutex_t mutex);

//////////////////////////////////////////////// sem
typedef void *osal_sem_t;

/**
 * @brief 创建一个信号量
 *
 * @name osal_sem_create
 *
 * @param[in] init 信号量初始值
 *
 * @retval NULL 创建失败
 * @retval other 信号量句柄
 */
typedef osal_sem_t (*osal_api_sem_create)(uint32_t init);

/**
 * @brief 销毁信号量
 *
 * @name osal_sem_destory
 *
 * @param[in] sem 信号量句柄
 *
 * @retval OSAL_API_OK 成功
 * @retval other 失败
 */
typedef int (*osal_api_sem_destory)(osal_sem_t sem);

/**
 * @brief 等待信号量
 *
 * @name osal_sem_wait
 *
 * @param[in] sem 信号量句柄
 * @param[in] timeout_ms 等待超时时间 ms
 *
 * @retval OSAL_API_OK 成功
 * @retval other 失败
 */
typedef int (*osal_api_sem_wait)(osal_sem_t sem, uint32_t timeout_ms);

/**
 * @brief 释放信号量
 *
 * @name osal_sem_post
 *
 * @param[in] sem 信号量句柄
 *
 * @retval OSAL_API_OK 成功
 * @retval other 失败
 */
typedef int (*osal_api_sem_post)(osal_sem_t sem);

////////////////////////////////////////////////// shm

/**
 * @brief 创建一个共享内存
 *
 * @name osal_shm_create
 *
 * @param[in] key key, 用于创建共享内存
 * @param[in] size 共享内存大小
 *
 * @retval NULL 创建失败
 * @retval other 共享内存地址
 */
typedef void *(*osal_api_shm_create)(const char *key, int size);

/**
 * @brief 销毁一个共享内存
 *
 * @name osal_shm_destory
 *
 * @param[in] shm 共享内存地址
 *
 * @retval OSAL_API_OK 成功
 * @retval other 失败
 */
typedef int (*osal_api_shm_destory)(void *shm);

//////////////////////////////////////////////// event
typedef void *osal_event_t;

/**
 * @brief 创建一个事件
 *
 * @name osal_event_create
 *
 * @retval NULL 创建失败
 * @retval other 事件句柄
 */
typedef osal_event_t (*osal_api_event_create)(void);

/**
 * @brief 销毁事件
 *
 * @name osal_event_destory
 *
 * @param[in] event 事件句柄
 */
typedef void (*osal_api_event_destory)(osal_event_t event);

/**
 * @brief 等待对应的事件
 *
 * @name osal_event_wait
 *
 * @param[in] event 事件句柄
 * @param[in] set 等待的标记位
 * @param[in] option 选项 [ and | or | clear ]
 * @param[in] timeout_ms 超时时间 ms
 *
 * @retval OSAL_API_OK 成功
 * @retval other 失败
 */
typedef int (*osal_api_event_wait)(osal_event_t event, uint32_t set, uint32_t option, uint32_t timeout_ms);

/**
 * @brief 触发对应的事件
 *
 * @name osal_event_set
 *
 * @param[in] event 事件句柄
 * @param[in] set 触发的标记位
 *
 * @retval OSAL_API_OK 成功
 * @retval other 失败
 */
typedef int (*osal_api_event_set)(osal_event_t event, uint32_t set);

//////////////////////////////////////////////// mq

//////////////////////////////////////////////// timer

//////////////////////////////////////////////// time

/**
 * @brief 计算超时时间
 *
 * @name osal_calc_timedwait
 *
 * @param[out] tm 返回的结构体
 * @param[in] ms 超时时间
 *
 * @retval OSAL_API_OK 成功
 * @retval other 失败
 */
typedef int (*osal_api_calc_timedwait)(struct timespec *tm, uint32_t ms);

//////////////////////////////////////////////// signal

//////////////////////////////////////////////// file

//////////////////////////////////////////////// misc
// system sysinfo env...

/**
 * @brief 设备重启
 *
 * @name osal_reboot
 */
typedef void (*osal_api_reboot)(void);

/**
 * @brief 获取osal版本
 *
 * @name osal_get_version
 *
 * @retval 版本号字符串
 */
typedef const char *(*osal_api_get_version)(void);

/**
 * @brief 获取设备启动时间
 *
 * @name osal_uptime
 *
 * @retval 启动时间
 */
typedef uint64_t (*osal_api_uptime)(void);

/**
 * @brief 获取一个随机数
 *
 * @name osal_random
 *
 * @retval 生成的随机数
 */
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
