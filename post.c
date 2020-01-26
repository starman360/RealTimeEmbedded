#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "post.h"
#include "UART.h"

#define POST_ROUTINE_COMPLETE "POST routine finished successfully.\t\r\n"
int post_routine() {
	USART_Write(USART2, (uint8_t *)POST_ROUTINE_COMPLETE, strlen(POST_ROUTINE_COMPLETE));
	return 0;
}
