#ifndef RANGING_H
#define RANGING_H
// Ranges:
// 0 -  1m    - 000
// 1 -  10m 	- 001
// 2 -  100m  - 010
// 3 -  1 		- 011
// 4 -  10    - 100

// Set a range manually
// Sets digital pins 2, 3 and 4 on J7 to output the desired range, in 3 bit encoding.
// Pin 2 is the MSB and pin 4 is the LSB
void setRange(int range);
// Automatically chose a suitable range for the user
int autoRange(int range);

#endif
