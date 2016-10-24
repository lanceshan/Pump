/*
 * commprotocol.c
 * version 1.0
 */
#include "globalvars.h"
#include "commprotocol.h"
#include "../hardware/uart.h"
#include "../hardware/uart0_master.h"

#include "AS1.h"

uint8 UART_CRC8(uint8 org_data[], uint8 n)
{
	uint8 i,x, crcbuff,crc = 0;
	for(x=0; x<n; x++)
	{
		crcbuff = org_data[x];
		for(i = 0; i < 8; i++)
		{
			if(((crc ^ crcbuff) & 0x01) == 0)
			crc >>= 1;
			else
			{
				crc ^= 0x18;   //CRC=X8+X5+X4+1
				crc >>= 1;
				crc |= 0x80;
			}
			crcbuff >>= 1;
		}
	}
	return crc;
}

unsigned char RxMessage(unsigned char buf[])  //解析从串口收到的命令数据包，包括效验码解析、参数提取，返回收到的有效数据包的数据长度
{
	uint8 ret = 0;
	if(7 == uart0_master_rd(buf, 7)) // uart1_rd(buf, 6))
	{
		if(UART_CRC8(buf, 6) != buf[6])return ret;
		if(('Y' == buf[0])&&('L' == buf[1]))
		{
			if( 0x52 == buf[2])
			{
				if((0 != buf[3])&&(1 != buf[3]))
				{
					ret = 0;
				}
				else
				{
					gMessageOfControl.direction = buf[3];	//direction
					gMessageOfControl.targetSpeed = ((uint16)buf[4] << 8) + buf[5];	//speed
					gMessageOfControl.new_cmd_flag = 1;
					ret = 7;
				}
			}	
		}
		else
		{
			ret = 0;
		}
	}
	else
	{
		ret = 0;
	}
		
	return ret;
}

void TxMessage(unsigned char buf[], unsigned char len) //从串口发送命令数据包，包括参数核对、校验码编码
{
	uart0_master_wr(buf, len); //uart1_wr(buf, len);
}
