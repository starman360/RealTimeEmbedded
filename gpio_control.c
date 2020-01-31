#include "stm32l476xx.h"
#include "gpio_control.h"

void init_pa0(void) {
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;        // enable clock for A group of GPIO
    GPIOA->MODER &= ~0x3;                       // clear out bits 0 and 1 for pa0
    GPIOA->MODER |= 0x2;                        // enable alternate function mode for pa0
    GPIOA->AFR[0] |= 0x1;                       // enable pa0 alternate function 1
    /* 
    GPIOA->PUPDR &= ~0x3;                       // clear out bits 0 and 1 for pa0
    GPIOA->PUPDR |= 0x2;                        // set pa0 as pull-down
    */
}
