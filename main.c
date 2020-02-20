#include <stdlib.h>
#include <string.h>
#include "servo_input.h"
#include "LED.h"
#include "GPIO.h"
#include "SysClock.h"
#include "stm32l476xx.h"
#include "UART.h"
#include "servo_input.h"

int main(void){
	System_Clock_Init();
	LED_Init();
	GPIO_Init();
	UART2_Init();
	USART_Write(USART2, (uint8_t* )"\r\n", strlen("\r\n"));
	while(input() == 0) {
		// get input
	}
	USART_Write(USART2, (uint8_t* )"\r\nfinished", strlen("\r\nfinished"));
}


