#ifndef FREQCALC_H
#define FREQCALC_H

#include <stdlib.h>

typedef struct MeasurementVals {
	int lastReadVal;
	int hasStartedTiming;
	int timerCount;
} MeasurementVals;

// Based on an input digital pulse code signal, measure the frequency of that signal
void initFreqCalc(MeasurementVals *vals);
void startFreqCalc(void);
void stopFreqCalc(void);
double getFreq(void);

#endif
