#ifndef _OSAL_MUTEX_H_
#define _OSAL_MUTEX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef void *osal_mutex_t;

/**
 * @brief Create a mutex object.
 * 
 * @return The mutex object.
 */
osal_mutex_t osal_mutex_create(void);

/**
 * @brief Destroy a mutex object.
 * 
 * @param mutex The mutex object.
 */
void osal_mutex_destroy(osal_mutex_t mutex);

/**
 * @brief Lock a mutex object.
 * 
 * @param mutex The mutex object.
 */
void osal_mutex_lock(osal_mutex_t mutex);

/**
 * @brief Unlock a mutex object.
 * 
 * @param mutex The mutex object.
 */
void osal_mutex_unlock(osal_mutex_t mutex);

#endif // !_OSAL_MUTEX_H_
