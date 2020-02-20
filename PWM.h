#ifndef _PWM_H_
#define _PWM_H_

#include "stm32l476xx.h"
#include "stdVars.h"

void shawn_pwn(void);
void pwm_Init(void);
void pwm2_Init(void);
void pwm_IEN(bool val);
void pwm_EN(bool);
void pwm_Set_DC(int val); // SET Duty Cycle



#endif
