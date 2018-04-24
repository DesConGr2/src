#include "hardwareSelection.h"
#include "digitalIO.h"
#include "ADC.h"
#include "DAC.h"

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
	}
}

//NOTE (chris) : Using pins 2, 3 and 4 of J7 to output these signals, J7 pin 2 is the MSB 
//This currently isnt shown in the code since the "setPin" function takes the GPIO pin number rather than the 
//board edge connector pin number, refer to the module webpage's edge connector sheet
void setRange(int module, int range) {
	switch(module) {
		// Voltage
		case 0:
			switch(range) {
				case 0:
					// 1m
					setPin("J7", 3, 0);
					setPin("J7", 4, 0);
					setPin("J7", 5, 0);
				break;
				case 1:
					// 10m
					setPin("J7", 3, 0);
					setPin("J7", 4, 0);
					setPin("J7", 5, 0);
				break;
				case 2:
					// 100m
					setPin("J7", 3, 0);
					setPin("J7", 4, 0);
					setPin("J7", 5, 1);
				break;
				case 3:
					// 1
					setPin("J7", 3, 0);
					setPin("J7", 4, 1);
					setPin("J7", 5, 0);
				break;
				case 4:
					// 10
					setPin("J7", 3, 0);
					setPin("J7", 4, 1);
					setPin("J7", 5, 1);
				break;
				case 5:
					// 1m AC
					setPin("J7", 3, 1);
					setPin("J7", 4, 0);
					setPin("J7", 5, 0);
				break;
				case 6:
					// 10m AC
					setPin("J7", 3, 1);
					setPin("J7", 4, 0);
					setPin("J7", 5, 0);
				break;
				case 7:
					// 100m AC
					setPin("J7", 3, 1);
					setPin("J7", 4, 0);
					setPin("J7", 5, 1);
				break;
				case 8:
					// 1 AC
					setPin("J7", 3, 1);
					setPin("J7", 4, 1);
					setPin("J7", 5, 0);
				break;
				case 9:
					// 10 AC
					setPin("J7", 3, 1);
					setPin("J7", 4, 1);
					setPin("J7", 5, 1);
				break;
			}			
		break;
		// Current
		case 1:
		break;
		// Resistance
		case 2:
			switch(range) {
				// 1k
				case 0:
					setPin("J7", 3, 0);
					setPin("J7", 4, 0);
					setPin("J7", 5, 0);
					setDAC(2.2);
				break;
				// 5k
				case 1:
					setPin("J7", 3, 0);
					setPin("J7", 4, 0);
					setPin("J7", 5, 1);
					setDAC(1.9);
				break;
				// 10k
				case 2:
					setPin("J7", 3, 0);
					setPin("J7", 4, 0);
					setPin("J7", 5, 1);
					setDAC(2.2);
				break;
				// 50k
				case 3:
					setPin("J7", 3, 0);
					setPin("J7", 4, 1);
					setPin("J7", 5, 0);
					setDAC(1.9);
				break;
				// 100k
				case 4:
					setPin("J7", 3, 0);
					setPin("J7", 4, 1);
					setPin("J7", 5, 0);
					setDAC(2.2);
				break;
				// 500k
				case 5:
					setPin("J7", 3, 0);
					setPin("J7", 4, 1);
					setPin("J7", 5, 1);
					setDAC(1.9);
				break;
				// 1M
				case 6:
					setPin("J7", 3, 0);
					setPin("J7", 4, 1);
					setPin("J7", 5, 1);
					setDAC(2.2);
				break;
			}
		break;
		// Frequency
		case 3:
		break;
		// Capacitance
		case 4:
		break;
	}
}

// NOTE currently only ranges down
//int autoRange(int range) {	
//	// @Warning: there might be an issue to do with the speed that this while loop works at, the hardware may
//	// not be able to keep up. A delay might need to be included.
//	while((range >= 0) && (range <= 4)) {
//		// Check the ADC1 value, see if it fits into the range and if not set the range down
//		// This might change based on the way we deal with each pass of reads, might have all the reads
//		// in one place and just reference the read value here
//		int val = readADC1();
//		
//		// @Hardcode: current max/min ADC values
//		if(val < 0.3) {
//			(range)--;	
//			setRange(range);
//		}	else if(val > 3.1) {
//			(range)++;
//			setRange(range);
//		}
//	}
//	
//	// A good thing to do here might be to leave these values as "Out of Range" and display something 
//	// to notify the user that the measurment is out of range??
//	if(range < 0) {
//		range = 0;
//	}
//	if(range > 4) {
//		range = 4;
//	}
//	return range;
//}

int autoRange(int range){ return 0;}

