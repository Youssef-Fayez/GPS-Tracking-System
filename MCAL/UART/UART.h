#ifndef UART_H
#define UART_H

#define U          0x55               //Ascii code for U
#define checksum   0x2A               //Ascii code for *
#define ENTER      0x0D               //ASCII code for ENTER


void UART_Init(void);
char UART_Read_Char(void);
void UART_Write_Char(u8 data);
void UART_Print_String(u8 *pt);

// @parameters : pass an array with lengh len to store string sent by gps module
void Get_String_From_GPSModule(u8 *fix, u8 len); 


























#endif