#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "../../tm4c123gh6pm.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "CLCD.h"

//LCD_CMD(0x80) fisrt row first coloumn
//LCD_CMD(0xC0) second row first coloumn

void delay(u32 d){
    while(d--);
}

void LCD_Init(void){
GPIO_Ports_Init(PORTB , VARYING);
GPIO_Ports_Init(PORTE , VARYING);
GPIO_Set_Pin_Mode(PORTB , GPIO_PIN7 , OUTPUT);
GPIO_Set_Pin_Mode(PORTB , GPIO_PIN6 , OUTPUT);
GPIO_Set_Pin_Mode(PORTB , GPIO_PIN2 , OUTPUT);
GPIO_Set_Pin_Mode(PORTB , GPIO_PIN4 , OUTPUT);
GPIO_Set_Pin_Mode(PORTB , GPIO_PIN1 , OUTPUT);
GPIO_Set_Pin_Mode(PORTB , GPIO_PIN0 , OUTPUT);
GPIO_Set_Pin_Mode(PORTE , GPIO_PIN4 , OUTPUT);
GPIO_Set_Pin_Mode(PORTE , GPIO_PIN5 , OUTPUT);
GPIO_Set_Pin_Mode(PORTE , GPIO_PIN1 , OUTPUT);
GPIO_Set_Pin_Mode(PORTE , GPIO_PIN2 , OUTPUT);
GPIO_Set_Pin_Mode(PORTE , GPIO_PIN3 , OUTPUT);
}

void LCD_Init_2(void){
 LCD_CMD(0x38);  //8-bit mode utilising 16 coloumns and 2 rows
 LCD_CMD(0x06); //auto increament when data is written in 1 crusor
 LCD_CMD(0x0C);  //crusor off and display On
 LCD_CMD(0x01);  //clearscreen
}

void Print_Data(u8 data){
    // zero bit = D0 = PA7
    if ((data & 0x01)== 0x01){
    GPIO_Set_Pin_Value(PORTB , GPIO_PIN7 , HIGH);}
    else{
    GPIO_Set_Pin_Value(PORTB , GPIO_PIN7 , LOW);}
    // first bit = D1 = PA6
    if ((data & 0x02)== 0x02){
    GPIO_Set_Pin_Value(PORTB , GPIO_PIN6 , HIGH);}
    else{
    GPIO_Set_Pin_Value(PORTB , GPIO_PIN6 , LOW);}
    // second bit = D2 = PA5
    if ((data & 0x04) == 0x04){
    GPIO_Set_Pin_Value(PORTB , GPIO_PIN2 , HIGH);}
    else{
    GPIO_Set_Pin_Value(PORTB , GPIO_PIN2 , LOW);}
    // third bit = D3 = PB4
    if ((data & 0x08)== 0x08){
    GPIO_Set_Pin_Value(PORTB , GPIO_PIN4 , HIGH);}
    else{
    GPIO_Set_Pin_Value(PORTB , GPIO_PIN4 , LOW);}
    // fourth bit = D4 = PE5
    if ((data & 0x10)== 0x10){
    GPIO_Set_Pin_Value(PORTE , GPIO_PIN5 , HIGH);}
    else{
    GPIO_Set_Pin_Value(PORTE , GPIO_PIN5 , LOW);}
    // fifth bit = D5 = PE4
    if ((data & 0x20)== 0x20){
    GPIO_Set_Pin_Value(PORTE , GPIO_PIN4 , HIGH);}
    else{
    GPIO_Set_Pin_Value(PORTE , GPIO_PIN4 , LOW);}
    // sixth bit = D6 = PB1
    if ((data & 0x40)== 0x40){
    GPIO_Set_Pin_Value(PORTB , GPIO_PIN1 , HIGH);}
    else{
    GPIO_Set_Pin_Value(PORTB , GPIO_PIN1 , LOW);}
    // seventh bit = D7 = PB0
    if ((data & 0x80)== 0x80){
    GPIO_Set_Pin_Value(PORTB , GPIO_PIN0 , HIGH);}
    else{
    GPIO_Set_Pin_Value(PORTB , GPIO_PIN0 , LOW);
    }

}

void LCD_Data(u8 data){
Print_Data(data);                                           //Pass 8-bit data to datalines
GPIO_Set_Pin_Value(PORTE , GPIO_PIN2 , LOW);              //TURN OFF RW to be in write operation
GPIO_Set_Pin_Value(PORTE , GPIO_PIN1 , HIGH);           //turn On the RS to write data on data register
GPIO_Set_Pin_Value(PORTE , GPIO_PIN3 , HIGH);            // turn On enable to enable CLK of LCD
delay(10000);                                            //Wait for sometime
GPIO_Set_Pin_Value(PORTE , GPIO_PIN3 , LOW);          //turn OFF enable
}

void LCD_CMD(u8 cmd){
Print_Data(cmd);                                           //Pass 8-bit data to datalines
GPIO_Set_Pin_Value(PORTE , GPIO_PIN2 , LOW);           //TURN OFF RW to be in write operation
GPIO_Set_Pin_Value(PORTE , GPIO_PIN1 , LOW);           //turn OFF the RS to write data on INSTRUCTION register
GPIO_Set_Pin_Value(PORTE , GPIO_PIN3 , HIGH);            // turn On enable to enable CLK of LCD
delay(10000);                                            //Wait for sometime
GPIO_Set_Pin_Value(PORTE , GPIO_PIN3 , LOW);          //turn OFF enable
}

void LCD_String(u8 *str, u32 len){
u8 i;
for(i=0; i<len; i++){
    LCD_Data(str[i]);
}
}

void reverse(u8 *str, u8 length) {
    u8 start = 0;
    u8 end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}
void itoa(s32 num, u8* str, u8 base) {
    u8 i = 0;
    u8 isNegative = 0;

    // Handle 0 explicitly, otherwise empty string is printed
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        
    }

    // Handle negative numbers
    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num /= base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Null terminate string

    // Reverse the string
    reverse(str, i);

}




void floatToString(f32 num, u8* buffer, u8 precision) {
    u32 digit;
	u8 i;
	u8 integerLength;
	u32 integerPart = (u32)num;
    f32 fractionalPart = num - integerPart;

    // Convert integer part to string
    itoa(integerPart, buffer, 10);

    // Find the position to start writing the fractional part
    integerLength = strlen(buffer);
    buffer[integerLength++] = '.';

    // Calculate the fractional part
    for (i = 0; i < precision; i++) {
        fractionalPart *= 10;
        digit = (u32)fractionalPart;
        buffer[integerLength++] = '0' + digit;
        fractionalPart -= digit;
    }

    // Null-terminate the string
    buffer[integerLength] = '\0';
}