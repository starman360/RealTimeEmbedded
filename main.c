#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "timing_control.h"
#include "post.h"
#include <string.h>
#include <stdio.h>

int main(void){
	PROJ1_INIT();
	POST();
	loop();
}


