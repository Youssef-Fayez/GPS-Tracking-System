#ifndef CLCD_H
#define CLCD_H

#define MAX_FLOAT_STRING_SIZE 32
//LCD_CMD(0x80) fisrt row first coloumn
//LCD_CMD(0xC0) second row first coloumn

/*
there are two steps:
1-Pass the address which where you are going to print
2-Pass the data which  you are going to print
*/
/*

RS=1 Data provided will be stored in data register
RS=0 Data provided will be stored in instruction register

RS= PD0
RW= PD1
EN= PD2
D0= PA7
D1= PA6
D2= PA5
D3= PB4
D4= PE5
D5= PE4
D6= PB1
D7= PB0
*/
/*
Common Cathode
0= 0X3F
1= 0X06
2= 0X5B
3= 0X4F
4= 0X66
5= 0X6D
6= 0X7C
7= 0X07
8= 0X7F
9= 0X6F
*/

void delay(u32 d);
void LCD_Init(void);
void LCD_Init_2(void);
void Print_Data(u8 data);
void LCD_Data(u8 data);
void LCD_CMD(u8 cmd);
void LCD_String(u8 *str, u32 len);

void reverse(u8 *str, u8 length);
void itoa(s32 num, u8* str, u8 base);
void floatToString(f32 num, u8* buffer, u8 precision);





#endif
