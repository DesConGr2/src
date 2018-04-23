#include "STM32F4xx.h"
#include "freqCalc.h"
#include "digitalIO.h"
#include <stdlib.h>

// TODO: rename
typedef struct FreqVals {
	int lastReadVal;
	int hasStartedTiming;
	double timerCount;
	double averages[10];
} FreqVals;

FreqVals *vals;

void initFreqCalc(void) {
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	// SET J6 pin 6 to the alternate function
	GPIOC->AFR[0] &= 0x0 << (4 * 6);
	GPIOC->AFR[0] |= 0x1 << (4 * 6);
	
	TIM1->CCMR1 &= 00;
	TIM1->CCMR1 |= 01;
	
	// Setting to 0, activate on rising edge
	TIM1->CCER &= 0 << 1;
	TIM1->CCER &= 0 << 3;
	
	TIM1->CCMR1 &= 00 << 8;
	TIM1->CCMR1 |= 01 << 8;
	
	// Setting to 1, activate on falling edge
	TIM1->CCER |= 1 << 5;
	TIM1->CCER |= 1 << 7;
	
	TIM1->SMCR &= 000 << 4;
	TIM1->SMCR |= 101 << 4;
	
	TIM1->SMCR &= 000;
	TIM1->SMCR |= 100;
	
	TIM1->CCER |= 1;
	TIM1->CCER |= 1 << 4;
	
	
	
	
	
	
//	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; 
//	TIM2->ARR     = 840;        // Auto Reload Register value => 1ms
//  //TIM2->ARR     = 84000000;        
//	TIM2->DIER   |= 0x0001;       // DMA/IRQ Enable Register - enable IRQ on update
//  TIM2->CR1    |= 0x0001;       // Enable Counting
//	
//	NVIC_EnableIRQ(TIM2_IRQn);    // Enable IRQ for TIM2 in NVIC
//	
	vals = malloc(sizeof(FreqVals));
	
	vals->hasStartedTiming = 0;
	vals->lastReadVal = 0;
	vals->timerCount = 0;
	
	vals->averages[0] = 0.0;
	vals->averages[1] = 0.0;
	vals->averages[2] = 0.0;
	vals->averages[3] = 0.0;
	vals->averages[4] = 0.0;
	vals->averages[5] = 0.0;
	vals->averages[6] = 0.0;
	vals->averages[7] = 0.0;
	vals->averages[8] = 0.0;
	vals->averages[9] = 0.0;
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
										vals->averages[4] +
										vals->averages[5] +
										vals->averages[6] +
										vals->averages[7] +
										vals->averages[8] +
										vals->averages[9]) / 10.0f;
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
	int rdVal = readPin(13);
	
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
			//calculatedFreq *= 0.8f;
	
			for(int i = 0; i < 10; i++) {				
				if(i != 9) {
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
