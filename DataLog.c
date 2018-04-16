#include "stm32f4xx.h"                  		// Device header
#include "DataLog.h"
#include "lcdDisplay.h"
#include "ADC.h" 
#include <stdlib.h>
#include <stdio.h>


double DataOut;
int position;
int displayPosistion;
int sizeOfDatalog;
int check;
double *Datalog;

		
///////////////Basic functions///////////////
void addToDatalog(double value)
{
	 if(position >= sizeOfDatalog-1)
	 {
		displayType("The datalog is full");//To be displayed in the datalog sections of dislpay
		//delay
		displayType("                   ");
	 }
	 else
	 {
		 Datalog[position] = value;
		 displayReading(value);//needs to be changed to the datalog display
		 position++;
	 }
}

//Make's a datalog 
void datalogButton(double value)
{
	if(check == 0)
	{
		sizeOfDatalog = 15;
		position = 0;
		displayPosistion = 0;
		check = 1;
		Datalog = (double *)malloc(sizeof(sizeOfDatalog));
		addToDatalog(value);
	}
	else
	{
		addToDatalog(value);
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
	free(datalog);
}

///////////////Adevnaced problems///////////////
	
//allows the user to manually cycle though the datalog
void manualDisplayIncrement(void)
{
	if(displayPosistion != sizeOfDatalog-1)
	{
		displayPosistion++;
		displayReading(displayPosistion);//Needs to be changed to the datalog section
	}
}

void manualDisplayDecrement(void)
{
	if(displayPosistion != 0)
	{
		displayPosistion--;
		displayReading(displayPosistion);//Needs to be changed to the datalog section
	}
}

//Set the size of datalog
void setDataLogSize(int value)
	{
		sizeOfDatalog = value;
		Datalog = (double *)realloc(Datalog, sizeOfDatalog);
	}
	



