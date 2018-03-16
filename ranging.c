#include "ranging.h"
#include "digitalIO.h"
#include "ADC.h"


// NOTE (chris) : Using pins 2 and 3 of J7 to output these signals, J7 pin 2 is the MSB 
// This currently isnt shown in the code since the "setPin" function takes the GPIO pin number rather than the 
// board edge connector pin number, refer to the module webpage's edge connector sheet
void setRange(int range) {
	switch(range) {
		case 0:
			// 00 for 1m
			setPin(3, 0);
			setPin(4, 0);
		break;
		case 1:
			// 01 for 10m
			setPin(3, 0);
			setPin(4, 1);
		break;
		case 2:
			// 10 for 100m
			setPin(3, 1);
			setPin(4, 0);
		break;
		case 3:
			// 11 for 1
			setPin(3, 1);
			setPin(4, 1);
		break;
	}
}

// NOTE currently only ranges down, talk to harry about ranging up
void autoRange(int *range) {	
	// @Warning: there might be an issue to do with the speed that this while loop works at, the hardware may
	// not be able to keep up. A delay might need to be included.
	while(range != 0) {
		// Check the ADC1 value, see if it fits into the range and if not set the range down
		// This might change based on the way we deal with each pass of reads, might have all the reads
		// in one place and just reference the read value here
		int val = readADC1();
		
		if(val < 0.3) {
			(*range)--;	
			setRange(*range);
		}	else if(val > 3.1) {
			(*range)++;
			setRange(*range);
		}
	}
}

