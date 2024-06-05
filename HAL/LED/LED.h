#ifndef LED_H
#define LED_H


typedef enum {
    RED   = 1,
    BLUE  = 2,
    GREEN = 3,
}LED_Colour;

typedef enum {
    OFF,
    ON,
}LED_Mode;

typedef enum {
    SW2 = 0,
    SW1 = 4,
}Switches;


void LED_Mod(u8 Colour , u8 mode);
void LED_Change_Colour(void);






#endif
