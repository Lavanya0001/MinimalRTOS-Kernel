#pragma once

#ifndef OSKERNEL_H_
#define OSKERNEL_H_

#include <stdint.h>
#include "stm32wb55xx.h"

#define THUMB_MODE_BIT_pos		24U
#define THUMB_MODE_BIT_Msk		(1UL << THUMB_MODE_BIT_pos)
#define THUMB_MODE				THUMB_MODE_BIT_Msk

#define BaseType_t		int32_t
#define UBaseType_t		uint32_t

typedef BaseType_t 	semaphore_t;
typedef UBaseType_t TaskProfiler_t;

//Enumeration for task states
typedef enum {
    TASK_READY,
    TASK_RUNNING,
    TASK_BLOCKED,
    TASK_SUSPENDED
}task_state_t;

void osKernelInit(void);
void oskernelStackInit(int i);
uint8_t osKernelAddThreads(void(*task0)(void),void(*task1)(void),void(*task2)(void));
void osKernelLaunch(uint32_t quanta);

void osThreadYield(void);
void task3(void);

void osSemaphoreInit(int32_t *semaphore,int32_t value);
void osSemaphoreGive(int32_t *semaphore);
void osSemaphoreWait(int32_t *semaphore);

#endif /* OSKERNEL_H_ */
