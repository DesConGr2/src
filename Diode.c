#include "stm32f4xx.h"   
#include "Diode.h"
#include <stdlib.h>
#include <stdio.h>

int displayDiode(double value){
	if(value >= 1.5) {
		 //displayForward();
		return 1;
	} else if(1.5 >= value){
		 //displayReverse();
		return -1;
	} else {
		return 0;
	}
}
