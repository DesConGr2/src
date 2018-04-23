#ifndef SERIAL_COMMS_H
#define SERIAL_COMMS_H

void CommsInit(void);
void WriteToOutputString(double output);
void PB_FTDI_Wait_Until_Ready(void);
void PB_FTDI_Send(char *OutString, int howMany);
void PB_FTDI_SendNewLine(void);

#endif
