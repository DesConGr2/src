#ifndef SERIAL_COMMS_H
#define SERIAL_COMMS_H

void CommsInit(void);
void PB_FTDI_Wait_Until_Ready();
void PB_FTDI_Send(char *OutString, int howMany);
void WriteToOutputString(double output);
void WriteDataLogMessage();
void PB_FTDI_SendNewLine();

#endif
