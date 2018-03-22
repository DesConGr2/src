#include "lcdDisplay.h"
// Taken from "LCD Driver New Software" (written By Joel Ferguson) on the module webpage
#include "lcd_driver.h"											// Driver to control the LCD screen operation
#include <stdlib.h>
#include <stdio.h>

void initDisplay(void) {
	lcd_change_settings(LCD_POWER_ON, LCD_CURSOR_OFF, LCD_CBLINK_OFF);
	
	lcd_init(LCD_LINES_TWO, LCD_CURSOR_OFF, LCD_CBLINK_OFF, 16);
}

void displayType(char *string) {
	//lcd_clear_display();
	
	lcd_write_string(string, 0, 0);
}

void displayStringRange(char *string) {
	//lcd_clear_display();
	
	lcd_write_string(string, 0, 7);
}

void displayStringReading(char *string) {
	//lcd_clear_display();
	
	lcd_write_string(string, 1, 0);
}

void displayClear(void) {
	lcd_clear_display();
}

void displayReading(double value) {
	char *displayValue = (char *)malloc(sizeof(double) * 16);

	sprintf(displayValue, "%.4f", value);
	
	displayStringReading(displayValue);
	
	//bug fix by JJ, need to dealloc mem
	free(displayValue);
}

void displayRange(double value) {
	char *displayValue = (char *)malloc(sizeof(double) * 16);

	sprintf(displayValue, "%.3f", value);
	
	displayStringRange(displayValue);
	
	//bug fix by JJ, need to dealloc mem
	free(displayValue);
}
