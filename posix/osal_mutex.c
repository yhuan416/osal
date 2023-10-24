#include "osal.h"

#include <pthread.h>

osal_mutex_t osal_mutex_create(void)
{
    pthread_mutex_t *mutex = (pthread_mutex_t *)osal_malloc(sizeof(pthread_mutex_t));
    if (mutex == NULL) { return NULL; }

    pthread_mutex_init(mutex, NULL);
    return mutex;
}

void osal_mutex_destroy(osal_mutex_t mutex)
{
    if (mutex == NULL) { return; }

    pthread_mutex_destroy((pthread_mutex_t *)mutex);
    osal_free(mutex);
}

void osal_mutex_lock(osal_mutex_t mutex)
{
    if (mutex == NULL) { return; }

    pthread_mutex_lock((pthread_mutex_t *)mutex);
}

void osal_mutex_unlock(osal_mutex_t mutex)
{
    if (mutex == NULL) { return; }

    pthread_mutex_unlock((pthread_mutex_t *)mutex);
}
