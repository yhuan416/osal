#ifndef _OSAL_TASK_H_
#define _OSAL_TASK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// task
typedef void *TaskId;

typedef void *(*TaskFunc)(void *arg);

typedef struct TaskAttr {
    const char *name;   // name of the thread
    uint32_t stackSize;
    uint16_t priority;
} TaskAttr;

void *osal_task_create(TaskFunc func, void *arg, TaskAttr *attr);

void osal_task_join(void *task);

int32_t osal_task_self(void);

#endif // !_OSAL_TASK_H_
