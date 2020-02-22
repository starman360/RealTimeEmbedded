#ifndef _USER_INPUT_H_
#define _USER_INPUT_H_

#include "Servo.h"

typedef struct Cmd {
	char s1_cmd;
	char s2_cmd;
}Cmd;

void process_command(Cmd *cmd, Servo *s);
void process_recipe(void);
int input(Cmd *cmd);
char toLowercase(char);

#endif
