/* @brief: In this project, we will test different scheduling algorithms like
 * 1. Cooperative Scheduler
 *		1.1 Timer Interrupt using TIM2
 * 2. RoundRobbin Scheduler
 * 		2.1 Timer Interrupt using TIM2
 * 		2.2 Periodic Task Execution
 * 		2.3 Cooperative Semaphore Sync
 * 3. Non-Premptive Scheduling
*/
#include <rtos_config.h>
#include <stdio.h>
#include "led.h"
#include "uart.h"
#include "oskernel.h"
#include "timer.h"

#if SEMA
	semaphore_t semaphore1,semaphore2;
#endif

#if TIMER
	TaskProfiler_t pTask1_Profiler,pTask2_Profiler;
#endif

TaskProfiler_t Task0_Profiler, Task1_Profiler, Task2_Profiler;
void task3(void){

	#if TIMER
		pTask2_Profiler++;
	#endif

}
void task0(void)
{
	while(1)
	{
	#if RR_SCHEDULER
		#if SEMA
			osSemaphoreWait(&semaphore2);
		#endif
		Task0_Profiler++;
		#if UART_DEBUG_IN_TASK
			printf("task -0 is running..\n");
		#endif
		#if SEMA
			osSemaphoreGive(&semaphore1);
		#endif
	#endif

	#if COOP_SCHEDULER
			Task0_Profiler++;
			#if UART_DEBUG_IN_TASK
				printf("task -0 is running..\n");
			#endif
			osThreadYield();
	#endif
	}
}

void task1(void)
{
	while(1)
	{

	#if RR_SCHEDULER
		#if SEMA
			osSemaphoreWait(&semaphore1);
		#endif
		Task1_Profiler++;
		#if UART_DEBUG_IN_TASK
			printf("task -1 is running..\n");
		#endif
		#if SEMA
			osSemaphoreGive(&semaphore2);
		#endif
	#endif

	#if COOP_SCHEDULER
		Task1_Profiler++;
 		#if UART_DEBUG_IN_TASK
			printf("task -1 is running..\n");
		#endif
		osThreadYield();
	#endif
	}
}

void task2(void)
{
	while(1)
	{
	#if RR_SCHEDULER
		Task2_Profiler++;
		#if UART_DEBUG_IN_TASK
			printf("task -2 is running..\n");
		#endif
		#if SEMA
			osSemaphoreGive(&semaphore1);
		#endif
	#endif

	#if COOP_SCHEDULER
		Task2_Profiler++;
		#if UART_DEBUG_IN_TASK
			printf("task -2 is running..\n");
		#endif
		osThreadYield();

	#endif


	}
}

int main()
{
#if UART_DEBUG
	uart_tx_init();
	printf("Using UART1 for Logs..");
#endif

	SysTick_Init();
	Led_Init();

#if RTOS
	/*Timer2 Initialization for PERODIC TASK*/
	#if TIMER
		Timer2_Init();
	#endif

	/*Semaphore Initialization for SYNC TASK*/
	#if SEMA
		osSemaphoreInit(&semaphore1, 1);
		osSemaphoreInit(&semaphore2, 0);
	#endif

	/*Initializing KERNEL*/
	osKernelInit();

	/*Add THREDS to kernel*/
	if(!osKernelAddThreads(&task0, &task1, &task2)){
		printf("ERROR in task creation");
		while(1);
	}

	/*Set Kernel LAUNCH*/
	osKernelLaunch();
#endif

	/* If RTOS = 1,Scheduler reaches here*/
	while(1){
		Led_Toggle(ON_BOARD_LED_BLUE);
		SysTick_Delay_Sec(1);

	}
}

void TIM2_IRQHandler(void)
{
	/*Clear UIE(Update Interrupt)flag*/
	TIM2->SR &= ~TIM_SR_UIF;

#if TIMER
	pTask1_Profiler++;
#endif
}



