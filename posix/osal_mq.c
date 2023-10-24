#include "osal.h"

#include <pthread.h>

typedef struct mq_t
{
    const char *name;
    uint32_t msgSize;
    uint32_t msgCount;
} mq_t;

osal_mq_t osal_mq_create(const char *name, uint32_t msgSize, uint32_t msgCount)
{
    mq_t *mq = (mq_t *)osal_malloc(sizeof(mq_t));
    if (mq == NULL) {
        return NULL;
    }

    mq->name = name;
    mq->msgSize = msgSize;

    // ...

    return mq;
}

void osal_mq_destroy(osal_mq_t mq)
{
    // ...

    osal_free(mq);
}

int32_t osal_mq_send(osal_mq_t mq, const void *msg, uint32_t timeout)
{

}

int32_t osal_mq_recv(osal_mq_t mq, void *msg, uint32_t timeout)
{

}
