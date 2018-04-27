#include "stm32f4xx.h"                  		
#include "DataLog.h"
#include "lcdDisplay.h"
#include "ADC.h" 
#include <stdlib.h>
#include <stdio.h>
#include "lcd_driver.h"	
#include "serial_comms.h"

int posistion;
int sizeOfDatalog;
int check;
int x;
double *DatalogValue;
char *DatalogType;
double *DatalogRange;

void addToDatalog(double value, double range, char *type){
	 if(posistion >= sizeOfDatalog-1){
		posistion = 0;
		DatalogValue[posistion] = value;
		DatalogRange[posistion] = range;
 		DatalogType[posistion] = *type;
		 posistion++;
	 } else {
		 DatalogValue[posistion] = value;
		 DatalogRange[posistion] = range;
		 DatalogType[posistion] = *type;
		 posistion++;
	 }
}

void datalogButton(double value, double range, char *type){
	if(check == 0){
		sizeOfDatalog = 20;
		posistion = 1;
		check = 1;
		x = 0;
		DatalogValue = (double *)malloc(sizeof(double)*sizeOfDatalog); 
		//DatalogRange = (double *)malloc(sizeof(double)*sizeOfDatalog);
		DatalogType = (char *)malloc(sizeof(char)*sizeOfDatalog);
		addToDatalog(value, range, type);
	} else {
		addToDatalog(value, range, type);
	}
}

void displayDatalogType(char *string, double range) {
	if(1 >= range){
		lcd_write_string("m", 1, 8);
	} else {
		lcd_write_string(" ", 1, 8);
	}
	lcd_write_string(string, 1, 9);
}


void cycleDatalogUp(void){
	if(x >= posistion-1) {
		displayDatalogValueClear();
		x = 0;
	} else{
		x++;
		displayReading(DatalogValue[x]);  
		char *type = (char *)malloc(sizeof(char));
		*type = DatalogType[x];
		displayDatalogType(type, DatalogRange[x]);
		free(type);
		
	}
}

void cycleDatalogDown(void){
	if(2 > x) {
		displayDatalogValueClear();
		x = posistion; 
	} else {
		x--;
		displayReading(DatalogValue[x]);
		char *type = (char *)malloc(sizeof(char));
		*type = DatalogType[x];
		displayDatalogType(type, DatalogRange[x]);
		free(type);
		
	}
}


//dislays each value from the datalog for a period of time
//void displayDatalog(void){
//	for(int i = 0; i >= sizeOfDatalog-1; i++){
//		if(DatalogValue[i] == NULL)
//		{
//			i = sizeOfDatalog-1;
//		}else{
//			//set datalog title to dislpay
//			displayReading(DatalogValue[i]);
//			//add delay
//		}
//	}
//}

void clearDatalog(void){
	free(DatalogValue);
	free(DatalogType);
	check = 0;
	x = 0;
	posistion = 0; 
	lcd_write_string("claer", 1, 7);
}

void sendDatalog(void){
	for(int i = 0; i >= posistion; i++){
		 WriteToOutputString(DatalogValue[i]);
	}
}

void displayDatalogValueClear(void) {
	lcd_write_string("               ", 1, 0);
}


