#include "STM32F4xx.h"
#include "freqCalc.h"
#include "digitalIO.h"
#include <stdlib.h>

//double getFreq(void) {
//}
MeasurementVals *vals;

void initFreqCalc(MeasurementVals *valsIn) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; 
	TIM2->ARR     = 8400;        // Auto Reload Register value => 1ms
  TIM2->DIER   |= 0x0001;       // DMA/IRQ Enable Register - enable IRQ on update
  TIM2->CR1    |= 0x0001;       // Enable Counting
	
	NVIC_EnableIRQ(TIM2_IRQn);    // Enable IRQ for TIM2 in NVIC
	
	vals = valsIn;
	
	vals->hasStartedTiming = 0;
	vals->lastReadVal = 0;
	vals->timerCount = 0;
}

void startFreqCalc(void) {
	TIM2->CR1 |= 0x0001;       // Enable Counting
}

void stopFreqCalc(void) {
	TIM2->CR1 &= ~0x0001;       // Disable Counting
}

void TIM2_IRQHandler(void) {
	TIM2->SR &= ~TIM_SR_UIF;      // clear IRQ flag in TIM2
	vals->timerCount++;
	int rdVal = readPin(15);
	
	if((rdVal == 1) && (vals->lastReadVal == 0)) {
		if(vals->hasStartedTiming == 0) {
			vals->hasStartedTiming = 1;
			vals->timerCount = 0;
		} else {
			vals->hasStartedTiming = 0;
			double freq = 1.0f / (vals->timerCount / 10000.0f);
			//displayReading(freq);
		}
	} else {
		if(vals->hasStartedTiming == 1) {
			vals->timerCount++;
		}
	}
	
	vals->lastReadVal = rdVal;
}
