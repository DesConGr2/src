#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

// Initialise the LCD display
void initDisplay(void);
// Display a string on the LCD display
void displayType(char *string);
void displayStringRange(char *string);
void displayReading(double value);
void displayClear(void);
// Display an integer value on the LCD display
//void displayInt(int value);
void displayRange(double value);
void displayAuto(int toggle);
void displayComms(int toggle);


#endif
