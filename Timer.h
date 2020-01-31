#ifndef _TIMER_H_
#define _TIMER_H_

#include "stm32l476xx.h"
#include "stdVars.h"

typedef int bool;
#define true 1
#define false 0

void timerInit(void);
void timerEN(bool);
int getCapturedTime(void);
int getTimeCounter(void);
int getStatus(void);
void resetTimer(void);
void clearTimeCaptureReg(void);
void clearCaptureFlag(void); 
int* getBins(void);
int getBinVal(int);
#endif
