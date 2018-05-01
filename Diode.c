#include "stm32f4xx.h"   
#include "Diode.h"
#include <stdlib.h>
#include <stdio.h>

int displayDiode(double value){
	if(value >= 0) {
		 //displayForward();
		return -1;
	} else if(0 > value){
		 //displayReverse();
		return 1;
	} else {
		return 0;
	}
}
