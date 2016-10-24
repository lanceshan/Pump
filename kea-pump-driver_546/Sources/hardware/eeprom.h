#ifndef __Eeprom_H
#define __Eeprom_H

#define EEPROM_HW_ADDR 0x00
#define EEPROM_WR_ADDRESS ((0xA0|EEPROM_HW_ADDR)|0x00)
#define EEPROM_RD_ADDRESS ((0xA0|EEPROM_HW_ADDR)|0x01)

#define EEPROM_WR_MAX 100

#define EEPROM_PUMP_SPEED_ADDRESS 0x00

unsigned short eeprom_wr(unsigned short eeDataAddr, unsigned char buf[], unsigned short len);
unsigned short eeprom_rd(unsigned short eeDataAddr, unsigned char buf[], unsigned short len);


#endif

