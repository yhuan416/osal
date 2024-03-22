#ifndef _OSAL_POSIX_H_
#define _OSAL_POSIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include <sys/time.h>

#include <pthread.h>

#ifndef osal_malloc
#define osal_malloc osal_api.malloc
#define osal_free free
#define osal_calloc osal_api.calloc
#define osal_realloc osal_api.realloc
#endif // !osal_malloc

#ifndef osal_get_version
#define osal_get_version() "1.0.0"
#endif // !osal_get_version

#ifndef osal_task_create
#define osal_task_create osal_api.task_create
#define osal_task_self() ((osal_task_t)pthread_self())
#define osal_task_sleep(s) sleep(s)
#define osal_task_usleep(us) usleep(us)
#define osal_task_destory(task) pthread_cancel((pthread_t)task)
#define osal_task_yield() (-1)
#define osal_task_suspend(task) (-1)
#define osal_task_resume(task) (-1)
#define osal_task_get_priority(task, pri) (-1)
#define osal_task_set_priority(task, pri) (-1)
#endif // !osal_task_create

#endif
