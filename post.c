#include "string.h"
#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "timing_control.h"
#include "GPIO.h"
#include "Timer.h"
#include "post.h"
#include "stdVars.h"
//#define DEBUG

int post() {
	char rxByte;
	int watchdog = 0;
	timer_EN(1);
	int TC = 0;
	while(!get_status()){
		TC = get_time_counter();
		if (TC > 200000){
			watchdog = 1;
			break;
		}
	}
	if (watchdog){ // Handle Error
		USART_Write(USART2, (uint8_t *)POST_ROUTINE_FAILED, strlen(POST_ROUTINE_FAILED));	
		USART_Write(USART2, (uint8_t *)POST_ROUTINE_RESTART, strlen(POST_ROUTINE_RESTART));			
		rxByte = USART_Read(USART2);
		if (rxByte == 'N' || rxByte == 'n') {
			return 1;
		}
		return 0;
	}
	else { // On Success
		USART_Write(USART2, (uint8_t *)POST_ROUTINE_COMPLETE, strlen(POST_ROUTINE_COMPLETE));
		post_complete = 1;
	}
	
	timer_EN(0); // Turn off timer
	return 0;
}


void proj1_init(void){
	System_Clock_Init(); // Switch System Clock = 80 MHz
	LED_Init();
	timer_Init();
	GPIO_Init();
	UART2_Init();
}
