#include "stm32f4xx.h"                  		// Device header
#include <stdio.h>
#include <stdlib.h>
#include "ADC.h"
#include "lcd_display.h"
#include "SWT.h"


/*----------------------------------------------------------------------------
  Function that initializes Button pins
 *----------------------------------------------------------------------------*/
	void BTN_Init(void) {

		RCC->AHB1ENR  |= ((1UL <<  0) );              /* Enable GPIOA clock         */

		GPIOA->MODER    &= ~((3UL << 2*0)  );         /* PA.0 is input              */
		GPIOA->OSPEEDR  &= ~((3UL << 2*0)  );         /* PA.0 is 50MHz Fast Speed   */
		GPIOA->OSPEEDR  |=  ((2UL << 2*0)  ); 
		GPIOA->PUPDR    &= ~((3UL << 2*0)  );         /* PA.0 is no Pull up         */

		

	}

	/*----------------------------------------------------------------------------
		Function that reads User Button pin
	 *----------------------------------------------------------------------------*/
	 uint32_t BTN_Get(void) {

	 return (GPIOA->IDR & (1UL<<0));
	}
	 
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
	
	int readingIndex, resolutionIndex; //keeps track of current index of array for navigation through options
	
	//testing for button functionality
	uint32_t btns = 0;
	char *dispVal = (char *)malloc(sizeof(unsigned int) * 16);

  SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }

  initDisplay();
  BTN_Init();   
  SWT_Init();	
  

  while(1) {                                    /* Loop forever               */
    btns = SWT_Get();                           /* Read switch states         */
		
		
		//display btn press
		sprintf(dispVal, "%X", btns);
	
		displayString(dispVal);
	}
	
	
}
