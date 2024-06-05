#ifndef EEPROM_H_
#define EEPROM_H_





 void EEPROMINIT(void); 
 

void EEPROM_Write(u32 address, u32 data);


u32 EEPROM_Read(u32 address);


#endif 