#include <stdio.h>
#include <stdlib.h>
#include "STM32F4xx.h"
#include "ADC.h"
#include "digitalIO.h"
#include "lcdDisplay.h"
#include "sound_response.h"

#include "freqCalc.h"
#include "UI.h"
#include "serial_comms.h"
#include "DAC.h"

int main (void) {
	initDigitalIO();
	// TODO: change to 'initADC1()' to be consistent with the other naming
	ADC1Init();
	initUI();
	
	initDAC();
	
	while(1) {}		
}
