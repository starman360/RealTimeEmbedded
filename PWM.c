#include "PWM.h"

//USING TIMER 2
void shawn_pwn(void) {
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
	TIM2->PSC |= 0x4F;
	
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // ch1
	TIM2->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2; // ch2
	TIM2->CCMR1 |= TIM_CCMR1_OC1PE; //ch1 preload enable
	TIM2->CCMR1 |= TIM_CCMR1_OC2PE; //ch2 preload enable
	TIM2->CR1 = TIM_CR1_ARPE; // auto reload
	
	TIM2->CCER |= TIM_CCER_CC1E; // ch1 enable output
	TIM2->CCER |= TIM_CCER_CC2E; // ch2 enable output
	
	TIM2->ARR = 20000;
	TIM2->CCR1 |= 5000; // test values
	TIM2->CCR2 |= 5000; // test values
	
	TIM2->EGR |= TIM_EGR_UG;
	
	TIM2->CR1 |= TIM_CR1_CEN;
	
}

void pwm_Init(void){
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
  TIM2->PSC |= 0x4F;               // Loading the value 79 into prescaler reg
  TIM2->CCER &= ~TIM_CCER_CC1E;    // Turn Off Timer
  TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;//(0x60); // Sets to PWM mode 1
	TIM2->CCMR1 |= TIM_CCMR1_OC1PE; // Sets Preload enable
	TIM2->CR1 |= TIM_CR1_ARPE; // Auto preload enable
	TIM2->CCER &= ~TIM_CCER_CC1NP; // Active LOW
	TIM2->CCER |= TIM_CCER_CC1NE;
	TIM2->ARR &= ~0xFFFFFFFF;
	TIM2->ARR |= 0x4E20; // SET to 20ms
	//TIM2->BDTR |= TIM_BDTR_MOE;
	TIM2->EGR |= TIM_EGR_UG;         // Update
	TIM2->CCR1 |= 10000;
	TIM2->CCER |= TIM_CCER_CC1E;
	TIM2->CR1 |= TIM_CR1_CEN;
}	

/*
	Changes the position of a servo by updating the duty cycle
	val - new duty cycle value
	servo_id - controls which servo to move
*/
void pwm_Set_DC(int val, int servo_id) {
	if (servo_id == 1) {
		TIM2->CCR1 |= val;
	}
	if (servo_id == 2) {
		TIM2->CCR2 = val;
	}
	// update duty cycle 
	TIM2->EGR |= TIM_EGR_UG;    
}

void pwm_EN(bool val)
{
    if (val) {
        TIM2->CR1 |= TIM_CR1_CEN;
		}
    else
		{
        TIM2->CR1 &= ~TIM_CR1_CEN;
		}
}
int get_status(void);
void reset_timer(void);
