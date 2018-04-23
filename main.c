#include <stdio.h>
#include <stdlib.h>
#include "STM32F4xx.h"
#include "ADC.h"
#include "digitalIO.h"
#include "lcdDisplay.h"
#include "sound_response.h"
#include "freqCalc.h"
#include "UI.h"
#include "serial_comms.h"
#include "DAC.h"

int main (void) {
	initDigitalIO();
	// TODO: change to 'initADC1()' to be consistent with the other naming
	ADC1Init();
	initUI();
	initDAC();
	
//	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
//	TIM1->PSC = 1;
//	// SET GPIOE pin 9 to the alternate function
//	//GPIOE->MODER &= 00 << (2 * 9);
//	GPIOE->MODER &= 0xFFF3FFFF;
//	//GPIOE->MODER |= 10 << (2 * 9);
//	GPIOE->MODER |= 1 << 19;
//	
//	//GPIOE->AFR[1] &= 0x0 << (4 * 1);
//	GPIOE->AFR[1] &= 0xFFFFFF0F;
//	GPIOE->AFR[1] |= 0x1 << (4 * 1);
//	
//	//TIM1->CCMR1 &= 00;
//	TIM1->CCMR1 &= 0xFFFFFFFC;
//	TIM1->CCMR1 |= 01;
//	
//	// Setting to 0, activate on rising edge
////	TIM1->CCER &= 0 << 1;
////	TIM1->CCER &= 0 << 3;
//	TIM1->CCER &= 0xFFFFFFFD;
//	TIM1->CCER &= 0xFFFFFFF7;
//	
//	//TIM1->CCMR1 &= 00 << 8;
//	TIM1->CCMR1 &= 0xFFFFFCFF;
//	TIM1->CCMR1 |= 1 << 9;
//	
//	// Setting to 1, activate on falling edge
//	TIM1->CCER |= 1 << 5;
//	TIM1->CCER |= 1 << 7;
//	
//	//TIM1->SMCR &= 000 << 4;
//	TIM1->SMCR &= 0xFFFFFF8F;
//	//TIM1->SMCR |= 101 << 4;
//	TIM1->SMCR |= 0x00000050;
//	
//	//TIM1->SMCR &= 000;
//	TIM1->SMCR &= 0xFFFFFFF8;
//	//TIM1->SMCR |= 100;
//	TIM1->SMCR |= 0x4;
//	
//	TIM1->CCER |= 1;
//	TIM1->CCER |= 1 << 4;
	
	while(1) {
		 //displayReading(TIM1->CCR1);
	}
		
}








