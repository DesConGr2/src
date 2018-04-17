#include "sound_response.h"
#include "digitalIO.h"
#include "ADC.h"

void turnBuzzerOn(void){
		setPin(6, 1);
}

void turnBuzzerOff(void){
		setPin(6, 0);
}
