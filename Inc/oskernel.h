#pragma once

#ifndef OSKERNEL_H_
#define OSKERNEL_H_

#include <stdint.h>
#include "stm32wb55xx.h"

#define BaseType_t		int32_t
#define UBaseType_t		uint32_t

typedef BaseType_t 	semaphore_t;
typedef UBaseType_t TaskProfiler_t;

#define PERIOD		100 		//PERIOD is 100*10. As 10 is the Quanta
#define TIM2_UIF	(1U << 0);	//TIM2 Interrupt_flag

void Timer2_1Hz_Interrupt_Init(void);
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
