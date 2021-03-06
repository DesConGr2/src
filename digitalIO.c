#include "digitalIO.h"
#include "stm32f4xx.h" 
#include <string.h>

// GPIOB & GPIOE will be used for the outputs
// GPIOC will be used for the inputs
void initDigitalIO(void) {
	// Enable GPIOB and GPIOE clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOEEN;
	// Set GPIOB pins 4, 5, 7, 8 and 15 for output
	// 01 is the MODER code for output
	GPIOB->MODER &= 0x3FFC30FF;
	GPIOB->MODER |= 0x00014500;
	// Set GPIOE pins 3, 4, 5, 6 and 7 for output
	GPIOE->MODER &= 0xFFFF003F;
	GPIOE->MODER |= 0x00005540;
	// Set GPIOC pins 6 and 13 to input
	// 00 is the MODER code for General purpose input
	GPIOC->MODER &= 0xF3FFCFFF;
}

int setPin(char* pinLine, int pin, int val) {
	if(strncmp(pinLine, "J5", 2) == 0) {
		if((pin < 4) || (pin == 6) || ((pin > 8) && (pin < 15)) || (pin > 15)) {
			// A user has tried to write outside of the pins available on J5
			// Return with a failure code
			return 0;
		}
		
		
	} else if(strncmp(pinLine, "J7", 2) == 0) {
		if((pin < 3) || (pin > 7)) {
			// A user has tried to write outside of the pins available on J7
			// Return with a failure code
			return 0;
		}	
	}
	
	if((val < 0) || (val > 1)) {
		// The value to be written is outside the range of possible values,
		// The only values that are allowed are 0 and 1
		return -1;
	}
	// Shift a high bit to the desired pin position
		uint32_t output = (1 << pin);
	
	if(val == 1) {
		if(strncmp(pinLine, "J5", 2) == 0) {
			//Set the bit on the pin high
			GPIOB->ODR |= output;
		} else if(strncmp(pinLine, "J7", 2) == 0) {
			GPIOE->ODR |= output;
		}
		// Return with a success code
		return 1;
	}
	else {
		if(strncmp(pinLine, "J5", 2) == 0) {
			// Set the bit on the pin low
			GPIOB->ODR &= ~output;
		} else if(strncmp(pinLine, "J7", 2) == 0) {
			GPIOE->ODR &= ~output;
		}
			
		// Return with a success code
		return 1;
	}
}

int readPin(int pin) {
	if(!(pin == 6 || pin == 13)) {
		return -1;
	}

	// Get the value of GPIOB's Input Data Register
	uint32_t input = GPIOC->IDR;
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
