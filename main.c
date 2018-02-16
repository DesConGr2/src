#include "stm32f4xx.h"                  		// Device header
#include <stdio.h>
#include <stdlib.h>

#include "ADC.h"
#include "lcdDisplay.h"
#include "buttons.h"

// NOTE (chris): I am choosing to use the board edge connector J5 for all the digital inputs
// 							 and J7 for all the digital outputs
// TODO (chris): move these functions out into their own header
void initDigitalIO();
int setPin(int pin, int val);
int readPin(int pin); 

int main (void) {
  // GPIOD/A/B clocks setup in this
	initDisplay();  
	// GPIOE clock set up in this
  initButtons();	
	
	initDigitalIO();
	
	// Read from GPIOB pin 4
	uint32_t input = GPIOB->IDR;
	int p4val;
	
	if((input & 0x00000010) == 1) {
		p4val = 1;
	} else {
		p4val = 0;
	}
	
  while(1) {                                                                   		
		displayInt(getButtonPressed());
		// TODO: figure out how to sleep the thread
	}
}

// GPIOB will be used for the inputs
// GPIOE will be used for the outputs
void initDigitalIO() {
	// Enable GPIOB and GPIOE clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOEEN;
	// Set GPIOB pins 4, 5, 7, 8 and 15 for input
	// 00 is the MODER code for input
	GPIOB->MODER &= 0x3FFC30FF;
	// Set GPIOE pins 3, 4, 5, 6 and 7 for output
	// 01 is the MODER code for General purpose output
	GPIOE->MODER &= 0xFFFF003F;
	GPIOE->MODER |= 0x00005540;
}

// Function will return:
//											 0  if the function received a pin that is out of range 
//											-1  if the functino received a value that is out of range
//											 1  if the write was successful
// @INCOMPLETE: this is not consistent with anything else
// here val can be either 0 or 1, we want to be able to set a pin high or low
int setPin(int pin, int val) {
	if((pin < 3) || (pin > 7)) {
		// A user has tried to write outside of the pins available on J7
		// Return with a failure code
		return 0;
	}
	if((val < 0) || (val > 1)) {
		// The value to be written is outside the range of possible values,
		// The only values that are allowed are 0 and 1
		return -1;
	}
	// Shift a high bit to the desired pin position
		uint32_t output = (1 << pin);
	
	if(val == 1) {
		//Set the bit on the pin high
		GPIOE->ODR |= output;
		// Return with a success code
		return 1;
	}
	else {
		// Set the bit on the pin low
		GPIOE->ODR ^= output;
		// Return with a success code
		return 1;
	}
}

// Function will return: 
//										  -1 if the desired pin is not valid											
//											 1 if the pin is high
//											 0 if the pin is low
int readPin(int pin) {
	if((pin < 4) || (pin == 6) || ((pin > 8) && (pin < 15)) || (pin > 15)) {
		// The desired pin is not valid
		return -1;
	}
	// Get the value of GPIOB's Input Data Register
	uint32_t input = GPIOB->IDR;
	// Isolate only the desired pin
	input &= (1 << pin);
	// Check the value of the pin
	if(input == 0) {
		// The pin was low, return 0
		return 0;
	} else {
		// The pin was high, return 1 
		return 1;
	}
}
