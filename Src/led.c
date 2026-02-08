#include "led.h"

#define GPIOBEN		(1U << 1) // 0b 0000 0000 0000 0000 0000 0000 0000 0010
#define LED_PIN		(1U << 5)

void led_init(void){

	/* Enable clock access to led port (port B)*/
	RCC->AHB2ENR |= GPIOBEN;

	/* Set led pin as output*/
	GPIOB->MODER |= (1U << 10);
	GPIOB->MODER &= ~(1U << 11);

}

void led_on(void){

	/* Set led pin HIGH (PB5)*/
	GPIOB->ODR |= (LED_PIN);
}

void led_off(void){

	/* Set led pin LOW (PB5)*/
	GPIOB->ODR &= ~(LED_PIN);

}
