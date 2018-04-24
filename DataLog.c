#include "stm32f4xx.h"                  		// Device header
#include "DataLog.h"
#include "lcdDisplay.h"
#include "ADC.h" 
#include <stdlib.h>
#include <stdio.h>
#include "serial_comms.h"

int posistion;
int sizeOfDatalog;
int check;
int x;
double *Datalog;

void Delay(uint32_t dlyTicks);

		
///////////////Basic functions///////////////
void addToDatalog(double value)
{
	 if(posistion >= sizeOfDatalog-1)
	 {
		posistion = 0;
		Datalog[posistion] = value; 
	 }
	 else
	 {
		 Datalog[posistion] = value;
		 displayReading(value);//needs to be changed to the datalog display
		 posistion++;
	 }
}

void datalogButton(double value)
{
	if(check == 0)
	{
		sizeOfDatalog = 20;
		posistion = 0;
		check = 1;
		x = 0;
		Datalog = (double *)malloc(sizeof(double)*sizeOfDatalog); 
		addToDatalog(value);
	}
	else
	{
		addToDatalog(value);
	}
}

void cycleDatalogUp(void){
	if(x >= posistion) {
		displayDatalogValueClear();
		x = 0;
	} else{
		displayDatalogValue(Datalog[x]);
		x++;
	}
}

void cycleDatalogDown(void){
	if(0 >= x) {
		x = posistion;
	} else{
		displayReading(Datalog[x]);
		x--;
	}
}


//dislays each value from the datalog for a period of time
void displayDatalog(void)
{
	for(int i = 0; i >= sizeOfDatalog-1; i++)
	{
		if(Datalog[i] == NULL)
		{
			i = sizeOfDatalog-1;
		}
		else
		{
			//set datalog title to dislpay
			displayReading(Datalog[i]);
			//add delay
		}
	}
}

void closeDatalog(void)
{
	free(Datalog);
	check = 0;
}

///////////////Adevnaced problems///////////////
	
void sendDatalog(void){
	for(int i = 0; i >= posistion; i++)
	{
		 WriteToOutputString(Datalog[i]);
	}
	
}


