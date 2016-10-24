/*
 * flash.c
 *
 *  Created on: Sep 27, 2016
 *      Author: Hill
 */

#include "flash.h"

void Flash_init(void)
{
   IFsh1_Init();
}

void Flash_EraseSector(IFsh1_TAddress Addr)
{
	if(Addr < FLASH_SECTOR_PARAM)return;	//只允许擦除最后一片扇区，用于保存系统版本号
	IFsh1_EraseSector(Addr);
}

void Flash_SetBytes(IFsh1_TAddress Addr, uint8 *buf, uint8 len)
{
	uint8 i = 0;
	if(Addr != FLASH_ADDR_VERSION)return;	//只允许写最后0x0f个字节区域，用于保存系统版本号
	for(i=0; i<len; i++)
		IFsh1_SetByteFlash((Addr+i), *(buf+i));
}

void Flash_GetBytes(uint32 Addr, uint8 *buf, uint8 len)
{
	uint8 i = 0;
	if(Addr != FLASH_ADDR_VERSION)return;	//只允许读最后0x0f个字节区域，用于保存系统版本号
	for(i=0; i<len; i++)
		IFsh1_GetByteFlash((IFsh1_TAddress)(Addr+i), (buf+i));
}

void Flash_Disable(void)
{
	uint8 state = 0;	
	
	while(!state)
	{
		if(!(FTMRE_FSTAT & FTMRE_FSTAT_CCIF_MASK))break;
		if(!(FTMRE_FCLKDIV & FTMRE_FCLKDIV_FDIVLCK_MASK))/* FCLKDIV register is not locked */
		{
			FTMRE_FCLKDIV = (FTMRE_FCLKDIV & ~(FTMRE_FCLKDIV_FDIV_MASK)) | FTMRE_FCLKDIV_FDIV(0);
			state = 1;
		}
	}	
}
