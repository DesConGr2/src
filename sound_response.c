#include "sound_response.h"
#include "digitalIO.h"
#include "ADC.h"

void turnBuzzerOn(void){
		setPin("J7", 6, 1);
}

void turnBuzzerOff(void){
		setPin("J7", 6, 0);
}
