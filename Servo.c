#include "Servo.h"

void init_servo(Servo *servo, int id, uint8_t recipe[], int recipe_size) {
	servo->id = id;
	servo->instruction_index = 0;
	servo->loop_start_index = 0;
	servo->in_loop = 0;
	servo->is_paused = 1;
	
	for (int i = 0; i < recipe_size; i++) {
		servo->recipe_instructions[i] = recipe[i];
	}
}
