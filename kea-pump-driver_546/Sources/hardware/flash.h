/*
 * flash.h
 *
 *  Created on: Sep 27, 2016
 *      Author: Hill
 */

#ifndef FLASH_H_
#define FLASH_H_

#include "IFsh1.h"

#define FLASH_SECTOR_PARAM			0x0001fe00	//ϵͳ������flash�еĴ洢����
#define FLASH_ADDR_VERSION			0x0001fff0	//ϵͳ�汾������flash �еĴ洢�׵�ַ��ռ��8���ֽ�

void Flash_init(void);
void Flash_EraseSector(IFsh1_TAddress Addr);
void Flash_SetBytes(IFsh1_TAddress Addr, uint8 *buf, uint8 len);
void Flash_GetBytes(uint32 Addr, uint8 *buf, uint8 len);
void Flash_Disable(void);

#endif /* FLASH_H_ */
