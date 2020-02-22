#ifndef _PWM_H_
#define _PWM_H_

#include "stm32l476xx.h"
#include "stdVars.h"

void pwm_init(void);
void pwm_IEN(bool val);
void pwm_EN(bool);
void pwm_Set_DC(int val, int servo); // SET Duty Cycle

#endif
