#ifndef _USER_INPUT_H_
#define _USER_INPUT_H_

#include "Servo.h"

typedef struct Cmd {
	char s1_cmd;
	char s2_cmd;
}Cmd;

void process_command(Cmd *cmd, Servo *s);
int input(Cmd *cmd);
char toUppercase(char);

#endif
