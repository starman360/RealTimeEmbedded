#include "Timer.h"

int bins[101];
int iter = 0;

void timerInit()
{
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;       // enable clock to timer 2
    TIM2->PSC |= 80;                            // Loading the value 79 into prescaler reg
    // Event Generation Register
    TIM2->EGR |= TIM_EGR_UG;                    // Force update prescale

    // Capture Compare Enable Register
    TIM2->CCER &= ~TIM_CCER_CC1E;               // Turn off timer
    // Capture Compare Mode Register
    TIM2->CCMR1 &= ~TIM_CCMR1_CC1S;             // Clear capture/compare 1 selection bits
    TIM2->CCMR1 |= TIM_CCMR1_CC1S_0;            // Sets TIM_CH1 to TI1
    
    TIM2->CCER &= ~TIM_CCER_CC1P;               // Input capture rising edges               
    TIM2->CCER |= TIM_CCER_CC1E;                // Enable capture for channel 1
    


    // TIM2->DIER |= TIM_DIER_CC1IE; // Interrupt Enable
	// iter = 1000;
}


void timerEN(bool val)
{
    if (val)
        TIM2->CR1 |= TIM_CR1_CEN;    // start count
    else
        TIM2->CR1 &= ~TIM_CR1_CEN;    // stop count
}

int getCapturedTime() {
    // capture/compare register 1
    // this will clear the CC1IF flag in the SR
    return TIM2->CCR1;
}

int getTimeCounter() {
    return TIM2->CNT;
}

int getStatus() {
    // status register
    // CC1IF - capture/compare 1 interrupt flag
    if (TIM2->SR & TIM_SR_CC1IF) {
        return 0;
    }
    return 1;
}

void resetTimer(){
    RCC->APB1RSTR1 &= ~(0x1);
}
void clearTimeCaptureReg() {
    TIM2->CCR1 = 0;
}

void TIM2_IRQHandler(void) {
	int timerVal = TIM2->CCR1; // Read from register which auto resets ISR Flag
	if (timerVal - lower_limit >= 0 && timerVal - lower_limit <= 100)
		bins[timerVal - lower_limit]++;
	if (iter) iter--;
	else timerEN(0);
}

int* getBins(void) {
	return bins;
}

int getBinVal(int i) {
	return bins[i];
}
