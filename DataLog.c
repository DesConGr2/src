#include "stm32f4xx.h"                  		
#include "DataLog.h"
#include "lcdDisplay.h"
#include "ADC.h" 
#include <stdlib.h>
#include <stdio.h>
#include "lcd_driver.h"	
#include "serial_comms.h"

int position;
int sizeOfDatalog = 20;
int check;
int x;
double DatalogValue[20];
char *DatalogType[20];
char DatalogRange[20];
//char Datalog[20]; 

//Issues so far:
//Why not implement it using an array? you seem to be randomly allocating memory and never deallocating it
//Using malloc without using the free() function, WILL fill the memory and crash the display
//You probably want to initialise the datalog and make a single structure of sizeOfDatalog amount of values

//e.g. 	double DataStruct[20]; //(or double DataStruct[sizeOfDataLog]; if you set DataLog as a const int)

//Do you need the range? how is the number stored, couldn't you just do the number and the type? e.g. 567.1234mV
//You could stor the type in a simple array also, then when you send them via comms, concantinate the strings or send them on after the other

//e.g. 	char *DataType[20];
//			char* output = malloc(sizeof(double) + sizeof(char)*4);
//			sprintf(output, "%f %s", DataStruct[i], DataType[i]);
//			writeStringAsOutput(ouput); 													--JJ has now written you this function in serial_comms
//			free(output); 																				--VERY IMPORTANT

//We have no more room on the display now that hardware have requested we show the reading type on the bottom line
//The only way to show this works will be using serial comms, or setting up a completely new mode on the board
//Both are very achievable on monday morning, just let's get working on it!
char displayDatalogRange(int range) {
	if(1 == range){
		return 'm';
	} else if(2 == range){
		return 'k';
	} else if(3 == range){
		return 'p';
	} else if(4 == range){
		return 'n';
	} else if(5 == range){
		return 'u';
	}else{
		return ' ';
	}
	
}

void addToDatalog(double value, int range, char *type){
	 if(position >= sizeOfDatalog-1){
		position = 1;
		DatalogValue[position] = value;
 		DatalogType[position] = type;
		DatalogRange[position] = displayDatalogRange(range);
		//char* value = (char *)malloc(sizeof(char));
		position++;
	 } else {
		 DatalogValue[position] = value;
		 DatalogType[position] = type;
		 DatalogRange[position] = displayDatalogRange(range);
		 position++;
	 }
}

void cycleDatalogUp(void){
	
	if(x >= position-1) {
		//displayDatalogValueClear();
		x = 0;
	} else{
		char *type = (char *)malloc(sizeof(char));
		x++;
		//displayReading(DatalogValue[x]);  
		
		//*type = DatalogType[x];
		
		//displayDatalogType(type, DatalogRange[x]);
		free(type);
		
	}
}

void cycleDatalogDown(void){
		if(1 >= x) {
		//displayDatalogValueClear();
		x = position; 
	} else {
		x--;
		//displayReading(DatalogValue[x]);
		char *type = (char *)malloc(sizeof(char));
		
		//*type = DatalogType[x];
		
		//displayDatalogType(type, DatalogRange[x]);
		free(type);
		
	}
}

void clearDatalog(void){
	free(DatalogValue);
	free(DatalogType);
	free(DatalogRange);
	check = 0;
	x = 0;
	position = 0; 
}

void sendDatalog(void){
	
	WriteDataLogMessage();
	
	char* output = malloc(sizeof(double) + sizeof(char)*4);		 													
			
	for(int i = 0; i < 20; i++){
		sprintf(output, "%f%c%s", DatalogValue[i], DatalogRange[i], DatalogType[i]);
		//sprintf(output, "%f%s", DatalogValue[i], DatalogType[i]);
		writeStringAsOutput(output);
	}
	free(output);
}

