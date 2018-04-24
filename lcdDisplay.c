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

void displayAuto(int toggle) {
		//simply display an A if auto ranging is on
		if(toggle == 1){
			lcd_write_string("A", 0, 15);
		} else {
			lcd_write_string(" ", 0, 15);
		}
}

void displayLog(char *string) {
		//simply display an Log if datalog is on
		lcd_write_string(string, 0, 3);
}

void displayDatalogValue(double value){
	char *displayValue = (char *)malloc(sizeof(double) * 16);

	sprintf(displayValue, "%.3f", value);
	
	lcd_write_string(displayValue, 1, 9);
	
	free(displayValue);
}

void displayDatalogValueClear(void) {
	lcd_write_string("        ", 1, 9);
}

void displayTransistor(double value){
	if(value >= 0) {
		lcd_write_string("           ", 1, 9);
		lcd_write_string("PNP", 1, 9);
	} else if(0 >= value){
		lcd_write_string("           ", 1, 9);
		lcd_write_string("NPN", 1, 9);
	} else {
		lcd_write_string("           ", 1, 9);
	}
}

void displayDiode(double value){
	if(value >= 0) {
		lcd_write_string("           ", 1, 9);
		lcd_write_string("Reverse", 1, 9);
	} else if(0 >= value){
		lcd_write_string("           ", 1, 9);
		lcd_write_string("Forward", 1, 9);
	} else {
		lcd_write_string("           ", 1, 9);
	}
}
	
/*void displayDatalog(int i, double value) {
	lcd_write_string("Value", 1, 0);
	
	char *displayi = (char *)malloc(sizeof(int) * 16);
	//sprintf(displayi, i);
	
	char *displayValue = (char *)malloc(sizeof(double) * 16);
	sprintf(displayValue, "%.3f", value);
	
}*/
