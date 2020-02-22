#include "Servo.h"
#include "PWM.h"
#include "cookbook.h"

void init_servo(Servo *servo, int id) {
	servo->id = id;
	servo->instruction_index = 0;
	servo->loop_start_index = 0;
	servo->in_loop = 0;
	servo->enable = 1;
}


void run(Servo *servo){
	int recipe_inst = lookup(servo->recipe_num, servo->instruction_index);
	int param = get_param(recipe_inst);
	if (servo->enable){ //if issues, debug this
		if (servo->recipe_process) // A delay based on prev command
				servo->recipe_process--;
		else {
			switch (get_op(recipe_inst)){
				case MOV:
						pwm_Set_DC(get_pwm_val(param), servo->id);
						// ABS VALUE OF ( POS - PARAM) -> recipe process;
						break;
				case WAIT:
						// WAIT FOR N >= 0 1/10th seconds
						break;
				case LOOP:
						servo->loop_cnt = param;
						servo->loop_start_index = servo->instruction_index + 1;
						break;
				case END_LOOP:
						if (servo->loop_cnt){
							servo->instruction_index = servo->loop_start_index; 
						}
						break;
				case RECIPE_END:
						//servo->instruction_index = 0;
						servo->enable = 0;
						break;
				case ANMOLDOESSOMETHING:
						break;
				case ANMOLDOESSOMETHINGELSE:
						break;		
			}
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
