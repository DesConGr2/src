#include "stm32f4xx.h"                  		// Device header
#include <stdio.h>
#include <stdlib.h>

#include "ADC.h"
#include "lcdDisplay.h"
#include "buttons.h"
#include "digitalIO.h"



int main (void) {
  // GPIOD/A/B clocks setup in this
	initDisplay();  
	// GPIOE clock set up in this
  initButtons();	
	
	initDigitalIO();
	
	// Write to J7 pin 7
	setPin(7, 1);
	int readVal = 0;
  while(1) {                                                                   		
		// Read from J5 pin 4 and display
		readVal = readPin(4);
		
		if(readVal == -1) {
		displayString("Error");
		} else {
			displayInt(readVal);
		}
		
	}
}


