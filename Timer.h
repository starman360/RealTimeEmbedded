#ifndef _TIMER_H_
#define _TIMER_H_

#include "stm32l476xx.h"
#include "stdVars.h"

typedef int bool;
#define true 1
#define false 0

void timerInit(void);
void timerIEN(bool val);
void timerEN(bool);
int* getBins(void);
int getBinVal(int);
int getCapturedTime(void);
int getStatus(void);
int getTimeCounter(void);
#endif
