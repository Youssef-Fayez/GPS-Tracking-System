#ifndef UART_H
#define UART_H

#define U          0x55               //Ascii code for U
#define CHECKSUM   0x2A               //Ascii code for *
#define ENTER      0x0D              //ASCII code for ENTER


typedef enum {
    UART0 =0,
    UART2 =2,
}UART_NO;


void UART_Init(u8 UART_no);
u8 UART_Read_Char(u8 UART_no);
void UART_Write_Char(u8 UART_no,u8 data);
void UART_Get_String(u8 *Command, u32 len) ;
void UART_Get_coord(u8 *coordinate, u32 len);
void UART_Print_String(u8 UART_no ,u8 *pt);





#endif
