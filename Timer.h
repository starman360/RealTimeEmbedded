#ifndef _TIMER_H_
#define _TIMER_H_

#include "stm32l476xx.h"

typedef int bool;
#define true 1
#define false 0

void timerInit();
void timerEN(bool);

#endif