#include <stdlib.h>
#include <stdio.h>

#define MOV 32					// 001
#define WAIT 64					// 010
#define LOOP 128				// 100
#define END_LOOP 160		// 101
#define RECIPE_END 0		// 0
#define RECIPE_INSTRUCTION_LENGTH 50

uint8_t base_recipe[2][RECIPE_INSTRUCTION_LENGTH] = {
	{
		MOV+0,
		MOV+5,
		MOV+0,
		MOV+3,
		LOOP+0,
		MOV+1,
		MOV+4,
		END_LOOP,
		MOV+0,
		MOV+2,
		WAIT+0,
		MOV+3,
		WAIT+0,
		MOV+2,
		MOV+3,
		WAIT+31,
		WAIT+31,
		WAIT+31,
		MOV+4,
		RECIPE_END
	},
	{
		MOV+0,
		MOV+5,
		MOV+0,
		MOV+3,
		LOOP+0,
		MOV+1,
		MOV+4,
		END_LOOP,
		MOV+0,
		MOV+2,
		WAIT+0,
		MOV+3,
		WAIT+0,
		MOV+2,
		MOV+3,
		WAIT+31,
		WAIT+31,
		WAIT+31,
		MOV+4,
		RECIPE_END
	}
};
