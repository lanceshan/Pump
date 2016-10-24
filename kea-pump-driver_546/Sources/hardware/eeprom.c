#include "i2c.h"
#include "eeprom.h"

//返回成功写入的字节数目，失败返回0
unsigned short eeprom_wr(unsigned short eeDataAddr, unsigned char buf[], unsigned short len)
{
	unsigned char eebuf[EEPROM_WR_MAX + 2];
	unsigned char i = 0;

	if(len > EEPROM_WR_MAX) return 0;
	
	eebuf[0] = (eeDataAddr >> 8)&0xff;
	eebuf[1] = eeDataAddr&0xff;
	for(i = 0;i < len;i++)
		eebuf[i + 2] = buf[i];
	
	return i2c_wr(EEPROM_WR_ADDRESS>>1, eebuf, len + 2);
}

//返回成功读取的字节数目，失败返回0
unsigned short eeprom_rd(unsigned short eeDataAddr, unsigned char buf[], unsigned short len)
{
	unsigned char eebuf[EEPROM_WR_MAX + 2];

	if(len > EEPROM_WR_MAX) return 0;
	
	eebuf[0] = (eeDataAddr >> 8)&0xff;
	eebuf[1] = eeDataAddr&0xff;

	if(0 == i2c_wr(EEPROM_WR_ADDRESS>>1, eebuf, 2)) return 0;
	
	return i2c_rd(EEPROM_RD_ADDRESS>>1, buf, len);
}


