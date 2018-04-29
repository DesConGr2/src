#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

// Initialise the LCD display
void initDisplay(void);
// Display a string on the LCD display
void displayType(char *string);
void displayStringRange(char *string);
void displayReading(double value);
void displayIntReading(int value);
void displayClear(void);
// Display an integer value on the LCD display
//void displayInt(int value);
void displayRange(double value);
void displayAuto(int toggle);
void displayComms(int toggle);
void displayLogging(int toggle);

void displayV(void);
void displaymV(void);
void displayA(void);
void displaymA(void);
void displayOhm(void);
void displaykOhm(void);
void displayMOhm(void);
void displayHz(void);
void displaykHz(void);
void displayMHz(void);
void displaypF(void);
void displaynF(void);
void displayuF(void);
void displayForward(void);
void displayReverse(void);

#endif
