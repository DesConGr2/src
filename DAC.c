#include "DAC.h"
#include "STM32F4xx.h"

void initDAC(void) {
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;
	
	DAC1->CR |= DAC_CR_EN1;
	DAC1->CR |= DAC_CR_BOFF1;
	

}

void setDAC(double voltage) {
	int DACVoltage = 0;
	
	// 2.97V is 0xfff out
	if(voltage <= 2.97) {
			DACVoltage = (4095.0 / 2.97) * voltage;
	}	
	
	DAC1->DHR12R1 |= DACVoltage;
	
		//DAC1->DHR12R1 |= 0xfff;
}
