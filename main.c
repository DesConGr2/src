#include <stdio.h>
#include <stdlib.h>
#include "STM32F4xx.h"
#include "ADC.h"
#include "digitalIO.h"
#include "lcdDisplay.h"
#include "sound_response.h"
<<<<<<< HEAD
#include "DataLog.h"
#include "Diode.h"
#include "TransistorFunction.h"


void SysTick_Handler(void);
// Delays number of tick Syst icks (happens every 1 ms)
void Delay(uint32_t dlyTicks);
void processButtonPress(int buttonPressed, int *typeIndex, int *rangeIndex, int *autoRangeState, int* datalogMode, int* log);
void display(char *readType[], double voltageRange[], double currentRange[], double resistanceRange[], int *typeIndex, int *rangeIndex, int *autoRangeState, int *datalogMode, int *log);


int main (void) {
	//Control of system clock
  SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }
	//Define the arrays for the user options
	char *readType[7] = {"V         ", "A         ", "Ohm       ", "transistor     ", "Diode          ", "display        ","claer          "};
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
	
	//0 for off, 1 for on
	int *datalogMode = malloc(sizeof(int));
	*datalogMode = 0;
	
	//0 for off, 1 for on
	int *log = malloc(sizeof(int));
	*log = 0;
	
	
	//initialise
	initButtons();
	initDisplay();
=======
#include "freqCalc.h"
#include "UI.h"
#include "serial_comms.h"
#include "DAC.h"

int main (void) {
>>>>>>> master
	initDigitalIO();
	// TODO: change to 'initADC1()' to be consistent with the other naming
	ADC1Init();
	initUI();
	
	initDAC();
	
	while(1) {
<<<<<<< HEAD
		// Display refresh cycle
		Delay(200);
		// Check button press
		processButtonPress(getButtonPressed(), typeIndex, voltageRangeIndex, autoRangeState, datalogMode, log);
		// Adjust the internal settings based on user input
		if(*autoRangeState == 1) {
			autoRange(*voltageRangeIndex);
		} else {
			setRange(*voltageRangeIndex);
		}
			
		// Display settings
		display(readType, voltageRange, currentRange, resistanceRage, typeIndex, voltageRangeIndex, autoRangeState, datalogMode, log);
	}		
=======
	}
		
>>>>>>> master
}




<<<<<<< HEAD
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
void processButtonPress(int buttonPressed, int* typeIndex, int* rangeIndex, int* autoRangeState, int* datalogMode, int* log) {
	switch(buttonPressed){
		case 1:
			//this button increments read type
			if(*typeIndex == 6) {
				displayDatalogValueClear();
				*typeIndex = 0;
			} else if(*typeIndex == 5){
				displayDatalogValueClear();
			} else {
				++*typeIndex;
			}
		break;				
		case 2:
			//this button decrements read type
			if(*typeIndex == 0) {
				displayDatalogValueClear();
				*typeIndex = 6;
			} else if(*typeIndex == 5)  {
				displayDatalogValueClear();
			} else {
				--*typeIndex;
			}
		break;				
		case 3:
			//Used to cycle through the datalog
			if(*typeIndex == 5)
			{
				cycleDatalogUp();
			}else if(*autoRangeState == 0){
				//this button increments range type
				if(*rangeIndex == 4) {
					*rangeIndex = 0;
				} else {
					++*rangeIndex;
				}
			}
		break;				
		case 4:
			//Used to cycle through the datalog
			if(*typeIndex == 5)
			{
				cycleDatalogDown();
			}else if(*autoRangeState == 0){
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
	case 7:
		//this button adds value to datalog
		if(*typeIndex == 0 || *typeIndex == 1 || *typeIndex == 2){
			if(*log == 1){
				*log = 0;
			} else {
				*log = 1;
			}
	} 
	break;
	case 8:
		if(*typeIndex == 6) {
			clearDatalog();
		}else {
		sendDatalog();
		}
	break;
	}
}

void display(char *readType[], double voltageRange[], double currentRange[], double resistanceRange[], int *typeIndex, int *rangeIndex, int *autoRangeState, int *datalogMode, int *log) {	
	
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
						if(*log == 1){
							datalogButton(range1m(), 1 ,readType[*typeIndex] );
							*log = 0;
						}
				break;					
				case 1:
					displayReading(range10m());
					if(*log == 1){
								datalogButton(range10m(), 1, readType[*typeIndex]);
								*log = 0;
							}
				break;					
				case 2:
					displayReading(range100m());
					if(*log == 1){
							datalogButton(range100m(),1, readType[*typeIndex]);
							*log = 0;
						}
				break;
				case 3:
					displayReading(range1());
					if(*log == 1){
							datalogButton(range1(), 0, readType[*typeIndex]);
							*log = 0;
						}
				break;
				case 4:
					displayReading(range10());
					if(*log == 1){
							datalogButton(range10(), 0, readType[*typeIndex]);
							*log = 0;
						}
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
		case 3: 
			displayReading(range10());
			displayTransistor(range10());
		
		break;
		case 4:
			displayReading(range10());
			displayDiode(range10());	
		break;
	}
	
	//display if we are in auto mode or not
	displayAuto(*autoRangeState);
	
}
=======




>>>>>>> master
