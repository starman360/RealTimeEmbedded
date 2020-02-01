#include "string.h"
#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "timing_control.h"
#include "GPIO.h"
#include "Timer.h"
#include "post.h"
#define DEBUG

#define MAX_TIME 100000
#define GETALIFE 1

#define POST_ROUTINE_COMPLETE 	"POST routine finished successfully.\t\r\n"
#define POST_ROUTINE_FAILED		"POST routine failed.\r\t\n"
int POST() {
	int watchdog = 0;
	TIM2->SR &= ~TIM_SR_CC1IF; // RESET FLAG
	TIM2->SR &= ~TIM_SR_UIF; // RESET FLAG
	timerEN(1);
	int TC = 0;
	while(!getStatus()){
		TC = getTimeCounter();
		#ifdef DEBUG
		uint8_t buffer[BufferSize];  
		int n = sprintf((char *)buffer, "%d\r\n", TIM2->SR);
		USART_Write(USART2, buffer, n);
		#endif
		if (TC > 200000){
			watchdog = 1;
			break;
		}
		
	}
	if (watchdog){ // HANDLE ERROR
		USART_Write(USART2, (uint8_t *)POST_ROUTINE_FAILED, strlen(POST_ROUTINE_FAILED));	
		
	}
	
	// WE GOOCH
	timerEN(0);
	USART_Write(USART2, (uint8_t *)POST_ROUTINE_COMPLETE, strlen(POST_ROUTINE_COMPLETE));
			#ifndef DEBUG
		uint8_t buffer[BufferSize];  
		int n = sprintf((char *)buffer, "%d\r\n", TC);
		USART_Write(USART2, buffer, n);
		#endif
	while(1);
	return 0;
}
void PROJ1_INIT(void){
	System_Clock_Init(); // Switch System Clock = 80 MHz
	LED_Init();
	timerInit();
	GPIO_Init();
	UART2_Init();
}
