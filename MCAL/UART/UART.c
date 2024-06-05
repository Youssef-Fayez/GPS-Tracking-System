#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include <string.h>
#include <stdint.h>
#include "../../tm4c123gh6pm.h"
#include "UART.h"

#include "../../MCAL/GPIO/GPIO.h"

void UART_Init(u8 UART_no) { 
	switch (UART_no)
	{
	case UART0:
		SYSCTL_RCGCUART_R |= 0x01;  // activate UART0
		SYSCTL_RCGCGPIO_R |= 0x01; //activate GPIOA
        while ((SYSCTL_PRGPIO_R & 0x01) == 0){};	
		
		
		UART0_CTL_R &= ~0x0001;       // disable UART
		UART0_IBRD_R = 104;           // IBRD=int (80000000/(16*9600))=int (520.8333) 
		UART0_FBRD_R = 11;            // FBRD int (0.8333 * 64 + 0.5)
		UART0_LCRH_R = 0x0070;        // 8-bit word length, enable FIFO 001110000 
		UART0_CTL_R = 0x0301;         // enable RXE, TXE and UART 001100000001 
		GPIO_PORTA_AFSEL_R |= 0x03;   // enable alt function PAO,PA1 
		GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00)+0x00000011;
		/*
		configure
		UART for PAO, PA1
		*/
		GPIO_PORTA_DEN_R |= 0x03;     // enable digital I/O on PAO, PA1 
		GPIO_PORTA_AMSEL_R &= ~0x03;  // disable analog function on PAO, PA1
		break;

	case UART2:
		SYSCTL_RCGCUART_R |= 0x04; 
		SYSCTL_RCGCGPIO_R |= 0x08;
    	while ((SYSCTL_PRGPIO_R & 0x08) == 0); 
		while ((SYSCTL_PRUART_R & 0x04) == 0); 
		GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;
		GPIO_PORTD_CR_R |= 0xC0;
	
		UART2_CTL_R &= ~0X01;       // disable UART
		UART2_IBRD_R = 104;           // IBRD=int (80000000/(16*9600))=int (520.8333) 
		UART2_FBRD_R = 11;            // FBRD int (0.8333 * 64 + 0.5)
		UART2_LCRH_R = 0x0070;        // 8-bit word length, enable FIFO 001110000 
		UART2_CTL_R = 0x0301;         // enable RXE, TXE and UART 001100000001 
		GPIO_PORTD_AFSEL_R |= 0xC0;   // enable alt function PD6,PD7
		GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0x00FFFFFF) + 0x11000000;
		GPIO_PORTD_DIR_R |= 0xC0;
		GPIO_PORTD_DEN_R |= 0xC0;     // enable digital I/O on PD6, PD7 
		GPIO_PORTD_AMSEL_R &= ~0xC0;  // disable analog function on PD6, PD7
		break;
	default:
		break;
	}				// should be called only once

}
//to read UART data
u8 UART_Read_Char(u8 UART_no){
	switch (UART_no)
	{
	case UART0:
		while((UART0_FR_R & 0X0010) !=0);
		return (u8)(UART0_DR_R & 0XFF);
		break;
	case UART2 :
		while((UART2_FR_R & 0X0010) !=0);
		return (u8)(UART2_DR_R & 0XFF);
		break;
	default:
		break;
	}

}
//to write UART data
void UART_Write_Char(u8 UART_no,u8 data){
	switch (UART_no)
	{
	case UART0:
		while((UART0_FR_R & 0X0020) !=0); 
		UART0_DR_R=data;
		break;
	case UART2 :
		while((UART2_FR_R & 0X0020) !=0); 
		UART2_DR_R=data;
		break;
	default:
		break;
	}

}

void UART_Get_String(u8 *Command, u32 len){
	u8 character;
	u8 i;
	for(i=0; i<len; i++){
		character= UART_Read_Char(UART0);
		if(character != ENTER){
				Command[i]=character;
    	        UART_Write_Char(UART0,character);
		}
		else if(character == ENTER ) {
			break;	
		}		
	}
}

void UART_Get_coord(u8 *coordinate, u32 len){

	 	u8 recievedchar;
		u8 i;
		u8 m;
        u8 k;
        u8 g;
	    u8 l;
		u8 GPS_Checkname[]= "$GPRMC,"; 
	   k=0;

		for(i=0; i<800; i++){
			coordinate[k] = UART_Read_Char(UART2);
			if (coordinate[0]==GPS_Checkname[0]){
                i++;
                for(m =1 ; m<=6 ; m++){
                    coordinate[m]=UART_Read_Char(UART2);
                }
                
                if (strcmp(coordinate,GPS_Checkname)==0){
                    break; 
                    
                    }
                    
                else {
                    k=0;
                }       
			}
			else if(coordinate[0]!=GPS_Checkname[0])
			{
				strcpy (coordinate, "");
				k=0;
			}
			
		}
		strcpy (coordinate, "");
        for(g=0; g<len; g++){
			coordinate[g]=UART_Read_Char(UART2);
			if(coordinate[g]==CHECKSUM){
				break;
			}
		 }
				
		 
			
}

void UART_Print_String(u8 UART_no, u8 *pt){
	while(*pt){
		switch (UART_no){
			case UART0 :																					// to terminate at null character
				UART_Write_Char(UART0, *pt);            // print character by character
				pt++;                           // get next character by incresing the pointer pointing to the string

			case UART2 :
				UART_Write_Char(UART0, *pt);            // print character by character
				pt++; 
		}
	}
}

