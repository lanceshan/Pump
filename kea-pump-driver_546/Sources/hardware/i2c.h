#ifndef __I2c_H
#define __I2c_H


void i2c_init(void);

unsigned short i2c_wr(unsigned char slaveAddr, unsigned char buf[], unsigned short len);
unsigned short i2c_rd(unsigned char slaveAddr, unsigned char buf[], unsigned short len);


#endif

