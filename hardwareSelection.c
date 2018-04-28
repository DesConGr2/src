#include "hardwareSelection.h"
#include "digitalIO.h"
#include "ADC.h"
#include "DAC.h"
#include "MathsFunctions.h"
#include <math.h>

void setModule(int module) {
	switch(module) {
		// Voltage
		case 0:
			setPin("J5", 4, 0);
			setPin("J5", 5, 0);
			setPin("J5", 7, 0);
		break;
		// Current
		case 1:
			setPin("J5", 4, 0);
			setPin("J5", 5, 0);
			setPin("J5", 7, 1);
		break;
		// Resistance
		case 2:
			setPin("J5", 4, 0);
			setPin("J5", 5, 1);
			setPin("J5", 7, 0);
		break;
		// Frequency
		case 3:
			setPin("J5", 15, 0);
		break;
		// Capacitance
		case 4:
			setPin("J5", 15, 1);
		break;
		// Diode
		case 6:
			setPin("J5", 4, 0);
			setPin("J5", 5, 1);
			setPin("J5", 7, 1);
		break;
		// Transistor
		case 7:
			setPin("J5", 4, 0);
			setPin("J5", 5, 1);
			setPin("J5", 7, 1);
		break;
	}
}

//NOTE (chris) : Using pins 2, 3 and 4 of J7 to output these signals, J7 pin 2 is the MSB 
//This currently isnt shown in the code since the "setPin" function takes the GPIO pin number rather than the 
//board edge connector pin number, refer to the module webpage's edge connector sheet
void setRange(int module, int range, double ADCValue) {
	switch(module) {
		// Voltage
		case 0:
			switch(range) {
				case 0:
					// 10
					setPin("J7", 3, 0);
					setPin("J7", 4, 1);
					setPin("J7", 5, 1);
				
					if(fabs(range10(ADCValue)) > 10.0) {
						setPin("J5", 8, 1);
					} else {
						setPin("J5", 8, 0);
					}
				break;
				case 1:
					// 1
					setPin("J7", 3, 0);
					setPin("J7", 4, 1);
					setPin("J7", 5, 0);
					
					if(fabs(range1(ADCValue)) > 1.0) {
						setPin("J5", 8, 1);
					} else {
						setPin("J5", 8, 0);
					}
				break;
				case 2:
					// 100m
					setPin("J7", 3, 0);
					setPin("J7", 4, 0);
					setPin("J7", 5, 1);
				
					if(fabs(range100m(ADCValue)) > 100.0) {
						setPin("J5", 8, 1);
					} else {
						setPin("J5", 8, 0);
					}
				break;
				case 3:
					// 10m
					setPin("J7", 3, 0);
					setPin("J7", 4, 0);
					setPin("J7", 5, 0);
				
					if(fabs(range10m(ADCValue)) > 10.0) {
						setPin("J5", 8, 1);
					} else {
						setPin("J5", 8, 0);
					}
				break;
				case 4:
					// 10 AC
					setPin("J7", 3, 1);
					setPin("J7", 4, 1);
					setPin("J7", 5, 1);
				
					if(fabs(range10(ADCValue)) > 10.0) {
						setPin("J5", 8, 1);
					} else {
						setPin("J5", 8, 0);
					}
				break;
				case 5:
					// 1 AC
					setPin("J7", 3, 1);
					setPin("J7", 4, 1);
					setPin("J7", 5, 0);
				
					if(fabs(range1(ADCValue)) > 1.0) {
						setPin("J5", 8, 1);
					} else {
						setPin("J5", 8, 0);
					}
				break;
				case 6:
					// 100m AC
					setPin("J7", 3, 1);
					setPin("J7", 4, 0);
					setPin("J7", 5, 1);
				
					if(fabs(range100m(ADCValue)) > 100.0) {
						setPin("J5", 8, 1);
					} else {
						setPin("J5", 8, 0);
					}
				break;
				case 7:
					// 10m AC
					setPin("J7", 3, 1);
					setPin("J7", 4, 0);
					setPin("J7", 5, 0);
					
					if(fabs(range10m(ADCValue)) > 10.0) {
						setPin("J5", 8, 1);
					} else {
						setPin("J5", 8, 0);
					}
				break;
			}			
		break;
		// Current
		case 1:
			switch(range) {
				// 1
				case 0:
					setPin("J7", 3, 0);
					setPin("J7", 4, 1);
					setPin("J7", 5, 1);
				
					if(fabs(currentRange1(ADCValue)) > 1.0) {
						setPin("J5", 8, 1);
					} else {
						setPin("J5", 8, 0);
					}
				break;
				// 100m
				case 1:
					setPin("J7", 3, 0);
					setPin("J7", 4, 1);
					setPin("J7", 5, 0);
				
					if(fabs(currentRange100m(ADCValue)) > 100.0) {
						setPin("J5", 8, 1);
					} else {
						setPin("J5", 8, 0);
					}
				break;
				// 10m
				case 2:
					setPin("J7", 3, 0);
					setPin("J7", 4, 0);
					setPin("J7", 5, 1);
				
					if(fabs(currentRange10m(ADCValue)) > 10.0) {
						setPin("J5", 8, 1);
					} else {
						setPin("J5", 8, 0);
					}
				break;
				// 1m
				case 3:
					setPin("J7", 3, 0);
					setPin("J7", 4, 0);
					setPin("J7", 5, 0);
				
					if(fabs(currentRange1m(ADCValue)) > 1.0) {
						setPin("J5", 8, 1);
					} else {
						setPin("J5", 8, 0);
					}
				break;			
			}
		break;
		// Resistance
		case 2:
			// Set the required voltage range
			setPin("J7", 3, 0);
			setPin("J7", 4, 1);
			setPin("J7", 5, 1);
			switch(range) {
				// 1k
				case 0:
					setPin("J7", 6, 0);
					setPin("J7", 7, 0);
					setDAC(2.2);
				
					if(resistanceRange1k(ADCValue) > 1000) {
						setPin("J5", 8, 1);
					} else {
						setPin("J5", 8, 0);
					}
				break;
				// 5k
				case 1:
					setPin("J7", 6, 0);
					setPin("J7", 7, 1);
					setDAC(1.9);
				
					if(resistanceRange5k(ADCValue) > 5000) {
						setPin("J5", 8, 1);
					} else {
						setPin("J5", 8, 0);
					}
				break;
				// 10k
				case 2:
					setPin("J7", 6, 0);
					setPin("J7", 7, 1);
					setDAC(2.2);
				
					if(resistanceRange10k(ADCValue) > 10000) {
						setPin("J5", 8, 1);
					} else {
						setPin("J5", 8, 0);
					}
				break;
				// 50k
				case 3:
					setPin("J7", 6, 1);
					setPin("J7", 7, 0);
					setDAC(1.9);
				
					if(resistanceRange50k(ADCValue) > 50000) {
						setPin("J5", 8, 1);
					} else {
						setPin("J5", 8, 0);
					}
				break;
				// 100k
				case 4:
					setPin("J7", 6, 1);
					setPin("J7", 7, 0);
					setDAC(2.2);
				
					if(resistanceRange100k(ADCValue) > 100000) {
						setPin("J5", 8, 1);
					} else {
						setPin("J5", 8, 0);
					}
				break;
				// 500k
				case 5:
					setPin("J7", 6, 1);
					setPin("J7", 7, 1);
					setDAC(1.9);
				
					if(resistanceRange500k(ADCValue) > 500000) {
						setPin("J5", 8, 1);
					} else {
						setPin("J5", 8, 0);
					}
				break;
				// 1M
				case 6:
					setPin("J7", 6, 1);
					setPin("J7", 7, 1);
					setDAC(2.2);
				
					if(resistanceRange1M(ADCValue) > 1000000) {
						setPin("J5", 8, 1);
					} else {
						setPin("J5", 8, 0);
					}
				break;
			}
		break;
		// Frequency
		case 3:
			setPin("J5", 15, 0);	
		break;
		// Capacitance
		case 4:
			setPin("J5", 15, 1);

			switch(range) {
				case 0:
					setPin("J7", 3, 0);
					setPin("J7", 4, 0);
					setPin("J7", 5, 0);
				break;
				case 1:
					setPin("J7", 3, 0);
					setPin("J7", 4, 1);
					setPin("J7", 5, 0);
				break;
				case 2:
					setPin("J7", 3, 1);
					setPin("J7", 4, 0);
					setPin("J7", 5, 0);
				break;
				case 3:
					setPin("J7", 3, 1);
					setPin("J7", 4, 1);
					setPin("J7", 5, 0);
				break;
			}
		break;
		// Continuity
		case 5:
			setPin("J7", 3, 0);
			setPin("J7", 4, 1);
			setPin("J7", 5, 1);
		
			setPin("J7", 6, 0);
			setPin("J7", 7, 0);
			setDAC(2.2);
		
			if(resistanceRange1k(ADCValue) < 100) {
				setPin("J5", 8, 1);
			} else {
				setPin("J5", 8, 0);
			}
		break;
	}
}
	
int autoRange(int module, int range, double ADCValue){ 
	int retRange = 0;
	double rangeVal = 0.0;
	switch(module) {
		// Voltage
		case 0:
			switch(range) {
				// 10
				case 0:
					rangeVal = fabs(range10(ADCValue));
					if(rangeVal > 10.0) {
						// Buzz for out of range
						setPin("J5", 8, 1);
						retRange = range;
					} else if(rangeVal < 1.0) {
						retRange = range + 1;
					} else {
						setPin("J5", 8, 0);
					}
				break;
				// 1
				case 1:
					rangeVal = fabs(range1(ADCValue));
					if(rangeVal > 1.0) {
						retRange = range - 1;
					} else if(rangeVal < 0.1) {
						retRange = range + 1;
					}
				break;
				// 100m
				case 2:
					rangeVal = fabs(range100m(ADCValue));
					if(rangeVal > 100.0) {
						retRange = range - 1;
					} else if(rangeVal < 10.0) {
						retRange = range + 1;
					}
				break;
				// 10m
				case 3:
					rangeVal = fabs(range10m(ADCValue));
					if(rangeVal > 10.0) {
						retRange = range - 1;
					} else if(rangeVal < 1.0) {
						// Buzz for out of range
						setPin("J5", 8, 1);
						retRange = range;
					} else {
						setPin("J5", 8, 0);
					}
				break;
				// 10 AC
				case 4:
					rangeVal = fabs(range10(ADCValue));
					if(rangeVal > 10.0) {
						// Buzz for out of range
						setPin("J5", 8, 1);
						retRange = range;
					} else if(rangeVal < 1.0) {
						retRange = range + 1;
					} else {
						setPin("J5", 8, 0);
					}
				break;
				// 1 AC
				case 5:
					rangeVal = fabs(range1(ADCValue));
					if(rangeVal > 1.0) {
						retRange = range - 1;
					} else if(rangeVal < 0.1) {
						retRange = range + 1;
					}
				break;
				// 100m AC
				case 6:
					rangeVal = fabs(range100m(ADCValue));
					if(rangeVal > 100.0) {
						retRange = range - 1;
					} else if(rangeVal < 10.0) {
						retRange = range + 1;
					}
				break;
				// 10m AC
				case 7:
					rangeVal = fabs(range10m(ADCValue));
					if(rangeVal > 10.0) {
						retRange = range - 1;
					} else if(rangeVal < 1.0) {
						// Buzz for out of range
						setPin("J5", 8, 1);
						retRange = range;
					} else {
						setPin("J5", 8, 0);
					}
				break;
			}
		break;
		// Current
		case 1:
			switch(range) {
				// 1
				case 0:
					rangeVal = fabs(currentRange1(ADCValue));
					if(rangeVal > 1.0) {
						// Buzz for out of range
						setPin("J5", 8, 1);
						retRange = range;
					} else if(rangeVal < 0.1) {
						retRange = range + 1;
					} else {
						setPin("J5", 8, 0);
					}
				break;
				// 100m
				case 1:
					rangeVal = fabs(currentRange100m(ADCValue));
					if(rangeVal > 100.0) {					
						retRange = range - 1;
					} else if(rangeVal < 10.0) {
						retRange = range + 1;
					}
				break;
				// 10m
				case 2:
					rangeVal = fabs(currentRange10m(ADCValue));
					if(rangeVal > 10.0) {					
						retRange = range - 1;
					} else if(rangeVal < 1.0) {
						retRange = range + 1;
					}
				break;
				// 1m
				case 3:
					rangeVal = fabs(currentRange1m(ADCValue));
					if(rangeVal > 1.0) {					
						retRange = range - 1;
					} else if(rangeVal < 0.1) {
						// Buzz for out of range
						setPin("J5", 8, 1);
						retRange = range;
					} else {
						setPin("J5", 8, 0);
					}
				break;
			}
		break;
		// Resistance
		case 2:
			switch(range) {
				// 1k
				case 0:
					rangeVal = resistanceRange1k(ADCValue);
					if(rangeVal < 100.0) {
						// Buzz for out of range
						setPin("J5", 8, 1);
						retRange = range;
					} else if(rangeVal > 1000) {
						retRange = range + 1;
					} else {
						setPin("J5", 8, 0);
					}
				break;
				// 5k
				case 1:
					rangeVal = resistanceRange5k(ADCValue);
					if(rangeVal < 1000.0) {
						retRange = range - 1;
					} else if(rangeVal > 5000) {
						retRange = range + 1;
					}
				break;
				// 10k
				case 2:
					rangeVal = resistanceRange10k(ADCValue);
					if(rangeVal < 5000.0) {
						retRange = range - 1;
					} else if(rangeVal > 10000.0) {
						retRange = range + 1;
					}
				break;
				// 50k
				case 3:
					rangeVal = resistanceRange50k(ADCValue);
					if(rangeVal < 10000.0) {
						retRange = range - 1;
					} else if(rangeVal > 50000.0) {
						retRange = range + 1;
					}
				break;
				// 100k
				case 4:
					rangeVal = resistanceRange100k(ADCValue);
					if(rangeVal < 50000.0) {
						retRange = range - 1;
					} else if(rangeVal > 100000.0) {
						retRange = range + 1;
					}
				break;
				// 500k
				case 5:
					rangeVal = resistanceRange500k(ADCValue);
					if(rangeVal < 100000.0) {
						retRange = range - 1;
					} else if(rangeVal > 500000.0) {
						retRange = range + 1;
					}
				break;
				// 1M
				case 6:
					rangeVal = resistanceRange1M(ADCValue);
					if(rangeVal < 500000.0) {
						retRange = range - 1;
					} else if(rangeVal > 1000000.0) {
						// Buzz for out of range
						setPin("J5", 8, 1);
						retRange = range;
					} else {
						setPin("J5", 8, 0);
					}
				break;
			}
		break;
	}
	
	return retRange;
}

