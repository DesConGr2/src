#include "stm32f4xx.h"   
#include "lcd_driver.h"	
#include "TransistorFunction.h"
#include <stdlib.h>
#include <stdio.h>

int displayTransistor(double value){
	if(value >= 0) {
		// lcd_write_string("NPN", 1, 9);
		return 1;
	} else if(0 > value){
		// lcd_write_string("PNP", 1, 9);
		return -1;
	} else {
		return 0;
	}
}
