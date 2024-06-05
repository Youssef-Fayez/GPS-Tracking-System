#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "string.h"
#include "stdint.h"
#include "../../tm4c123gh6pm.h"
#include "segment.h"
#include "../../MCAL/GPIO/GPIO.h"
#include <math.h>

void Segment_Init(){
GPIO_Ports_Init(PORTA , VARYING);
GPIO_Ports_Init(PORTB , VARYING);
GPIO_Ports_Init(PORTE , VARYING);
GPIO_Set_Pin_Mode(PORTA , GPIO_PIN7 , OUTPUT);
GPIO_Set_Pin_Mode(PORTA , GPIO_PIN6 , OUTPUT);
GPIO_Set_Pin_Mode(PORTA , GPIO_PIN5 , OUTPUT);
GPIO_Set_Pin_Mode(PORTB , GPIO_PIN4 , OUTPUT);
GPIO_Set_Pin_Mode(PORTE , GPIO_PIN5 , OUTPUT);
GPIO_Set_Pin_Mode(PORTE , GPIO_PIN4 , OUTPUT);
GPIO_Set_Pin_Mode(PORTB , GPIO_PIN1 , OUTPUT);
GPIO_Set_Pin_Mode(PORTB , GPIO_PIN0 , OUTPUT);
}
/*
a= PA7
b= PA6
c= PA5
d= PB4
e= PE5
f= PE4
g= PB1
h= PB0
*/
/*
ENABLE CLOCK FUNCTONS PORTS A,B,E
DIGITILAIZE THE 8 PINS
CHOOSE OUTPUT
AND MASK WITH EACH BIT TO KNOW WHICH WILL WORK FROM a TO h
*/
// zero bit = a = PA7

void Segment(u8 data){
// zero bit = a = PA7
if (data & 0x01== 0x01)
GPIO_Set_Pin_Value(PORTA , GPIO_PIN7 , HIGH);
else
GPIO_Set_Pin_Value(PORTA , GPIO_PIN7 , LOW);
// zero bit = b = PA6
if (data & 0x02== 0x02)
GPIO_Set_Pin_Value(PORTA , GPIO_PIN6 , HIGH);
else
GPIO_Set_Pin_Value(PORTA , GPIO_PIN6 , LOW);
// zero bit = c = PA5
if (data & 0x04== 0x04)
GPIO_Set_Pin_Value(PORTA , GPIO_PIN5 , HIGH);
else
GPIO_Set_Pin_Value(PORTA , GPIO_PIN5 , LOW);
// zero bit = d = PB4
if (data & 0x08== 0x08)
GPIO_Set_Pin_Value(PORTB , GPIO_PIN4 , HIGH);
else
GPIO_Set_Pin_Value(PORTB , GPIO_PIN4 , LOW);
// zero bit = e = PE5
if (data & 0x08== 0x08)
GPIO_Set_Pin_Value(PORTE , GPIO_PIN5 , HIGH);
else
GPIO_Set_Pin_Value(PORTE , GPIO_PIN5 , LOW);
// zero bit = f = PE4
if (data & 0x08== 0x08)
GPIO_Set_Pin_Value(PORTE , GPIO_PIN4 , HIGH);
else
GPIO_Set_Pin_Value(PORTE , GPIO_PIN4 , LOW);
// zero bit = g = PB1
if (data & 0x10== 0x10)
GPIO_Set_Pin_Value(PORTE , GPIO_PIN1 , HIGH);
else
GPIO_Set_Pin_Value(PORTE , GPIO_PIN1 , LOW);
// zero bit = h = PB0
if (data & 0x20== 0x20)
GPIO_Set_Pin_Value(PORTB , GPIO_PIN0 , HIGH);
else
GPIO_Set_Pin_Value(PORTB , GPIO_PIN0 , LOW);
}

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