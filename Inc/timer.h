/*
 * timebase.h
 *
 *  Created on: Jan 10, 2026
 *      Author: lavanyaimadabattina
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

#define PERIOD	100 		//FREQUENCY = PERIOD * QUANTA

typedef volatile uint32_t __TIMER;
typedef uint32_t __REG;

void SysTick_Init(void);
void SysTick_Delay_Sec(uint32_t delay);
void SysTick_Delay_Ms(uint32_t delay);
uint32_t SysTick_get_tick();

void Timer2_Init(void);
#endif /* TIMER_H_ */
