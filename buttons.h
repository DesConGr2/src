#ifndef BUTTONS_H
#define BUTTONS_H

// Initialise the buttons to be ready for use
// This step must be done before attempting to read the button presses 
void initButtons();

// Find which button has been pressed.
// The returned number will be between 0 and 8,
// 1 is the leftmost button on the board, 8 is the rightmost button on the board
// 0 indicated that no button has been pressed.
int getButtonPressed();

#endif