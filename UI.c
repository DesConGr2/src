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

#include "DataLog.h"
#include "Diode.h"
#include "TransistorFunction.h"

typedef struct UIVals {
	char *readType[8];
	char *voltageRange[8];
	char *currentRange[4];
	char *resistanceRange[7];
	char *capacitanceRange[4];
	
	int typeIndex;
	int rangeIndex;
	
	//for debouncing
	int prevbtn;
	int debCount;
	//for display
	int dispcount;
	int autoRangeCount;
	//0 for off, 1 for on
	int autoRangeState;
	int commsState;
} UIVals;


UIVals *interfaceVals;
const int MAXINDEX[8] = {7, 3, 6, 0, 3, 0, 0, 0};

uint32_t ADCValues[50] = {0.0};
uint32_t ADCAverage = 0;
int ADCSampleCount = 50;

int logging;
int datalogMode;

void initUI(void) {
	initButtons();
	initDisplay();
	initFreqCalc();
	CommsInit();
	// Init the display timer
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	NVIC_EnableIRQ(TIM5_IRQn);    // Enable IRQ for TIM5 in NVIC

	TIM5->ARR     = 10*84000;    // Auto Reload Register value =>
	TIM5->DIER   |= 0x0001;       // DMA/IRQ Enable Register - enable IRQ on update
	TIM5->CR1    |= 0x0001;       // Enable Counting
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	NVIC_EnableIRQ(TIM2_IRQn);    // Enable IRQ for TIM3 in NVIC

	TIM2->ARR     = 20*84000;        // Auto Reload Register value => 1ms
	TIM2->DIER   |= 0x0001;       // DMA/IRQ Enable Register - enable IRQ on update
	TIM2->CR1    |= 0x0001;       // Enable Counting
	
	interfaceVals = malloc(sizeof(UIVals));
	
	//0 for off, 1 for on
	datalogMode = 0;
	

	//0 for off, 1 for on
	logging = 0;

	
	//Define the arrays for the user options
	interfaceVals->readType[0] = "V  ";
	interfaceVals->readType[1] = "A  ";
	interfaceVals->readType[2] = "Ohm";
	interfaceVals->readType[3] = "Hz ";
	interfaceVals->readType[4] = "C  ";
	interfaceVals->readType[5] = "Continuity";
	interfaceVals->readType[6] = "Diode";
	interfaceVals->readType[7] = "Transistor";
	
	interfaceVals->voltageRange[0] =  "10.0";
	interfaceVals->voltageRange[1] =   "1.0";
	interfaceVals->voltageRange[2] =   "0.1";
	interfaceVals->voltageRange[3] =   "0.01";
	interfaceVals->voltageRange[4] =  "10.0 AC";
	interfaceVals->voltageRange[5] =   "1.0 AC";
	interfaceVals->voltageRange[6] =   "0.1 AC";
	interfaceVals->voltageRange[7] =   "0.01 AC";
	
	interfaceVals->currentRange[0] = "1.0";
	interfaceVals->currentRange[1] = "0.1";
	interfaceVals->currentRange[2] = "0.01";
	interfaceVals->currentRange[3] = "0.001";

	interfaceVals->resistanceRange[0] = "1k";
	interfaceVals->resistanceRange[1] = "5k";
	interfaceVals->resistanceRange[2] = "10k";
	interfaceVals->resistanceRange[3] = "50k";
	interfaceVals->resistanceRange[4] = "100k";
	interfaceVals->resistanceRange[5] = "500k";
	interfaceVals->resistanceRange[6] = "1M";

	interfaceVals->capacitanceRange[0] = "pF";
	interfaceVals->capacitanceRange[1] = "nF";
	interfaceVals->capacitanceRange[2] = "uF";
	interfaceVals->capacitanceRange[3] = "High uF";
	
	interfaceVals->autoRangeCount = 0;
}


void processButtonPress(int buttonPressed, int* typeIndex, int* rangeIndex, int* autoRangeState, int* commsState) {
	switch(buttonPressed){
		// Leftmost button
		case 1:
			//this button increments read type
			if(*typeIndex == 7) {
				*typeIndex = 0;
			} else {
				++*typeIndex;
			}
			
			*rangeIndex = 0;
		break;				
		case 2:
			//this button decrements read type
			if(*typeIndex == 0) {
				*typeIndex = 7;
			} else {
				--*typeIndex;
			}
			
			*rangeIndex = 0;
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
				interfaceVals->autoRangeCount = 0;
			} else {
				*autoRangeState = 0;
			}
		break;
		case 6:
			//this button toggles serial comms
			if(*commsState == 0){
				*commsState = 1;
			} else {
				*commsState = 0;
			}
		break;
		case 7:
			//this button adds value to datalog if they are loggable
			if(*typeIndex < 5){
				if(logging == 1){
					logging = 0;
				} else {
					logging = 1;
				}
			} 
		break;
		// Send data log
		case 8:
			if(logging == 1) {
				logging = 0;
				sendDatalog();				
			} else {
				logging = 0;
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
			 int autoRangeState,
			 int commsState) 
{	
	
							 
	//initilise display value
	double displayVal;
	displayType(readType[typeIndex]);					
	//display if we are in auto and/or comms mode or not
	displayAuto(autoRangeState);
	displayComms(commsState);
	displayLogging(logging);
	
	switch(typeIndex){
		//Voltage
		case 0:		
			displayStringRange(voltageRange[rangeIndex]);

			switch(rangeIndex){
				case 0:
					displayVal = voltageRange10(ADCAverage);
					displayReading(displayVal);
					if(logging == 1){
						addToDatalog(displayVal, 1 ,readType[typeIndex] );
						logging = 0;
					}								
					displayV();
				
					// Attempt to send via uart
					if(commsState == 1)
					WriteToOutputString(displayVal);
					
				break;					
				case 1:

					displayVal = voltageRange1(ADCAverage);
					// Display to LCD
					displayReading(displayVal);
					if(logging == 1){
						addToDatalog(displayVal, 1 ,readType[typeIndex] );
						logging = 0;
					}
					displayV();
				
					// Attempt to send via uart
					if(commsState == 1)
					WriteToOutputString(displayVal);
					
				break;									
				case 2:
					displayVal = voltageRange100m(ADCAverage);				
					displayReading(displayVal);
					if(logging == 1){
						addToDatalog(displayVal, 1 ,readType[typeIndex] );
						logging = 0;
					}
					displaymV();
				
					// Attempt to send via uart
					if(commsState == 1)
					WriteToOutputString(displayVal);
					
				break;
				case 3:
					displayVal = voltageRange10m(ADCAverage);
					displayReading(displayVal);
					displaymV();
					
					// Attempt to send via uart
					if(commsState == 1)
					WriteToOutputString(displayVal);
					
				break;
				case 4:
					displayVal = voltageRange10AC(ADCAverage);
					displayReading(displayVal);
					if(logging == 1){
						addToDatalog(displayVal, 1 ,readType[typeIndex] );
						logging = 0;
					}	
					displayV();
				
					// Attempt to send via uart
					if(commsState == 1)
					WriteToOutputString(displayVal);
					
				break;
				case 5:
					displayVal = voltageRange1AC(ADCAverage);
					displayReading(displayVal);
					if(logging == 1){
						addToDatalog(displayVal, 1 ,readType[typeIndex] );
						logging = 0;
					}	
					displayV();
				
					// Attempt to send via uart
					if(commsState == 1)
					WriteToOutputString(displayVal);
					
				break;
				case 6:
					displayVal = voltageRange100mAC(ADCAverage);
					displayReading(displayVal);
					if(logging == 1){
						addToDatalog(displayVal, 1 ,readType[typeIndex] );
						logging = 0;
					}	
					displaymV();
				
					// Attempt to send via uart
					if(commsState == 1)
					WriteToOutputString(displayVal);
					
				break;
				case 7:
					displayVal = voltageRange10mAC(ADCAverage);
					displayReading(displayVal);
					if(logging == 1){
						addToDatalog(displayVal, 1 ,readType[typeIndex] );
						logging = 0;
					}	
					displaymV();
				
					// Attempt to send via uart
					if(commsState == 1)
					WriteToOutputString(displayVal);
					
				break;
			}
		break;
		//Current
		case 1:					
			displayStringRange(currentRange[rangeIndex]);
		
			switch(rangeIndex){
				case 0:
					displayVal = currentRange1(ADCAverage);
					// Display to LCD
					displayReading(displayVal);
					if(logging == 1){
						addToDatalog(displayVal, 1 ,readType[typeIndex] );
						logging = 0;
					}	
					displayA();
				
					// Attempt to send via uart
					if(commsState == 1)
					WriteToOutputString(displayVal);
					
				break;					
				case 1:
					displayVal = currentRange100m(ADCAverage);
					// Display to LCD
					displayReading(displayVal);
					if(logging == 1){
						addToDatalog(displayVal, 1 ,readType[typeIndex] );
						logging = 0;
					}	
					displaymA();
				
					// Attempt to send via uart
					if(commsState == 1)
					WriteToOutputString(displayVal);
					
				break;					
				case 2:
					displayVal = currentRange10m(ADCAverage);
					displayReading(displayVal);
					if(logging == 1){
						addToDatalog(displayVal, 1 ,readType[typeIndex] );
						logging = 0;
					}	
					displaymA();
				
					// Attempt to send via uart
					if(commsState == 1)
					WriteToOutputString(displayVal);
					
				break;
				case 3:
					displayVal = currentRange1m(ADCAverage);
					displayReading(displayVal);
					if(logging == 1){
						addToDatalog(displayVal, 1 ,readType[typeIndex] );
						logging = 0;
					}	
					displaymA();
				
					// Attempt to send via uart
					if(commsState == 1)
					WriteToOutputString(displayVal);
					
				break;
			}
		break;			
		//Resistance
		case 2:		
			displayStringRange(resistanceRange[rangeIndex]);		
		
			switch(interfaceVals->rangeIndex) {
				case 0:
					{
						displayVal = resistanceRange1k(ADCAverage);
						displayReading(displayVal);
						if(logging == 1){
							addToDatalog(displayVal, 1 ,readType[typeIndex] );
							logging = 0;
						}	
						displayOhm();
					}
				break;
				case 1:
					{
						displayVal = resistanceRange5k(ADCAverage);
						displayReading(displayVal);
						if(logging == 1){
							addToDatalog(displayVal, 1 ,readType[typeIndex] );
							logging = 0;
						}	
						displaykOhm();
					}
				break;
				case 2:
					{
						displayVal = resistanceRange10k(ADCAverage);
						displayReading(displayVal);
						if(logging == 1){
							addToDatalog(displayVal, 1 ,readType[typeIndex] );
							logging = 0;
						}	
						displaykOhm();
					}
				break;
				case 3:
					{
						displayVal = resistanceRange50k(ADCAverage);
						displayReading(displayVal);
						if(logging == 1){
							addToDatalog(displayVal, 1 ,readType[typeIndex] );
							logging = 0;
						}	
						displaykOhm();
					}
				break;
				case 4:
					{
						displayVal = resistanceRange100k(ADCAverage);
						displayReading(displayVal);
						if(logging == 1){
							addToDatalog(displayVal, 1 ,readType[typeIndex] );
							logging = 0;
						}	
						displaykOhm();
					}
				break;
				case 5:
					{
						displayVal = resistanceRange500k(ADCAverage);
						displayReading(displayVal);
						if(logging == 1){
							addToDatalog(displayVal, 1 ,readType[typeIndex] );
							logging = 0;
						}	
						displaykOhm();
					}
				break;
				case 6:
					{
						displayVal = resistanceRange1M(ADCAverage);
						displayReading(displayVal);
						if(logging == 1){
							addToDatalog(displayVal, 1 ,readType[typeIndex] );
							logging = 0;
						}	
						displaykOhm();
					}
				break;
			}
		break;
		//Frequency
		case 3:					
			displayVal = (double)84000000 / (double)TIM3->CCR1;
			displayReading(displayVal);
			if(logging == 1){
				addToDatalog(displayVal, 1 ,readType[typeIndex] );
				logging = 0;
			}	
		break;
		//Capacitance
		case 4:							
			displayStringRange(capacitanceRange[rangeIndex]);
			
			switch(rangeIndex) {
				// pF
				case 0:
					displayVal = capacitanceRangePF((double)84000000 / (double)TIM3->CCR1);
					displayReading(displayVal);
					if(logging == 1){
						addToDatalog(displayVal, 1 ,readType[typeIndex] );
						logging = 0;
					}	
				break;
				// nF
				case 1:
					displayVal = capacitanceRangeNF((double)84000000 / (double)TIM3->CCR1);
					displayReading(displayVal);
					if(logging == 1){
						addToDatalog(displayVal, 1 ,readType[typeIndex] );
						logging = 0;
					}
				break;
				// uF
				case 2:
					displayVal = capacitanceRangeUF((double)84000000 / (double)TIM3->CCR1);
					displayReading(displayVal);
					if(logging == 1){
						addToDatalog(displayVal, 1 ,readType[typeIndex] );
						logging = 0;
					}
				break;
				// High uF
				case 3:
					displayVal = capacitanceRangeHighUF((double)84000000 / (double)TIM3->CCR1);
					displayReading(displayVal);
					if(logging == 1){
						addToDatalog(displayVal, 1 ,readType[typeIndex] );
						logging = 0;
					}
				break;
			}
		break;
		// Continuity
		case 5:
		break;
		// Diode
		case 6:
			if(displayDiode(ADCAverage) == -1) {
				displayReverse();
			} else {
				displayForward();
			}
		break;
		// Transistor
		case 7:
			if(displayTransistor(ADCAverage) < 0) {
				//displayReading((double)"PNP");
			} else {
				//displayReading((double)"NPN");
			}
		break;
	}
	
}

void TIM5_IRQHandler(void) {
 	// clear IRQ flag in TIM5
 	TIM5->SR &= ~0x00000001;      
	
	ADCAverage = 0.0;
	
	// Poll the ADC
	uint32_t ADCValue = ADC1value();
	// Add the value to the averages
	for(int i = 0; i < ADCSampleCount; i++) {
		if(i != ADCSampleCount - 1) {
			ADCValues[i] = ADCValues[i + 1]; 
		} else {			
			ADCValues[i] = ADCValue;
		}
		
		ADCAverage += ADCValues[i];
	}
	
	ADCAverage /= (double)ADCSampleCount;
	
	setModule(interfaceVals->typeIndex);

	if(interfaceVals->autoRangeState == 1) {
		interfaceVals->autoRangeCount++;	
		
		if(interfaceVals->autoRangeCount == 200) {
			int newRange =  autoRange(interfaceVals->typeIndex, interfaceVals->rangeIndex, ADCAverage);
			interfaceVals->autoRangeCount = 0;
			if(newRange != interfaceVals->rangeIndex) {
				displayClear();
				interfaceVals->rangeIndex = newRange;
			}
		}
	} 
	
	setRange(interfaceVals->typeIndex, interfaceVals->rangeIndex, ADCAverage);
	
	// Display settings
	interfaceVals->dispcount++;
	
	
	
	if (interfaceVals->dispcount ==  20) {
		
		
	//display
	//displayClear();
	display(interfaceVals->readType, 
					interfaceVals->voltageRange, 
					interfaceVals->currentRange, 
					interfaceVals->resistanceRange, 
					interfaceVals->capacitanceRange, 
					interfaceVals->typeIndex, 
					interfaceVals->rangeIndex, 
					interfaceVals->autoRangeState,
				  interfaceVals->commsState);	
	//reset the counter
	interfaceVals->dispcount = 0;
	}	
}

void TIM2_IRQHandler(void) {
	// clear IRQ flag in TIM3
	TIM2->SR &= ~0x00000001;      
	
	// Check button press
	int curbtn = getButtonPressed();
	
	if( interfaceVals->prevbtn == curbtn ){
		
		if(interfaceVals->debCount == 3 && curbtn != 0) {
			displayClear();
			processButtonPress(curbtn, &interfaceVals->typeIndex, &interfaceVals->rangeIndex, &interfaceVals->autoRangeState, &interfaceVals->commsState);
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
