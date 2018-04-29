#ifndef SERIAL_COMMS_H
#define SERIAL_COMMS_H

void CommsInit(void);
void PB_FTDI_Wait_Until_Ready(void);
void PB_FTDI_Send(char *OutString, int howMany);
void WriteToOutputString(double output);
void writeStringAsOutput(char *output);
void WriteDataLogMessage(void);
void PB_FTDI_SendNewLine(void);


#endif
