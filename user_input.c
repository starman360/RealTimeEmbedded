#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user_input.h"
#include "stm32l476xx.h"
#include "UART.h"
#include "stdVars.h"
#include "cookbook.h"
#include "PWM.h"
#include "Timer.h"
#include "LED.h"

int cmdPos = 1;

void process_command(Cmd *cmd, Servo *s){
	char c;
	if (s->id == 1) c = cmd->s1_cmd;
	if (s->id == 2) c = cmd->s2_cmd;
	
	USART_Write(USART2, (uint8_t *)"char: ", sizeof("char: "));
	USART_Write(USART2, (uint8_t *)&c, sizeof(char));
	USART_Write(USART2, (uint8_t *)"\r\n", sizeof("\r\n"));
	
	switch(c) {
		case 'P':
			s->enable = 0; // paused servo 1 or 2 here
			break;
		case 'C':
			s->enable = 1; // unpause servo 1 or 2 here
			break;
		case 'R':
			if (s->pos > MIN_POS) {
				s->pos --; // move servo 1 or 2 one position to the right (as long as it is not pos 0)
				pwm_Set_DC(get_pwm_val(s->pos), s->id);
			}
			break;
		case 'L':
			if (s->pos < MAX_POS) {
				s->pos ++;// move servo 1 or 2 one position to the left (as long as it is not pos 5)
				pwm_Set_DC(get_pwm_val(s->pos), s->id);
			}
			break;
		case 'N':
			// No-op ignore
			break;
		case 'B':
			s->instruction_index = 0;  // Start or tratser recipe
			s->enable = 1;
			break;
		default:
			// no valid command entered
			USART_Write(USART2, (uint8_t *)"\r\nInvalid Command\r\n>", 18);
			break;
	}
}


char toUppercase(char c) {
	if (c >= 0x61 && c <= 0x7a)
		return (c - 0x20);
	return c;
}


int input(Cmd *cmd) {
	char rxByte = '0';
	rxByte = USART_Read_nb(USART2);
	
	if(rxByte == 0) return 0; // If nothing exit
	
	if(rxByte == 'x'){
		cmd->s1_cmd = 0;
		cmd->s2_cmd = 0;
		cmdPos = 1;
		USART_Write(USART2, (uint8_t *)USER_INTERRUPT_PRINT, strlen(USER_INTERRUPT_PRINT));
		return 0;
	}		
	if(rxByte == CR){
		cmdPos = 1;
		USART_Write(USART2, (uint8_t *)"\r\n", strlen("\r\n"));
		return 1;
	}
	
	// echo back input
	USART_Write(USART2, (uint8_t *)&rxByte, sizeof(char));
	// all input converted to lowercase
	rxByte = toUppercase(rxByte);
		
	if (cmdPos == 1)
		cmd->s1_cmd = rxByte;
	if (cmdPos == 2)
		cmd->s2_cmd = rxByte;
	cmdPos++;
	return 0;
	
}
