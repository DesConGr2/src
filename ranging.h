#ifndef RANGING_H
#define RANGING_H
// Ranges:
// UNUSED
// 0 -  1m    - 000
// UNUSED
// 1 -  10m 	- 000
// 2 -  100m  - 001
// 3 -  1 		- 010
// 4 -  10    - 011

// Set a range manually
// Sets digital pins 2, 3 and 4 on J7 to output the desired range, in 3 bit encoding.
// Pin 2 is the MSB and pin 4 is the LSB
void setRange(int range);
// Automatically chose a suitable range for the user
int autoRange(int range);

#endif
