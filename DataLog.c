#include "stm32f4xx.h"                  		
#include "DataLog.h"
#include "lcdDisplay.h"
#include "ADC.h" 
#include <stdlib.h>
#include <stdio.h>
#include "lcd_driver.h"	
#include "serial_comms.h"

int position;
int sizeOfDatalog;
int check;
int x;
double *DatalogValue;
char *DatalogType;
int *DatalogRange;

void addToDatalog(double value, int range, char *type){
	 if(position >= sizeOfDatalog-1){
		position = 1;
		DatalogValue[position] = value;
 		DatalogType[position] = *type;
		DatalogRange[position] = range;
		position++;
	 } else {
		 DatalogValue[position] = value;
		DatalogRange[position] = range;
		 DatalogType[position] = *type;
		 position++;
	 }
}

void datalogButton(double value, int range, char *type){
	if(check == 0){
		sizeOfDatalog = 20;
		position = 1;
		check = 1;
		x = 0;
		DatalogValue = (double *)malloc(sizeof(double)*sizeOfDatalog); 
		DatalogRange = (int *)malloc(sizeof(int)*sizeOfDatalog);
		DatalogType = (char *)malloc(sizeof(char)*sizeOfDatalog);
		addToDatalog(value, range, type);
	} else {
		addToDatalog(value, range, type);
	}
}

void displayDatalogType(char *string, int range) {
	if(1 == range){
		lcd_write_string("m", 1, 8);
	} else {
		lcd_write_string(" ", 1, 8);
	}
	lcd_write_string(string, 1, 9);
}


void cycleDatalogUp(void){
	
	if(x >= position-1) {
		//displayDatalogValueClear();
		x = 0;
	} else{
		char *type = (char *)malloc(sizeof(char));
		x++;
		//displayReading(DatalogValue[x]);  
		*type = DatalogType[x];
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
		*type = DatalogType[x];
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
	//lcd_write_string("claer", 1, 7);
}

void sendDatalog(void){
	for(int i = 0; i >= position; i++){
		 WriteToOutputString(DatalogValue[i]);
	}
}

void displayDatalogValueClear(void) {
	//lcd_write_string("               ", 1, 0);
}

