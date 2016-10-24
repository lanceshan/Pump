/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : IntFlashLdd1.c
**     Project     : kea-pump
**     Processor   : SKEAZ128MLK4
**     Component   : FLASH_LDD
**     Version     : Component 01.106, Driver 01.01, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-10-19, 14:32, # CodeGen: 13
**     Abstract    :
**          This embedded component implements an access to an on-chip flash memory.
**          Using this component the flash memory could be written to, erased,
**          read from. Some other services would be provided, if they are supported
**          by hardware, e.g. changes of the flash memory protection state.
**     Settings    :
**          Component name                                 : IntFlashLdd1
**          Device                                         : FTMRE
**          Clock frequency                                : 1.2 MHz
**          Use user memory areas                          : no
**          Interrupt service                              : Enabled
**            Read batch size                              : Unlimited
**            Command complete interrupt                   : 
**              Interrupt                                  : INT_FTMRE
**              Interrupt priority                         : medium priority
**              ISR name                                   : IntFlashLdd1_CommandCompleteInterrupt
**          Safe launch and wait                           : yes
**            Safe routine location                        : On stack
**            Interruptable wait loop                      : no
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : no
**            Event mask                                   : 
**              OnOperationComplete                        : Enabled
**              OnError                                    : Enabled
**            CPU clock/configuration selection            : 
**              Clock configuration 0                      : This component enabled
**              Clock configuration 1                      : This component disabled
**              Clock configuration 2                      : This component disabled
**              Clock configuration 3                      : This component disabled
**              Clock configuration 4                      : This component disabled
**              Clock configuration 5                      : This component disabled
**              Clock configuration 6                      : This component disabled
**              Clock configuration 7                      : This component disabled
**     Contents    :
**         Init               - LDD_TDeviceData* IntFlashLdd1_Init(LDD_TUserData *UserDataPtr);
**         Read               - LDD_TError IntFlashLdd1_Read(LDD_TDeviceData *DeviceDataPtr,...
**         Write              - LDD_TError IntFlashLdd1_Write(LDD_TDeviceData *DeviceDataPtr, LDD_TData...
**         Erase              - LDD_TError IntFlashLdd1_Erase(LDD_TDeviceData *DeviceDataPtr,...
**         GetOperationStatus - LDD_FLASH_TOperationStatus IntFlashLdd1_GetOperationStatus(LDD_TDeviceData...
**         GetError           - void IntFlashLdd1_GetError(LDD_TDeviceData *DeviceDataPtr,...
**         Main               - void IntFlashLdd1_Main(LDD_TDeviceData *DeviceDataPtr);
**         GetDriverState     - LDD_TDriverState IntFlashLdd1_GetDriverState(LDD_TDeviceData *DeviceDataPtr);
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
** @file IntFlashLdd1.c
** @version 01.01
** @brief
**          This embedded component implements an access to an on-chip flash memory.
**          Using this component the flash memory could be written to, erased,
**          read from. Some other services would be provided, if they are supported
**          by hardware, e.g. changes of the flash memory protection state.
*/         
/*!
**  @addtogroup IntFlashLdd1_module IntFlashLdd1 module documentation
**  @{
*/         

/* MODULE IntFlashLdd1. */

#include "IFsh1.h"
#include "IntFlashLdd1.h"
/* {Default RTOS Adapter} No RTOS includes */
#include "SIM_PDD.h"
#include "FTMRE_PDD.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SAFE_ROUTINE_SIZE 28U

/*
Safe launch and wait routine code. This code launch a command and
waits until command completion or command violation. Routine is
written as array of bytes to be constant size and compiler independent.
C language implementation could look like:

void SafeRoutine(void) {
  FTMRE_PDD_LaunchCommand(FTMRE_BASE_PTR);
  while (!FTMRE_PDD_GetCommandCompleteInterruptFlag(FTMRE_BASE_PTR)) {};
}
*/

typedef void (* LDD_FLASH_TSafeRoutinePtr)(void); /* Safe routine pointer type */

typedef struct {
  uint8_t SafeRoutine[SAFE_ROUTINE_SIZE]; /* Safe routine buffer */
} LDD_FLASH_TSafeRoutine;              /* Safe routine buffer type */

const static uint8_t SafeRoutine[SAFE_ROUTINE_SIZE - 4U] = {
  0x00U,0xb5U,               /*  push	{lr}                                         */
  0x04U,0x4aU,               /*  ldr	r2, [pc, #16]	; (bc <SafeRoutine___+0x14>) */
  0x80U,0x23U,               /*  movs	r3, #128	; 0x80                       */
  0x13U,0x70U,               /*  strb	r3, [r2, #0]                                 */
  0x11U,0x78U,               /*  ldrb	r1, [r2, #0]                                 */
  0x48U,0xb2U,               /*  sxtb	r0, r1                                       */
  0x00U,0x28U,               /*  cmp	r0, #0                                       */
  0xfbU,0xdaU,               /*  bge.n	b0 <SafeRoutine___+0x8>                      */
  0x00U,0xbdU,               /*  pop	{pc}                                         */
  0xc0U,0x46U,               /*  nop			; (mov r8, r8)               */
  (uint8_t)((0x40020005U>>0)&0xFFU),  /* FTMRE_FSTAT register address                 */
  (uint8_t)((0x40020005U>>8)&0xFFU),
  (uint8_t)((0x40020005U>>16)&0xFFU),
  (uint8_t)((0x40020005U>>24)&0xFFU)
};

typedef struct {
  LDD_FLASH_TOperationType   CurrentOperation;   /* Current operation type */
  LDD_FLASH_TOperationStatus CurrentOperationStatus; /* Current operation status */
  LDD_FLASH_TAddress         CurrentFlashAddress; /* Address of destination/source in the flash memory for the operation step */
  uint32_t                   CurrentUserAddress; /* Address of destination/source in the user memory for the operation step */
  LDD_FLASH_TDataSize        CurrentDataSize;    /* Data size of the current operation step */
  LDD_FLASH_TErrorFlags      CurrentErrorFlags;  /* Current error flags */
  LDD_TUserData             *UserDataPtr;        /* Device mode user device data structure */
} IntFlashLdd1_TDeviceData, *IntFlashLdd1_TDeviceDataPtr; /* Device data structure type */

/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static IntFlashLdd1_TDeviceData DevDataPtr__DEFAULT_RTOS_ALLOC;
/* {Default RTOS Adapter} Global variable used for passing a parameter into ISR */
static IntFlashLdd1_TDeviceDataPtr INT_FTMRE__DEFAULT_RTOS_ISRPARAM;

/* Internal method prototypes */
static LDD_TError CheckStateAndRange(IntFlashLdd1_TDeviceDataPtr DevDataPtr, LDD_FLASH_TAddress Address, LDD_FLASH_TDataSize Size);

/*
** ===================================================================
**     Method      :  CheckStateAndRange (component FLASH_LDD)
**
**     Description :
**         Range check internal routine. This routine is used by the 
**         component's method to test the input address range.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static LDD_TError CheckStateAndRange(IntFlashLdd1_TDeviceDataPtr DevDataPtr, LDD_FLASH_TAddress Address, LDD_FLASH_TDataSize Size)
{
  /* Input parameter test - this test can be disabled by setting the "Ignore range checking"
     property to the "yes" value in the "Configuration inspector" */
  if (Address >= (IntFlashLdd1_BLOCK0_ADDRESS + IntFlashLdd1_BLOCK0_SIZE)) {
    return ERR_PARAM_ADDRESS;
  }
  Address += Size;
  if (Address > (IntFlashLdd1_BLOCK0_ADDRESS + IntFlashLdd1_BLOCK0_SIZE)) {
    return ERR_PARAM_SIZE;
  }
  if (DevDataPtr->CurrentOperationStatus > LDD_FLASH_IDLE) {
    return ERR_BUSY;
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  IntFlashLdd1_Init (component FLASH_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the "Enable
**         in init. code" property is set to "yes" ([Enabled in init.
**         code]) value then the device is also enabled(see the
**         description of the Enable() method). In this case the
**         Enable() method is not necessary and needn't to be generated.
**         This method can be called only once. Before the second call
**         of Init() the Deinit() must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Device data structure pointer.
*/
/* ===================================================================*/
LDD_TDeviceData* IntFlashLdd1_Init(LDD_TUserData *UserDataPtr)
{
  IntFlashLdd1_TDeviceData *DevDataPtr;

  /* Allocate FLASH_LDD device structure */
  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DevDataPtr = &DevDataPtr__DEFAULT_RTOS_ALLOC;
  DevDataPtr->UserDataPtr = UserDataPtr; /* Store the user data */
  /* Allocate interrupt vector(s) */
  /* {Default RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable */
  INT_FTMRE__DEFAULT_RTOS_ISRPARAM = DevDataPtr;
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_IntFlashLdd1_ID,DevDataPtr);
  DevDataPtr->CurrentOperationStatus = LDD_FLASH_IDLE; /* Initialization of the Current operation status variable */
  DevDataPtr->CurrentOperation = LDD_FLASH_NO_OPERATION; /* Initialization of the Current operation type item */
  DevDataPtr->CurrentErrorFlags = 0U;  /* Initialization of the Current error flags item */
  #if defined(SIM_PDD_CLOCK_GATE_FTMRE)
  SIM_PDD_SetClockGate(SIM_BASE_PTR, SIM_PDD_CLOCK_GATE_FTMRE, PDD_ENABLE);
  #endif
  /* FTMRE_FCLKDIV: FDIVLD=0,FDIVLCK=0,FDIV=0x13 */
  FTMRE_FCLKDIV = FTMRE_FCLKDIV_FDIV(0x13); /* Set clock divider */
  /* NVIC_IPR1: PRI_5=1 */
  NVIC_IPR1 = (uint32_t)((NVIC_IPR1 & (uint32_t)~(uint32_t)(
               NVIC_IP_PRI_5(0x02)
              )) | (uint32_t)(
               NVIC_IP_PRI_5(0x01)
              ));
  /* NVIC_ISER: SETENA31=0,SETENA30=0,SETENA29=0,SETENA28=0,SETENA27=0,SETENA26=0,SETENA25=0,SETENA24=0,SETENA23=0,SETENA22=0,SETENA21=0,SETENA20=0,SETENA19=0,SETENA18=0,SETENA17=0,SETENA16=0,SETENA15=0,SETENA14=0,SETENA13=0,SETENA12=0,SETENA11=0,SETENA10=0,SETENA9=0,SETENA8=0,SETENA7=0,SETENA6=0,SETENA5=1,SETENA4=0,SETENA3=0,SETENA2=0,SETENA1=0,SETENA0=0 */
  NVIC_ISER = NVIC_ISER_SETENA5_MASK;
  /* NVIC_ICER: CLRENA31=0,CLRENA30=0,CLRENA29=0,CLRENA28=0,CLRENA27=0,CLRENA26=0,CLRENA25=0,CLRENA24=0,CLRENA23=0,CLRENA22=0,CLRENA21=0,CLRENA20=0,CLRENA19=0,CLRENA18=0,CLRENA17=0,CLRENA16=0,CLRENA15=0,CLRENA14=0,CLRENA13=0,CLRENA12=0,CLRENA11=0,CLRENA10=0,CLRENA9=0,CLRENA8=0,CLRENA7=0,CLRENA6=0,CLRENA5=0,CLRENA4=0,CLRENA3=0,CLRENA2=0,CLRENA1=0,CLRENA0=0 */
  NVIC_ICER = 0x00U;
  return DevDataPtr;
}

/*
** ===================================================================
**     Method      :  IntFlashLdd1_Read (component FLASH_LDD)
*/
/*!
**     @brief
**         This method sets up a flash memory read operation. The
**         operation itself is performing by defined batches (property
**         [Read batch size]) by periodical calling the component�s
**         Main method in the user application (higher level OS service).
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         FromAddress     - Address to the flash
**                           memory the output data would be read from.
**     @param
**         ToPtr           - Pointer to a location the data would
**                           be written to.
**     @param
**         Size            - Size of the data (in bytes)  to be read
**                           from the flash memory.
**     @return
**                         - Error code
**                           ERR_OK - OK
**                           ERR_DISABLED - Component is disabled
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_BUSY - Some flash memory operation is
**                           already in progress 
**                           ERR_PARAM_ADDRESS - Desired flash memory
**                           area is out of allowed range
*/
/* ===================================================================*/
LDD_TError IntFlashLdd1_Read(LDD_TDeviceData *DeviceDataPtr, LDD_FLASH_TAddress FromAddress, LDD_TData *ToPtr, LDD_FLASH_TDataSize Size)
{
  IntFlashLdd1_TDeviceDataPtr DevDataPtr = (IntFlashLdd1_TDeviceDataPtr)DeviceDataPtr;
  LDD_TError Result;
  
  Result = CheckStateAndRange(DevDataPtr, FromAddress, Size);
  if (Result != ERR_OK) {
    return Result;
  }
  DevDataPtr->CurrentOperation = LDD_FLASH_READ;
  DevDataPtr->CurrentOperationStatus = LDD_FLASH_START;
  DevDataPtr->CurrentFlashAddress = FromAddress;
  DevDataPtr->CurrentUserAddress = (uint32_t)ToPtr;
  DevDataPtr->CurrentDataSize = Size;
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  IntFlashLdd1_Write (component FLASH_LDD)
*/
/*!
**     @brief
**         This method sets up a flash memory write operation. The
**         operation itself is performing by defined batches (property
**         [Write batch size]) by periodical calling the component�s
**         Main method in the user application (higher level OS service)
**         or by the component�s ISR, if an component�s interrupt
**         service is enabled.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         FromPtr         - Pointer to data to be written to
**                           the flash memory.
**     @param
**         ToAddress       - Address to the flash memory
**                           the input data would be written to.
**     @param
**         Size            - Size of the input data (in bytes) to be
**                           written to the flash memory.
**     @return
**                         - Error code
**                           ERR_OK - OK
**                           ERR_DISABLED - Component is disabled
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_BUSY - Some flash memory operation is
**                           already in progress 
**                           ERR_PARAM_ADDRESS - Desired flash memory
**                           area is out of allowed range
**                           ERR_NOTAVAIL - When Safe launch and wait
**                           mode is enabled (property Safe launch and
**                           wait) and safe routine location is defined
**                           in runtime (property Safe routine location)
**                           and the safe routine location has not been
**                           specified yet (the SetSafeRoutineLocation
**                           method has not been used to define the
**                           location the safe routine will be copied to).
*/
/* ===================================================================*/
LDD_TError IntFlashLdd1_Write(LDD_TDeviceData *DeviceDataPtr, LDD_TData *FromPtr, LDD_FLASH_TAddress ToAddress, LDD_FLASH_TDataSize Size)
{
  IntFlashLdd1_TDeviceDataPtr DevDataPtr = (IntFlashLdd1_TDeviceDataPtr)DeviceDataPtr;
  LDD_TError Result;
  
  Result = CheckStateAndRange(DevDataPtr, ToAddress, Size);
  if (Result != ERR_OK) {
    return Result;
  }
  FTMRE_PDD_SetCommand(FTMRE_BASE_PTR, FTMRE_PDD_CMD_PROGRAM_FLASH);
  DevDataPtr->CurrentOperation = LDD_FLASH_WRITE;
  DevDataPtr->CurrentOperationStatus = LDD_FLASH_START;
  DevDataPtr->CurrentUserAddress = (uint32_t)FromPtr;
  DevDataPtr->CurrentFlashAddress = ToAddress;
  DevDataPtr->CurrentDataSize = Size;
  FTMRE_PDD_EnableCommandCompleteInterrupt(FTMRE_BASE_PTR); /* Enable the Command complete interrupt */
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  IntFlashLdd1_Erase (component FLASH_LDD)
*/
/*!
**     @brief
**         This method sets up a flash memory erase operation. The
**         operation itself is performing by defined batches (property
**         [Erase batch size]) by periodical calling the component�s
**         Main method in the user application (higher level OS service)
**         or by the component�s ISR, if an component�s interrupt
**         service is enabled.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         FromAddress     - Address of the flash
**                           memory area (the first erase sector is the
**                           sector the given address belongs to) to be
**                           erased.
**     @param
**         Size            - Size of the flash memory area (in bytes)
**                           to be erased. The flash memory is erased by
**                           the erase sectors. The first erased sector
**                           is a sector the address specified by the
**                           input parameter Address belongs to. The
**                           last erased sector is a sector the address
**                           calculated like an addition of the address
**                           specified by the input parameter Address
**                           and the size specified by the input
**                           parameter Size belongs to.
**     @return
**                         - Error code
**                           ERR_OK - OK
**                           ERR_DISABLED - Component is disabled
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_BUSY - Some flash memory operation is
**                           already in progress 
**                           ERR_PARAM_ADDRESS - Desired flash memory
**                           area is out of allowed range or is not
**                           aligned to erasable units' bounderies
**                           ERR_NOTAVAIL - When Safe launch and wait
**                           mode is enabled (property Safe launch and
**                           wait) and safe routine location is defined
**                           in runtime (property Safe routine location)
**                           and the safe routine location has not been
**                           specified yet (the SetSafeRoutineLocation
**                           method has not been used to define the
**                           location the safe routine will be copied to).
*/
/* ===================================================================*/
LDD_TError IntFlashLdd1_Erase(LDD_TDeviceData *DeviceDataPtr, LDD_FLASH_TAddress FromAddress, LDD_FLASH_TDataSize Size)
{
  IntFlashLdd1_TDeviceDataPtr DevDataPtr = (IntFlashLdd1_TDeviceDataPtr)DeviceDataPtr;
  LDD_TError Result;
  
  Result = CheckStateAndRange(DevDataPtr, FromAddress, Size);
  if (Result != ERR_OK) {
    return Result;
  }
  DevDataPtr->CurrentOperation = LDD_FLASH_ERASE;
  DevDataPtr->CurrentOperationStatus = LDD_FLASH_START;
  DevDataPtr->CurrentDataSize = Size;
  /* FTMRE_PDD_CMD_ERASE_FLASH_SECTOR requires sector address to be 4 bytes aligned  */
  DevDataPtr->CurrentFlashAddress = FromAddress & ~(uint32_t)IntFlashLdd1_FLASH_WRITABLE_UNIT_MASK;
  FTMRE_PDD_SetCommand(FTMRE_BASE_PTR, FTMRE_PDD_CMD_ERASE_FLASH_SECTOR);
  FTMRE_PDD_EnableCommandCompleteInterrupt(FTMRE_BASE_PTR); /* Enable the Command complete interrupt */
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  IntFlashLdd1_GetOperationStatus (component FLASH_LDD)
*/
/*!
**     @brief
**         Returns a status of current (last) flash memory operation.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Current flash memory operation status. See
**                           the LDD_FLASH_TOperationStatus type's
**                           description for details.
*/
/* ===================================================================*/
LDD_FLASH_TOperationStatus IntFlashLdd1_GetOperationStatus(LDD_TDeviceData *DeviceDataPtr)
{
  return ((IntFlashLdd1_TDeviceDataPtr)(DeviceDataPtr))->CurrentOperationStatus; /* Return current operation status */
}

/*
** ===================================================================
**     Method      :  IntFlashLdd1_GetError (component FLASH_LDD)
*/
/*!
**     @brief
**         Returns an error state of a current (or last) flash
**         operation. 
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         OperationStatus - Pointer to an
**                           output structure with the error status
**                           details. See the LDD_FLASH_TErrorStatus
**                           type's description for details.
*/
/* ===================================================================*/
void IntFlashLdd1_GetError(LDD_TDeviceData *DeviceDataPtr, LDD_FLASH_TErrorStatus *OperationStatus)
{
  IntFlashLdd1_TDeviceDataPtr DevDataPtr = (IntFlashLdd1_TDeviceDataPtr)DeviceDataPtr; /* Auxiliary variable - pointer to an internal state structure */

  /* Copy of information from internal status structure to the output error status structure */
  /* {Default RTOS Adapter} Critical section begin, general PE function is used */
  EnterCritical();
  OperationStatus->CurrentOperation = DevDataPtr->CurrentOperation; /* Copy the Current operation type to the output structure */
  /*
  OperationStatus->CurrentCommand = DevDataPtr->CurrentCommand;
  */
  OperationStatus->CurrentErrorFlags = DevDataPtr->CurrentErrorFlags; /* Copy the Current error flags to the output structure */
  OperationStatus->CurrentAddress = DevDataPtr->CurrentFlashAddress; /* Copy the Current flash address to the output structure */
  OperationStatus->CurrentDataPtr = (LDD_TData *)DevDataPtr->CurrentUserAddress; /* Copy the Current input/output data pointer to the output structure */
  OperationStatus->CurrentDataSize = DevDataPtr->CurrentDataSize; /* Copy the Current input/output data size to the output structure */
  /* {Default RTOS Adapter} Critical section end, general PE function is used */
  ExitCritical();
}

/*
** ===================================================================
**     Method      :  IntFlashLdd1_Main (component FLASH_LDD)
*/
/*!
**     @brief
**         This method is used to perform one batch of a flash memory
**         operation. This method is used to perform batches of all
**         flash memory operations (Write, Read, Erase, EraseBlock,
**         VerifyErasedBlock) when the component works in the polled
**         mode (interrupt service is disabled - property [Interrupt
**         service]). This method performs batches of the read flash
**         memory operation, when the component works in the interrupt
**         triggered mode (interrupt service is enabled). This method
**         is enabled only if the component works in the polled mode or
**         if the Read method is enabled.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
*/
/* ===================================================================*/
void IntFlashLdd1_Main(LDD_TDeviceData *DeviceDataPtr)
{
  IntFlashLdd1_TDeviceDataPtr DevDataPtr = (IntFlashLdd1_TDeviceDataPtr)DeviceDataPtr;

  uint32 Index;
  uint32_t j;
  uint32_t AlignedFlashAddress;
  uint8_t WrittenData[4];
  LDD_FLASH_TSafeRoutine SaveRoutineStackSpace;
  LDD_FLASH_TSafeRoutinePtr SafeRoutinePtr;
  uint8_t CurrentFlags;
  
  if (DevDataPtr->CurrentOperationStatus == LDD_FLASH_START) {
    /* First run of current operation */
    FTMRE_PDD_ClearFlags(FTMRE_BASE_PTR, FTMRE_PDD_ACCESS_ERROR_FLAG | FTMRE_PDD_PROTECTION_VIOLATION_FLAG);
    CurrentFlags = 0U;
    DevDataPtr->CurrentErrorFlags = 0U;
    DevDataPtr->CurrentOperationStatus = LDD_FLASH_RUNNING;
  } else if(DevDataPtr->CurrentOperation == LDD_FLASH_READ) {
    /* For Read operation HW flags has no meaning */
    CurrentFlags = 0U;
  } else {
    /* After HW command is done HW flags must be checked */
    CurrentFlags = DevDataPtr->CurrentErrorFlags | FTMRE_PDD_GetFlags(FTMRE_BASE_PTR);
  }
  if (CurrentFlags != 0U) {
    /* Command error detected */
    DevDataPtr->CurrentOperationStatus = LDD_FLASH_FAILED;
    FTMRE_PDD_DisableCommandCompleteInterrupt(FTMRE_BASE_PTR); /* Disable the Command complete interrupt */
    IntFlashLdd1_OnError(DevDataPtr->UserDataPtr);
    return;
  } else if ((int32_t)DevDataPtr->CurrentDataSize <= 0) {
    /* Command done */
    DevDataPtr->CurrentOperationStatus = LDD_FLASH_IDLE;
    FTMRE_PDD_DisableCommandCompleteInterrupt(FTMRE_BASE_PTR); /* Disable the Command complete interrupt */
    IntFlashLdd1_OnOperationComplete(DevDataPtr->UserDataPtr);
  } else {
    /* Command in progress */
    switch (DevDataPtr->CurrentOperation) {
      case LDD_FLASH_WRITE:
        Index = 2U;
        FTMRE_PDD_SetAddress(FTMRE_BASE_PTR, DevDataPtr->CurrentFlashAddress & ~(uint32_t)IntFlashLdd1_FLASH_WRITABLE_UNIT_MASK);
        while ((DevDataPtr->CurrentDataSize) && (Index <= 5U)) {
          AlignedFlashAddress = DevDataPtr->CurrentFlashAddress & ~(uint32_t)IntFlashLdd1_FLASH_WRITABLE_UNIT_MASK;
          for (j=0x00U; j<=0x03U; j++) {
            if ((AlignedFlashAddress < DevDataPtr->CurrentFlashAddress) || (DevDataPtr->CurrentDataSize == 0x00U)) {
              WrittenData[j] = *(uint8_t*)AlignedFlashAddress++;
            } else {
              WrittenData[j] = *(uint8_t*)DevDataPtr->CurrentUserAddress++;
              DevDataPtr->CurrentDataSize--;
            }
          }
          AlignedFlashAddress = DevDataPtr->CurrentFlashAddress & ~(uint32_t)IntFlashLdd1_FLASH_WRITABLE_UNIT_MASK;
          if ((*(uint32_t*)AlignedFlashAddress ^ *(uint32_t*)(void*)WrittenData) & *(uint32_t*)(void*)WrittenData) {
            /* Only erase operation can change bits from 0 to 1 value */
            DevDataPtr->CurrentErrorFlags |= LDD_FLASH_MULTIPLE_WRITE_ERROR;
            return;
          }
          DevDataPtr->CurrentFlashAddress = AlignedFlashAddress + 4U;
          FTMRE_PDD_SetProgrammedWord(FTMRE_BASE_PTR, Index++, WrittenData[1], WrittenData[0]);
          FTMRE_PDD_SetProgrammedWord(FTMRE_BASE_PTR, Index++, WrittenData[3], WrittenData[2]);
        }
        break;
      case LDD_FLASH_ERASE:
        FTMRE_PDD_SetAddress(FTMRE_BASE_PTR, DevDataPtr->CurrentFlashAddress);
        DevDataPtr->CurrentFlashAddress += IntFlashLdd1_FLASH_ERASABLE_UNIT_SIZE;
        DevDataPtr->CurrentDataSize -= IntFlashLdd1_FLASH_ERASABLE_UNIT_SIZE;
        break;
      case LDD_FLASH_READ:
        while (DevDataPtr->CurrentDataSize) {
          *(uint8_t*)DevDataPtr->CurrentUserAddress++ = *(uint8_t*)DevDataPtr->CurrentFlashAddress++;
          DevDataPtr->CurrentDataSize--;
        }
        return;
      default:
        DevDataPtr->CurrentDataSize = 0U;
        break;
    }
    /* The safe routine must be aligned to 16bit word */
    SafeRoutinePtr = (LDD_FLASH_TSafeRoutinePtr)(((uint32_t)&SaveRoutineStackSpace + 1U) & ~(uint32_t)1U);
    /* Copy the safe routine's code to a buffer on the stack */
    *(LDD_FLASH_TSafeRoutine *)(void *)SafeRoutinePtr = *(LDD_FLASH_TSafeRoutine *)(void *)&SafeRoutine;
    ((LDD_FLASH_TSafeRoutinePtr)((uint32_t)(SafeRoutinePtr) | 1U))(); /* Run the Safe routine */
  }
}

/*
** ===================================================================
**     Method      :  IntFlashLdd1_CommandCompleteInterrupt (component FLASH_LDD)
**
**     Description :
**         Command complete interrupt service routine.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(IntFlashLdd1_CommandCompleteInterrupt)
{
  /* {Default RTOS Adapter} ISR parameter is passed through the global variable */
  IntFlashLdd1_TDeviceDataPtr DevDataPtr = INT_FTMRE__DEFAULT_RTOS_ISRPARAM;
  IntFlashLdd1_Main((LDD_TDeviceData *)DevDataPtr);
}
/*
** ===================================================================
**     Method      :  IntFlashLdd1_GetDriverState (component FLASH_LDD)
*/
/*!
**     @brief
**         This method returns the current driver status.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - The current driver status mask.
**                           Following status masks defined in PE_Types.
**                           h can be used to check the current driver
**                           status.
**                           PE_LDD_DRIVER_DISABLED_IN_CLOCK_CONFIGURATIO
**                           N - 1 - Driver is disabled in the current
**                           mode; 0 - Driver is enabled in the current
**                           mode.  
**                           PE_LDD_DRIVER_DISABLED_BY_USER - 1 - Driver
**                           is disabled by the user; 0 - Driver is
**                           enabled by the user.        
**                           PE_LDD_DRIVER_BUSY - 1 - Driver is the BUSY
**                           state; 0 - Driver is in the IDLE state.
*/
/* ===================================================================*/
LDD_TDriverState IntFlashLdd1_GetDriverState(LDD_TDeviceData *DeviceDataPtr)
{
  IntFlashLdd1_TDeviceDataPtr DevDataPtr = (IntFlashLdd1_TDeviceDataPtr)DeviceDataPtr;
  LDD_TDriverState DriverState = 0x00U;

  if (DevDataPtr->CurrentOperationStatus > LDD_FLASH_IDLE) {
    DriverState |= PE_LDD_DRIVER_BUSY; /* Driver is BUSY */
  }
  return DriverState;
}

/* END IntFlashLdd1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif

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