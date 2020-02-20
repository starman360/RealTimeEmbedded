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
#include "PWM.h"
//#define DEBUG

int post() {
	return 0;
}


void proj2_init(void){
	System_Clock_Init(); // Switch System Clock = 80 MHz
	LED_Init();
	GPIO_Init();
	shawn_pwn();
	UART2_Init();
}
