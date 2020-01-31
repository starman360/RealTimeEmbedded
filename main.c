#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "timing_control.h"
#include "timer.h"
#include "gpio_control.h"

#include <string.h>
#include <stdio.h>

int main(void){
	System_Clock_Init(); // Switch System Clock = 80 MHz
	LED_Init();
	init_pa0();
	timerInit();
	UART2_Init();
	controller();
}


