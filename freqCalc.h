#ifndef FREQCALC_H
#define FREQCALC_H

#include <stdlib.h>


// Based on an input digital pulse code signal, measure the frequency of that signal
void initFreqCalc(void);
void startFreqCalc(void);
void stopFreqCalc(void);
double getFrequency(void);
double getAveragedFrequency(void);
double getPeriod(void);

#endif
