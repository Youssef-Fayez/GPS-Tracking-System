#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../tm4c123gh6pm.h"
#include "UART.h"

#include "../../MCAL/GPIO/GPIO.h"

void Get_fix_From_GPSModule(u8 *fix, u8 len){
	u8 character;
    len = 100;
	for(u8 i=0; i<len; i++){
	 character= UART_Read_Char();
		if(character != checksum && character != ENTER){
		        fix[i]=character;
                UART_Write_Char(character);
		}
		else if(character == checksum || character == ENTER ) break;			
	}

}

void UART_Print_String(u8 *pt){
while(*pt){                           // to terminate at null character
	UART_Write_Char(*pt);            // print character by character
	pt++;                           // get next character by incresing the pointer pointing to the string
}
}