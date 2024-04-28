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
    SW1 = 0,
    SW2 = 4,
}Switches;


void LED_Mode(u8 Colour , u8 mode);
void LED_Change_Colour(void);
void LED_mainfuctn(u8 distance);

















#endif