#ifndef DataLog_H
#define DataLog_H

void clearDatalog(void);

void datalogButton(double value, int range, char *type);

void cycleDatalogDown(void);

void cycleDatalogUp(void);

void sendDatalog(void);

void displayDatalogValueClear(void);
	
#endif
