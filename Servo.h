#ifndef SERVO_H
#define SERVO_H
#include "stm32l476xx.h"

#define MIN_POS 0
#define MAX_POS 6


typedef struct Servo {
	int id;									// map id to channel
	int enable;					// status flag for servo running/paused
	int pos;						// 
	int instruction_index; 	// current instruction index in recipe_instructions
	int recipe_num; // what recipe to use
	int recipe_process; // This allows for each command to set a delay in loop timers (100ms) until the next instruction
	int loop_start_index;  	// index of where a loop begins
	int loop_cnt;						// status flag for in a loop
	int err;						// status flag for encountering recipe error
	
}Servo ;

void init_servo(Servo *servo, int id);

void run(Servo *servo);

int get_op(int cmd);
int get_param(int cmd);
int get_pwm_val(int servo_pos);
// functions we will need
/*
 move, loop control, wait
*/
#endif
