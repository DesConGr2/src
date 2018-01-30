#include "lcd_display.h"
// Taken from "LCD Driver New Software" (written By Joel Ferguson) on the module webpage
#include "lcd_driver.h"											// Driver to control the LCD screen operation

void initDisplay(void) {
	lcd_change_settings(LCD_POWER_ON, LCD_CURSOR_OFF, LCD_CBLINK_OFF);
	
	lcd_init(LCD_LINES_ONE, LCD_CURSOR_OFF, LCD_CBLINK_OFF, 16);
}


void displayString(char *string) {
	lcd_write_string(string, 0, 0);
}
