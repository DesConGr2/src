#ifndef MATHSFUNCTIONS_H
#define MATHSFUNCTIONS_H
#include <stdint.h>

// Perform calculations to convert
double voltageRange10m(uint32_t ADCValue);
double voltageRange100m(uint32_t ADCValue);
double voltageRange1(uint32_t ADCValue);
double voltageRange10(uint32_t ADCValue);

double voltageRange10mAC(uint32_t ADCValue);
double voltageRange100mAC(uint32_t ADCValue);
double voltageRange1AC(uint32_t ADCValue);
double voltageRange10AC(uint32_t ADCValue);

double currentRange1m(uint32_t ADCValue);
double currentRange10m(uint32_t ADCValue);
double currentRange100m(uint32_t ADCValue);
double currentRange1(uint32_t ADCValue);

double resistanceRange1k(uint32_t ADCValue);
double resistanceRange5k(uint32_t ADCValue);
double resistanceRange10k(uint32_t ADCValue);
double resistanceRange50k(uint32_t ADCValue);
double resistanceRange100k(uint32_t ADCValue);
double resistanceRange500k(uint32_t ADCValue);
double resistanceRange1M(uint32_t ADCValue);

double capacitanceRangePF(double frequency);
double capacitanceRangeNF(double frequency);
double capacitanceRangeUF(double frequency);
double capacitanceRangeHighUF(double frequency);

#endif
