#include "stm32f4xx.h"                  		// Device header
#include "ADC.h"

double returnValue; 

//-------------------Code format---------------------------//
//	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
//	double returnVal = (double)value * (Total range / 4096.0f) - Offset; 
//	return returnVal;
//---------------------------------------------------------//

double range12(double ADCvalue){
	
//	returnValue = (8*ADCvalue) - 12;

//	return(returnValue);
	
	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
	double returnVal = (double)value * (24.0f / 4096.0f) - 12; 
	return returnVal;
}

double range1(double ADCvalue){
	
//	returnValue = (0.66666666666667*ADCvalue) - 1;

//	return(returnValue);
	
		uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
	double returnVal = (double)value * (2.0f / 4096.0f) - 1; 
	return returnVal;
}

double range100m(double ADCvalue){
	
//	returnValue = (66.66666666666667*ADCvalue) - 100;

//	return(returnValue);
	
	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
	double returnVal = (double)value * (0.2f / 4096.0f) - 0.1f; 
	return returnVal;
}

double range1m(double ADCvalue){
	
	returnValue = (0.66666666666667*ADCvalue) - 1;

	return(returnValue);
}