#include "IIC.h"
#include "i2c.h"

void i2c_init(void)
{
	IIC_Init();
}

//���سɹ�д����ֽ���Ŀ��ʧ�ܷ���0
unsigned short i2c_wr(unsigned char slaveAddr, unsigned char buf[], unsigned short len)
{
	unsigned short wrLen = 0;
	unsigned char errCode = 0;
	
	errCode = IIC_SelectSlave(slaveAddr);
	if(errCode != ERR_OK) return 0;

	errCode = IIC_SendBlock(buf, len, &wrLen);
	if(errCode != ERR_OK) return 0;

	if(len != wrLen) return 0;
	else return len;
	
}

//���سɹ���ȡ���ֽ���Ŀ��ʧ�ܷ���0
unsigned short i2c_rd(unsigned char slaveAddr, unsigned char buf[], unsigned short len)
{
	unsigned short rdLen = 0;
	unsigned char errCode = 0;
	
	errCode = IIC_SelectSlave(slaveAddr);
	if(errCode != ERR_OK) return 0;

	errCode = IIC_RecvBlock(buf, len, &rdLen);
	if(errCode != ERR_OK) return 0;

	if(len != rdLen) return 0;
	else return len;
	
}


