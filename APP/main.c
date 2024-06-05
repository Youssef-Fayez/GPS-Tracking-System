#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include "../tm4c123gh6pm.h"

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"


#include "../MCAL/GPIO/GPIO.h"
#include "../MCAL/UART/UART.h"
#include "../MCAL/STK/STK.h"
#include "../MCAL/EEPROM/EEPROM.h"


#include "../HAL/CLCD/CLCD.h"
#include "../HAL/GPS/GPS.h"
#include "../HAL/LED/LED.h"


int main(){
	
	u8 coordinate[80]= {0} ;
	u8 dest_lat[10];
	u8 dest_long[10];
	u8 command_U[2];
	u8 DIST[6];
	f32 LATITUDE[]={0}; 
	f32 LONGITUDE[]={0};
	u8 LCD_Print[]={0};
	
	
	u8 flag;
	u8 l=0;
	u8 comma_counter=0;

/////////////////// EEPROM////////////////////
	u32 lat_to_integer_counter;
	u32 long_to_integer_counter;
	u32 lat_to_float_counter;
	u32 long_to_float_counter;	
	f32 laat =0;
	f32 loong=0;
	u32 addresss=0;
	u8 read_counter=0;
	u8 flagg=1;
//////////////////////////////////////////////

	u8 check_distance[6]={0};
	u8 dest_lati1[12]= {0};
	u8 dest_1[12]={0};
	static f32 dest;
	static f32 dest_lati=0;
	static f32 dest_lon=0;
	static f32 lat1 ;
	static f32 lon1;
	static f32 lat2 ;
	static f32 lon2;
	static f32 dest_latitude ;
    static f32 dest_longitude;
	

	u8 Switch_1;
	u8  latcounter=0;
	u8  longcounter=0;
	f32 distance=0;
	u32 coordinateLength;
	u32 LCDLength;
	f32 CHECK_DISTANCE;
	
	
  
	SysTick_Init();
	GPIOF_Init();
    GPIO_Ports_Init(PORTA , VARYING);
	UART_Init(UART0);
	UART_Init(UART2);

	UART_Print_String(UART0, "ENTER U or N \n");

	UART_Get_String(command_U, 2);

	if(strcmp(command_U, "U") ==0){
		while(flagg){
		laat=EEPROM_Read(addresss);
		if(laat!=52){
		laat/=1000000;
		LATITUDE[read_counter++]=laat;	
		addresss+=4;
		}	
		else if(laat==52){
			addresss+=4;
			flagg=0;		
		}
	}
		
		read_counter=0;
		flagg=1;
		
		while(flagg){
		loong=EEPROM_Read(addresss);
		if(loong!=53){
		loong/=1000000;
		LONGITUDE[read_counter++]=loong;	
		addresss+=4;
		}	
		else if(loong==52){
			addresss+=4;
			flagg=0;	
		
		}
	}

		
	UART_Print_String(UART0, LATITUDE);
   UART_Print_String(UART0, LONGITUDE);

		while(1){}
	}

		UART_Print_String(UART0, "ENTER THE DESTINATION LATITUDE \n");
		UART_Get_String(dest_lat,10);
		UART_Print_String(UART0, "ENTER THE DESTINATION LONGITUDE \n");
		UART_Get_String(dest_long,10);
	
	dest_latitude = atof2(dest_lat);
	dest_longitude = atof2(dest_long);
	dest_lati = ToDegreesAndMinutes(dest_latitude);
	dest_lon = ToDegreesAndMinutes(dest_longitude);

	memset(coordinate,0,80);
	UART_Get_coord(coordinate, 80);
	
	
	do{
		if(coordinate[l] == comma){
			comma_counter++;
		}
		else if(coordinate[l] == 'A' && comma_counter==1 ){
			flag=1;
		}
		else if(coordinate[l] != 'A' && comma_counter==1){
			UART_Get_coord(coordinate, 80);
			l=0;
			comma_counter=0;
		}
   l++;		
	}while(flag==0);
	
	
	UART_Print_String(UART0, coordinate);
	coordinateLength = strlen(coordinate);
 
	lat1=get_lat(coordinate,coordinateLength);	
	lon1=get_long(coordinate,coordinateLength);
	   LATITUDE[0] =lat1;
		LONGITUDE[0]=lon1;
		latcounter=1;
		longcounter=1;	
		LCD_Init();
		delay(10000);
		LCD_Init_2();
		LCD_CMD(0x80); //cursor to first row and first column

while(1){
	
		
	
		memset(coordinate,0,80);
		UART_Get_coord(coordinate, 80);

		comma_counter=0;
		do{
		if(coordinate[l] == comma){
			comma_counter++;
		}
		else if(coordinate[l] == 'A' && comma_counter==1 ){
			flag=1;
		}
		else if(coordinate[l] != 'A' && comma_counter==1){
			UART_Get_coord(coordinate, 80);
			l=0;
			comma_counter=0;
		}
   l++;		
	}while(flag==0);
		
	
	UART_Print_String(UART0, coordinate);

	
	lat2=get_lat(coordinate,coordinateLength);
	lon2=get_long(coordinate,coordinateLength);

	distance+=get_distance(lat1,lon1,lat2,lon2);
	CHECK_DISTANCE = get_distance(lat2,lon2,dest_lati,dest_lon);

	subs(&lat1, &lon1, &lat2, &lon2);

	lat2= ToDegree (lat2);
	lon2= ToDegree (lat2);
	
	LATITUDE[latcounter++]= lat2;
	LONGITUDE[longcounter++]= lon2;
	

	
	
	floatToString(CHECK_DISTANCE, check_distance, 2);
	UART_Print_String(UART0, check_distance);
	
	

	floatToString(distance, DIST, 2);
	LCD_CMD(0x80);
	LCD_String("DISTANCE: ", 9);
	LCDLength = strlen(DIST);
	LCD_CMD(0xC0);
	LCD_String(DIST, LCDLength);
	
  if (CHECK_DISTANCE < 6){
    LED_Mod(GREEN , ON);
	LCD_CMD(0x80);
	LCD_String("Arrived  ", 9);
	LCD_CMD(0xC0);
	LCD_String("          ", 10);
			
		}
	
		Switch_1=GPIO_Get_Pin_Value(PORTF , SW1);
		
		if(Switch_1==0) {
			for(lat_to_integer_counter =0; lat_to_integer_counter<latcounter ; lat_to_integer_counter++){
			laat=	LATITUDE[lat_to_integer_counter];
			laat*=1000000;	
			EEPROM_Write(addresss, (u32)laat);
			addresss+=4;
			}
			EEPROM_Write(addresss, 52);
			addresss+=4;
			
			for(long_to_integer_counter =0; long_to_integer_counter<longcounter ; long_to_integer_counter++){
			loong =	LONGITUDE[long_to_integer_counter];
			loong*=1000000;	
			EEPROM_Write(addresss, (u32) loong);
			addresss+=4;
			}
			EEPROM_Write(addresss, 53);
			

			LED_Change_Colour ();
		}

		
	}

SysTick_Wait10ms(300);
		}
