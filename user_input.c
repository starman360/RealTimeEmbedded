#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user_input.h"
#include "stm32l476xx.h"
#include "UART.h"
#include "stdVars.h"

#define CMD_LENGTH 2

char cmd[CMD_LENGTH];

void delay(void) {
	for (int i = 0; i < 200000; i++);
}

void process_input() {
	for (int i = 0; i < SERVO_COUNT; i ++) {
		switch(cmd[i]) {
			case 'P':
			case 'p':
				// paused servo 1 or 2 here
				break;
			case 'C':
			case 'c':
				// unpause servo 1 or 2 here
				break;
			case 'R':
			case 'r':
				// move servo 1 or 2 one position to the right (as long as it is not pos 0)
				break;
			case 'L':
			case 'l':
				// move servo 1 or 2 one position to the left (as long as it is not pos 5)
				break;
			case 'N':
			case 'n':
				// No-op ignore for servo 1 or two 
				break;
			case 'B':
			case 'b':
				// Start or retarst recipe
				break;
			
			default:
				// no valid command entered
				USART_Write(USART2, (uint8_t *)"\r\nInvalid Command\r\n>", 18);
		}
	}
}

int input() {
	int status = 0; // input not finished
	char rxByte;
	static int index;
	
	rxByte = USART_Read(USART2);
	
	// user interrupt
	if(rxByte == 'x' || rxByte == 'X'){
		index = 0;
		USART_Write(USART2, (uint8_t *)USER_INTERRUPT_PRINT, strlen(USER_INTERRUPT_PRINT));
	}
	// user pressed enter AND two characters have been entered
	else if (rxByte == CR && index == CMD_LENGTH ) {
		process_input();
		status = 1; // input finished
	}
	// user pressed backspace 
	else if (rxByte == BACKSPACE && index > 0) {
		index--;
		USART_Write(USART2, (uint8_t *)&rxByte, sizeof(char)); // echo 
	}
	// add character
	else {
		// cr and backspace are not considered characters
		if (rxByte == CR || rxByte == BACKSPACE) {
			return status;
		}
		// extra characters being entered situation
		if (rxByte != CR && index == CMD_LENGTH) {
			return status;
		// add the character
		} else {
			cmd[index] = rxByte;
			USART_Write(USART2, (uint8_t *)&rxByte, sizeof(char)); // echo
			index++;
		}
	}
	delay();
	return status;
}
