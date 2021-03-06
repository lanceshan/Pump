/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : IFsh1.h
**     Project     : kea-pump
**     Processor   : SKEAZ128MLK4
**     Component   : IntFLASH
**     Version     : Component 02.409, Driver 01.02, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-10-13, 18:36, # CodeGen: 11
**     Abstract    :
**         This component "IntFLASH" implements an access to internal FLASH.
**         The component support reading/writing data into FLASH, erasing of
**         selected sector.
**         The component supports events if the write interrupt is supported.
**         The component supports following modes of write operations:
**           - Write - writing without any test.
**           - Destructive write - sector is erased if necessary.
**           - Safe write - user event is invoked to save and resore data
**                          from the current sector.
**         The component requires on-chip FLASH memory (not used/allocated by
**         other components).
**     Settings    :
**          Component name                                 : IFsh1
**          FLASH                                          : FTMRE
**          FLASH_LDD                                      : FLASH_LDD
**          Write method                                   : Write
**          Interrupt service/event                        : Enabled
**            Command complete interrupt                   : 
**              Interrupt                                  : INT_FTMRE
**              Interrupt priority                         : medium priority
**          Wait in RAM                                    : yes
**          Virtual page                                   : Enabled
**            Allocated                                    : By the component
**            Page size                                    : 2048
**          Initialization                                 : 
**            Events enabled in init.                      : yes
**            Wait enabled in init.                        : yes
**          CPU clock/speed selection                      : 
**            FLASH clock                                  : 
**            High speed mode                              : This component enabled
**            Low speed mode                               : This component disabled
**            Slow speed mode                              : This component disabled
**     Contents    :
**         DisableEvent - byte IFsh1_DisableEvent(void);
**         EnableEvent  - byte IFsh1_EnableEvent(void);
**         EraseSector  - byte IFsh1_EraseSector(IFsh1_TAddress Addr);
**         SetByteFlash - byte IFsh1_SetByteFlash(IFsh1_TAddress Addr, byte Data);
**         GetByteFlash - byte IFsh1_GetByteFlash(IFsh1_TAddress Addr, byte *Data);
**         SetBytePage  - byte IFsh1_SetBytePage(word Index, byte Data);
**         SetWordPage  - byte IFsh1_SetWordPage(word Index, word Data);
**         GetBytePage  - byte IFsh1_GetBytePage(word Index, byte *Data);
**         GetWordPage  - byte IFsh1_GetWordPage(word Index, word *Data);
**         SetPage      - byte IFsh1_SetPage(IFsh1_TAddress Addr);
**         GetPage      - byte IFsh1_GetPage(IFsh1_TAddress Addr);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file IFsh1.h
** @version 01.02
** @brief
**         This component "IntFLASH" implements an access to internal FLASH.
**         The component support reading/writing data into FLASH, erasing of
**         selected sector.
**         The component supports events if the write interrupt is supported.
**         The component supports following modes of write operations:
**           - Write - writing without any test.
**           - Destructive write - sector is erased if necessary.
**           - Safe write - user event is invoked to save and resore data
**                          from the current sector.
**         The component requires on-chip FLASH memory (not used/allocated by
**         other components).
*/         
/*!
**  @addtogroup IFsh1_module IFsh1 module documentation
**  @{
*/         

#ifndef __IFsh1_H
#define __IFsh1_H

/* MODULE IFsh1. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "IntFlashLdd1.h"

#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifndef __BWUserType_IFsh1_TDataAddress
#define __BWUserType_IFsh1_TDataAddress
  typedef byte* IFsh1_TDataAddress ;   /* Address of the data block in memory for methods Get/SetBlockFlash. To maintain backward compatibility, it is double-word on Freescale 56800/E family, otherwise it is pointer to the smallest addressable unit (byte).  */
#endif

#define IFsh1_WRITE_TYPE_NORMAL
/*Size of the virtual page in minimal addressable units (usually in bytes). The constant is defined only if the size is non-zero. */
#define IFsh1_VIRTUAL_PAGE_SIZE         (0x0800U)
/* Number of flash memory areas. For each area there are several constants with information about the area. */
#define IFsh1_AREA_COUNT                (0x01U)
/* Size of programming phrase. */
#define IFsh1_PROGRAMMING_PHRASE        (0x04U)
/* Minimal erasable unit. Value is in minimal addressable units. */
#define IFsh1_AREA_SECTOR_SIZE          (0x0200U)
/* TRUE if the component setting allows rewrite of already programmed flash memory location. */
#define IFsh1_ALLOW_CLEAR               (FALSE)

typedef LDD_FLASH_TAddress  IFsh1_TAddress;

void IFsh1_Init(void);
/*
** ===================================================================
**     Method      :  IFsh1_Init (component IntFLASH)
**
**     Description :
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

/*
** ===================================================================
**     Method      :  IFsh1_DisableEvent (component IntFLASH)
*/
/*!
**     @brief
**         This method disables all the events except [OnSaveBuffer],
**         [OnRestoreBuffer] and [OnEraseError]. The method is
**         available only if any event is enabled.
**     @return
**                         - Error code, possible codes: 
**                           - ERR_OK - OK 
**                           - ERR_SPEED - This device does not work in
**                           the active speed mode
*/
/* ===================================================================*/
byte IFsh1_DisableEvent(void);

/*
** ===================================================================
**     Method      :  IFsh1_EnableEvent (component IntFLASH)
*/
/*!
**     @brief
**         This method enables all the events except [OnSaveBuffer],
**         [OnRestoreBuffer] and [OnEraseError]. The method is
**         available only if any event is enabled.
**     @return
**                         - Error code, possible codes: 
**                           - ERR_OK - OK 
**                           - ERR_SPEED - This device does not work in
**                           the active speed mode
*/
/* ===================================================================*/
byte IFsh1_EnableEvent(void);

/*
** ===================================================================
**     Method      :  IFsh1_EraseSector (component IntFLASH)
*/
/*!
**     @brief
**         Erases the sector to which address Addr belongs.
**     @param
**         Addr            - Address in FLASH.
**     @return
**                         - Error code, possible codes: 
**                           - ERR_OK - OK 
**                           - ERR_NOTAVAIL - Desired program/erase
**                           operation is not available 
**                           - ERR_RANGE - Address is out of range 
**                           - ERR_SPEED - This device does not work in
**                           the active speed mode 
**                           - ERR_BUSY - Device is busy 
**                           - ERR_PROTECT - Flash is write protect 
**                           - ERR_VALUE - Flash sector erase was not
**                           successful
*/
/* ===================================================================*/
byte IFsh1_EraseSector(IFsh1_TAddress Addr);

/*
** ===================================================================
**     Method      :  IFsh1_SetByteFlash (component IntFLASH)
*/
/*!
**     @brief
**         Writes a byte to an address in FLASH. The operation of this
**         method depends on the "Write method" property and state of
**         the flash. Please see more details on general info page of
**         the help.
**     @param
**         Addr            - Address to FLASH.
**     @param
**         Data            - Data to write.
**     @return
**                         - Error code, possible codes: 
**                           - ERR_OK - OK 
**                           - ERR_NOTAVAIL - Desired program/erase
**                           operation is not available 
**                           - ERR_RANGE - Address is out of range 
**                           - ERR_VALUE - Read value is not equal to
**                           written value 
**                           - ERR_SPEED - This device does not work in
**                           the active speed mode 
**                           - ERR_BUSY - Device is busy 
**                           - ERR_PROTECT - Flash is write protect
*/
/* ===================================================================*/
byte IFsh1_SetByteFlash(IFsh1_TAddress Addr, byte Data);

/*
** ===================================================================
**     Method      :  IFsh1_GetByteFlash (component IntFLASH)
*/
/*!
**     @brief
**         Gets byte from an address in FLASH.
**     @param
**         Addr            - Address to FLASH.
**     @param
**         Data            - A pointer to the returned 8-bit data.
**     @return
**                         - Error code, possible codes: 
**                           - ERR_OK - OK 
**                           - ERR_RANGE - Address is out of range 
**                           - ERR_BUSY - Device is busy
*/
/* ===================================================================*/
byte IFsh1_GetByteFlash(IFsh1_TAddress Addr, byte *Data);

/*
** ===================================================================
**     Method      :  IFsh1_SetBytePage (component IntFLASH)
*/
/*!
**     @brief
**         Writes a byte to an address of the virtual page. This method
**         is only available when [Virtual page] property is enabled.
**     @param
**         Index           - Index to virtual page.
**     @param
**         Data            - Data to write.
**     @return
**                         - Error code, possible codes: 
**                           - ERR_OK - OK 
**                           - ERR_RANGE - Index is out of range 
**                           - ERR_NOTAVAIL - Virtual page address not
**                           set by the user
*/
/* ===================================================================*/
byte IFsh1_SetBytePage(word Index, byte Data);

/*
** ===================================================================
**     Method      :  IFsh1_SetWordPage (component IntFLASH)
*/
/*!
**     @brief
**         Writes a word to an address in the virtual page. This method
**         is only available when [Virtual page] property is enabled.
**     @param
**         Index           - Index to virtual page.
**     @param
**         Data            - Data to write.
**     @return
**                         - Error code, possible codes: 
**                           - ERR_OK - OK 
**                           - ERR_RANGE - Index is out of range
**                           - ERR_NOTAVAIL - Virtual page address not
**                           set by the user
*/
/* ===================================================================*/
byte IFsh1_SetWordPage(word Index, word Data);

/*
** ===================================================================
**     Method      :  IFsh1_GetBytePage (component IntFLASH)
*/
/*!
**     @brief
**         Gets a byte from an address in the virtual page. This method
**         is only available when [Virtual page] property is enabled.
**     @param
**         Index           - Index to a virtual page.
**     @param
**         Data            - A pointer to the returned 8-bit data.
**     @return
**                         - Error code, possible codes: 
**                           - ERR_OK - OK 
**                           - ERR_RANGE - Index is out of range
**                           - ERR_NOTAVAIL - Virtual page address not
**                           set by the user
*/
/* ===================================================================*/
byte IFsh1_GetBytePage(word Index, byte *Data);

/*
** ===================================================================
**     Method      :  IFsh1_GetWordPage (component IntFLASH)
*/
/*!
**     @brief
**         Gets a word from an address in the virtual page. This method
**         is only available when [Virtual page] property is enabled.
**     @param
**         Index           - Index to virtual page.
**     @param
**         Data            - A pointer to the returned 16-bit data.
**     @return
**                         - Error code, possible codes: 
**                           - ERR_OK - OK 
**                           - ERR_RANGE - Index is out of range 
**                           - ERR_NOTAVAIL - Virtual page address not
**                           set by the user
*/
/* ===================================================================*/
byte IFsh1_GetWordPage(word Index, word *Data);

/*
** ===================================================================
**     Method      :  IFsh1_SetPage (component IntFLASH)
*/
/*!
**     @brief
**         Writes a virtual page to an address in FLASH. This method is
**         enabled only if [Virtual page] property is enabled. The
**         operation of this method depends on the "Write method"
**         property and state of the flash. Please see more details on
**         general info page of the help.
**     @param
**         Addr            - Address in FLASH.
**     @return
**                         - Error code, possible codes: 
**                           - ERR_OK - OK 
**                           - ERR_NOTAVAIL - Desired program/erase
**                           operation is not available 
**                           - ERR_RANGE - The address is out of range 
**                           - ERR_VALUE - The read value is not equal
**                           to the written value 
**                           - ERR_SPEED - This device does not work in
**                           the active speed mode 
**                           - ERR_BUSY - Device is busy 
**                           - ERR_PROTECT - Flash is write protect
*/
/* ===================================================================*/
byte IFsh1_SetPage(IFsh1_TAddress Addr);

/*
** ===================================================================
**     Method      :  IFsh1_GetPage (component IntFLASH)
*/
/*!
**     @brief
**         Gets the virtual page from FLASH. This method is enabled
**         only if [Virtual page] property is enabled.
**     @param
**         Addr            - Address in FLASH.
**     @return
**                         - Error code, possible codes: 
**                           - ERR_OK - OK 
**                           - ERR_RANGE - The address is out of range 
**                           - ERR_BUSY - Device is busy
*/
/* ===================================================================*/
byte IFsh1_GetPage(IFsh1_TAddress Addr);

void IntFlashLdd1_OnOperationComplete(LDD_TUserData *UserDataPtr);

void IntFlashLdd1_OnError(LDD_TUserData *UserDataPtr);

/* END IFsh1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif
/* ifndef __IFsh1_H */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
