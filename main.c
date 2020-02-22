#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "PWM.h"
#include "GPIO.h"
#include "stdVars.h"
#include "servo.h"
#include "recipe_instructions.h"

int main(void){
	System_Clock_Init();
	LED_Init();
	UART2_Init();
	GPIO_Init();
	shawn_pwn();

	init_servo(&ch1_servo, 1, base_recipe[0], sizeof(base_recipe[0])/sizeof(base_recipe[0][0]));
	init_servo(&ch2_servo, 2, base_recipe[1], sizeof(base_recipe[1])/sizeof(base_recipe[1][0]));
	
	while(1){
		
	}
}


