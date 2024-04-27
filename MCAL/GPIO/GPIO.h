#ifndef GPIO_H
#define GPIO_H

typedef enum {

    GPIO_PIN0,          /**< GPIO Pin 0 */
    GPIO_PIN1,          /**< GPIO Pin 1 */
    GPIO_PIN2,          /**< GPIO Pin 2 */
    GPIO_PIN3,          /**< GPIO Pin 3 */
    GPIO_PIN4,          /**< GPIO Pin 4 */
    GPIO_PIN5,          /**< GPIO Pin 5 */
    GPIO_PIN6,          /**< GPIO Pin 6 */
    GPIO_PIN7,          /**< GPIO Pin 7 */
    GPIO_PIN8,          /**< GPIO Pin 8 */
    GPIO_PIN9,          /**< GPIO Pin 9 */
    GPIO_PIN10,         /**< GPIO Pin 10 */
    GPIO_PIN11,         /**< GPIO Pin 11 */
    GPIO_PIN12,         /**< GPIO Pin 12 */
    GPIO_PIN13,         /**< GPIO Pin 13 */
    GPIO_PIN14,         /**< GPIO Pin 14 */
    GPIO_PIN15,         /**< GPIO Pin 15 */
} GPIO_PIN;

typedef enum {
    PORTA,
    PORTB,
    PORTC,
    PORTD,
    PORTF,
} GPIO_PORTS;

typedef enum {
    LOW,
    HIGH,
}GPIO_VALUE;

typedef enum {
    INPUT,
    OUTPUT,
}GPIO_MODE;

void GPIO_Ports_Init(u8 port , u8 mode);
void GPIO_Set_Port_value(u8 port , u8 value);
void GPIO_Set_Pin_Mode(u8 port , u8 pin , u8 value);
void GPIO_Set_Pin_value(u8 port , u8 pin , u8 value);
void GPIOF_Init(void);










#endif