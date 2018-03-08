#include "stm32f4xx.h"                  		// Device header
#include <stdio.h>
#include <stdlib.h>

#include "ADC.h"
#include "lcdDisplay.h"
#include "buttons.h"
#include "digitalIO.h"
#include "ranging.h"



int main (void) {
	// GPIOD/A/B clocks setup in this
	initDisplay();  
	// GPIOE clock set up in this
	initButtons();	
	
	initDigitalIO();



	int range = 3;
	setRange(range);
	autoRange(&range);
	

	while(1) {}
}




