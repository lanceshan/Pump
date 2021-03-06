/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : GPIO1.c
**     Project     : kea-pump
**     Processor   : SKEAZ128MLK4
**     Component   : GPIO_LDD
**     Version     : Component 01.128, Driver 01.08, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-07-17, 11:32, # CodeGen: 3
**     Abstract    :
**         The HAL GPIO component will provide a low level API for unified
**         access to general purpose digital input/output pins across
**         various device designs.
**
**         RTOS drivers using HAL GPIO API will be simpler and more
**         portable to various microprocessors.
**     Settings    :
**          Component name                                 : GPIO1
**          Port                                           : GPIOA
**          Port width                                     : 32 bits
**          Mask of allocated pins                         : E0042002
**          Interrupt service/event                        : Disabled
**          Bit fields                                     : 6
**            Bit field                                    : 
**              Field name                                 : CCEN
**              Pins                                       : 1
**                Pin                                      : 
**                  Pin                                    : PTB5/KBI0_P13/FTM2_CH5/SPI0_PCS/ACMP1_OUT
**                  Pin signal                             : 
**                  Initial pin direction                  : Output
**                    Initial output state                 : 0
**                  Initial pin event                      : Disabled
**            Bit field                                    : 
**              Field name                                 : CHI
**              Pins                                       : 1
**                Pin                                      : 
**                  Pin                                    : PTC2/KBI0_P18/FTM2_CH2/ADC0_SE10
**                  Pin signal                             : 
**                  Initial pin direction                  : Output
**                    Initial output state                 : 0
**                  Initial pin event                      : Disabled
**            Bit field                                    : 
**              Field name                                 : CLO
**              Pins                                       : 1
**                Pin                                      : 
**                  Pin                                    : PTD7/KBI0_P31/UART2_TX
**                  Pin signal                             : 
**                  Initial pin direction                  : Output
**                    Initial output state                 : 0
**                  Initial pin event                      : Disabled
**            Bit field                                    : 
**              Field name                                 : BLO
**              Pins                                       : 1
**                Pin                                      : 
**                  Pin                                    : PTD6/KBI0_P30/UART2_RX
**                  Pin signal                             : 
**                  Initial pin direction                  : Output
**                    Initial output state                 : 0
**                  Initial pin event                      : Disabled
**            Bit field                                    : 
**              Field name                                 : BHI
**              Pins                                       : 1
**                Pin                                      : 
**                  Pin                                    : PTD5/KBI0_P29/PWT_IN0
**                  Pin signal                             : 
**                  Initial pin direction                  : Output
**                    Initial output state                 : 0
**                  Initial pin event                      : Disabled
**            Bit field                                    : 
**              Field name                                 : uHome
**              Pins                                       : 1
**                Pin                                      : 
**                  Pin                                    : PTA1/KBI0_P1/FTM0_CH1/I2C0_4WSDAOUT/ACMP0_IN1/ADC0_SE1
**                  Pin signal                             : 
**                  Initial pin direction                  : Input
**                  Initial pin event                      : Disabled
**          Initialization                                 : 
**            Auto initialization                          : yes
**            Event mask                                   : 
**              OnPortEvent                                : Disabled
**     Contents    :
**         Init            - LDD_TDeviceData* GPIO1_Init(LDD_TUserData *UserDataPtr);
**         SetFieldValue   - void GPIO1_SetFieldValue(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField...
**         GetFieldValue   - GPIO1_TFieldValue GPIO1_GetFieldValue(LDD_TDeviceData *DeviceDataPtr,...
**         ClearFieldBits  - void GPIO1_ClearFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField...
**         SetFieldBits    - void GPIO1_SetFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField...
**         ToggleFieldBits - void GPIO1_ToggleFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField...
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
** @file GPIO1.c
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
**  @addtogroup GPIO1_module GPIO1 module documentation
**  @{
*/         

/* MODULE GPIO1. */

#include "GPIO1.h"
/* {Default RTOS Adapter} No RTOS includes */
#include "IO_Map.h"

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct {
  LDD_TUserData *UserData;             /* RTOS device data structure */
} GPIO1_TDeviceData, *GPIO1_TDeviceDataPtr; /* Device data structure type */
/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static GPIO1_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
/*
** ===================================================================
**     Method      :  GPIO1_Init (component GPIO_LDD)
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
LDD_TDeviceData* GPIO1_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate LDD device structure */
  GPIO1_TDeviceData *DeviceDataPrv;

  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  /* Save RTOS Device structure */
  DeviceDataPrv->UserData = UserDataPtr; /* Store the RTOS device structure */
  /* GPIOA_PDOR: PDO&=~0xE0042000 */
  GPIOA_PDOR &= (uint32_t)~(uint32_t)(GPIO_PDOR_PDO(0xE0042000));
  /* GPIOA_PIDR: PID&=~2 */
  GPIOA_PIDR &= (uint32_t)~(uint32_t)(GPIO_PIDR_PID(0x02));
  /* GPIOA_PDDR: PDD&=~2,PDD|=0xE0042000 */
  GPIOA_PDDR = (uint32_t)((GPIOA_PDDR & (uint32_t)~(uint32_t)(
                GPIO_PDDR_PDD(0x02)
               )) | (uint32_t)(
                GPIO_PDDR_PDD(0xE0042000)
               ));
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_GPIO1_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv);
}

/*
** ===================================================================
**     Method      :  GPIO1_SetFieldValue (component GPIO_LDD)
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
void GPIO1_SetFieldValue(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field, GPIO1_TFieldValue Value)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  switch (Field) {                     /* no break */
    case CCEN: {                       /* bit field #0 */
      GPIO_PDD_SetPortDataOutput(GPIO1_MODULE_BASE_ADDRESS,
        (
          GPIO_PDD_GetPortDataOutput(GPIO1_MODULE_BASE_ADDRESS)
          & ((GPIO1_TPortValue)(~((GPIO1_TPortValue)GPIO1_CCEN_MASK)))
        )
        | (
          ((GPIO1_TPortValue)(Value << GPIO1_CCEN_START_BIT))
          & ((GPIO1_TPortValue)GPIO1_CCEN_MASK)
        )
      );
      break;
    }
    case CHI: {                        /* bit field #1 */
      GPIO_PDD_SetPortDataOutput(GPIO1_MODULE_BASE_ADDRESS,
        (
          GPIO_PDD_GetPortDataOutput(GPIO1_MODULE_BASE_ADDRESS)
          & ((GPIO1_TPortValue)(~((GPIO1_TPortValue)GPIO1_CHI_MASK)))
        )
        | (
          ((GPIO1_TPortValue)(Value << GPIO1_CHI_START_BIT))
          & ((GPIO1_TPortValue)GPIO1_CHI_MASK)
        )
      );
      break;
    }
    case CLO: {                        /* bit field #2 */
      GPIO_PDD_SetPortDataOutput(GPIO1_MODULE_BASE_ADDRESS,
        (
          GPIO_PDD_GetPortDataOutput(GPIO1_MODULE_BASE_ADDRESS)
          & ((GPIO1_TPortValue)(~((GPIO1_TPortValue)GPIO1_CLO_MASK)))
        )
        | (
          ((GPIO1_TPortValue)(Value << GPIO1_CLO_START_BIT))
          & ((GPIO1_TPortValue)GPIO1_CLO_MASK)
        )
      );
      break;
    }
    case BLO: {                        /* bit field #3 */
      GPIO_PDD_SetPortDataOutput(GPIO1_MODULE_BASE_ADDRESS,
        (
          GPIO_PDD_GetPortDataOutput(GPIO1_MODULE_BASE_ADDRESS)
          & ((GPIO1_TPortValue)(~((GPIO1_TPortValue)GPIO1_BLO_MASK)))
        )
        | (
          ((GPIO1_TPortValue)(Value << GPIO1_BLO_START_BIT))
          & ((GPIO1_TPortValue)GPIO1_BLO_MASK)
        )
      );
      break;
    }
    case BHI: {                        /* bit field #4 */
      GPIO_PDD_SetPortDataOutput(GPIO1_MODULE_BASE_ADDRESS,
        (
          GPIO_PDD_GetPortDataOutput(GPIO1_MODULE_BASE_ADDRESS)
          & ((GPIO1_TPortValue)(~((GPIO1_TPortValue)GPIO1_BHI_MASK)))
        )
        | (
          ((GPIO1_TPortValue)(Value << GPIO1_BHI_START_BIT))
          & ((GPIO1_TPortValue)GPIO1_BHI_MASK)
        )
      );
      break;
    }
    case uHome: {                      /* bit field #5 */
      GPIO_PDD_SetPortDataOutput(GPIO1_MODULE_BASE_ADDRESS,
        (
          GPIO_PDD_GetPortDataOutput(GPIO1_MODULE_BASE_ADDRESS)
          & ((GPIO1_TPortValue)(~((GPIO1_TPortValue)GPIO1_uHome_MASK)))
        )
        | (
          ((GPIO1_TPortValue)(Value << GPIO1_uHome_START_BIT))
          & ((GPIO1_TPortValue)GPIO1_uHome_MASK)
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
**     Method      :  GPIO1_GetFieldValue (component GPIO_LDD)
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
GPIO1_TFieldValue GPIO1_GetFieldValue(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  switch (Field) {                     /* no break */
    case CCEN: {                       /* bit field #0 */
      return
        (GPIO1_TFieldValue)(
          (
            GPIO_PDD_GetPortDataInput(GPIO1_MODULE_BASE_ADDRESS)
            & (GPIO1_TPortValue)GPIO1_CCEN_MASK
          )
          >> GPIO1_CCEN_START_BIT
        );
    }
    case CHI: {                        /* bit field #1 */
      return
        (GPIO1_TFieldValue)(
          (
            GPIO_PDD_GetPortDataInput(GPIO1_MODULE_BASE_ADDRESS)
            & (GPIO1_TPortValue)GPIO1_CHI_MASK
          )
          >> GPIO1_CHI_START_BIT
        );
    }
    case CLO: {                        /* bit field #2 */
      return
        (GPIO1_TFieldValue)(
          (
            GPIO_PDD_GetPortDataInput(GPIO1_MODULE_BASE_ADDRESS)
            & (GPIO1_TPortValue)GPIO1_CLO_MASK
          )
          >> GPIO1_CLO_START_BIT
        );
    }
    case BLO: {                        /* bit field #3 */
      return
        (GPIO1_TFieldValue)(
          (
            GPIO_PDD_GetPortDataInput(GPIO1_MODULE_BASE_ADDRESS)
            & (GPIO1_TPortValue)GPIO1_BLO_MASK
          )
          >> GPIO1_BLO_START_BIT
        );
    }
    case BHI: {                        /* bit field #4 */
      return
        (GPIO1_TFieldValue)(
          (
            GPIO_PDD_GetPortDataInput(GPIO1_MODULE_BASE_ADDRESS)
            & (GPIO1_TPortValue)GPIO1_BHI_MASK
          )
          >> GPIO1_BHI_START_BIT
        );
    }
    case uHome: {                      /* bit field #5 */
      return
        (GPIO1_TFieldValue)(
          (
            GPIO_PDD_GetPortDataInput(GPIO1_MODULE_BASE_ADDRESS)
            & (GPIO1_TPortValue)GPIO1_uHome_MASK
          )
          >> GPIO1_uHome_START_BIT
        );
    }
    default:
      break;                           /* Invalid BitField is not treated, result is undefined */
  } /* switch (Field) */
  return (GPIO1_TFieldValue)0U;
}

/*
** ===================================================================
**     Method      :  GPIO1_ClearFieldBits (component GPIO_LDD)
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
void GPIO1_ClearFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field, GPIO1_TFieldValue Mask)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  switch (Field) {                     /* no break */
    case CCEN: {                       /* bit field #0 */
      GPIO_PDD_ClearPortDataOutputMask(GPIO1_MODULE_BASE_ADDRESS,
        ((GPIO1_TPortValue)GPIO1_CCEN_MASK)
        & ((GPIO1_TPortValue)(Mask << GPIO1_CCEN_START_BIT))
      );
      break;
    }
    case CHI: {                        /* bit field #1 */
      GPIO_PDD_ClearPortDataOutputMask(GPIO1_MODULE_BASE_ADDRESS,
        ((GPIO1_TPortValue)GPIO1_CHI_MASK)
        & ((GPIO1_TPortValue)(Mask << GPIO1_CHI_START_BIT))
      );
      break;
    }
    case CLO: {                        /* bit field #2 */
      GPIO_PDD_ClearPortDataOutputMask(GPIO1_MODULE_BASE_ADDRESS,
        ((GPIO1_TPortValue)GPIO1_CLO_MASK)
        & ((GPIO1_TPortValue)(Mask << GPIO1_CLO_START_BIT))
      );
      break;
    }
    case BLO: {                        /* bit field #3 */
      GPIO_PDD_ClearPortDataOutputMask(GPIO1_MODULE_BASE_ADDRESS,
        ((GPIO1_TPortValue)GPIO1_BLO_MASK)
        & ((GPIO1_TPortValue)(Mask << GPIO1_BLO_START_BIT))
      );
      break;
    }
    case BHI: {                        /* bit field #4 */
      GPIO_PDD_ClearPortDataOutputMask(GPIO1_MODULE_BASE_ADDRESS,
        ((GPIO1_TPortValue)GPIO1_BHI_MASK)
        & ((GPIO1_TPortValue)(Mask << GPIO1_BHI_START_BIT))
      );
      break;
    }
    case uHome: {                      /* bit field #5 */
      GPIO_PDD_ClearPortDataOutputMask(GPIO1_MODULE_BASE_ADDRESS,
        ((GPIO1_TPortValue)GPIO1_uHome_MASK)
        & ((GPIO1_TPortValue)(Mask << GPIO1_uHome_START_BIT))
      );
      break;
    }
    default:
      break;                           /* Invalid Field is not treated, result is undefined */
  } /* switch (Field) */
}

/*
** ===================================================================
**     Method      :  GPIO1_SetFieldBits (component GPIO_LDD)
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
void GPIO1_SetFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field, GPIO1_TFieldValue Mask)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  switch (Field) {                     /* no break */
    case CCEN: {                       /* bit field #0 */
      GPIO_PDD_SetPortDataOutputMask(GPIO1_MODULE_BASE_ADDRESS,
        ((GPIO1_TPortValue)GPIO1_CCEN_MASK)
        & ((GPIO1_TPortValue)(Mask << GPIO1_CCEN_START_BIT))
      );
      break;
    }
    case CHI: {                        /* bit field #1 */
      GPIO_PDD_SetPortDataOutputMask(GPIO1_MODULE_BASE_ADDRESS,
        ((GPIO1_TPortValue)GPIO1_CHI_MASK)
        & ((GPIO1_TPortValue)(Mask << GPIO1_CHI_START_BIT))
      );
      break;
    }
    case CLO: {                        /* bit field #2 */
      GPIO_PDD_SetPortDataOutputMask(GPIO1_MODULE_BASE_ADDRESS,
        ((GPIO1_TPortValue)GPIO1_CLO_MASK)
        & ((GPIO1_TPortValue)(Mask << GPIO1_CLO_START_BIT))
      );
      break;
    }
    case BLO: {                        /* bit field #3 */
      GPIO_PDD_SetPortDataOutputMask(GPIO1_MODULE_BASE_ADDRESS,
        ((GPIO1_TPortValue)GPIO1_BLO_MASK)
        & ((GPIO1_TPortValue)(Mask << GPIO1_BLO_START_BIT))
      );
      break;
    }
    case BHI: {                        /* bit field #4 */
      GPIO_PDD_SetPortDataOutputMask(GPIO1_MODULE_BASE_ADDRESS,
        ((GPIO1_TPortValue)GPIO1_BHI_MASK)
        & ((GPIO1_TPortValue)(Mask << GPIO1_BHI_START_BIT))
      );
      break;
    }
    case uHome: {                      /* bit field #5 */
      GPIO_PDD_SetPortDataOutputMask(GPIO1_MODULE_BASE_ADDRESS,
        ((GPIO1_TPortValue)GPIO1_uHome_MASK)
        & ((GPIO1_TPortValue)(Mask << GPIO1_uHome_START_BIT))
      );
      break;
    }
    default:
      break;                           /* Invalid Field is not treated, result is undefined */
  } /* switch (Field) */
}

/*
** ===================================================================
**     Method      :  GPIO1_ToggleFieldBits (component GPIO_LDD)
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
void GPIO1_ToggleFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field, GPIO1_TFieldValue Mask)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  switch (Field) {                     /* no break */
    case CCEN: {                       /* bit field #0 */
      GPIO_PDD_TogglePortDataOutputMask(GPIO1_MODULE_BASE_ADDRESS,
        ((GPIO1_TPortValue)GPIO1_CCEN_MASK)
        & ((GPIO1_TPortValue)(Mask << GPIO1_CCEN_START_BIT))
      );
      break;
    }
    case CHI: {                        /* bit field #1 */
      GPIO_PDD_TogglePortDataOutputMask(GPIO1_MODULE_BASE_ADDRESS,
        ((GPIO1_TPortValue)GPIO1_CHI_MASK)
        & ((GPIO1_TPortValue)(Mask << GPIO1_CHI_START_BIT))
      );
      break;
    }
    case CLO: {                        /* bit field #2 */
      GPIO_PDD_TogglePortDataOutputMask(GPIO1_MODULE_BASE_ADDRESS,
        ((GPIO1_TPortValue)GPIO1_CLO_MASK)
        & ((GPIO1_TPortValue)(Mask << GPIO1_CLO_START_BIT))
      );
      break;
    }
    case BLO: {                        /* bit field #3 */
      GPIO_PDD_TogglePortDataOutputMask(GPIO1_MODULE_BASE_ADDRESS,
        ((GPIO1_TPortValue)GPIO1_BLO_MASK)
        & ((GPIO1_TPortValue)(Mask << GPIO1_BLO_START_BIT))
      );
      break;
    }
    case BHI: {                        /* bit field #4 */
      GPIO_PDD_TogglePortDataOutputMask(GPIO1_MODULE_BASE_ADDRESS,
        ((GPIO1_TPortValue)GPIO1_BHI_MASK)
        & ((GPIO1_TPortValue)(Mask << GPIO1_BHI_START_BIT))
      );
      break;
    }
    case uHome: {                      /* bit field #5 */
      GPIO_PDD_TogglePortDataOutputMask(GPIO1_MODULE_BASE_ADDRESS,
        ((GPIO1_TPortValue)GPIO1_uHome_MASK)
        & ((GPIO1_TPortValue)(Mask << GPIO1_uHome_START_BIT))
      );
      break;
    }
    default:
      break;                           /* Invalid Field is not treated, result is undefined */
  } /* switch (Field) */
}

/* END GPIO1. */

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
