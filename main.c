#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "PWM.h"
#include "GPIO.h"
#include "stdVars.h"

int main(void){
	System_Clock_Init();
	LED_Init();
	UART2_Init();
	GPIO_Init();
	shawn_pwn();
	Green_LED_On();
	while(1){
		
	}
}


