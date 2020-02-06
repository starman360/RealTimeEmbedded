#ifndef _TIMER_H_
#define _TIMER_H_

#include "stm32l476xx.h"
#include "stdVars.h"

void timer_Init(void);
void timer_IEN(bool val);
void timer_EN(bool);
int* get_bins(void);
int get_bin_val(int);
int get_captured_time(void);
int get_status(void);
int get_time_counter(void);
void reset_timer(void);

#endif
