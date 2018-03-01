#include "stm32f4xx.h"                  		// Device header
#include <stdio.h>
#include <stdlib.h>

#include "ADC.h"
#include "lcdDisplay.h"
#include "buttons.h"
#include "digitalIO.h"

void setRange(int range);

int main (void) {
	// GPIOD/A/B clocks setup in this
	initDisplay();  
	// GPIOE clock set up in this
	initButtons();	
	
	initDigitalIO();



	int range = 0;

	// Check the ADC value, see if it fits into the range and if not set the range down
	int val = readADC1();

	// loop through this until a suitable range is found (or maybe just jump straight to the right range if pos???)
	// Changing the range will move to a higher gain circuit so we just update the internal range here 
	while(range != 0) {
		if(val < 0.3) {
			range --;	
		}	
	}
	
	

	

	

  	while(1) {
	}
}

// Ranges:
// 0 - 1m
// 1 - 10m
// 2 - 100m
// 3 - 1

// Set the digital IO pins out based on the range
// Harry suggested using a 2 bit address for these ranges since thats 
// what the switches take (or something like that)

void setRange(int range) {
	// NOTE (chris) : Using pins 2 and 3 of J7 to output these signals, J7 pin 2 is the MSB 
	// This currently isnt shown in the code since the "setPin" function takes the GPIO pin number rather than the 
	// board edge connector pin number, refer to the module webpage's edge connector sheet
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



