#include "STM32F4xx.h"
#include "freqCalc.h"
#include "digitalIO.h"

struct measurmentData {
	
};

void initFreqCalc() {
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; 
	NVIC_EnableIRQ(TIM2_IRQn);    // Enable IRQ for TIM2 in NVIC
	
	//TIM2->ARR     = 0;        // Auto Reload Register value => 1ms
  TIM2->DIER   |= 0x0001;       // DMA/IRQ Enable Register - enable IRQ on update
  //TIM2->CR1    |= 0x0001;       // Enable Counting
}

void startFreqCalc() {
	TIM2->CNT = 0;
	TIM2->CR1 |= 0x0001;       // Enable Counting
}

void stopFreqCalc() {
	TIM2->CR1 &= ~0x0001;       // Disable Counting
}

void TIM2_IRQHandler(void) {
	static int lastVal = 0;
	// 0 for not started, 1 for started
	static int hasStartedTiming = 0; 
	TIM2->SR &= ~0x00000001;      // clear IRQ flag in TIM2
	// Read from J5 pin 3 every tick of the timer
	int val = readPin(4);
	
	if((val == 1) && (lastVal == 0)) {
		// Start timing OR End timing if timing had already been started
		if(hasStartedTiming == 0) {
			TIM2->CR1 |= 0x0001;       // Enable Counting
			hasStartedTiming = 1;
		} else {
			TIM2->CR1 &= ~0x0001;       // Disable Counting
			// Set the variable in some data structure to be the count
			//? = TIM2->CNT
		}
	}
	lastVal = val;
}