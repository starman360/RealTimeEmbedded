#ifndef RECIPE_INSTRUCTIONS_H
#define RECIPE_INSTRUCTIONS_H
#include "stm32l476xx.h"
#include "Servo.h"



#define MOV  				(32)
#define WAIT 				(64)
#define LOOP 				(128)
#define END_LOOP 		(160)
#define RECIPE_END 	(0)
#define JMP (161)
#define RET (162)

#define OP_MASK (224)
#define PARAM_MASK (31)

extern uint8_t cookbk[3][64];
int lookup(int recipe_num, int i);


#endif
