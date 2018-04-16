#include <stdio.h>
#include <stdlib.h>

#include "stm32f4xx.h"
#include "serial_comms.h"


//---------------------------------------------------------------//
// When opening the connection use a baud rate of 25000					 //
// Initial tests have had the connection at COM6 port						 //
//---------------------------------------------------------------//

void CommsInit(void) {
		 // USART2 is connected to the FTDI module via PA2) 
		 const unsigned int RCC_APB1RSTR = RCC_BASE + 0x20;
		 const unsigned int USART2_BIT_IN_RCC = RCC_APB1RSTR_USART2RST_Pos;

		 RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // Enable the UART2 clock

		 // First, reset the UART then bring it out of reset:
		 *(unsigned int*)RCC_APB1RSTR |= 1UL << USART2_BIT_IN_RCC;
		 *(unsigned int*)RCC_APB1RSTR &= ~(1UL << USART2_BIT_IN_RCC);

		 // Set up the baud rate for the UART as a division from 1 MHz,
		 // to four binary places. For example, for 9600 baud, 1 MHz
		 // / 104 = 9600. That's less than 0.2% out, and it’s close
		 // enough. (Note: this works up to 1 MBaud.)
		 USART2->BRR = 104 << 4; // Set for 9600 baud
		 USART2->CR1 = (1UL << 13) | (1UL << 3);

		 // Turn clock to GPIOA on, set-up PA2 as an output, and configure
		 // PA2 to take input from USART2 (note you have to turn the clock
		 // on before writing to the register):
		 RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
		 GPIOA->AFR[0] = (GPIOA->AFR[0] & 0xFFFFF0FF) | (0x7 << 8);
		 // Set mode to alternate function IO push-pull output:
		 unsigned int bit = 2;
		 unsigned long bitMask = ~(3UL << 2*bit);
		 GPIOA->MODER = (GPIOA->MODER & bitMask) | (2UL << 2*bit); 

}

void PB_FTDI_Wait_Until_Ready() {
 unsigned int bReady = 0;
 do {
 bReady = USART2->SR & (1UL << 7);
 } while (!bReady);
} 


void PB_FTDI_Send(char *OutString, int howMany) {
 // Sends howMany bytes, starting at the address pointed to by
 // bytes, or until it reaches the end of the string (whichever
 // happens first).
 unsigned int next = 0;
 while (next++ < howMany && *OutString) {
 PB_FTDI_Wait_Until_Ready();
 USART2->DR = *OutString++;
 }
} 


void WriteToOutputString(double output) {
	
			
		// Initialise the Output String
		char *OutString = (char *)malloc(sizeof(double) * 16);
	
		// ENSURE TO CALL THIS FUNCTION BEFORE STARTING TO SEND THE STRING
		// OTHERWISE YOU WILL NOT SEND ANYTHING COHERENT AND IT MAY GET STUCK
		sprintf(OutString, "%.4f", output);
		
		// JUST SEND IT OMG
		PB_FTDI_Send(OutString, 16);
	
		free(OutString);
}

void SendViaSerial(void) {
	
}

void PB_FTDI_SendNewLine() {
 // Does what it says on the tin... sends a CR and LF: 
 PB_FTDI_Wait_Until_Ready();
 USART2->DR = '\r';
 PB_FTDI_Wait_Until_Ready();
 USART2->DR = '\n';
} 

