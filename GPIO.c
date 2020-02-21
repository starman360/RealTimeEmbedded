#include "GPIO.h"

void GPIO_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;	// enable GPIO A
	GPIOA->MODER &= ~(0xFFFF); 						// clear P1 and P0
	GPIOA->MODER |= 0x0A;  								// set GPIOA P1 and P0 in AF mode
	GPIOA->AFR[0] |= 0x11; 								// set GPIOA P1 and P0 channel
}
