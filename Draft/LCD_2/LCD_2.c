#include "tm4c123gh6pm.h"


void delay (long d)
{
   while(d--);
}

typedef enum {
    LOW,
    HIGH,
}GPIO_VALUE;


#define SET_BIT(REG, BIT_NUMBER)  REG |= (1 << BIT_NUMBER)


#define CLR_BIT(REG, BIT_NUMBER)  REG &= ~(1 << BIT_NUMBER)

#define TOG_BIT(REG, BIT_NUMBER)  REG ^= (1 << BIT_NUMBER)

#define GET_BIT(REG, BIT_NUMBER)  ((REG & (1 << BIT_NUMBER)) >> BIT_NUMBER)

typedef enum {
    PORTA,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
    PORTF,
} GPIO_PORTS;
typedef enum {
    INPUT,
    OUTPUT,
    VARYING,
}GPIO_MODE;

void GPIO_Set_Pin_Mode(char port , char pin , char mode) // mode : INPUT , OUTPUT
{
    switch (port){
    case PORTA:
       switch (mode){
       case OUTPUT :
            SET_BIT(GPIO_PORTA_DIR_R, pin) ;
            break;
       case INPUT : 
            CLR_BIT(GPIO_PORTA_DIR_R, pin) ; 
            break;    
        default:       
            break;
       }
       break;
       
    case PORTB:
       switch(mode){
       case OUTPUT :
            SET_BIT(GPIO_PORTB_DIR_R, pin) ;
            break;
       case INPUT  : 
            CLR_BIT(GPIO_PORTB_DIR_R, pin) ; 
            break; 
        default:       
            break;   
        
       }
       break;
    
    case PORTD:
       switch(mode){
       case OUTPUT :
            SET_BIT(GPIO_PORTD_DIR_R, pin) ;
            break;
       case INPUT  : 
            CLR_BIT(GPIO_PORTD_DIR_R, pin) ; 
            break; 
        default:       
            break;
       }
       break;
        
    case PORTF:
       switch (mode){
       case OUTPUT :
            SET_BIT(GPIO_PORTF_DIR_R, pin) ;
            break;
       case INPUT  : 
            CLR_BIT(GPIO_PORTF_DIR_R, pin) ; 
            break;    
        default:       
            break;    
       }
       break;
     
    default:
    break;
    }
}
void GPIO_Set_Pin_value(char port , char pin , char value) 
{
    switch (port){
    case PORTA:
       switch (value){
       case HIGH :
            SET_BIT(GPIO_PORTA_DATA_R, pin) ;
            break;
       case LOW : 
            CLR_BIT(GPIO_PORTA_DATA_R, pin) ; 
            break;    
        default:       
            break;
       }
       break;
       
    case PORTB:
       switch(value){
       case HIGH :
            SET_BIT(GPIO_PORTB_DATA_R, pin) ;
            break;
       case LOW  : 
            CLR_BIT(GPIO_PORTB_DATA_R, pin) ; 
            break; 
        default:       
            break;   
        
       }
       break;
    
    case PORTD:
       switch(value){
       case HIGH :
            SET_BIT(GPIO_PORTD_DATA_R, pin) ;
            break;
       case LOW  : 
            CLR_BIT(GPIO_PORTD_DATA_R, pin) ; 
            break; 
        default:       
            break;
       }
       break;
        
    case PORTF:
       switch (value){
       case HIGH :
            SET_BIT(GPIO_PORTF_DATA_R, pin) ;
            break;
       case LOW  : 
            CLR_BIT(GPIO_PORTF_DATA_R, pin) ; 
            break;    
        default:       
            break;    
       }
       break;
     
    default:
        break;
 }
 }
/*  
    RS=PD0
    RW=PD1
    EN=PD2

		D0 - PA7
		D1-  PA6
	  D2 - PA5
		D3 - PB4
		D4 - PE5
		D5 - PE4
		D6 - PB1
		D7 - PB0
	
	*/
//print data function on LCD
 void Printdata(char data) //data  8 bit hexadecimal
 {
	//zeroth bit ---> D0 =PA7
	if( (data & 0x01)==0x01 ){
		GPIO_Set_Pin_value(PORTA,7,HIGH);
	}
	else{
		GPIO_Set_Pin_value(PORTA,7,LOW);
	}

    //First bit ---> D1 =PA6
	if( (data & 0x02)==0x02 ){
		GPIO_Set_Pin_value(PORTA,6,HIGH);
	}
	else{
		GPIO_Set_Pin_value(PORTA,6,LOW);
	}

    //second bit ---> D2 =PA5
	if( (data & 0x04)==0x04 ){
		GPIO_Set_Pin_value(PORTA,5,HIGH);
	}
	else{
		GPIO_Set_Pin_value(PORTA,5,LOW);
	}

    //third bit ---> D3 =PB4
	if( (data & 0x08)==0x08 ){
		GPIO_Set_Pin_value(PORTB,4,HIGH);
	}
	else{
		GPIO_Set_Pin_value(PORTB,4,LOW);
	}

    //fourth bit ---> D4 =PE5
	if( (data & 0x10)==0x10 ){
		GPIO_Set_Pin_value(PORTE,5,HIGH);
	}
	else{
		GPIO_Set_Pin_value(PORTE,5,LOW);
	}

    //fifth bit ---> D5 =PE4
	if( (data & 0x20)==0x20 ){
		GPIO_Set_Pin_value(PORTE,4,HIGH);
	}
	else{
		GPIO_Set_Pin_value(PORTE,4,LOW);
	}

    //sixth bit ---> D6 =PB1
	if( (data & 0x40)==0x40 ){
		GPIO_Set_Pin_value(PORTB,1,HIGH);
	}
	else{
		GPIO_Set_Pin_value(PORTB,1,LOW);
	}

    //seventh bit ---> D7 =PB0
	if( (data & 0x80)==0x80 ){
		GPIO_Set_Pin_value(PORTB,0,HIGH);
	}
	else{
		GPIO_Set_Pin_value(PORTB,0,LOW);
	}

}

	
	void lcd_data(char data)
	{
     Printdata(data);                  //pass the data in the datalines of lcd
     GPIO_Set_Pin_value(GPIO_PORTD_DATA_R,1,LOW) ;    //turn of the R/W pin for write operation in lcd
     GPIO_Set_Pin_value(GPIO_PORTD_DATA_R ,0,HIGH);     //turn on the RS for writing to the data register of lcd
     GPIO_Set_Pin_value(GPIO_PORTD_DATA_R ,2,HIGH);     //turn on the En of lcd for enabling the clock of lcd
     delay(10000);                            //wait for sometime
     GPIO_Set_Pin_value(GPIO_PORTD_DATA_R ,2, LOW);             //Turn off the En of lcd		
	
	}
	
	
  //Sending commands to LCD

void lcd_cmd(char data)
{
	//pass 8 bit data to the data lines of LCD
	Printdata(data);
	//Turn off the R/W for enabling write operation on LCD ( R/W ---> PD1 )
	GPIO_Set_Pin_value(PORTD,1,LOW);
	//Turn ON RS for writing to the instructions Register of LCD ( RS ---> PD0 )
	GPIO_Set_Pin_value(PORTD,0,LOW);
	//Turn on EN of LCD for enabling clk of LCD ( EN ---> PD2 )
	GPIO_Set_Pin_value(PORTD,2,HIGH);
	//Wait for sometime
	delay(10000);
	//Turn off EN
	GPIO_Set_Pin_value(PORTD,2,LOW);
}
	
	
	void lcd_string( char *str , int len){
	
	int i;
	  for (i=0;i<len;i++){
		lcd_data(str[i]);
		}
	}
	
	
	void lcd_init(void){
	  
		lcd_cmd(0x38); //8bit mode utilising 16 columns and 2 rows
		lcd_cmd(0x06); // autoincrementing the cursor when prints the data in current		
		lcd_cmd(0x0C); //cursor off and display on
		lcd_cmd(0x01); //clearscreen
	
	
	}
	
	
int main(){

 //enable the clock of GPIO A,B,D,E
	SYSCTL_RCGCGPIO_R |= 0x1B;
	//Digitalize these 8 pins
	GPIO_PORTA_DEN_R  |= 0xE0;
	GPIO_PORTB_DEN_R  |= 0x13;
	GPIO_PORTD_DEN_R  |= 0x07;
	GPIO_PORTE_DEN_R  |= 0x30;
	//config these 8 pins as output pins
	GPIO_Set_Pin_Mode ( PORTA , 7 , OUTPUT);
	GPIO_Set_Pin_Mode ( PORTA , 6 , OUTPUT);
	GPIO_Set_Pin_Mode ( PORTA , 5 , OUTPUT);
	GPIO_Set_Pin_Mode ( PORTB , 4 , OUTPUT);
	GPIO_Set_Pin_Mode ( PORTB , 1 , OUTPUT);
	GPIO_Set_Pin_Mode ( PORTB , 0 , OUTPUT);
	GPIO_Set_Pin_Mode ( PORTE , 4 , OUTPUT);
	GPIO_Set_Pin_Mode ( PORTE , 5 , OUTPUT);
	lcd_init();
	// 0x80
	// 0xC0
	lcd_cmd(0x80); //cursor to first row and first column
	lcd_data('a');
	lcd_cmd(0xC0); // cursor to second row and first column
	lcd_data('b');
	while(1){
	}
}