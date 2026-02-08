
/*
 * Scheduler Selection:
 * - Cooperative
 * - Round Robin (SysTick-based)
 * - Priority-based (future)
 */

#ifndef RTOS_CONFIG_H_
#define RTOS_CONFIG_H_

#define COOP_SCHEDULER	1U

#if !COOP_SCHEDULER
	#define RR_SCHEDULER	1U
#else
	#define RR_SCHEDULER	0U
#endif

#if RR_SCHEDULER
#define PERODIC_TASK	1U
#endif

#define SEMA			1U
#define TIMER			1U


#define UART_DEBUG			1U //Always, UART_DEBUG = 1; to get log from the MCU
#define UART_DEBUG_IN_TASK 	0U

#ifdef RR_SCHEDULER		//Round-Robin Scheduler
	#define QUNATA	10 	// Milli-Seconds
#endif

#define oSconfig_MAX_PRIOITIES 			3

#define oSconfig_Prioirty_LOW			3
#define oSconfig_Prioirty_MEDIUM		2
#define oSconfig_Prioirty_HIGH			1




#endif /* RTOS_CONFIG_H_ */
