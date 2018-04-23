#include "ranging.h"
#include "digitalIO.h"
#include "ADC.h"
#include "sound_response.h"


//NOTE (chris) : Using pins 2, 3 and 4 of J7 to output these signals, J7 pin 2 is the MSB 
//This currently isnt shown in the code since the "setPin" function takes the GPIO pin number rather than the 
//board edge connector pin number, refer to the module webpage's edge connector sheet
void setRange(int range) {
	switch(range) {
		case 0:
			// 000 for 1m
//			setPin(3, 0);
//			setPin(4, 0);
//			setPin(5, 0);
		break;
		case 1:
			// 000 for 10m
			setPin("J7", 3, 0);
			setPin("J7", 4, 0);
			setPin("J7", 5, 0);
		break;
		case 2:
			// 001 for 100m
			setPin("J7", 3, 0);
			setPin("J7", 4, 0);
			setPin("J7", 5, 1);
		break;
		case 3:
			// 010 for 1
			setPin("J7", 3, 0);
			setPin("J7", 4, 1);
			setPin("J7", 5, 0);
		break;
		case 4:
			// 011 for 10
			setPin("J7", 3, 0);
			setPin("J7", 4, 1);
			setPin("J7", 5, 1);
		break;
	}
}

// TEST FOR HARRY
//void setRange(int range) {
//	switch(range) {
//		case 0:
//			// 11 for 1m
//			setPin(3, 1);
//			setPin(4, 1);
//		break;
//		case 1:
//			// 10 for 10m
//			setPin(3, 1);
//			setPin(4, 0);
//		break;
//		case 2:
//			// 01 for 100m
//			setPin(3, 0);
//			setPin(4, 1);
//		break;
//		case 3:
//			// 00 for 1
//			setPin(3, 0);
//			setPin(4, 0);
//		break;
//		case 4:
//			// 00 for 10
////			setPin(3, 0);
////			setPin(4, 0);
//		break;
//	}
//}

// NOTE currently only ranges down
int autoRange(int range) {	
	// @Warning: there might be an issue to do with the speed that this while loop works at, the hardware may
	// not be able to keep up. A delay might need to be included.
	while((range >= 0) && (range <= 4)) {
		// Check the ADC1 value, see if it fits into the range and if not set the range down
		// This might change based on the way we deal with each pass of reads, might have all the reads
		// in one place and just reference the read value here
		int val = readADC1();
		
		// @Hardcode: current max/min ADC values
		if(val < 0.3) {
			(range)--;	
			setRange(range);
		}	else if(val > 3.1) {
			(range)++;
			setRange(range);
		}
	}
	
	// A good thing to do here might be to leave these values as "Out of Range" and display something 
	// to notify the user that the measurment is out of range??
	if(range < 0) {
		range = 0;
	}
	if(range > 4) {
		range = 4;
	}
	return range;
}

