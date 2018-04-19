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

//void SysTick_Handler(void);
//// Delays number of tick Syst icks (happens every 1 ms)
//void Delay(uint32_t dlyTicks);

int main (void) {

	//Control of system clock
//  SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
//  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
//    while (1);                                  /* Capture error              */
//  }
	
	//initialise
	initDigitalIO();
	// TODO: change to 'initADC1()' to be consistent with the other naming
	ADC1Init();
	initUI();
	//CommsInit();
	
	// Do DAC things
//	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
//	RCC->APB1ENR |= RCC_APB1ENR_DACEN;
//	
	// DONT NEED TO ADJUST GPIOA, ITS ALREADY BEING SETUP IN THE DISPLAY CODE
//	// Set the DAC1 pin to analog mode
//	//GPIOA->MODER = 0x3 << (2 * 4);
//	// Disable terminating resistors
//	GPIOA->PUPDR = 0;
//	
//	DAC1->CR |= DAC_CR_EN1;
//	DAC1->CR |= DAC_CR_BOFF1;
//	
//	DAC1->DHR12R1 |= 0xac6;
	
	
	
	
	
	
	
	//initFreqCalc();

	//Wlecome message (tests screen)
	//turnBuzzerOn();
	//displayType("Welcome!");
	//Delay(1000);
  //displayClear();
	//turnBuzzerOff();
	
	
	while(1) {
//		if (GPIOE->IDR & 0x0001) GPIOA->ODR |=  0x0040;   // LED on
//    else                     GPIOA->ODR &= ~0x0040;   // else LED off
//    if (GPIOE->IDR & 0x0002) UART4->DR = 'a';   // send    
//    for (int i = 0; i<100000; i++) {};          // waste time
	}
		
}

//// Counts 1ms timeTicks
//volatile uint32_t msTicks;
///*----------------------------------------------------------------------------
//  SysTick_Handler
// *----------------------------------------------------------------------------*/
//void SysTick_Handler(void) {
//  msTicks++;
//}
///*----------------------------------------------------------------------------
//  delays number of tick Systicks (happens every 1 ms)
// *----------------------------------------------------------------------------*/
//void Delay (uint32_t dlyTicks) {                                              
//  uint32_t curTicks;

//  curTicks = msTicks;
//  while ((msTicks - curTicks) < dlyTicks);
//}

///*----------------------------------------------------------------------------//
//// Code to deal with the user interface and the screen refresh rate...				//
//// Multithreading would be ideal but fork() and <sys/types.h> are Os related	//
//// libraries and functions, so no good for development board. Investigate 		//
//// other ways of threading, but for now will use time slicing for system			//
//// Coded by: jjds502																													//
//// Inital version: 23/03/2018																									//
//// Consider using interrupts...																								//
////																																						//
//// https://www.fmf.uni-lj.si/~ponikvar/STM32F407%20project/										//
//// https://stm32f4-discovery.net/2014/08/stm32f4-external-interrupts-tutorial/
////----------------------------------------------------------------------------*/






