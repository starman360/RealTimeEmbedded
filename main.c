#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "PWM.h"
#include "GPIO.h"
#include "stdVars.h"
#include "servo.h"
#include "recipe_instructions.h"
#include "user_input.h"

#define length(A) sizeof(A)/sizeof(A[0])

int main(void){
	System_Clock_Init();
	LED_Init();
	UART2_Init();
	GPIO_Init();
	pwm_init();
	
	Cmd cmd;
	
	init_servo(&ch1_servo, 1);
	init_servo(&ch2_servo, 2);
	
	while(1){
		if(input(&cmd)){
			process_command(&cmd, &ch1_servo);
			process_command(&cmd, &ch2_servo);
		}
		process_recipe();
		//DELAY
		// Deal with Input
		// Eecute command
		// Increment pos
	}
}


