#include "lcdDisplay.h"
// Taken from "LCD Driver New Software" (written By Joel Ferguson) on the module webpage
#include "lcd_driver.h"											// Driver to control the LCD screen operation
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void initDisplay(void) {
	lcd_change_settings(LCD_POWER_OFF, LCD_CURSOR_OFF, LCD_CBLINK_OFF);
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
	//lcd_write_string("         ", 1, 8);
}

void displayClear(void) {
	lcd_clear_display();
}

void displayReading(double value) {
	char *displayValue = (char *)malloc(sizeof(double) * 16);

	//Display the reading
	sprintf(displayValue, "%.4f", value);
	displayStringReading(displayValue);
	
	//fill the remaining space
	int ExtraSpace = strlen(displayValue);
	
	for(int i = ExtraSpace; i < 12; i++){
			lcd_write_string(" ", 1, i);
	}
	//bug fix by JJ, need to dealloc mem
	free(displayValue);
}

void displayIntReading(int value) {
	char *displayValue = (char *)malloc(sizeof(int) * 16);

	sprintf(displayValue, "%i", value);
	
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

void displayComms(int toggle) {
		//simply display an A if auto ranging is on
		if(toggle == 1){
			lcd_write_string("S", 0, 14);
		} else {
			lcd_write_string(" ", 0, 14);
		}
}

void displayLogging(int toggle) {
		//simply display an A if auto ranging is on
		if(toggle == 1){
			lcd_write_string("D", 0, 13);
		} else {
			lcd_write_string(" ", 0, 13);
		}
}

void displayV(void){
lcd_write_string("V   ", 1, 12);
}

void displaymV(void) {
	lcd_write_string("mV  ", 1, 12);
}

void displayA(void) {
	lcd_write_string("A   ", 1, 12);
}

void displaymA(void) {
	lcd_write_string("mA  ", 1, 12);
}

void displayOhm(void) {
	lcd_write_string("Ohm ", 1, 12);
}

void displaykOhm(void) {
	lcd_write_string("kOhm", 1, 12);
}

void displayMOhm(void) {
	lcd_write_string("MOhm", 1, 12);
}

void displayHz(void) {
	lcd_write_string("Hz  ", 1, 12);
}

void displaykHz(void) {
	lcd_write_string("kHz ", 1, 12);
}

void displayMHz(void) {
	lcd_write_string("MHz ", 1, 12);
}

void displaypF(void) {
	lcd_write_string("pF  ", 1, 12);
}

void displaynF(void) {
	lcd_write_string("nF  ", 1, 12);
}

void displayuF(void) {
	lcd_write_string("uF  ", 1, 12);
}

void displayForward(void) {
	lcd_write_string("+-", 0, 13);
	lcd_write_string("Forward Bias PN", 1, 0);
}

void displayReverse(void) {
	lcd_write_string("+-", 0, 13);
	lcd_write_string("Reverse Bias NP", 1, 0);
}

void displayPNP(void) {
	lcd_write_string("+-", 0, 13);
	lcd_write_string("PNP", 1, 13);
}

void displayNPN(void) {
	lcd_write_string("+-", 0, 13);
	lcd_write_string("NPN", 1, 13);
}

