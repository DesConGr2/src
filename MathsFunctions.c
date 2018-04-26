#include "stm32f4xx.h"                  		// Device header
#include "ADC.h"

//-------------------Code format---------------------------//
//	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
//	double returnVal = (double)value * (Total range / 4096.0f) - Offset; 
//	return returnVal;
//---------------------------------------------------------//

double range1m(uint32_t ADCValue){
	
//	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
	double voltPerBit = 3.318f / 4096.0f;
	double bitsIn3V = 3.0f / voltPerBit;
	//double retVal = (double)ADCValue * (0.002f / bitsIn3V) - 0.001f; 
	double retVal = ((((double)ADCValue * voltPerBit) - 1.613) / (0.1513)) * 1000.0;
	
	return retVal;
}

double range10m(uint32_t ADCValue){
	
//	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
	double voltPerBit = 3.34f / 4096.0f;
	double bitsIn3V = 3.0f / voltPerBit;
	//double retVal = ADCValue * (0.02f / bitsIn3V) - 0.01f; 
	double retVal = ((((double)ADCValue * voltPerBit) - 1.625) / (151.703)) * 1000.0;
	
	return retVal;
}


double range100m(uint32_t ADCValue){
	
//	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
	double voltPerBit = 3.318f / 4096.0f;
	double bitsIn3V = 3.0f / voltPerBit;
	//double retVal = ADCValue * (0.2f / bitsIn3V) - 0.1f; 
	double retVal = ((((double)ADCValue * voltPerBit) - 1.614) / (15.1634)) * 1000.0;
	
	return retVal;
}

double range1(uint32_t ADCValue){
	
	//uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
	// 3.354 Accurate MAX
	// 3V == +1V
	// 0V == -1V
	double voltPerBit = 3.318f / 4096.0f;
	double bitsIn3V = 3.0f / voltPerBit;

	//double retVal = (ADCValue * (2.0f / bitsIn3V)) - 1.0f; 
	double retVal = (((double)ADCValue * voltPerBit) - 1.613) / (1.5103);
	return retVal;
}

double range10(uint32_t ADCValue){
	
//	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
//	//
	double voltPerBit = 3.312f / 4096.0f;
	double bitsIn3V = 3.0f / voltPerBit;
	//double retVal = (ADCValue * (20.0f / bitsIn3V) - 10.0f) - 1.0; 
	
	double retVal = (((double)ADCValue * voltPerBit) - 1.613) / (0.1513);
	
	return retVal;
}



double currentRange1m(uint32_t ADCValue){
	
//	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
	double voltPerBit = 3.34f / 4096.0f;
	double bitsIn3V = 3.0f / voltPerBit;
	//double retVal = ADCValue * (0.02f / bitsIn3V) - 0.01f; 
	//double retVal = ((((double)ADCValue * voltPerBit) - 1.625) / (151.703)) * 100.0;
	
	//double retVal = ((((((double)ADCValue * voltPerBit) - 0.0022) / 13.6949) - 1.625) / 151.703) * 1000.0;
	double retVal = ((((((double)ADCValue * voltPerBit) - 1.625) / 151.703) - 0.0022) / 13.6949) * 1000.0;
	
	
	return retVal;
}


double currentRange10m(uint32_t ADCValue){
	
//	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
	double voltPerBit = 3.318f / 4096.0f;
	double bitsIn3V = 3.0f / voltPerBit;
	//double retVal = ADCValue * (0.2f / bitsIn3V) - 0.1f; 
	//double retVal = ((((double)ADCValue * voltPerBit) - 1.614) / (15.1634)) * 100.0;
	//double retVal = ((((((double)ADCValue * voltPerBit) - 0.002) / 11.241) - 1.614) / 15.1634) * 1000.0;
	double retVal = ((((((double)ADCValue * voltPerBit) - 1.614) / 15.1634) - 0.002) / 11.241) * 1000.0;
	
	return retVal;
}

double currentRange100m(uint32_t ADCValue){
	
	//uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
	// 3.354 Accurate MAX
	// 3V == +1V
	// 0V == -1V
	double voltPerBit = 3.318f / 4096.0f;
	double bitsIn3V = 3.0f / voltPerBit;

	//double retVal = (ADCValue * (2.0f / bitsIn3V)) - 1.0f; 
	//double retVal = ((((double)ADCValue * voltPerBit) - 1.613) / (1.5103)) * 100.0;
	//double retVal = ((((((double)ADCValue * voltPerBit) - 0.0019) / 11.068) - 1.613) / 1.5103) * 1000.0;
	double retVal = ((((((double)ADCValue * voltPerBit) - 1.613) / 1.5103) - 0.0019) / 11.068) * 1000.0;
	
	return retVal;
}

double currentRange1(uint32_t ADCValue){
	
//	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
//	//
	double voltPerBit = 3.312f / 4096.0f;
	double bitsIn3V = 3.0f / voltPerBit;
	//double retVal = (ADCValue * (20.0f / bitsIn3V) - 10.0f) - 1.0; 
	
	//double retVal = ((((double)ADCValue * voltPerBit) - 1.613) / (0.1513)) / 10.0;
	//double retVal = ((((((double)ADCValue * voltPerBit) - 0.002) / 11.21) - 1.613) / 0.1513);
	double retVal = ((((((double)ADCValue * voltPerBit) - 1.613) / 0.1513) - 0.0002) / 11.21);
	
	return retVal;
}

double resistanceRange1k(uint32_t ADCValue) {
	double voltPerBit = 3.312f / 4096.0f;
	double bitsIn3V = 3.0f / voltPerBit;
	
	//double retVal = ((((double)ADCValue * voltPerBit) - (-0.029286)) / 0.0021069);
	double retVal = ((((((double)ADCValue * voltPerBit) - 1.613) / (0.1513)) - (-0.029286)) / 0.0021069);
	
	return retVal;
}
double resistanceRange5k(uint32_t ADCValue) {

}
double resistanceRange10k(uint32_t ADCValue) {
	double voltPerBit = 3.312f / 4096.0f;
	double bitsIn3V = 3.0f / voltPerBit;
	
	//double retVal = ((((double)ADCValue * voltPerBit) - (0.08)) / 0.000264);
	double retVal = ((((((double)ADCValue * voltPerBit) - 1.613) / (0.1513)) -  (0.08)) / 0.000264);
	
	return retVal;
}
double resistanceRange50k(uint32_t ADCValue) {

}
double resistanceRange100k(uint32_t ADCValue) {
	double voltPerBit = 3.312f / 4096.0f;
	double bitsIn3V = 3.0f / voltPerBit;
	
	//double retVal = ((((double)ADCValue * voltPerBit) - (0.165)) / 0.0000238);
	double retVal = ((((((double)ADCValue * voltPerBit) - 1.613) / (0.1513)) -  (0.165)) / 0.0000238);
	
	return retVal;
}
// CAN BE FITTED TO LINEAR BUT IS NOT ACCURATE
double resistanceRange500k(uint32_t ADCValue) {
	double voltPerBit = 3.312f / 4096.0f;
	double bitsIn3V = 3.0f / voltPerBit;
	
	//double retVal = ((((double)ADCValue * voltPerBit) - (0.19272)) / 0.0000034903);
	double retVal = ((((((double)ADCValue * voltPerBit) - 1.613) / (0.1513)) -  (0.19272)) / 0.0000034903);
	
	return retVal;
}
double resistanceRange1M(uint32_t ADCValue) {
	double voltPerBit = 3.312f / 4096.0f;
	double bitsIn3V = 3.0f / voltPerBit;
	
	//double retVal = ((((double)ADCValue * voltPerBit) - (0.49)) / 0.0000009);
	double retVal = ((((((double)ADCValue * voltPerBit) - 1.613) / (0.1513)) -  (0.49)) / 0.0000009);
	
	
	return retVal;
}	

//double testRange(void){
//	uint32_t value = ADC1value(); 												/* Gets a 12 bit right-aligned value from the ADC */
//	//
//	double voltPerBit = 3.354f / 4096.0f;
//	//double bitsIn3V = 3.0f / voltPerBit;
//	double returnVal = (double)value * voltPerBit; 
//	return returnVal;
//}

