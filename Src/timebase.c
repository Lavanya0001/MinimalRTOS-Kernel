#include "timebase.h"
#include "stm32wb55xx.h"

#define ONE_SEC_LOAD	4000000UL
#define MAX_DELAY		0xFFFFFFFFUL

volatile uint32_t g_curr_tick;
volatile uint32_t g_curr_tick_p;

volatile uint32_t tick_freq = 1;

static void inline SysTick_Inc(void)
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
void SysTick_Delay_Sec(uint32_t delay)
{
	uint32_t tickstart = get_tick();
	uint32_t wait = delay;

// Now,I am not using this as its becoming +1
//	if(wait < MAX_DELAY)
//	{
//		wait += (uint32_t)tick_freq;
//	}

	while((get_tick() - tickstart) < wait)
	{
		//Does Nothing
	}
}

void SysTick_Init(void)
{
	/* Reload the timer with number of cycles per second*/
	SysTick->LOAD = ONE_SEC_LOAD - 1;

	/* Clear SysTick current value register*/
	SysTick->VAL = 0UL;

	/* Select internal clock source*/
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk;

	/* Enable interrupt */
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

	/* Enable sysTick */
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	/* Enable global interrupts */
	__enable_irq();
}

void Timer2_Init(void)
{
	/* Enable clock source access for Timer2,APB1*/
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

	/* Set timer pre-scaler */
	TIM2->PSC = 400 - 1; // 4,000,000/400 = 10KHzTIM2_ENABLE

	/* Set auto-reload value (ARR) */
	TIM2->ARR = 10000 - 1; // 10000/10000 = 1Hz

	/* Clear timer counter */
	TIM2->CNT = 0;

	/* Enable timer counter*/
	TIM2->CR1 = TIM_CR1_CEN;

	/* Enable timer interrupt*/
	TIM2->DIER |= TIM_DIER_UIE;

	/* Enable timer interrupt in NVIC*/
	NVIC_EnableIRQ(TIM2_IRQn);
}

void SysTick_Handler(void)
{
	SysTick_Inc();
}
