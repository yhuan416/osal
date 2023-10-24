#ifndef _OSAL_TASK_H_
#define _OSAL_TASK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef void *osal_task_t;

typedef void *(*osal_task_func_t)(void *arg);

typedef struct osal_task_attr_t {
    const char *name;   // name of the task
    uint32_t stackSize; // stack size of the task
    uint32_t affinity;  // affinity of the task
    uint16_t priority;  // priority of the task
} osal_task_attr_t;

/**
 * @brief Create a task object.
 * 
 * @param func The entry function of the task.
 * @param arg The argument of the entry function.
 * @param attr The attribute of the task.
 * 
 * @return The task object.
 */
osal_task_t osal_task_create(osal_task_func_t func, void *arg, osal_task_attr_t *attr);

/**
 * @brief Wait for the task to terminate.
 * 
 * @param task The task object.
 */
void osal_task_join(osal_task_t task);

/**
 * @brief Get the task id of the current task.
 * 
 * @return The task id.
 */
int32_t osal_task_self(void);

/**
 * @brief Current task delay some milliseconds
 * 
 * @param ms delay milliseconds
 */
void osal_task_delay_ms(uint32_t ms);

/**
 * @brief Current task delay some seconds
 * 
 * @param ms delay seconds
 */
void osal_task_delay(uint32_t s);

#endif // !_OSAL_TASK_H_
