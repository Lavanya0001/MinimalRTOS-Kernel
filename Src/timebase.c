#include "timebase.h"
#include "stm32wb55xx.h"

#define ONE_SEC_LOAD	4000000

#define CTRL_EN			(1U << 0)
#define CTRL_TICKINT	(1U << 1)
#define CTRL_CLKSRC		(1U << 2)
#define CTRL_COUNTFLAG	(1U << 16)

#define MAX_DELAY		0xFFFFFFFF

volatile uint32_t g_curr_tick;
volatile uint32_t g_curr_tick_p;

volatile uint32_t tick_freq = 1;

static void tick_increment(void)
{
	g_curr_tick += tick_freq;
}


uint32_t get_tick(void)
{
	__disable_irq();
	g_curr_tick_p = g_curr_tick;
	__enable_irq();

	return g_curr_tick_p;

}

/* Delay in seconds*/
void delay(uint32_t delay)
{
	uint32_t tickstart = get_tick();
	uint32_t wait = delay;

/* Now,I am not using this as its becoming +1*/
//	if(wait < MAX_DELAY)
//	{
//		wait += (uint32_t)tick_freq;
//	}
	while((get_tick() - tickstart) < wait)
	{

	}
}

void timebase_init(void)
{
	/* Reload the timer with number of cycles per second*/
	SysTick->LOAD = ONE_SEC_LOAD - 1;

	/* Clear SysTick current value register*/
	SysTick->VAL = 0;

	/* Select internal clock source*/
	SysTick->CTRL = CTRL_CLKSRC;

	/* Enable interrupt */
	SysTick->CTRL |= CTRL_TICKINT;

	/* Enable sysTick */
	SysTick->CTRL |= CTRL_EN;

	/* Enable global interrupts */
	__enable_irq();
}

/* Here you can keep this SysTick_Handler and keep the ISR Routine for the delay*/
