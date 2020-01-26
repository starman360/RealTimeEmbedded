#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "stm32l476xx.h"
#include "UART.h"
#include "post.h"
#include "timing_control.h"

#define ENTER_KEY 0x0D
#define BACKSPACE_KEY 0x7F
#define CHANGE_LOWER_LIMIT_Q "Change lower limit (y|n):"
#define ENTER_LOWER_LIMIT "\r\nEnter lower limit: "
#define OUT_OF_RANGE_LIMIT "\r\nLower limit out of range. Select between 50-9950"
#define INVALID_NUMBER_ENTERED "\r\nNot a valid lower limit"
#define INVALID_ENTRY "\r\nNot a valid entry\r\n"
#define WAIT_ENTER "Press enter to begin timing test\r\n"
#define BEGIN_TIMING_TEST "Running timing test"
#define RUN_TEST_AGAIN "\r\nRun the test again (y|n):"

int lower_limit = 950;
int upper_limit = 1050;

void controller() {
	post_routine();
	while (1) {
		print_limits();
		change_limits();
		wait_enter();
		USART_Write(USART2, (uint8_t *)BEGIN_TIMING_TEST, strlen(BEGIN_TIMING_TEST));
		if (run_again()) {
			break;
		}
	}
}

void wait_enter() {
	char rxByte;
	USART_Write(USART2, (uint8_t *)WAIT_ENTER, strlen(WAIT_ENTER));
	while (1) {
		rxByte = USART_Read(USART2);
		if (rxByte == ENTER_KEY) {
			break;
		}
	}
}

void print_limits() {
	uint8_t buffer[BufferSize];  
	int n = sprintf((char *)buffer, "lower = %d\t", lower_limit);
	n += sprintf((char *)buffer + n, "upper = %d\r\n", upper_limit);
	USART_Write(USART2, buffer, n);
}

void change_limits() {
	uint8_t limit_buf[BufferSize];
	memset(limit_buf, '\0', sizeof limit_buf);
	char rxByte;

	while (1) {
		USART_Write(USART2, (uint8_t *)CHANGE_LOWER_LIMIT_Q, strlen(CHANGE_LOWER_LIMIT_Q));
		rxByte = USART_Read(USART2);
		if (rxByte == 'N' || rxByte == 'n') {
			USART_Write(USART2, (uint8_t* )"\r\n", strlen("\r\n"));  
			return;
		}
		else if (rxByte == 'Y' || rxByte == 'y') {
			USART_Write(USART2, (uint8_t* )ENTER_LOWER_LIMIT, strlen(ENTER_LOWER_LIMIT));
			// read the lower limit input
			while (1) {
				rxByte = USART_Read(USART2);
				if (rxByte == ENTER_KEY && (strlen((char *) limit_buf) > 0)) {
					sanitize_cmd((char *)&limit_buf);
					// verify number entered
					if (process_buf((char *)&limit_buf)) {
						memset(limit_buf, 0, sizeof (limit_buf));
					}
					// show new limits 
					else {
						USART_Write(USART2, (uint8_t* )"\r\n", strlen("\r\n"));  
						print_limits();
						break;
					}
				}
				// TODO: add check for if character vs digit
				else if (rxByte) {
					append_digit((char *)&limit_buf, rxByte);
					USART_Write(USART2, (uint8_t *)&rxByte, 1);
				}
				spin_function();
			}
			break;
		}
		else {
			USART_Write(USART2, (uint8_t *)INVALID_ENTRY, strlen(INVALID_ENTRY));
		}
	}
}

int process_buf(char *str) {
	int errnum;
	int limit;
	limit = strtol(str, NULL, 0);
	errnum = errno;
	// The given base contains an unsupported value.
	if (errnum == EINVAL) {
		return 1;
	}
	// The resulting value was out of range.
	if (errnum == ERANGE) {
		return 1;
	}
	if (limit < 50 || limit > 9950) {
		USART_Write(USART2, (uint8_t *)OUT_OF_RANGE_LIMIT, strlen(OUT_OF_RANGE_LIMIT));
		USART_Write(USART2, (uint8_t* )ENTER_LOWER_LIMIT, strlen(ENTER_LOWER_LIMIT));
		return 1;
	}
	lower_limit = limit;
	upper_limit = limit + 100;
	return 0;
}

void sanitize_cmd(char *str) {
	int len = strlen(str);
	str[len] = '\0';
}

void append_digit(char *number, char c) {
    int len = strlen(number);
    number[len] = c;
}

void spin_function(void) {
	for (int i = 0; i < 200000; i++);
}

int run_again() {
	char rxByte;
	USART_Write(USART2, (uint8_t *)RUN_TEST_AGAIN, strlen(RUN_TEST_AGAIN));
	while(1) {
		rxByte = USART_Read(USART2);
		if (rxByte == 'N' || rxByte == 'n') {
			return 1;
		}
		else if(rxByte == 'Y' || rxByte == 'y') {
			USART_Write(USART2, (uint8_t* )"\r\n", strlen("\r\n"));
			return 0;
		}
	}
}
