#include "stm32f4xx.h"                  		// Device header
#include "ADC.h"

// ADC functions taken from "ADC_LEDs K5" on the module webpage

/* Function to intiialise ADC1    */
void ADC1Init(void) {
	/* Enable clocks */
	RCC->APB2ENR  |= RCC_APB2ENR_ADC1EN;
	RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOCEN;
	
	/* ADC12_IN14 is the channel we shall use. It is connected to 
	 * PC4 which is connected to the board edge connectors */
	GPIOC->MODER = 0x3 << (2 * 4);
	GPIOC->PUPDR = 0;
	
	/* Set ADC to discontinuous conversion mode. */
	ADC1->CR1 = 0x00;
	ADC1->CR1 |= ADC_CR1_DISCEN;
	
	/* Ensure CR2 is set to zero. This means data will be right aligned, 
	 * DMA is disabled and there are no extrnal triggers/injected channels */
	ADC1->CR2 = 0x00;
	
	/* Set to one conversion at a time, and set that first conversion 
	 * to come from channel 14 (connected to PC4) */
	ADC1->SQR1 &= ~ADC_SQR1_L;
	ADC1->SQR3 = 14 & ADC_SQR3_SQ1;
	
	/* Enable the ADC */
	ADC1->CR2 |= ADC_CR2_ADON;
}
	
/* function to read ADC and retun value */
uint32_t ADC1value (void) {
	/* set SWSTART to 1 to start conversion */
	ADC1->CR2 |= ADC_CR2_SWSTART;
	
	/* Wait until End Of Conversion bit goes high */
	while (!(ADC1->SR & ADC_SR_EOC));
	
	/* Return data value */
	return (ADC1->DR);
}

// double readADC1(void) {
//	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
//	double returnVal = (double)value * (3.3f / 4096.0f); 
//	return returnVal;
//}
	

/* Function to intiialise ADC2    */

void ADC2Init(void) {
	/* Enable clocks */
	RCC->APB2ENR  |= RCC_APB2ENR_ADC2EN;
	RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOCEN;
	
	/* ADC12_IN15 is the channel we shall use. It is connected to 
	 * PC5 which is connected to the board edge connectors */
	GPIOC->MODER = 0x3 << (2 * 5);
	GPIOC->PUPDR = 0;
	
	/* Set ADC to discontinuous conversion mode. */
	ADC2->CR1 = 0x00;
	ADC2->CR1 |= ADC_CR1_DISCEN;
	
	/* Ensure CR2 is set to zero. This means data will be right aligned, 
	 * DMA is disabled and there are no extrnal triggers/injected channels */
	ADC2->CR2 = 0x11;
	
	/* Set to one conversion at a time, and set that first conversion 
	 * to come from channel 15 (connected to PC5) */
	ADC2->SQR1 &= ~ADC_SQR1_L;
	ADC2->SQR3 = 15 & ADC_SQR3_SQ1;
	
	/* Enable the ADC */
	ADC2->CR2 |= ADC_CR2_ADON;
}
	
/* function to read ADC and retun value */
uint32_t ADC2value (void) {
	/* set SWSTART to 1 to start conversion */
	ADC2->CR2 |= ADC_CR2_SWSTART;
	
	/* Wait until End Of Conversion bit goes high */
	while (!(ADC2->SR & ADC_SR_EOC));
	
	/* Return data value */
	return (ADC2->DR);
}

// double readADC2(void) {
//	uint32_t value = ADC2value(); 												/* Gets a 12 bit right-aligned value from the ADC */
//	double returnVal = (double)value * (3.3f / 4096.0f); 
//	return returnVal;
//}

