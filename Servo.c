#include "Servo.h"
#include "PWM.h"
#include "cookbook.h"
#include "UART.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "LED.h"

void init_servo(Servo *servo, int id, int recipe_num) {
	servo->id = id;
	servo->instruction_index = 0;
	servo->loop_start_index = 0;
	servo->loop_cnt = 0;
	servo->enable = 0;
	servo->recipe_num = recipe_num;
	servo->recipe_delay = 0;
	servo->pos = 0;
	
	// set the initial position of the servo
	pwm_Set_DC(get_pwm_val(servo->pos), servo->id);
}


void run(Servo *servo){
	int recipe_inst = lookup(servo->recipe_num, servo->instruction_index);
	int param = get_param(recipe_inst);
	if (servo->enable){ //if issues, debug this
		if (servo->recipe_delay) // A delay based on prev command
				servo->recipe_delay--;
		else {
			switch (get_op(recipe_inst)){
				case MOV:
						pwm_Set_DC(get_pwm_val(param), servo->id); // MOVE NOW
						servo->recipe_delay = abs(servo->pos - param) * 2; // ABS VALUE OF ( POS - PARAM) -> recipe process;
						servo->pos = param;
						break;
				case WAIT:
						servo->recipe_delay += (param + 1);
						// WAIT FOR N >= 0 1/10th seconds
						break;
				case LOOP:
						// check if b in a loop
						if (servo->loop_cnt) {
							servo->err = NEST_LOOP_ERR;
							break;
						}
						servo->loop_cnt = param + 1; // iterations in loop
						servo->loop_start_index = servo->instruction_index;
						break;
				case END_LOOP:
						if (servo->loop_cnt){ // If loop counter is 0 then continue on
							servo->instruction_index = servo->loop_start_index;
							servo->loop_cnt --;
						}
						break;
				case RECIPE_END:
						//servo->instruction_index = 0;
						servo->enable = 0;
						break;
				case JMP: // JMP 4
						if (servo->id == 1){
							servo_copy(servo, &ch1_servo_cp);
						}
						if (servo->id == 2){
							servo_copy(servo, &ch2_servo_cp);
						}
						servo->instruction_index = param;
						break;
				case RET:
						if (servo->id == 1){
							servo_copy(&ch1_servo_cp, servo);
						}
						if (servo->id == 2){
							servo_copy(&ch2_servo_cp, servo);
						}
						break;
				default:
					servo->err = COMMAND_ERR;
					
			}
			if (servo->err) servo->enable = 0;
			status_indicator(servo);
			//print_status(servo);
			servo->instruction_index ++;
		}
	}
}

int get_op(int cmd){
	return OP_MASK & cmd;
}
int get_param(int cmd){
	return PARAM_MASK & cmd;
}

int get_pwm_val(int servo_pos){ // returns us
	return (servo_pos * 200) + 1000;
}

void print_status(Servo *servo){
	uint8_t buffer[64]; 
	int n = sprintf((char *)buffer, "id: %d\r\n",servo->id);
	USART_Write(USART2, (uint8_t *) buffer, n);
	
	n = sprintf((char *)buffer, "enable: %d\r\n",servo->enable);
	USART_Write(USART2, (uint8_t *) buffer, n);
	n = sprintf((char *)buffer, "pos: %d\r\n",servo->pos);
	USART_Write(USART2, (uint8_t *) buffer, n);
	n = sprintf((char *)buffer, "instruction_index: %d\r\n",servo->instruction_index);
	USART_Write(USART2, (uint8_t *) buffer, n);
	n = sprintf((char *)buffer, "recipe_num: %d\r\n",servo->recipe_num);
	USART_Write(USART2, (uint8_t *) buffer, n);
	n = sprintf((char *)buffer, "loop_start_index: %d\r\n",servo->loop_start_index);
	USART_Write(USART2, (uint8_t *) buffer, n);
	n = sprintf((char *)buffer, "loop_cnt: %d\r\n",servo->loop_cnt);
	USART_Write(USART2, (uint8_t *) buffer, n);
	USART_Write(USART2, (uint8_t *)"\r\n", strlen("\r\n"));
}

void status_indicator(Servo *s){
	if (s->enable && s->id == 1) {
			Green_LED_On();
		}
	if(!s->enable && s->id == 1) {
		Green_LED_Off();
	}
	if (s->err == COMMAND_ERR) {
		Red_LED_On();
	}
	if (s->err == NEST_LOOP_ERR) {
		Red_LED_On();
		Green_LED_On();
	}
}

void servo_copy(Servo *s, Servo *scp){
	scp->id = s->id;
	scp->instruction_index = s->instruction_index;
	scp->loop_start_index = s->loop_start_index;
	scp->loop_cnt = s->loop_cnt;
	scp->enable = s->enable;
	scp->recipe_num = s->recipe_num;
	scp->recipe_delay = s->recipe_delay;
	scp->pos = s->pos;
}







