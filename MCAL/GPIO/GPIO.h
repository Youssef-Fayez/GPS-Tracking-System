#ifndef GPIO_H
#define GPIO_H
//#include "../../tm4c123gh6pm.h"
typedef enum {

    GPIO_PIN0,          /**< GPIO Pin 0 */
    GPIO_PIN1,          /**< GPIO Pin 1 */
    GPIO_PIN2,          /**< GPIO Pin 2 */
    GPIO_PIN3,          /**< GPIO Pin 3 */
    GPIO_PIN4,          /**< GPIO Pin 4 */
    GPIO_PIN5,          /**< GPIO Pin 5 */
    GPIO_PIN6,          /**< GPIO Pin 6 */
    GPIO_PIN7,          /**< GPIO Pin 7 */
} GPIO_PIN;

typedef enum {
    PORTA,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
    PORTF,
} GPIO_PORTS;

typedef enum {
    LOW,
    HIGH,
}GPIO_VALUE;

typedef enum {
    INPUT,
    OUTPUT,
    VARYING,
}GPIO_MODE;

void GPIO_Ports_Init(u8 port , u8 mode);
void GPIO_Set_Pin_Value(u8 port , u8 pin , u8 value);
u8 GPIO_Get_Pin_Value(u8 port , u8 pin );
void GPIOF_Init(void);

#endif
