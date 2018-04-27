#include "stm32f4xx.h"   
#include "lcd_driver.h"	
#include "TransistorFunction.h"
#include <stdlib.h>
#include <stdio.h>

void displayTransistor(double value){
	if(value >= 0) {
		lcd_write_string("           ", 1, 9);
		lcd_write_string("PNP", 1, 9);
	} else if(0 >= value){
		lcd_write_string("           ", 1, 9);
		lcd_write_string("NPN", 1, 9);
	} else {
		lcd_write_string("           ", 1, 9);
	}
}
