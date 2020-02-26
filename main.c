#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "PWM.h"
#include "GPIO.h"
#include "stdVars.h"
#include "servo.h"
#include "cookbook.h"
#include "user_input.h"
#include "Timer.h"
#include "string.h"

#define SERVO1_RECIPE_NUM 2
#define SERVO2_RECIPE_NUM	2

int main(void){
	System_Clock_Init();
	LED_Init();
	UART2_Init();
	GPIO_Init();
	pwm_Init();
	timer_Init();
	Cmd cmd;
	
	init_servo(&ch1_servo, 1 , SERVO1_RECIPE_NUM);
	init_servo(&ch2_servo, 2 , SERVO2_RECIPE_NUM);
	
	timer_EN(1); // Turn on main function timer
	
	
	while(1){
		if (!timerFlag){ // RUN 100ms (10Hz)
				timerFlag = 0;				
			if(input(&cmd)){
				process_command(&cmd, &ch1_servo);
				process_command(&cmd, &ch2_servo);
				print_status(&ch1_servo);
				print_status(&ch2_servo);
			}
			//run(&ch1_servo);
			//run(&ch2_servo);
			//print_status(&ch1_servo);
			//print_status(&ch2_servo);
			
			//DELAY
			// Deal with Input
			
			// Eecute command
			// Increment pos
		}
	}
}


