#ifndef _OSAL_API_H_
#define _OSAL_API_H_

#if defined(__linux__)
#include "osal_posix.h"
#endif

/**
 * @brief osal_api 返回值
 *
 * @enum osal_api_ret
 */
enum osal_api_ret
{
    OSAL_API_OK = 0,              /*!< ok */
    OSAL_API_FAIL = -1,           /*!< fail */
    OSAL_API_TIMEOUT = -2,        /*!< time out */
    OSAL_API_INVALID = -3,        /*!< invalid args */
    OSAL_API_MEM_ALLOC_FAIL = -4, /*!< no mem */
};

/**
 * @brief wait forever
 * 
 */
#define OSAL_API_WAITFOREVER (-1)

//////////////////////////////////////////////// mem

/// \addtogroup osal_api
/// @{

/**
 * @brief same as malloc
 *
 * @interface osal_malloc
 *
 * @param[in] size 申请的内存大小
 *
 * @note void *osal_malloc(size_t size);
 */
typedef void *(*osal_api_malloc)(size_t size);

/**
 * @brief same as free
 *
 * @interface osal_free
 *
 * @param[in] ptr 内存地址
 *
 * @note void osal_free(void *ptr);
 *
 */
typedef void (*osal_api_free)(void *ptr);

/**
 * @brief same as calloc
 *
 * @interface osal_calloc
 *
 * @param[in] num 分配的内存块数
 * @param[in] size 单块内存的大小
 *
 * @note void *osal_calloc(size_t num, size_t size);
 *
 */
typedef void *(*osal_api_calloc)(size_t num, size_t size);

/**
 * @brief same as realloc
 *
 * @interface osal_realloc
 *
 * @param[in] ptr 内存地址
 * @param[in] size 新的大小
 *
 * @note void *osal_realloc(void *ptr, size_t size);
 */
typedef void *(*osal_api_realloc)(void *ptr, size_t size);

/// @}

//////////////////////////////////////////////// task
typedef void *osal_task_t;

/**
 * @brief 线程入口
 *
 * @interface osal_task_func_t
 *
 * @param[in] arg 线程参数
 */
typedef void *(*osal_task_func_t)(void *arg);

/**
 * @brief 创建一个线程
 *
 * @interface osal_task_create
 *
 * @param[in] name 线程名, 可以填NULL
 * @param[in] func 线程入口
 * @param[in] arg 线程参数
 * @param[in] stack_start 线程栈地址, 为RTOS预留
 * @param[in] stack_size 线程栈大小
 * @param[in] priority 线程优先级, 为RTOS预留
 *
 * @return 线程句柄 or NULL
 *
 * @note osal_task_t osal_task_create(const char *name,
                                            osal_task_func_t func,
                                            void *arg,
                                            void *stack_start,
                                            int stack_size,
                                            int priority);
 */
typedef osal_task_t (*osal_api_task_create)(const char *name,
                                            osal_task_func_t func,
                                            void *arg,
                                            void *stack_start,
                                            int stack_size,
                                            int priority);

/**
 * @brief 销毁一个线程
 *
 * @interface osal_task_destory
 *
 * @param[in] task 线程句柄
 *
 * @return OSAL_API_OK: 成功, 其他: 失败
 *
 * @see osal_api_ret
 * 
 * @note int osal_task_destory(osal_task_t task);
 *
 */
typedef int (*osal_api_task_destory)(osal_task_t task);

typedef osal_task_t (*osal_api_task_self)(void);

typedef int (*osal_api_task_yield)(void);

typedef int (*osal_api_task_sleep)(uint32_t s);

typedef int (*osal_api_task_usleep)(uint32_t us);

/**
 * @brief 线程挂起, 为RTOS预留.
 *
 * @interface osal_task_suspend
 *
 * @param[in] task 线程句柄
 *
 * @return OSAL_API_OK: 成功, 其他: 失败
 *
 * @see osal_api_ret
 *
 */
typedef int (*osal_api_task_suspend)(osal_task_t task);

/**
 * @name osal_task_resume
 *
 * @interface osal_task_suspend
 * @brief 线程恢复, 为RTOS预留
 *
 * @param[in] task 线程句柄
 *
 * @return OSAL_API_OK: 成功, 其他: 失败
 * 
 * @see osal_api_ret
 *
 */
typedef int (*osal_api_task_resume)(osal_task_t task);

/**
 * @name osal_task_get_priority
 *
 * @brief 获取线程优先级, 为RTOS预留
 *
 * @param task 线程句柄
 * @param priority [out] 线程优先级
 *
 * @return OSAL_API_OK: 成功, 其他: 失败
 * 
 * @see osal_api_ret
 *
 */
typedef int (*osal_api_task_get_priority)(osal_task_t task, int *priority);

/**
 * @name osal_task_set_priority
 *
 * @brief 设置线程优先级, 为RTOS预留
 *
 * @param task 线程句柄
 * @param priority 线程优先级
 *
 * @return OSAL_API_OK: 成功, 其他: 失败
 * 
 * @see osal_api_ret
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
    /**
     * @brief same as malloc
     *
     * @see osal_malloc
     */
    osal_api_malloc malloc;

    /**
     * @brief same as free
     *
     * @see osal_free
     */
    osal_api_free free;

    /**
     * @brief same as calloc
     *
     * @see osal_calloc
     */
    osal_api_calloc calloc;

    /**
     * @brief same as realloc
     *
     * @see osal_realloc
     */
    osal_api_realloc realloc;

    /**
     * @brief 创建一个线程
     *
     * @param name 线程名, 可以填NULL
     * @param func 线程入口, see @{osal_task_func_t}
     * @param arg 线程参数
     * @param stack_start 线程栈地址, 为RTOS预留
     * @param stack_size 线程栈大小
     * @param priority 线程优先级, 为RTOS预留
     *
     * @return
     *      线程句柄
     *      NULL, 创建失败
     *
     * @see osal_task_create
     */
    osal_api_task_create task_create;

    /**
     * @brief 销毁一个线程
     *
     * @param task 线程句柄
     *
     * @return
     *      OSAL_API_OK: 成功, 其他: 失败
     *
     * @see OSAL_API_RET
     * @see osal_task_destory
     *
     */
    osal_api_task_destory task_destory;

    /**
     * @brief 获取当前线程句柄
     *
     * @return
     *      线程句柄
     *
     */
    osal_api_task_self task_self;

    /**
     * @brief 主动触发线程调度, 为RTOS预留
     *
     * @return
     *      OSAL_API_OK: 成功, 其他: 失败
     *
     * @see OSAL_API_RET
     *
     */
    osal_api_task_yield task_yield;

    /**
     * @brief 线程秒级睡眠
     *
     * @param s sleep time(s)
     *
     * @return
     *      OSAL_API_OK: 成功, 其他: 失败
     *
     * @see OSAL_API_RET
     *
     */
    osal_api_task_sleep task_sleep;

    /**
     * @brief 线程微秒级睡眠
     *
     * @param s sleep time(us)
     *
     * @return
     *      OSAL_API_OK: 成功, 其他: 失败
     *
     * @see OSAL_API_RET
     *
     */
    osal_api_task_usleep task_usleep;

    /**
     * @brief 线程挂起, 为RTOS预留
     *
     * @param task 线程句柄
     *
     * @return
     *      OSAL_API_OK: 成功, 其他: 失败
     *
     * @see osal_task_suspend
     *
     */
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
