/*
 * timebase.h
 *
 *  Created on: Jan 10, 2026
 *      Author: lavanyaimadabattina
 */

#ifndef TIMEBASE_H_
#define TIMEBASE_H_

#include <stdint.h>

#define PERIOD	100 		//FREQUENCY = PERIOD * QUANTA

uint32_t get_tick(void);
void SysTick_Init(void);
void SysTick_Delay_Sec(uint32_t delay);

void Timer2_Init(void);


#endif /* TIMEBASE_H_ */
