
/*
 * Scheduler Selection:
 * - Cooperative
 * - Round Robin (SysTick-based)
 * - Priority-based (future)
 */

#ifndef RTOS_CONFIG_H_
#define RTOS_CONFIG_H_

#define NON_RTOS   		0U
#define COOPERATIVE 	1U
#define ROUND_ROBIN 	2U
#define PRIORITY		3U

#define RTOS_SCHEDULER COOPERATIVE

#if (RTOS_SCHEDULER == NON_RTOS)
	#define RTOS 		   0U
	#define COOP_SCHEDULER 0U
	#define RR_SCHEDULER   0U
	#define RTOS 		   0U
#elif(RTOS_SCHEDULER == ROUND_ROBIN)
	#define RTOS 		    1U
	#define RR_SCHEDULER	1U
	#define QUANTA			1000U

#elif(RTOS_SCHEDULER == COOPERATIVE)
	#define RTOS 		    1U
	#define COOP_SCHEDULER	1U

#endif

#define PERODIC_TASK	0U
#define SEMA			0U
#define TIMER			0U



#define UART_DEBUG			1U //Always, UART_DEBUG = 1; to get log from the MCU
#define UART_DEBUG_IN_TASK 	0U

#define oSconfig_MAX_PRIOITIES 			3

#define oSconfig_Prioirty_LOW			3
#define oSconfig_Prioirty_MEDIUM		2
#define oSconfig_Prioirty_HIGH			1




#endif /* RTOS_CONFIG_H_ */
