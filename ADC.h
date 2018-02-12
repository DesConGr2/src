#ifndef ADC_H
#define ADC_H
	
	void ADC1Init(void);
	
	unsigned int readADC1(void);
	
	void ADC2Init(void);
	
	unsigned int  readADC2(void);
	
	void wait(int dlyTicks);
	
#endif
