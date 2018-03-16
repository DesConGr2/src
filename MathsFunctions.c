#include "stm32f4xx.h"                  		// Device header
#include "ADC.h"

//-------------------Code format---------------------------//
//	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
//	double returnVal = (double)value * (Total range / 4096.0f) - Offset; 
//	return returnVal;
//---------------------------------------------------------//

double range12(void){
	
	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
	//
	double returnVal = (double)value * (24.0f / 4096.0f) - 12; 
	return returnVal;
}

double range1(void){
	
	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
	double returnVal = (double)value * (2.0f / 4096.0f) - 1; 
	return returnVal;
}

double range100m(void){
	
	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
	double returnVal = (double)value * (0.2f / 4096.0f) - 0.1f; 
	return returnVal;
}

double range1m(void){
	
	
	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
	double returnVal = (double)value * (0.002f / 4096.0f) - 0.001f; 
	return returnVal;
}