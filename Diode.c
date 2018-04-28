#include "stm32f4xx.h"   
#include "lcd_driver.h"	
#include "Diode.h"
#include <stdlib.h>
#include <stdio.h>

int displayDiode(double value){
	if(value >= 1.5) {
		// lcd_write_string("           ", 1, 9);
		// lcd_write_string("Reverse", 1, 9);
		return -1;
	} else if(1.5 >= value){
		// lcd_write_string("           ", 1, 9);
		// lcd_write_string("Forward", 1, 9);
		return 1;
	} else {
		//lcd_write_string("           ", 1, 9);
	}
}
