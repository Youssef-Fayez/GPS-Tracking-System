#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../tm4c123gh6pm.h"
#include "LED.h"

#include "../../MCAL/GPIO/GPIO.h"


void LED_Mod(u8 colour , u8 mode) {
	switch(colour)
	{
		case RED:
		switch(mode){
			case ON:
			SET_BIT(GPIO_PORTF_DATA_R, RED) ;
			break;
			
			case OFF:
			CLR_BIT(GPIO_PORTF_DATA_R, RED) ;
			break;
			
			default:
			break;
		}
		break;
		
		case BLUE:
		switch(mode){
			case ON:
			SET_BIT(GPIO_PORTF_DATA_R, BLUE) ;
			break;
			
			case OFF:
			CLR_BIT(GPIO_PORTF_DATA_R, BLUE) ;
			break;
			
			default:
			break;
		}
		break;
		
		case GREEN:
		switch(mode){
			case ON:
			SET_BIT(GPIO_PORTF_DATA_R, GREEN) ;
			break;
			
			case OFF:
			CLR_BIT(GPIO_PORTF_DATA_R, GREEN) ;
			break;
			
			default:
			break;
		}
		break;
		
		default:
		break;
	}
}

 void LED_Change_Colour (void){
	u8 RED_ON = GPIO_Get_Pin_Value(PORTF , GPIO_PIN1);
    u8 BLUE_ON = GPIO_Get_Pin_Value(PORTF , GPIO_PIN2);
    u8 GREEN_ON = GPIO_Get_Pin_Value(PORTF , GPIO_PIN3);
	if(RED_ON == 1){
		GPIO_PORTF_DATA_R &= ~ 0x0E;
		SET_BIT(GPIO_PORTF_DATA_R, BLUE);
	}
	else if(BLUE_ON == 1)
		{
			GPIO_PORTF_DATA_R &= ~ 0x0E;
			SET_BIT(GPIO_PORTF_DATA_R, GREEN);
		}
	else if(GREEN_ON == 1)
		{
				GPIO_PORTF_DATA_R &= ~ 0x0E;
				SET_BIT(GPIO_PORTF_DATA_R, RED);
		}
      
}










