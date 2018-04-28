#ifndef HARDWARE_SELECTION_H
#define HARDWARE_SELECTION_H

// Modules:
// 0 - Voltage
// 1 - Current
// 2 - Resistance
// 3 - Frequency
// 4 - Capacitance

// Ranges:
// Voltage:
// 0 - 10      - 011
// 1 - 1       - 010
// 2 - 100m    - 001 
// 3 - 10m     - 000
// 4 - 10 AC   - 111
// 5 - 1 AC    - 110
// 6 - 100m AC - 101
// 7 - 10m AC  - 100
// Current:
// 0 - 1    - 011
// 1 - 100m - 010
// 2 - 10m  - 001
// 3 - 1m   - 000
// Resistance:
// 0 - 1k   - 00
// 1 - 5k   - 01
// 2 - 10k  - 01
// 3 - 50k  - 10
// 4 - 100k - 10
// 5 - 500k - 11
// 6 - 1M   - 11
// Capacitace:
// 0 - ? - 000
// 1 - ? - 001
// 2 - ? - 010 

// J7: 
// Pin 2,3,4 - Range addresses
// Pin 5,6 - OhmMeter addresses
// J5:
// Pin 3,4,5 - Module addresses
// Pin 6 - Audio response
// Pin 7 - Freq/Capacitance selection

// Set a range manually
// Sets digital pins 2, 3 and 4 on J7 to output the desired range, in 3 bit encoding.
// Pin 2 is the MSB and pin 4 is the LSB
// J7 5+6 for OhmMeter
void setRange(int module, int range, double ADCValue);
// Set the hardware module you wnat to select.
// Using J5 pins 3-5, 3 MSB 5 LSB
void setModule(int module);

// Use J5 pin 7 for freq/Cap
// Use J5 pin 6 for audio resopnse

// Automatically chose a suitable range for the user
int autoRange(int module, int range, double ADCValue);

#endif
