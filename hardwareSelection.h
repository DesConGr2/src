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
// 4 - 1m      - 000
// 5 - 10 AC   - 111
// 6 - 1 AC    - 110
// 7 - 100m AC - 101
// 8 - 10m AC  - 100
// 9 - 1m AC   - 100
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
// Frequency:
// idk if this even needs to be here
// Capacitace:
// idk yet
// ADD A RANGE WHICH Is JUST RESISTANCE BUT BUZZES OUT OF RANGE



// Set a range manually
// Sets digital pins 2, 3 and 4 on J7 to output the desired range, in 3 bit encoding.
// Pin 2 is the MSB and pin 4 is the LSB
void setRange(int module, int range);
// Set the hardware module you wnat to select.
// Using J5 pins 3-5, 3 MSB 5 LSB
void setModule(int module);

// Automatically chose a suitable range for the user
int autoRange(int range);

#endif
