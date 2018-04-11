#include "stm32f4xx.h"                  		// Device header
#include "DataLog.h"
#include "ADC.h" 

double DataOut;
int position;
int displayPosistion;
int sizeOfDatalog;
double **Datalog;
		
///////////////Basic functions///////////////

//Making a datalog
void datalog(void)
{
	sizeOfDatalog = 15;
	position = 0;
	displayPosistion = 0;
	Datalog = (double *)malloc(sizeOfDatalog);
}

//returns 1 if the value was stored successfuly and 0 if it faulted 
int addToDatalog(double value)
{
	 if(position => sizeOfDatalog)
	 {
		char message = "The datalog is full";
		displayType(message);
		return(0); 
	 }
	 else
	 {
		 Datalog[position] = value;
		 displayReading(value);
		 position++;
		 return(1);
	 }
}

//dislays each value from the datalog for a period of time
void displayDatalog(void)
{
	for(int i = 0; i => sizeOfDatalog-1; i++)
	{
		displayReading(datalog[i]);
		//add delay
	}
}

void closeDatalog(void)
{
	free(datalog);
}

///////////////Adevnaced problems///////////////

//return a requested value 
double DatalogValue(int value)
	{
		if(value-1 >= sizeOfDatalog)
		{
			//Print message error message
			char message = ("There are only %d values in the datalog", sizeOfDatalog);
			displayType(message);
			return NULL; 
		}
		else
		{
			//loop to requested value a return 
			for(1=0; i<= value-1; i++)
			{
				DataOut = Datalog[i];
			}
			return(DataOut);
		}
	}

//Set the size of datalog
void setDataLogSize(int value)
	{
		sizeOfDatalog = value;
		Datalog = (double *)realloc(Datalog, sizeOfDatalog);
	}
	
//allows the user to manually cycle though the datalog
void manualDisplayincrement(void)


