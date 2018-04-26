#ifndef MATHSFUNCTIONS_H
#define MATHSFUNCTIONS_H
// Perform calculations to convert
double range1m(uint32_t ADCValue);
double range10m(uint32_t ADCValue);
double range100m(uint32_t ADCValue);
double range1(uint32_t ADCValue);
double range10(uint32_t ADCValue);

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

double testRange(void);

#endif
