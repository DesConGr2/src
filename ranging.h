#ifndef RANGING_H
#define RANGING_H
// Ranges:
// 0 -  1m    - 00
// 1 -  10m 	- 01
// 2 -  100m  - 10
// 3 -  1 		- 11

// Set a range manually
// Sets digital pins 2 and 3 on J7 to output the desired range, in 2 bit encoding.
// Pin 2 is the MSB and pin 3 is the LSB
void setRange(int range);
// Automatically chose a suitable range for the user
void autoRange(int *range);

#endif
