#ifndef TIMER_CONTROL_H
#define TIMER_CONTROL_H
#include <stdio.h>

void loop(void);
void wait_enter(void);
void print_limits(void);
void change_limits(void);
int process_buf(char *str);
void sanitize_cmd(char *str);
void append_digit(char *number, char c);
void spin_function(void);
int run_again(void);
#endif
