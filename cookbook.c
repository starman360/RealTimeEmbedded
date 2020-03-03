#include "cookbook.h"

int lookup(int recipe_num, int i){
	return cookbk[recipe_num][i];
}

/* Required recipe */
uint8_t cookbk[3][64] = {
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
		LOOP+0,
		MOV+1,
		MOV+4,
		END_LOOP,
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
		LOOP+1,
		MOV+1,
		MOV+4,
		END_LOOP,
		MOV+1,
		RECIPE_END
	}
	
};
