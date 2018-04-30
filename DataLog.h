#ifndef DataLog_H
#define DataLog_H

void clearDatalog(void);

void addToDatalog(double value, int range, char *type);

void cycleDatalogDown(void);

void cycleDatalogUp(void);

void sendDatalog(void);

#endif
