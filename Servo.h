#ifndef SERVO_H
#define SERVO_H
#include "stm32l476xx.h"

#define MOV  				(32)
#define WAIT 				(64)
#define LOOP 				(128)
#define END_LOOP 		(160)
#define RECIPE_END 	(0)
#define RECIPE_INSTR_LEN (64)
#define OP_MASK (224)

#define POS_0_PERIOD 0
#define POS_1_PERIOD 0
#define POS_2_PERIOD 0
#define POS_3_PERIOD 0
#define POS_4_PERIOD 0
#define POS_5_PERIOD 0


typedef struct Servo Servo;

struct Servo {
	int instruction_index; // current instruction index in recipe_instructions
	int in_loop;
	// int loop_index; // not sure we need this?
	int is_paused;
	int is_running;
	uint8_t recipe_instructions[RECIPE_INSTR_LEN];
		
};
// functions we will need
/*
 move, loop control, wait
*/
#endif
