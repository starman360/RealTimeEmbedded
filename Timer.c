#include "Timer.h"
#include "UART.h"
#include "string.h"

void timer_Init(void) {
	
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;
	TIM3->PSC |= 0x9E; // 2us
	//TIM3->PSC |= 0x13C; // 2us
	
	TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // ch1
	TIM3->CCMR1 |= TIM_CCMR1_OC1PE; //ch1 preload enable
	TIM3->CR1 = TIM_CR1_ARPE; // auto reload
	
	TIM3->CCER |= TIM_CCER_CC1E; // ch1 enable output
	
	TIM3->ARR = 0xC350; // 50000 *2us = 100ms
	
	TIM3->EGR |= TIM_EGR_UG;
	
	TIM3->CR1 |= TIM_CR1_CEN;
}

void timer_IEN(bool val){
	if (val)	
		TIM3->DIER |= TIM_DIER_CC1IE; // Interrupt Enable
	else
		TIM3->DIER &= ~TIM_DIER_CC1IE; // Interrupt Enable
}

void timer_EN(bool val)
{
	timer_IEN(1);
    if (val) {
        TIM3->CR1 |= TIM_CR1_CEN;
				NVIC_EnableIRQ(TIM3_IRQn);
		}
    else
		{
        TIM3->CR1 &= ~TIM_CR1_CEN;
				NVIC_DisableIRQ(TIM3_IRQn);
		}
}


int get_captured_time(void) {
		return TIM3->CCR1;
}

int get_status(void) {
	return TIM3->SR & TIM_SR_CC1IF;
}

int get_time_counter(void) {
	return TIM3->CNT;
}

void TIM3_IRQHandler(void) {
	TIM3->SR &= ~(0x2);
	timerFlag = 1;
}
