#include "stm32f4xx.h"                  		// Device header
#include <stdio.h>
#include <stdlib.h>
#include "ADC.h"
#include "lcd_display.h"
#include "SWT.h"

	 
int main (void) {
	
	//ADC reding and display testing
	/*
	initDisplay();
	ADC1Init();
	unsigned int val = readADC1();
	char *dispVal = (char *)malloc(sizeof(unsigned int) * 16);
	sprintf(dispVal, "%d", val);
	
	displayString(dispVal);
	*/
	
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
	int btns = 0;
	char *dispVal = (char *)malloc(sizeof(unsigned int) * 16);

//  SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
//  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
//    while (1);                                  /* Capture error              */
//  }

  initDisplay();  
  SWT_Init();	
  

  while(1) {                                    /* Loop forever               */
    btns = SWT_Get();                           /* Read switch states         */
		
		// The order of buttons on the board will be 1 - 8 from left to right
		int buttonNumber = 0;
		
		btns &= 0x0000FF00;
		
		switch(btns) {
			case 0x00000100:
				buttonNumber = 1;
			break;
			case 0x00000200:
				buttonNumber = 2;
			break;
			case 0x00000400:
				buttonNumber = 3;
			break;
			case 0x00000800:
				buttonNumber = 4;
			break;
			case 0x00001000:
				buttonNumber = 5;
			break;
			case 0x00002000:
				buttonNumber = 6;
			break;
			case 0x00004000:
				buttonNumber = 7;
			break;
			case 0x00008000:
				buttonNumber = 8;
			break;
			default:
				buttonNumber = 0;
			break;
		}
		
		//display btn press
		sprintf(dispVal, "%i", buttonNumber);
	
		displayString(dispVal);
		
		//figure out how to sleep the thread
	}
	
	
}
