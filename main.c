#include <stdio.h>
#include <stdlib.h>
#include "STM32F4xx.h"
#include "ADC.h"
#include "lcdDisplay.h"
#include "buttons.h"
#include "digitalIO.h"
#include "mathsFunctions.h"
#include "ranging.h"
#include "sound_response.h"

void SysTick_Handler(void);
// Delays number of tick Syst icks (happens every 1 ms)
void Delay(uint32_t dlyTicks);
void processButtonPress(int buttonPressed, int *typeIndex, int *rangeIndex, int *autoRangeState);
void display(char *readType[], double voltageRange[], double currentRange[], double resistanceRange[], int *typeIndex, int *rangeIndex, int *autoRangeState);


int main (void) {
	//Control of system clock
  SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }
	//Define the arrays for the user options
	char *readType[3] = {"V  ", "A  ", "Ohm"};
	double voltageRange[5] = {0.001, 0.01, 0.1, 1, 10};
	double currentRange[4] = {0.001, 0.01, 0.1, 1};
	// Unsure about what ranges we have for the resistance
	double resistanceRage[1] = {1000000};
	int *typeIndex = malloc(sizeof(int));
	int *voltageRangeIndex = malloc(sizeof(int));
	int *currentRangeIndex = malloc(sizeof(int));
	
	//0 for off, 1 for on
	int *autoRangeState = malloc(sizeof(int));
	*autoRangeState = 0;
	
	//initialise
	initButtons();
	initDisplay();
	initDigitalIO();
	ADC1Init();
	
	//Wlecome message (tests screen)
	turnBuzzerOn();
	displayType("Welcome!");
	Delay(1000);
	displayClear();
	turnBuzzerOff();
	
	while(1) {
		// Display refresh cycle
		Delay(200);
		// Check button press
		processButtonPress(getButtonPressed(), typeIndex, voltageRangeIndex, autoRangeState);
		// Adjust the internal settings based on user input
		if(*autoRangeState == 1) {
			autoRange(voltageRangeIndex);
		} else {
			setRange(*voltageRangeIndex);
		}
		// Display settings
		display(readType, voltageRange, currentRange, resistanceRage, typeIndex, voltageRangeIndex, autoRangeState);
	}		
}

// Counts 1ms timeTicks
volatile uint32_t msTicks;
/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
  msTicks++;
}

/*----------------------------------------------------------------------------
  delays number of tick Systicks (happens every 1 ms)
 *----------------------------------------------------------------------------*/
void Delay (uint32_t dlyTicks) {                                              
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks);
}

/*----------------------------------------------------------------------------//
// Code to deal with the user interface and the screen refresh rate...				//
// Multithreading would be ideal but fork() and <sys/types.h> are Os related	//
// libraries and functions, so no good for development board. Investigate 		//
// other ways of threading, but for now will use time slicing for system			//
// Coded by: jjds502																													//
// Inital version: 23/03/2018																									//
// Consider using interrupts...																								//
//																																						//
// https://www.fmf.uni-lj.si/~ponikvar/STM32F407%20project/										//
// https://stm32f4-discovery.net/2014/08/stm32f4-external-interrupts-tutorial/
//----------------------------------------------------------------------------*/
void processButtonPress(int buttonPressed, int* typeIndex, int* rangeIndex, int* autoRangeState) {
	switch(buttonPressed){
		case 1:
			//this button increments read type
			if(*typeIndex == 2) {
				*typeIndex = 0;
			} else {
				++*typeIndex;
			}
		break;				
		case 2:
			//this button decrements read type
			if(*typeIndex == 0) {
				*typeIndex = 2;
			} else {
				--*typeIndex;
			}
		break;				
		case 3:
			if(*autoRangeState == 0){
				//this button increments range type
				if(*rangeIndex == 4) {
					*rangeIndex = 0;
				} else {
					++*rangeIndex;
				}
			}
		break;				
		case 4:
			if(*autoRangeState == 0){
				//this button decrements range type
				if(*rangeIndex == 0) {
					*rangeIndex = 4;
				} else {
					--*rangeIndex;
				}
			}
		break;	
		case 5:
			//this button toggles autoranging
			if(*autoRangeState == 0){
				*autoRangeState = 1;
			} else {
				*autoRangeState = 0;
			}
		break;
	}
}

void display(char *readType[], double voltageRange[], double currentRange[], double resistanceRange[], int *typeIndex, int *rangeIndex, int *autoRangeState) {	
	
	//display type
	displayType(readType[*typeIndex]);
	
	//display resolution
	switch(*typeIndex){
		case 0:
			//Display the range (resolution)
			displayRange(voltageRange[*rangeIndex]);
		
			//---- Code for displaying the reading ----//
			switch(*rangeIndex){
				case 0:
						displayReading(range1m());
				break;					
				case 1:
					displayReading(range10m());
				break;					
				case 2:
					displayReading(range100m());
				break;
				case 3:
					displayReading(range1());
				break;
				case 4:
					displayReading(range10());
				break;
			}
			
			//-----------------------------------------//
		break;
		case 1:
			//Display the range (resolution)
			//displayRange(ARANGE[*rangeIndex]);
		
			//---- Code for displaying the reading ----//
			displayReading(readADC1());
			//-----------------------------------------//
		break;			
		case 2:
			//Display the range (resolution)
			displayRange(resistanceRange[0]);
		
			//---- Code for displaying the reading ----//
			displayReading(readADC1());
			//-----------------------------------------//
		break;
	}
	
	//display if we are in auto mode or not
	displayAuto(*autoRangeState);
	
}
