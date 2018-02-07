#include "buttons.h"
#include "SWT.h"

void initButtons() {
	SWT_Init();
}

int getButtonPressed() {
	// Get the data from the relevant GPIO register 
	int buttons = SWT_Get();

	// Isolate the bits that pertain to the 8 buttons on the board
	buttons &= 0x0000FF00;

	// The leftmost button is button 1, the rightmost button is button 8
	// If no button has been pressed the value of buttons is set to 0 
	switch(buttons) {
		case 0x00000100:
			buttons = 1;
		break;
		case 0x00000200:
			buttons = 2;
		break;
		case 0x00000400:
			buttons = 3;
		break;
		case 0x00000800:
			buttons = 4;
		break;
		case 0x00001000:
			buttons = 5;
		break;
		case 0x00002000:
			buttons = 6;
		break;
		case 0x00004000:
			buttons = 7;
		break;
		case 0x00008000:
			buttons = 8;
		break;
		default:
			buttons = 0;
		break;
	}

	return buttons;
}