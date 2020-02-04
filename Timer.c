#include "Timer.h"
#include "UART.h"
#include "string.h"
int bins[101];
int oldtimerVal = 0;


void timerInit(void) {
		iter = 1000;
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
    TIM2->PSC |= 0x4F;               // Loading the value 79 into prescaler reg
    TIM2->EGR |= TIM_EGR_UG;         // Update prescale
    TIM2->CCER &= ~TIM_CCER_CC1E;    // Turn Off Timer
		TIM2->CCMR1 &= ~TIM_CCMR1_IC1F;		// Turn off filter
    TIM2->CCMR1 |= (TIM_CCMR1_CC1S_0); // Sets TIM_CH1 to TI1
    // Setting input capture mode to start on rising	
    TIM2->CCER &= ~(TIM_CCER_CC1NP + TIM_CCER_CC1P);
		TIM2->CCER |= TIM_CCER_CC1E;
}

void timerIEN(bool val){
	if (val)	
		TIM2->DIER |= TIM_DIER_CC1IE; // Interrupt Enable
	else
		TIM2->DIER &= ~TIM_DIER_CC1IE; // Interrupt Enable
}

void timerEN(bool val)
{
    if (val) {
        TIM2->CR1 |= TIM_CR1_CEN;
				NVIC_SetPriority(TIM2_IRQn, 0);
				NVIC_EnableIRQ(TIM2_IRQn);
		}
    else
		{
        TIM2->CR1 &= ~TIM_CR1_CEN;
				NVIC_DisableIRQ(TIM2_IRQn);
		}
}



int* getBins(void) {
	return bins;
}

int getBinVal(int i) {
	return bins[i];
}

int getCapturedTime(void) {
		return TIM2->CCR1;
}

int getStatus(void) {
	return TIM2->SR & TIM_SR_CC1IF;
}

int getTimeCounter(void) {
	return TIM2->CNT;
}

void TIM2_IRQHandler(void) {
	int newtimerVal = TIM2->CCR1; // Read from register which auto resets ISR Flag
	int timerVal =  newtimerVal - oldtimerVal;
	oldtimerVal = newtimerVal;
	if (timerVal - lower_limit >= 0 && timerVal - lower_limit <= 100)
		bins[timerVal - lower_limit]++;
	if (iter) iter--;
	else {
		timerEN(0);
		done = 1;
	}
}
