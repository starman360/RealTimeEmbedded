#include "stm32l476xx.h"
#include "UART.h"
#include "timing_control.h"
#include "post.h"
#include "stdVars.h"

int main(void){
	proj1_init();
	while(!post_complete){
		if (post())
			return 1; // End of Program
	}
	loop();
}


