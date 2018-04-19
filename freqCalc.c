#include "STM32F4xx.h"
#include "freqCalc.h"
#include "digitalIO.h"
#include <stdlib.h>

// TODO: rename
typedef struct FreqVals {
	int lastReadVal;
	int hasStartedTiming;
	double timerCount;
	double averages[5];
} FreqVals;

FreqVals *vals;

void initFreqCalc(void) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; 
	TIM2->ARR     = 84;        // Auto Reload Register value => 1ms
  //TIM2->ARR     = 84000000;        
	TIM2->DIER   |= 0x0001;       // DMA/IRQ Enable Register - enable IRQ on update
  TIM2->CR1    |= 0x0001;       // Enable Counting
	
	NVIC_EnableIRQ(TIM2_IRQn);    // Enable IRQ for TIM2 in NVIC
	
	vals = malloc(sizeof(FreqVals));
	
	vals->hasStartedTiming = 0;
	vals->lastReadVal = 0;
	vals->timerCount = 0;
	
	vals->averages[0] = 0.0;
	vals->averages[1] = 0.0;
	vals->averages[2] = 0.0;
	vals->averages[3] = 0.0;
	vals->averages[4] = 0.0;
}

double getFrequency() {
	double freq = 1.0f / (vals->timerCount);
	return freq;
}

double getAveragedFrequency() {
	double avgFreq = (vals->averages[0] +
										vals->averages[1] +
										vals->averages[2] +
										vals->averages[3] +
										vals->averages[4]) / 5.0f;
	return avgFreq;
}

double getPeriod() {
	//return (vals->timerCount / 1000000.0f);
	return (vals->timerCount);
}

void startFreqCalc(void) {
	TIM2->CR1 |= 0x0001;       // Enable Counting
}

void stopFreqCalc(void) {
	TIM2->CR1 &= ~0x0001;       // Disable Counting
}

void TIM2_IRQHandler(void) {
	TIM2->SR &= ~TIM_SR_UIF;      // clear IRQ flag in TIM2
	//vals->timerCount += (8400 / 1000000.0f);
	//vals->timerCount += (TIM2->ARR / 84000000.0f);
	int rdVal = readPin(15);
	
	if(!((rdVal == 0) && (vals->lastReadVal == 1))) {
		//vals->timerCount += (((float)TIM2->CNT + (float)TIM2->ARR) / 84000000.0f);
		vals->timerCount += (((float)TIM2->ARR) / 84000000.0f);
	} else {
		if(vals->hasStartedTiming == 0) {
			vals->hasStartedTiming = 1;
			vals->timerCount = 0.0f;
		} else {
			vals->hasStartedTiming = 0;
			double calculatedFreq = 1.0 / vals->timerCount;
			
			// BODGE: times the value by 0.8 to get a closer to accurate value ;(
			calculatedFreq *= 0.8f;
	
			for(int i = 0; i < 5; i++) {				
				if(i != 4) {
					vals->averages[i] = vals->averages[i+1];
				} else {
					vals->averages[i] = calculatedFreq;
				}
			}
		}
	}
	// Look for falling edge
//	if((rdVal == 0) && (vals->lastReadVal == 1)) {
//		if(vals->hasStartedTiming == 0) {
//			vals->hasStartedTiming = 1;
//			vals->timerCount = 0.0f;
//		} else {
//			vals->hasStartedTiming = 0;
//			double calculatedFreq = 1.0 / vals->timerCount;
//	
//			for(int i = 0; i < 5; i++) {				
//				if(i != 4) {
//					vals->averages[i] = vals->averages[i+1];
//				} else {
//					vals->averages[i] = calculatedFreq;
//				}
//			}
//		}
//	} else {
//		if(vals->hasStartedTiming == 1) {
//			//vals->timerCount++;
//			
//			vals->timerCount += (((float)TIM2->CNT + (float)TIM2->ARR) / 84000000.0f);
//			//vals->timerCount += (((float)TIM2->ARR) / 84000000.0f);
//		}
//	}
	
	vals->lastReadVal = rdVal;
}
