#include "DAC.h"
#include "STM32F4xx.h"

void initDAC(void) {
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;
	
	DAC1->CR |= DAC_CR_EN1;
	DAC1->CR |= DAC_CR_BOFF1;
	
	DAC1->DHR12R1 |= 0xac6;
}

void setDAC(double voltage) {
	
}
