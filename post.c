#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Timer.h"
#include "post.h"
#include "UART.h"
#define MAX_TIME 100000

#define POST_ROUTINE_COMPLETE 	"POST routine finished successfully.\t\r\n"
#define POST_ROUTINE_FAILED		"POST routine failed.\r\t\n"
int post_routine() {
	timerEN(1);
	uint32_t init_time = (uint32_t)getTime();
	int flag = 1;
	while(1) {
		if (getStatus()) {
			if (getTime() - init_time <= MAX_TIME) {
				USART_Write(USART2, (uint8_t *)POST_ROUTINE_COMPLETE, strlen(POST_ROUTINE_COMPLETE));
				flag = 0;
				break;
			}
			else {
				USART_Write(USART2, (uint8_t *)POST_ROUTINE_FAILED, strlen(POST_ROUTINE_FAILED));
				break;
			}
		}
		if (getTime() - init_time > MAX_TIME) {
			USART_Write(USART2, (uint8_t *)POST_ROUTINE_FAILED, strlen(POST_ROUTINE_FAILED));
			break;
		}
	}
	timerEN(0);
	return flag;
}
