#ifndef DIGITALIO_H
#define DIGITALIO_H

// NOTE (chris): I am choosing to use the board edge connector J5 for all the digital inputs
// 							 and J7 for all the digital outputs

// Initialise GPIOB and GPIOE for reading and writing to respectively
void initDigitalIO(void);

// Function will return:
//											 0  if the function received a pin that is out of range 
//											-1  if the functino received a value that is out of range
//											 1  if the write was successful
// here val can be either 0 or 1, we want to be able to set a pin high or low
int setPin(int pin, int val);

// Function will return: 
//										  -1 if the desired pin is not valid											
//											 1 if the pin is high
//											 0 if the pin is low
int readPin(int pin); 

#endif
