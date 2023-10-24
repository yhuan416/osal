#ifndef _OSAL_MQ_H_
#define _OSAL_MQ_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "osal_common.h"

typedef void *osal_mq_t;

osal_mq_t osal_mq_create(const char *name, uint32_t msgSize, uint32_t msgCount);

void osal_mq_destroy(osal_mq_t mq);

int32_t osal_mq_send(osal_mq_t mq, const void *msg, uint32_t timeout);

int32_t osal_mq_recv(osal_mq_t mq, void *msg, uint32_t timeout);

#endif // !_OSAL_MQ_H_
