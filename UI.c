#include "STM32F4xx.h"
#include <stdlib.h>

#include "UI.h"
#include "lcdDisplay.h"
#include "mathsFunctions.h"
#include "ADC.h"
#include "hardwareSelection.h"
#include "buttons.h"
#include "FreqCalc.h"
#include "serial_comms.h"
#include "digitalIO.h"
#include "DAC.h"

typedef struct UIVals {
	char *readType[5];
	char *voltageRange[6];
	char *currentRange[4];
	char *resistanceRage[7];
	char *capacitanceRange[3];
	
	int typeIndex;
	int rangeIndex;
	
	//for debouncing
	int prevbtn;
	int debCount;
	//for display
	int dispcount;
	//0 for off, 1 for on
	int autoRangeState;
} UIVals;


UIVals *interfaceVals;
const int MAXINDEX[5] = {5, 3, 6, 0, 2};


void initUI(void) {
	initButtons();
	initDisplay();
	initFreqCalc();
	// Init the display timer
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	NVIC_EnableIRQ(TIM5_IRQn);    // Enable IRQ for TIM5 in NVIC

	TIM5->ARR     = 10*84000;    // Auto Reload Register value =>
	TIM5->DIER   |= 0x0001;       // DMA/IRQ Enable Register - enable IRQ on update
	TIM5->CR1    |= 0x0001;       // Enable Counting
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	
	NVIC_EnableIRQ(TIM3_IRQn);    // Enable IRQ for TIM3 in NVIC

	TIM3->ARR     = 20*84000;        // Auto Reload Register value => 1ms
	TIM3->DIER   |= 0x0001;       // DMA/IRQ Enable Register - enable IRQ on update
	TIM3->CR1    |= 0x0001;       // Enable Counting
	
	interfaceVals = malloc(sizeof(UIVals));
	
	//Define the arrays for the user options
	interfaceVals->readType[0] = "V  ";
	interfaceVals->readType[1] = "A  ";
	interfaceVals->readType[2] = "Ohm";
	interfaceVals->readType[3] = "Hz ";
	interfaceVals->readType[4] = "C  ";
	
	interfaceVals->voltageRange[0] =  "0.001";
	interfaceVals->voltageRange[1] =  "0.01";
	interfaceVals->voltageRange[2] =  "0.1";
	interfaceVals->voltageRange[3] =  "1.0";
	interfaceVals->voltageRange[4] = "10.0";
	interfaceVals->voltageRange[5] = "Test";
	
	interfaceVals->currentRange[0] = "0.001";
	interfaceVals->currentRange[1] = "0.01";
	interfaceVals->currentRange[2] = "0.1";
	interfaceVals->currentRange[3] = "1.0";
	
	interfaceVals->capacitanceRange[0] = "1.0";
	interfaceVals->capacitanceRange[1] = "2.0";
	interfaceVals->capacitanceRange[2] = "3.0";

	// Unsure about what ranges we have for the resistance
	interfaceVals->resistanceRage[0] = "1k";
	interfaceVals->resistanceRage[1] = "5k";
	interfaceVals->resistanceRage[2] = "10k";
	interfaceVals->resistanceRage[3] = "50k";
	interfaceVals->resistanceRage[4] = "100k";
	interfaceVals->resistanceRage[5] = "500k";
	interfaceVals->resistanceRage[6] = "1M";
}

void processButtonPress(int buttonPressed, int* typeIndex, int* rangeIndex, int* autoRangeState) {
	switch(buttonPressed){
		case 1:
			//this button increments read type
			if(*typeIndex == 4) {
				*typeIndex = 0;
			} else {
				++*typeIndex;
			}
		break;				
		case 2:
			//this button decrements read type
			if(*typeIndex == 0) {
				*typeIndex = 4;
			} else {
				--*typeIndex;
			}
		break;				
		case 3:
			if(*autoRangeState == 0){
				//this button increments range type
				// TODO: make the range index change based on what is being measured
				if(*rangeIndex == MAXINDEX[*typeIndex]) {
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
					*rangeIndex = MAXINDEX[*typeIndex];
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

void display(char *readType[], 
			 char *voltageRange[], 
			 char *currentRange[], 
			 char *resistanceRange[], 
			 char *capacitanceRange[], 
			 int typeIndex, 
			 int rangeIndex, 
			 int autoRangeState) 
{	
	double displayVal;
	
	displayType(readType[typeIndex]);

	switch(typeIndex){
		//Voltage
		case 0:		
			displayStringRange(voltageRange[rangeIndex]);

			switch(rangeIndex){
				case 0:
					displayVal = range1m();			
					displayReading(displayVal);
				break;					
				case 1:
					displayVal = range10m();					
					displayReading(displayVal);									
				break;					
				case 2:
					displayVal = range100m();				
					displayReading(displayVal);
				break;
				case 3:
					displayVal = range1();
					displayReading(displayVal);					
				break;
				case 4:
					displayVal = range10();
					displayReading(range10());
				break;
				case 5:
					displayVal = testRange();
					displayReading(displayVal);
				break;
			}
		break;
		//Current
		case 1:					
			displayStringRange(currentRange[rangeIndex]);
	
			switch(rangeIndex){
				case 0:
					displayVal = range1m();
					displayReading(displayVal);
				break;					
				case 1:
					displayVal = range10m();
					displayReading(displayVal);														
				break;					
				case 2:
					displayVal = range100m();				
					displayReading(displayVal);
				break;
				case 3:
					displayVal = range1();
					displayReading(displayVal);																			
				break;
				case 4:
					displayVal = range10();
					displayReading(range10());
				break;
				case 5:
					displayVal = testRange();
					displayReading(displayVal);
				break;
			}
		break;			
		//Resistance
		case 2:		
			displayStringRange(resistanceRange[rangeIndex]);		
		
			switch(interfaceVals->rangeIndex) {
				case 0:
					{
						double val = readADC1();
						double grad = ((1000.0 - 100.0) / (2.1 - 0.19));
						displayReading(val * grad);
					}
				break;
				case 1:

					{
						double val = readADC1();
						double grad = ((5000.0 - 1000.0) / (2.8 - 0.55));
						displayReading(val * grad);
					}
				break;
				case 2:
					{
						double val = readADC1();
						double grad = ((10000.0 - 5000.0) / (2.72 - 1.4));
						displayReading(val * grad);
					}
				break;
				case 3:
					{
						double val = readADC1();
						double grad = ((50000.0 - 10000.0) / (2.77 - 0.56));
						displayReading(val * grad);
					}
				break;
				case 4:
					{
						double val = readADC1();
						double grad = ((100000.0 - 50000.0) / (2.55 - 1.36));
						displayReading(val * grad);
					}
				break;
				case 5:
					{
						double val = readADC1();
						double grad = ((500000.0 - 100000.0) / (1.91- 0.49));
						displayReading(val * grad);
					}
				break;
				case 6:
					{
						double val = readADC1();
						double grad = ((1000000.0 - 500000.0) / (1.39 - 0.94));
						displayReading(val * grad);
					}
				break;
			}
		break;
		//Frequency
		case 3:		
			displayReading(getAveragedFrequency());
			//displayReading(getPeriod());
		break;
		//Capacitance
		case 4:							
			displayStringRange(capacitanceRange[rangeIndex]);
			if(rangeIndex == 0) {
				// Hacky way of addressing things for harry 
				setRange(0);
				double cap = (getPeriod() / (0.693 * 60000000));
				displayReading(cap);
				
			} else if(rangeIndex == 1) {
				// Hacky way of addressing things for harry 
				setRange(1);
				double cap = (getPeriod() / (0.693 * 60000));
				displayReading(cap);
				
			} else if (rangeIndex == 2) {
				// Hacky way of addressing things for harry 
				setRange(2);
				double cap = (getPeriod() / (0.693 * 6000));
				displayReading(cap);
			}
			
			displayReading(getPeriod());
		break;
	}
	
	//display if we are in auto mode or not
	displayAuto(autoRangeState);
}

void TIM5_IRQHandler(void) {
 	// clear IRQ flag in TIM5
 	TIM5->SR &= ~0x00000001;      
	
	setModule(interfaceVals->typeIndex);

	if(interfaceVals->autoRangeState == 1) {
		autoRange(interfaceVals->rangeIndex);
	} else {	
		setRange(interfaceVals->rangeIndex);
	}
	
	// Display settings
	interfaceVals->dispcount++;
	
	if (interfaceVals->dispcount ==  20) {
	//display
	display(interfaceVals->readType, 
					interfaceVals->voltageRange, 
					interfaceVals->currentRange, 
					interfaceVals->resistanceRage, 
					interfaceVals->capacitanceRange, 
					interfaceVals->typeIndex, 
					interfaceVals->rangeIndex, 
					interfaceVals->autoRangeState);	
	//reset the counter
	interfaceVals->dispcount = 0;
	}	
}

void TIM3_IRQHandler(void) {
	// clear IRQ flag in TIM3
	TIM3->SR &= ~0x00000001;      
	
	// Check button press
	int curbtn = getButtonPressed();
	
	if( interfaceVals->prevbtn == curbtn ){
		
		if(interfaceVals->debCount == 3 && curbtn != 0) {
			displayClear();
			processButtonPress(curbtn, &interfaceVals->typeIndex, &interfaceVals->rangeIndex, &interfaceVals->autoRangeState);
			interfaceVals->debCount++;
		} else if(interfaceVals->debCount < 4) {
			interfaceVals->debCount++;
		}	
			
	} else {
		//update the button pressed
		interfaceVals->debCount = 0;
		interfaceVals->prevbtn = curbtn;
	}
}


/*---------------------------------------------------------------------------------//
// Code to deal with the user interface and the screen refresh rate...		       //
// Multithreading would be ideal but fork() and <sys/types.h> are Os related       //
// libraries and functions, so no good for development board. Investigate 	       //
// other ways of threading, but for now will use time slicing for system	       //
// Coded by: jjds502								  						       //
// Inital version: 23/03/2018												       //
// Consider using interrupts...												       //
//																			       //
// https://www.fmf.uni-lj.si/~ponikvar/STM32F407%20project/					       //
// https://stm32f4-discovery.net/2014/08/stm32f4-external-interrupts-tutorial/     //
//---------------------------------------------------------------------------------*/