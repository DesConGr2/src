#include "stm32f4xx.h"                  		// Device header
#include "ADC.h"

//-------------------Code format---------------------------//
//	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
//	double returnVal = (double)value * (Total range / 4096.0f) - Offset; 
//	return returnVal;
//---------------------------------------------------------//

double range1m(void){
	
	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
	double voltPerBit = 3.354f / 4096.0f;
	double bitsIn3V = 3.0f / voltPerBit;
	double returnVal = (double)value * (0.002f / bitsIn3V) - 0.001f; 
	return returnVal;
}

double range10m(void){
	
	
	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
	double voltPerBit = 3.354f / 4096.0f;
	double bitsIn3V = 3.0f / voltPerBit;
	double returnVal = (double)value * (0.02f / bitsIn3V) - 0.01f; 
	return returnVal;
}


double range100m(void){
	
	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
	double voltPerBit = 3.354f / 4096.0f;
	double bitsIn3V = 3.0f / voltPerBit;
	double returnVal = (double)value * (0.2f / bitsIn3V) - 0.1f; 
	return returnVal;
}

double range1(void){
	
	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
	// 3.354 Accurate MAX
	// 3V == +1V
	// 0V == -1V
	double voltPerBit = 3.354f / 4096.0f;
	double bitsIn3V = 3.0f / voltPerBit;
	
	double returnVal = ((double)value * (2.0f / bitsIn3V)) - 1.0f; 
	return returnVal;
}

double range10(void){
	
	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
	//
	double voltPerBit = 3.354f / 4096.0f;
	double bitsIn3V = 3.0f / voltPerBit;
	double returnVal = (double)value * (20.0f / bitsIn3V) - 10.0f; 
	return returnVal;
}

double testRange(void){
	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
	//
	double voltPerBit = 3.354f / 4096.0f;
	//double bitsIn3V = 3.0f / voltPerBit;
	double returnVal = (double)value * voltPerBit; 
	return returnVal;
}
