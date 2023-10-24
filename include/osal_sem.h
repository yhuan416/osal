#ifndef _OSAL_SEM_H_
#define _OSAL_SEM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "osal_common.h"

typedef void *osal_sem_t;

osal_sem_t osal_sem_create(uint32_t count, uint32_t init);

void osal_sem_destroy(osal_sem_t sem);

int32_t osal_sem_give(osal_sem_t sem, uint32_t timeout);

int32_t osal_sem_take(osal_sem_t sem, uint32_t timeout);

#endif // !_OSAL_SEM_H_
