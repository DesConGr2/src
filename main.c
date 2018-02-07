#include "stm32f4xx.h"                  		// Device header
#include <stdio.h>
#include <stdlib.h>

#include "ADC.h"
#include "lcd_display.h"
#include "buttons.h"

	 
int main (void) {
	//Overall Display tetsing
	//--------------------------------------------------//
	// Display should show the type of reading you are 	//
	// currently seeing and the resolution on the top		//
	// line. The second line will contain the reading		//
	// as read and translated from the ADC.							//
	//--------------------------------------------------//
	
	//declare variables needed for the display
	char *line1 = (char *)malloc(sizeof(char) * 16);
	char *line2 = (char *)malloc(sizeof(char) * 16);
	
	//int readingIndex, resolutionIndex; //keeps track of current index of array for navigation through options
	
	//testing for button functionality
	char *dispVal = (char *)malloc(sizeof(unsigned int) * 16);

//  SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
//  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
//    while (1);                                  /* Capture error              */
//  }

  initDisplay();  
  initButtons();	
  

  while(1) {                                                                   		
		// display which button has been pressed
		sprintf(dispVal, "%i", getButtonPressed());
	
		displayString(dispVal);
		
		// TODO: figure out how to sleep the thread
	}
	
	
}
