#include <stdio.h>
#include <stdlib.h>

#include "stm32f4xx.h"
#include "serial_comms.h"


//---------------------------------------------------------------//
// When opening the connection use a baud rate of 25000					 //
//---------------------------------------------------------------//

void CommsInit(void) {
	
		// Module adapted from Serial_Port_Communication_with_the_FTDI_UM232H.pdf
	  // Version 0.3 April 2018 - Dave Pearce
		// Adapted from void PB_FTDI_Init() (Page 6)
	
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
		 //USART2->CR1 = (1UL << 13) | (1UL << 3);
		 USART2->CR1 |= USART_CR1_TE | USART_CR1_UE;

		 // Turn clock to GPIOA on, set-up PA2 as an output, and configure
		 // PA2 to take input from USART2 (note you have to turn the clock
		 // on before writing to the register):
		 RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
		 //GPIOA->AFR[0] = (GPIOA->AFR[0] & 0xFFFFF0FF) | (0x7 << 8);
		 GPIOA->MODER &= ~GPIO_MODER_MODE2_Msk;
		 GPIOA->MODER |= GPIO_MODER_MODE2_1;
		 
		 GPIOA->AFR[0] |= GPIO_AFRL_AFRL2_0;
		 GPIOA->AFR[0] |= GPIO_AFRL_AFRL2_1;
		 GPIOA->AFR[0] |= GPIO_AFRL_AFRL2_2;
		 GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL2_3;
		 // Set mode to alternate function IO push-pull output:
		 //unsigned int bit = 2;
		 //unsigned long bitMask = ~(3UL << 2*bit);
		 

}

void PB_FTDI_Wait_Until_Ready() {
	
 // Module from Serial_Port_Communication_with_the_FTDI_UM232H.pdf
 // Version 0.3 April 2018 - Dave Pearce
 // See void PB_FTDI_Init() (Page 7)
	
 unsigned int bReady = 0;
 do {
 bReady = USART2->SR & (1UL << 7);
 } while (!bReady);
} 

void PB_FTDI_Send(char *OutString, int howMany) {
	
 // Module from Serial_Port_Communication_with_the_FTDI_UM232H.pdf
 // Version 0.3 April 2018 - Dave Pearce
 // See void void PB_FTDI_Send()  (Page 7)
	
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
		sprintf(OutString, "%.4f", output);
		
		// JUST SEND IT OMG
		PB_FTDI_Send(OutString, 16);
		PB_FTDI_SendNewLine();
	
		free(OutString);
}

void writeStringAsOutput(char *output) {
	
		// JUST SEND IT OMG
		PB_FTDI_Send(output, 16);
		PB_FTDI_SendNewLine();
}


void WriteDataLogMessage() {
	
		//Simply specify to user that the data is from the data log
		PB_FTDI_Send("Data from Data log", 16);
		PB_FTDI_SendNewLine();

}

void PB_FTDI_SendNewLine() {
	
 // Module from Serial_Port_Communication_with_the_FTDI_UM232H.pdf
 // Version 0.3 April 2018 - Dave Pearce
 // See void void PB_FTDI_SendNewLine()  (Page 7)
	
 // Does what it says on the tin... sends a CR and LF: 
 PB_FTDI_Wait_Until_Ready();
 USART2->DR = '\r';
 PB_FTDI_Wait_Until_Ready();
 USART2->DR = '\n';
} 

