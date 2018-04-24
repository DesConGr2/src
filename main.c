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
<<<<<<< HEAD

//void SysTick_Handler(void);
//// Delays number of tick Syst icks (happens every 1 ms)
//void Delay(uint32_t dlyTicks);
=======
>>>>>>> fe4522e522cf09d5f0037212e63f9f2aacfe281e

int main (void) {
	initDigitalIO();
	// TODO: change to 'initADC1()' to be consistent with the other naming
	ADC1Init();
	initUI();
<<<<<<< HEAD
	
	initDAC();
	
	//setDAC(1.0);
	//initDisplay();
	//CommsInit();
	
	// Do DAC things
//	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
//RCC->APB1ENR |= RCC_APB1ENR_DACEN;
//	
	// DONT NEED TO ADJUST GPIOA, ITS ALREADY BEING SETUP IN THE DISPLAY CODE
//	// Set the DAC1 pin to analog mode
//	//GPIOA->MODER = 0x3 << (2 * 4);
//	// Disable terminating resistors
//	GPIOA->PUPDR = 0;
//	
	//DAC1->CR |= DAC_CR_EN1;
	//DAC1->CR |= DAC_CR_BOFF1;
//	
	//DAC1->DHR12R1 |= 0xfff;
	
	
	
	
	
	
	
	//initFreqCalc();

	//Wlecome message (tests screen)
	//turnBuzzerOn();
	//displayType("Welcome!");
	//Delay(1000);
  //displayClear();
	//turnBuzzerOff();
=======
	initDAC();
>>>>>>> fe4522e522cf09d5f0037212e63f9f2aacfe281e
	
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








