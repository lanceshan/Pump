/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : PwmLdd1.h
**     Project     : kea-pump
**     Processor   : SKEAZ128MLK4
**     Component   : PWM_LDD
**     Version     : Component 01.013, Driver 01.03, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-10-19, 14:32, # CodeGen: 13
**     Abstract    :
**          This component implements a pulse-width modulation generator
**          that generates signal with variable duty and fixed cycle.
**          This PWM component provides a high level API for unified
**          hardware access to various timer devices using the TimerUnit
**          component.
**     Settings    :
**          Component name                                 : PwmLdd1
**          Period device                                  : FTM2_MOD
**          Duty device                                    : FTM2_C4V
**          Output pin                                     : PTB4/KBI0_P12/FTM2_CH4/SPI0_MISO/ACMP1_IN2/NMI_b
**          Output pin signal                              : 
**          Counter                                        : FTM2_CNT
**          Interrupt service/event                        : Enabled
**            Interrupt                                    : INT_FTM2
**            Interrupt priority                           : high priority
**            Iterations before action/event               : 1
**          Period                                         : 125 ?s
**          Starting pulse width                           : 62.5 ?s
**          Initial polarity                               : low
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : yes
**            Event mask                                   : 
**              OnEnd                                      : Enabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**          Referenced components                          : 
**            Linked component                             : TU3
**     Contents    :
**         Init       - LDD_TDeviceData* PwmLdd1_Init(LDD_TUserData *UserDataPtr);
**         Enable     - LDD_TError PwmLdd1_Enable(LDD_TDeviceData *DeviceDataPtr);
**         Disable    - LDD_TError PwmLdd1_Disable(LDD_TDeviceData *DeviceDataPtr);
**         SetRatio8  - LDD_TError PwmLdd1_SetRatio8(LDD_TDeviceData *DeviceDataPtr, uint8_t Ratio);
**         SetRatio16 - LDD_TError PwmLdd1_SetRatio16(LDD_TDeviceData *DeviceDataPtr, uint16_t Ratio);
**         SetDutyUS  - LDD_TError PwmLdd1_SetDutyUS(LDD_TDeviceData *DeviceDataPtr, uint16_t Time);
**         SetDutyMS  - LDD_TError PwmLdd1_SetDutyMS(LDD_TDeviceData *DeviceDataPtr, uint16_t Time);
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
** @file PwmLdd1.h
** @version 01.03
** @brief
**          This component implements a pulse-width modulation generator
**          that generates signal with variable duty and fixed cycle.
**          This PWM component provides a high level API for unified
**          hardware access to various timer devices using the TimerUnit
**          component.
*/         
/*!
**  @addtogroup PwmLdd1_module PwmLdd1 module documentation
**  @{
*/         

#ifndef __PwmLdd1_H
#define __PwmLdd1_H

/* MODULE PwmLdd1. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "TU3.h"
#include "FTM_PDD.h"

#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 


#define PwmLdd1_PERIOD_VALUE 0x0BB8UL  /* Initial period value in ticks of the timer. */
#define PwmLdd1_PERIOD_VALUE_0 0x0BB8UL /* Period value in ticks of the timer in clock configuration 0. */

/*! Peripheral base address of a device allocated by the component. This constant can be used directly in PDD macros. */
#define PwmLdd1_PRPH_BASE_ADDRESS  0x4003A000U
  
/*! Device data structure pointer used when auto initialization property is enabled. This constant can be passed as a first parameter to all component's methods. */
#define PwmLdd1_DeviceData  ((LDD_TDeviceData *)PE_LDD_GetDeviceStructure(PE_LDD_COMPONENT_PwmLdd1_ID))

/* Methods configuration constants - generated for all enabled component's methods */
#define PwmLdd1_Init_METHOD_ENABLED    /*!< Init method of the component PwmLdd1 is enabled (generated) */
#define PwmLdd1_Enable_METHOD_ENABLED  /*!< Enable method of the component PwmLdd1 is enabled (generated) */
#define PwmLdd1_Disable_METHOD_ENABLED /*!< Disable method of the component PwmLdd1 is enabled (generated) */
#define PwmLdd1_SetRatio8_METHOD_ENABLED /*!< SetRatio8 method of the component PwmLdd1 is enabled (generated) */
#define PwmLdd1_SetRatio16_METHOD_ENABLED /*!< SetRatio16 method of the component PwmLdd1 is enabled (generated) */
#define PwmLdd1_SetDutyUS_METHOD_ENABLED /*!< SetDutyUS method of the component PwmLdd1 is enabled (generated) */
#define PwmLdd1_SetDutyMS_METHOD_ENABLED /*!< SetDutyMS method of the component PwmLdd1 is enabled (generated) */

/* Events configuration constants - generated for all enabled component's events */
#define PwmLdd1_OnEnd_EVENT_ENABLED    /*!< OnEnd event of the component PwmLdd1 is enabled (generated) */



/*
** ===================================================================
**     Method      :  PwmLdd1_Init (component PWM_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the
**         property ["Enable in init. code"] is set to "yes" value then
**         the device is also enabled (see the description of the
**         [Enable] method). In this case the [Enable] method is not
**         necessary and needn't to be generated. This method can be
**         called only once. Before the second call of Init the [Deinit]
**         must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* PwmLdd1_Init(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  PwmLdd1_Enable (component PWM_LDD)
*/
/*!
**     @brief
**         Enables the component - it starts the signal generation.
**         Events may be generated (see SetEventMask).
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError PwmLdd1_Enable(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  PwmLdd1_Disable (component PWM_LDD)
*/
/*!
**     @brief
**         Disables the component - it stops signal generation and
**         events calling.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError PwmLdd1_Disable(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  PwmLdd1_SetRatio8 (component PWM_LDD)
*/
/*!
**     @brief
**         This method sets a new duty-cycle ratio. Ratio is expressed
**         as an 8-bit unsigned integer number. 0 - FF value is
**         proportional to ratio 0 - 100%. The method is available
**         only if it is not selected list of predefined values in
**         [Starting pulse width] property. 
**         Note: Calculated duty depends on the timer capabilities and
**         on the selected period.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Ratio           - Ratio to set. 0 - 255 value is
**                           proportional to ratio 0 - 100%
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError PwmLdd1_SetRatio8(LDD_TDeviceData *DeviceDataPtr, uint8_t Ratio);

/*
** ===================================================================
**     Method      :  PwmLdd1_SetRatio16 (component PWM_LDD)
*/
/*!
**     @brief
**         This method sets a new duty-cycle ratio. Ratio is expressed
**         as a 16-bit unsigned integer number. 0 - FFFF value is
**         proportional to ratio 0 - 100%. The method is available
**         only if it is not selected list of predefined values in
**         [Starting pulse width] property. 
**         Note: Calculated duty depends on the timer possibilities and
**         on the selected period.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Ratio           - Ratio to set. 0 - 65535 value is
**                           proportional to ratio 0 - 100%
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError PwmLdd1_SetRatio16(LDD_TDeviceData *DeviceDataPtr, uint16_t Ratio);

/*
** ===================================================================
**     Method      :  PwmLdd1_SetDutyUS (component PWM_LDD)
*/
/*!
**     @brief
**         This method sets the new duty value of the output signal.
**         The duty is expressed in microseconds as a 16-bit unsigned
**         integer number. The method is available only if it is not
**         selected list of predefined values in [Starting pulse width]
**         property.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Time            - Duty to set [in microseconds]
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
**                           ERR_MATH - Overflow during evaluation
**                           ERR_PARAM_RANGE - Parameter out of range
*/
/* ===================================================================*/
LDD_TError PwmLdd1_SetDutyUS(LDD_TDeviceData *DeviceDataPtr, uint16_t Time);

/*
** ===================================================================
**     Method      :  PwmLdd1_SetDutyMS (component PWM_LDD)
*/
/*!
**     @brief
**         This method sets the new duty value of the output signal.
**         The duty is expressed in milliseconds as a 16-bit unsigned
**         integer number. The method is available only if it is not
**         selected list of predefined values in [Starting pulse width]
**         property.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Time            - Duty to set [in milliseconds]
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
**                           ERR_MATH - Overflow during evaluation
**                           ERR_PARAM_RANGE - Parameter out of range
*/
/* ===================================================================*/
LDD_TError PwmLdd1_SetDutyMS(LDD_TDeviceData *DeviceDataPtr, uint16_t Time);

/*
** ===================================================================
**     Method      :  PwmLdd1_OnCounterRestart (component PWM_LDD)
**
**     Description :
**         Called if counter overflow/underflow or counter is 
**         reinitialized by modulo or compare register matching. 
**         OnCounterRestart event and Timer unit must be enabled. See <a 
**         href="UntitledMethods.html#SetEventMask">SetEventMask</a> and 
**         <a href="UntitledMethods.html#GetEventMask">GetEventMask</a> 
**         methods.This event is available only if a <a 
**         href="UntitledProperties.html#IntServiceCounter">Interrupt</a> 
**         is enabled. The event services the event of the inherited 
**         component and eventually invokes other events.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void TU3_OnCounterRestart(LDD_TUserData *UserDataPtr);

/* END PwmLdd1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __PwmLdd1_H */
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
