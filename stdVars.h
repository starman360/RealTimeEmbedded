#ifndef STDVARS_H
#define STDVARS_H
#include "Servo.h"

#define CR 0x0D
#define ENTER_KEY 0x0D
#define BACKSPACE_KEY 0x7F
#define BACKSPACE 0x7F
#define INVALID_COMMAND "\r\nInvalid command entered"
#define USER_INTERRUPT_PRINT "\r\n>"
#define SERVO_COUNT 2

typedef int bool;
#define true 1
#define false 0

extern Servo ch1_servo;
extern Servo ch2_servo;

#endif
