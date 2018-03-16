/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: MOdification to Drive 2x16 LCD
 * Note(s): 
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/
 
 /* MODIFIED BY D. CHESMORE JANUARY 2013   */
 
#include <stdio.h>
#include <stdlib.h>
#include "STM32F4xx.h"

#include "ADC.h"
#include "lcdDisplay.h"
#include "buttons.h"
#include "digitalIO.h"
#include "MathsFunctions.h"


volatile uint32_t msTicks;                      /* counts 1ms timeTicks       */
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

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {

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
	
	//Control of system clock
  SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }

	//Declare variables
	int btnPressed;
	
	//Define the arrays for the user options
	char *RDTYPE[3] = {"V  ", "A  ", "Ohm"};
	double VRANGE[3] = {12, 1, 0.1};
	double ARANGE[3] = {1, 0.1, 0.01};
	double RRANGE[3] = {1, 10, 100};
	int TYPindex = 0, RNGindex = 0;
	
	//initialise
	initButtons();
	initDisplay();
	initDigitalIO();
	ADC1Init();
	
	//Wlecome message (tests screen)
	displayType("Welcome!");
	Delay(1000);
	displayClear();
	
	while(1)
	{
		//Display refresh cycle
		Delay(200);
		
		btnPressed = getButtonPressed();
		//----------------------------Check Button press--------------------------------------//
		switch(btnPressed){
			case 1 :
				//this button increments read type
				if(TYPindex == 2) {
					TYPindex = 0;
				} else {
					++TYPindex;
				}
				break;
				
			case 2 :
				//this button decrements read type
				if(TYPindex == 0) {
					TYPindex = 2;
				} else {
					--TYPindex;
				}
				break;
				
			case 3 :
				//this button increments read type
				if(RNGindex == 2) {
					RNGindex = 0;
				} else {
					++RNGindex;
				}
				break;
				
			case 4 :
				//this button decrements read type
				if(RNGindex == 0) {
					RNGindex = 2;
				} else {
					--RNGindex;
				}
				break;
				
		}
		//------------------------------------Display settings--------------------------------//
		
		//display type
		displayType(RDTYPE[TYPindex]);
		
		//display resolution
		switch(TYPindex){
			case 0:
				//Display the range (resolution)
				displayRange(VRANGE[RNGindex]);
			
				//---- Code for displaying the reading ----//
				switch(RNGindex){
					case 0:
							displayReading(range12());
					break;
					
					case 1:
						displayReading(range1());
					break;
					
					case 2:
						displayReading(range100m());
					break;
				}
				//-----------------------------------------//
			break;
			
			case 1:
				//Display the range (resolution)
				displayRange(ARANGE[RNGindex]);
			
				//---- Code for displaying the reading ----//
				displayReading(readADC1());
				//-----------------------------------------//
			break;
			
			case 2:
				//Display the range (resolution)
				displayRange(RRANGE[RNGindex]);
			
				//---- Code for displaying the reading ----//
				displayReading(readADC1());
				//-----------------------------------------//
			break;
		}
	}
				
}

