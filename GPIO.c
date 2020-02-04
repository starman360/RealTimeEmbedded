#include "GPIO.h"

void GPIO_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	GPIOA->MODER &= ~0x03; // FULL RESET
	GPIOA->MODER |= 0x2;
	GPIOA->AFR[0] |= 0x1;
}
