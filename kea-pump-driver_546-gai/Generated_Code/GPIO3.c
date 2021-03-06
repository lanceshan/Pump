/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : GPIO3.c
**     Project     : kea-pump
**     Processor   : SKEAZ128MLK4
**     Component   : GPIO_LDD
**     Version     : Component 01.128, Driver 01.08, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-10-19, 14:32, # CodeGen: 13
**     Abstract    :
**         The HAL GPIO component will provide a low level API for unified
**         access to general purpose digital input/output pins across
**         various device designs.
**
**         RTOS drivers using HAL GPIO API will be simpler and more
**         portable to various microprocessors.
**     Settings    :
**          Component name                                 : GPIO3
**          Port                                           : GPIOC
**          Port width                                     : 32 bits
**          Mask of allocated pins                         : 24
**          Interrupt service/event                        : Disabled
**          Bit fields                                     : 2
**            Bit field                                    : 
**              Field name                                 : AHI2
**              Pins                                       : 1
**                Pin                                      : 
**                  Pin                                    : PTI2/IRQ
**                  Pin signal                             : 
**                  Initial pin direction                  : Output
**                    Initial output state                 : 0
**                  Initial pin event                      : Disabled
**            Bit field                                    : 
**              Field name                                 : ALO
**              Pins                                       : 1
**                Pin                                      : 
**                  Pin                                    : PTI5/IRQ
**                  Pin signal                             : 
**                  Initial pin direction                  : Output
**                    Initial output state                 : 0
**                  Initial pin event                      : Disabled
**          Initialization                                 : 
**            Auto initialization                          : yes
**            Event mask                                   : 
**              OnPortEvent                                : Disabled
**     Contents    :
**         Init            - LDD_TDeviceData* GPIO3_Init(LDD_TUserData *UserDataPtr);
**         SetFieldValue   - void GPIO3_SetFieldValue(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField...
**         GetFieldValue   - GPIO3_TFieldValue GPIO3_GetFieldValue(LDD_TDeviceData *DeviceDataPtr,...
**         ClearFieldBits  - void GPIO3_ClearFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField...
**         SetFieldBits    - void GPIO3_SetFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField...
**         ToggleFieldBits - void GPIO3_ToggleFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField...
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
** @file GPIO3.c
** @version 01.08
** @brief
**         The HAL GPIO component will provide a low level API for unified
**         access to general purpose digital input/output pins across
**         various device designs.
**
**         RTOS drivers using HAL GPIO API will be simpler and more
**         portable to various microprocessors.
*/         
/*!
**  @addtogroup GPIO3_module GPIO3 module documentation
**  @{
*/         

/* MODULE GPIO3. */

#include "GPIO3.h"
/* {Default RTOS Adapter} No RTOS includes */
#include "IO_Map.h"

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct {
  LDD_TUserData *UserData;             /* RTOS device data structure */
} GPIO3_TDeviceData, *GPIO3_TDeviceDataPtr; /* Device data structure type */
/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static GPIO3_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
/*
** ===================================================================
**     Method      :  GPIO3_Init (component GPIO_LDD)
*/
/*!
**     @brief
**         This method initializes the associated peripheral(s) and the
**         component internal variables. The method is called
**         automatically as a part of the application initialization
**         code.
**     @param
**         UserDataPtr     - Pointer to the RTOS device
**                           structure. This pointer will be passed to
**                           all events as parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* GPIO3_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate LDD device structure */
  GPIO3_TDeviceData *DeviceDataPrv;

  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  /* Save RTOS Device structure */
  DeviceDataPrv->UserData = UserDataPtr; /* Store the RTOS device structure */
  /* GPIOC_PDOR: PDO&=~0x24 */
  GPIOC_PDOR &= (uint32_t)~(uint32_t)(GPIO_PDOR_PDO(0x24));
  /* GPIOC_PDDR: PDD|=0x24 */
  GPIOC_PDDR |= GPIO_PDDR_PDD(0x24);
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_GPIO3_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv);
}

/*
** ===================================================================
**     Method      :  GPIO3_SetFieldValue (component GPIO_LDD)
*/
/*!
**     @brief
**         This method sets the output data value of the specified bit
**         field.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Field           - Bit field to write. Bit fields are
**                           defined during design time and for each bit
**                           field there is a generated constant.
**     @param
**         Value           - Aligned data value to writting to the
**                           specified bit field. The bit 0 corresponds
**                           with the pin which has index 0 within the
**                           given bit field, the bit 1 corresponds with
**                           the pin which has index 1 within the given
**                           bit field, etc.
*/
/* ===================================================================*/
void GPIO3_SetFieldValue(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field, GPIO3_TFieldValue Value)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  switch (Field) {                     /* no break */
    case AHI2: {                       /* bit field #0 */
      GPIO_PDD_SetPortDataOutput(GPIO3_MODULE_BASE_ADDRESS,
        (
          GPIO_PDD_GetPortDataOutput(GPIO3_MODULE_BASE_ADDRESS)
          & ((GPIO3_TPortValue)(~((GPIO3_TPortValue)GPIO3_AHI2_MASK)))
        )
        | (
          ((GPIO3_TPortValue)(Value << GPIO3_AHI2_START_BIT))
          & ((GPIO3_TPortValue)GPIO3_AHI2_MASK)
        )
      );
      break;
    }
    case ALO: {                        /* bit field #1 */
      GPIO_PDD_SetPortDataOutput(GPIO3_MODULE_BASE_ADDRESS,
        (
          GPIO_PDD_GetPortDataOutput(GPIO3_MODULE_BASE_ADDRESS)
          & ((GPIO3_TPortValue)(~((GPIO3_TPortValue)GPIO3_ALO_MASK)))
        )
        | (
          ((GPIO3_TPortValue)(Value << GPIO3_ALO_START_BIT))
          & ((GPIO3_TPortValue)GPIO3_ALO_MASK)
        )
      );
      break;
    }
    default:
      break;                           /* Invalid Field is not treated, result is undefined */
  } /* switch (Field) */
}

/*
** ===================================================================
**     Method      :  GPIO3_GetFieldValue (component GPIO_LDD)
*/
/*!
**     @brief
**         This method returns the current input data of the specified
**         field.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Field           - Bit field to reading. Bit fields are
**                           defined during design time and for each bit
**                           field there is a generated constant.
**     @return
**                         - Aligned current port input value masked for
**                           allocated pins of the field. The bit 0
**                           corresponds with the pin which has index 0
**                           within the given bit field, the bit 1
**                           corresponds with the pin which has index 1
**                           within the given bit field, etc.
*/
/* ===================================================================*/
GPIO3_TFieldValue GPIO3_GetFieldValue(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  switch (Field) {                     /* no break */
    case AHI2: {                       /* bit field #0 */
      return
        (GPIO3_TFieldValue)(
          (
            GPIO_PDD_GetPortDataInput(GPIO3_MODULE_BASE_ADDRESS)
            & (GPIO3_TPortValue)GPIO3_AHI2_MASK
          )
          >> GPIO3_AHI2_START_BIT
        );
    }
    case ALO: {                        /* bit field #1 */
      return
        (GPIO3_TFieldValue)(
          (
            GPIO_PDD_GetPortDataInput(GPIO3_MODULE_BASE_ADDRESS)
            & (GPIO3_TPortValue)GPIO3_ALO_MASK
          )
          >> GPIO3_ALO_START_BIT
        );
    }
    default:
      break;                           /* Invalid BitField is not treated, result is undefined */
  } /* switch (Field) */
  return (GPIO3_TFieldValue)0U;
}

/*
** ===================================================================
**     Method      :  GPIO3_ClearFieldBits (component GPIO_LDD)
*/
/*!
**     @brief
**         This method drives the specified bits of the specified bit
**         field to the inactive level.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Field           - Bit field to write. Bit fields are
**                           defined during design time and for each bit
**                           field there is a generated constant.
**     @param
**         Mask            - Aligned mask of bits to setting the
**                           inactive level. Each field pin has
**                           corresponding bit in the mask. Bit value 0
**                           means not selected bit, bit value 1 means
**                           selected bit. The bit 0 corresponds with
**                           the pin which has index 0 within the given
**                           bit field, the bit 1 corresponds with the
**                           pin which has index 1 within the given bit
**                           field, etc.
*/
/* ===================================================================*/
void GPIO3_ClearFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field, GPIO3_TFieldValue Mask)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  switch (Field) {                     /* no break */
    case AHI2: {                       /* bit field #0 */
      GPIO_PDD_ClearPortDataOutputMask(GPIO3_MODULE_BASE_ADDRESS,
        ((GPIO3_TPortValue)GPIO3_AHI2_MASK)
        & ((GPIO3_TPortValue)(Mask << GPIO3_AHI2_START_BIT))
      );
      break;
    }
    case ALO: {                        /* bit field #1 */
      GPIO_PDD_ClearPortDataOutputMask(GPIO3_MODULE_BASE_ADDRESS,
        ((GPIO3_TPortValue)GPIO3_ALO_MASK)
        & ((GPIO3_TPortValue)(Mask << GPIO3_ALO_START_BIT))
      );
      break;
    }
    default:
      break;                           /* Invalid Field is not treated, result is undefined */
  } /* switch (Field) */
}

/*
** ===================================================================
**     Method      :  GPIO3_SetFieldBits (component GPIO_LDD)
*/
/*!
**     @brief
**         This method drives the specified bits of the specified bit
**         field to the active level.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Field           - Bit field to write. Bit fields are
**                           defined during design time and for each bit
**                           field there is a generated constant.
**     @param
**         Mask            - Aligned mask of bits to setting the
**                           active level. Each field pin has
**                           corresponding bit in the mask. Bit value 0
**                           means not selected bit, bit value 1 means
**                           selected bit. The bit 0 corresponds with
**                           the pin which has index 0 within the given
**                           bit field, the bit 1 corresponds with the
**                           pin which has index 1 within the given bit
**                           field, etc.
*/
/* ===================================================================*/
void GPIO3_SetFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field, GPIO3_TFieldValue Mask)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  switch (Field) {                     /* no break */
    case AHI2: {                       /* bit field #0 */
      GPIO_PDD_SetPortDataOutputMask(GPIO3_MODULE_BASE_ADDRESS,
        ((GPIO3_TPortValue)GPIO3_AHI2_MASK)
        & ((GPIO3_TPortValue)(Mask << GPIO3_AHI2_START_BIT))
      );
      break;
    }
    case ALO: {                        /* bit field #1 */
      GPIO_PDD_SetPortDataOutputMask(GPIO3_MODULE_BASE_ADDRESS,
        ((GPIO3_TPortValue)GPIO3_ALO_MASK)
        & ((GPIO3_TPortValue)(Mask << GPIO3_ALO_START_BIT))
      );
      break;
    }
    default:
      break;                           /* Invalid Field is not treated, result is undefined */
  } /* switch (Field) */
}

/*
** ===================================================================
**     Method      :  GPIO3_ToggleFieldBits (component GPIO_LDD)
*/
/*!
**     @brief
**         This method inverts the specified bits of the specified bit
**         field to other level.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Field           - Bit field to write. Bit fields are
**                           defined during design time and for each bit
**                           field there is a generated constant.
**     @param
**         Mask            - Aligned mask of bits to inverting the
**                           current level. Each field pin has
**                           corresponding bit in the mask. Bit value 0
**                           means not selected bit, bit value 1 means
**                           selected bit. The bit 0 corresponds with
**                           the pin which has index 0 within the given
**                           bit field, the bit 1 corresponds with the
**                           pin which has index 1 within the given bit
**                           field, etc.
*/
/* ===================================================================*/
void GPIO3_ToggleFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field, GPIO3_TFieldValue Mask)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  switch (Field) {                     /* no break */
    case AHI2: {                       /* bit field #0 */
      GPIO_PDD_TogglePortDataOutputMask(GPIO3_MODULE_BASE_ADDRESS,
        ((GPIO3_TPortValue)GPIO3_AHI2_MASK)
        & ((GPIO3_TPortValue)(Mask << GPIO3_AHI2_START_BIT))
      );
      break;
    }
    case ALO: {                        /* bit field #1 */
      GPIO_PDD_TogglePortDataOutputMask(GPIO3_MODULE_BASE_ADDRESS,
        ((GPIO3_TPortValue)GPIO3_ALO_MASK)
        & ((GPIO3_TPortValue)(Mask << GPIO3_ALO_START_BIT))
      );
      break;
    }
    default:
      break;                           /* Invalid Field is not treated, result is undefined */
  } /* switch (Field) */
}

/* END GPIO3. */

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
