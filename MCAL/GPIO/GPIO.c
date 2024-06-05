#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../tm4c123gh6pm.h"

#include "GPIO.h"

void GPIO_Ports_Init(u8 port , u8 mode){
switch (port)
    {
    case PORTA:
        SYSCTL_RCGCGPIO_R |= 0x01;
        while ((SYSCTL_PRGPIO_R & 0x01) == 0){};
        GPIO_PORTA_LOCK_R = 0x4C4F434B;
				GPIO_PORTA_CR_R |= 0xFF;
        GPIO_PORTA_AMSEL_R &= ~0xFF;
        GPIO_PORTA_AFSEL_R &= ~0xFF;
        GPIO_PORTA_PCTL_R &= ~0x000FFF0;
        GPIO_PORTA_DEN_R |= 0xFF;
        GPIO_PORTA_DATA_R &= ~0xFF;
        switch (mode)
        {
        case OUTPUT:
            GPIO_PORTA_DIR_R |= 0xFF;
            break;
        case INPUT:
            GPIO_PORTA_DIR_R |= 0x00;
            break;
        case VARYING:
            break;
        }

        break;

    case PORTB:
        SYSCTL_RCGCGPIO_R |= 0x02;
        while ((SYSCTL_PRGPIO_R & 0x02) == 0);
        GPIO_PORTB_LOCK_R = 0x4C4F434B;
	      GPIO_PORTB_CR_R |= 0xFF;
        GPIO_PORTB_AMSEL_R &= ~0xFF;
        GPIO_PORTB_AFSEL_R &= ~0xFF;
        GPIO_PORTB_PCTL_R &= ~0x000FFF0;
        GPIO_PORTB_DEN_R |= 0xFF;
        GPIO_PORTB_DATA_R &= ~0xFF;
        switch (mode)
        {
        case OUTPUT:
            GPIO_PORTB_DIR_R |= 0xFF;
            break;
        case INPUT:
            GPIO_PORTB_DIR_R |= 0x00;
            break;
        case VARYING:
            break;
        }

        break;

    case PORTC:
        SYSCTL_RCGCGPIO_R |= 0x04;
        while ((SYSCTL_PRGPIO_R & 0x04) == 0);
        GPIO_PORTC_LOCK_R = 0x4C4F434B;
		    GPIO_PORTC_CR_R |= 0xFF;
        GPIO_PORTC_AMSEL_R &= ~0xFF;
        GPIO_PORTC_AFSEL_R &= ~0xFF;
        GPIO_PORTC_PCTL_R &= ~0x000FFF0;
        GPIO_PORTC_DEN_R |= 0xFF;
        GPIO_PORTC_DATA_R &= ~0xFF;
        switch (mode)
        {
        case OUTPUT:
            GPIO_PORTC_DIR_R |= 0xFF;
            break;
        case INPUT:
            GPIO_PORTC_DIR_R |= 0x00;
            break;
        case VARYING:
            break;
        }

        break;

    case PORTD:
        SYSCTL_RCGCGPIO_R |= 0x08;
        while ((SYSCTL_PRGPIO_R & 0x08) == 0);
        GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;
				GPIO_PORTD_CR_R |= 0xCF;
        GPIO_PORTD_AMSEL_R &= ~0xFF;
        GPIO_PORTD_AFSEL_R &= ~0xFF;
        GPIO_PORTD_PCTL_R &= ~0x000FFF0;
        GPIO_PORTD_DEN_R |= 0xFF;
        GPIO_PORTD_DATA_R &= ~0xFF;
        switch (mode)
        {
        case OUTPUT:
            GPIO_PORTD_DIR_R |= 0xFF;
            break;
        case INPUT:
            GPIO_PORTD_DIR_R |= 0x00;
            break;
        case VARYING:
            break;
        }

        break;

    case PORTE:
        SYSCTL_RCGCGPIO_R |= 0x10;
        while ((SYSCTL_PRGPIO_R & 0x10) == 0);
        GPIO_PORTE_LOCK_R = 0x4C4F434B;
		    GPIO_PORTE_CR_R |= 0xFF;
        GPIO_PORTE_AMSEL_R &= ~0xFF;
        GPIO_PORTE_AFSEL_R &= ~0xFF;
        GPIO_PORTE_PCTL_R &= ~0x000FFF0;
        GPIO_PORTE_DEN_R |= 0xFF;
        GPIO_PORTE_DATA_R &= ~0xFF;
        switch (mode)
        {
        case OUTPUT:
            GPIO_PORTE_DIR_R |= 0x3F;
            break;
        case INPUT:
            GPIO_PORTE_DIR_R |= 0x00;
            break;
        case VARYING:
            break;
        }

        break;

    case PORTF:
        SYSCTL_RCGCGPIO_R |= 0x20;
        while ((SYSCTL_PRGPIO_R & 0x20) == 0);
        GPIO_PORTF_LOCK_R = 0x4C4F434B;
		    GPIO_PORTF_CR_R |= 0x0E;
        GPIO_PORTF_AMSEL_R &= ~0x0E;
        GPIO_PORTF_AFSEL_R &= ~0x0E;
        GPIO_PORTF_PCTL_R &= ~0x000FFF0;
        GPIO_PORTF_DEN_R |= 0x0E;
        GPIO_PORTF_DATA_R &= ~0x0E;
        switch (mode)
        {
        case OUTPUT:
            GPIO_PORTF_DIR_R |= 0xFF;
            break;
        case INPUT:
            GPIO_PORTF_DIR_R |= 0x00;
            break;
        case VARYING:
            break;
        }

        break;
    }
}

void GPIO_Set_Port_Value(u8 port , u8 value){
switch (port){
    case PORTA:
       switch (value){
       case HIGH :
            GPIO_PORTA_DATA_R=0XFF;
            break;
       case LOW : 
            GPIO_PORTA_DATA_R=0x00  ; 
            break;    
        default:       
            break;
       }
       break;
       
    case PORTB:
       switch(value){
       case HIGH :
            GPIO_PORTB_DATA_R=0XFF ;
            break;
       case LOW  : 
            GPIO_PORTB_DATA_R=0x00  ; 
            break; 
        default:       
            break;   
        
       }
       break;

      case PORTC:
       switch(value){
       case HIGH :
            GPIO_PORTC_DATA_R=0XFF ;
            break;
       case LOW  : 
            GPIO_PORTC_DATA_R=0x00 ; 
            break; 
        default:       
            break;   
        
       }
       break;

    case PORTD:
       switch(value){
       case HIGH :
            GPIO_PORTD_DATA_R=0XFF ;
            break;
       case LOW  : 
            GPIO_PORTD_DATA_R=0x00  ; 
            break; 
        default:       
            break;
       }
       break;
        
			 case PORTE:
       switch(value){
       case HIGH :
            GPIO_PORTE_DATA_R=0XFF ;
            break;
       case LOW  : 
            GPIO_PORTE_DATA_R=0x00  ; 
            break; 
        default:       
            break;
       }
       break;
			 
    case PORTF:
       switch (value){
       case HIGH :
            GPIO_PORTF_DATA_R=0XFF;
            break;
       case LOW  : 
            GPIO_PORTF_DATA_R=0x00  ; 
            break;    
        default:       
            break;    
       }
       break;
     
    default:
        break;
    }
}


void GPIO_Set_Pin_Mode(u8 port , u8 pin , u8 mode){
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
     
     case PORTE:
       switch (mode){
       case OUTPUT :
            SET_BIT(GPIO_PORTE_DIR_R, pin) ;
            break;
       case INPUT : 
            CLR_BIT(GPIO_PORTE_DIR_R, pin) ; 
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
u8 GPIO_Get_Pin_Value(u8 port , u8 pin ){
    switch (port)
    {
    case PORTA:
        return GET_BIT(GPIO_PORTA_DATA_R, pin) ;
        break;
    case PORTB:
        return GET_BIT(GPIO_PORTB_DATA_R, pin) ;
        break;    
    case PORTC:
        return GET_BIT(GPIO_PORTC_DATA_R, pin) ;
        break;
    case PORTD:
        return GET_BIT(GPIO_PORTD_DATA_R, pin) ;
        break;
    case PORTE:
        return GET_BIT(GPIO_PORTE_DATA_R, pin) ;
        break;
    case PORTF:
        return GET_BIT(GPIO_PORTF_DATA_R, pin) ;
        break;

    default: break;
}
		return '0';
}

void GPIO_Set_Pin_Value(u8 port , u8 pin , u8 value){
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
        
			 case PORTE:
       switch(value){
       case HIGH :
            SET_BIT(GPIO_PORTE_DATA_R, pin) ;
            break;
       case LOW  : 
            CLR_BIT(GPIO_PORTE_DATA_R, pin) ; 
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

 void GPIOF_Init(void){
SYSCTL_RCGCGPIO_R |=  0x20;
while((SYSCTL_PRGPIO_R & 0x20) == 0);
GPIO_PORTF_LOCK_R   = 	 0x4C4F434B;
GPIO_PORTF_CR_R    |=  	0x1F;
GPIO_PORTF_AMSEL_R &= ~ 0x1F;
GPIO_PORTF_AFSEL_R &= ~ 0x1F;
GPIO_PORTF_PCTL_R  &= ~ 0xFFFFFFFF;
GPIO_PORTF_DEN_R   |= 	0x1F;
GPIO_PORTF_DIR_R   |= 	0x0E;
GPIO_PORTF_DATA_R  &= ~	0x1F;
GPIO_PORTF_PUR_R   |=   0x11;
}

