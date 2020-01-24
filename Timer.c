#include "Timer.h"

void timerInit()
{
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
    TIM2->PSC |= 0x4F;               // Loading the value 79 into prescaler reg
    TIM2->EGR |= TIM_EGR_UG;         // Update prescale
    TIM2->CCER &= ~TIM_CCER_CC1E;    // Turn Off Timer
    TIM2->CCMR1 |= TIM_CCMR1_CC1S_0; // Sets TIM_CH1 to TI1

    // Setting input capture mode to start on rising
    TIM2->CCER &= ~(TIM_CCER_CC1NP + TIM_CCER_CC1P);

    TIM2->DIER |= TIM_DIER_CC1IE;
}

void timerEN(bool val)
{
    if (val)
        TIM2->CCER |= TIM_CCER_CC1E;
    else
        TIM2->CCER &= ~TIM_CCER_CC1E;
}