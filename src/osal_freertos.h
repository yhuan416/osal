#ifndef _OSAL_FREERTOS_H_
#define _OSAL_FREERTOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <stddef.h>

#include <sys/time.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_system.h"
#include "esp_err.h"

// translate freeRTOS error code to osal error code
#define FREERTOS_CALL(err) ((err) == pdPASS ? 0 : -1)

#ifndef osal_malloc
#define osal_malloc osal_api.malloc
#define osal_free free
#define osal_calloc osal_api.calloc
#define osal_realloc osal_api.realloc
#endif // !osal_malloc

#ifndef osal_get_version
#define osal_get_version() esp_get_idf_version()
#endif // !osal_get_version

#ifndef osal_task_create
#define osal_task_create osal_api.task_create
#define osal_task_create_pin_to_core osal_api.task_create_pin_to_core
#define osal_task_self() xTaskGetCurrentTaskHandle()
#define osal_task_sleep(s) vTaskDelay(pdMS_TO_TICKS(s * 1000))
#define osal_task_usleep(us) usleep(us)
#define osal_task_destroy(task) vTaskDelete((TaskHandle_t)task)
#define osal_task_yield() taskYIELD()
#define osal_task_suspend(task) vTaskSuspend((TaskHandle_t)task)
#define osal_task_resume(task) vTaskResume((TaskHandle_t)task)
#define osal_task_get_priority osal_api.task_get_priority
#define osal_task_set_priority vTaskPrioritySet
#endif // !osal_task_create

#ifndef osal_mutex_create
#define osal_mutex_create() xSemaphoreCreateMutex()
#define osal_mutex_destroy(mutex) vSemaphoreDelete(mutex)
#define osal_mutex_lock(mutex, ms) FREERTOS_CALL(xSemaphoreTake(mutex, pdMS_TO_TICKS(ms)))
#define osal_mutex_trylock(mutex) FREERTOS_CALL(xSemaphoreTake(mutex, 0))
#define osal_mutex_unlock(mutex) FREERTOS_CALL(xSemaphoreGive(mutex))
#endif // !osal_mutex_create

#ifndef osal_sem_create
#define osal_sem_create(init) xSemaphoreCreateCounting(10, (init))
#define osal_sem_destroy(sem) vSemaphoreDelete(sem)
#define osal_sem_wait(sem, ms) FREERTOS_CALL(xSemaphoreTake(sem, pdMS_TO_TICKS(ms)))
#define osal_sem_post(sem, ms) FREERTOS_CALL(xSemaphoreGive(sem))
#endif // !osal_sem_create

#ifndef osal_mq_create
#define osal_mq_create(name, msg_size, msg_max, flag) xQueueCreate(msg_max, msg_size)
#define osal_mq_destroy(xQueue) vQueueDelete(xQueue)
#define osal_mq_send(xQueue, msg, msg_size, ms) FREERTOS_CALL(xQueueSend(xQueue, msg, pdMS_TO_TICKS(ms)))
#define osal_mq_recv(xQueue, msg, msg_size, ms) FREERTOS_CALL(xQueueReceive(xQueue, msg, pdMS_TO_TICKS(ms)))
#endif // !osal_mq_create

#endif // !_OSAL_FREERTOS_H_
