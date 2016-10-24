/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : TU2.h
**     Project     : kea-pump
**     Processor   : SKEAZ128MLK4
**     Component   : TimerUnit_LDD
**     Version     : Component 01.164, Driver 01.11, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-07-17, 11:32, # CodeGen: 3
**     Abstract    :
**          This TimerUnit component provides a low level API for unified hardware access across
**          various timer devices using the Prescaler-Counter-Compare-Capture timer structure.
**     Settings    :
**          Component name                                 : TU2
**          Module name                                    : FTM1
**          Counter                                        : FTM1_CNT
**          Counter direction                              : Up
**          Counter width                                  : 16 bits
**          Value type                                     : Optimal
**          Input clock source                             : Internal
**            Counter frequency                            : 750 kHz
**          Counter restart                                : On-match
**            Period device                                : FTM1_MOD
**            Period                                       : 88 ms
**            Interrupt                                    : Enabled
**              Interrupt                                  : INT_FTM1
**              Interrupt priority                         : high priority
**              ISR Name                                   : TU2_Interrupt
**          Channel list                                   : 0
**          Initialization                                 : 
**            Enabled in init. code                        : no
**            Auto initialization                          : no
**            Event mask                                   : 
**              OnCounterRestart                           : Enabled
**              OnChannel0                                 : Disabled
**              OnChannel1                                 : Disabled
**              OnChannel2                                 : Disabled
**              OnChannel3                                 : Disabled
**              OnChannel4                                 : Disabled
**              OnChannel5                                 : Disabled
**              OnChannel6                                 : Disabled
**              OnChannel7                                 : Disabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**     Contents    :
**         Init            - LDD_TDeviceData* TU2_Init(LDD_TUserData *UserDataPtr);
**         Enable          - LDD_TError TU2_Enable(LDD_TDeviceData *DeviceDataPtr);
**         Disable         - LDD_TError TU2_Disable(LDD_TDeviceData *DeviceDataPtr);
**         SetPeriodTicks  - LDD_TError TU2_SetPeriodTicks(LDD_TDeviceData *DeviceDataPtr, TU2_TValueType...
**         GetPeriodTicks  - LDD_TError TU2_GetPeriodTicks(LDD_TDeviceData *DeviceDataPtr, TU2_TValueType...
**         ResetCounter    - LDD_TError TU2_ResetCounter(LDD_TDeviceData *DeviceDataPtr);
**         GetCounterValue - TU2_TValueType TU2_GetCounterValue(LDD_TDeviceData *DeviceDataPtr);
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
** @file TU2.h
** @version 01.11
** @brief
**          This TimerUnit component provides a low level API for unified hardware access across
**          various timer devices using the Prescaler-Counter-Compare-Capture timer structure.
*/         
/*!
**  @addtogroup TU2_module TU2 module documentation
**  @{
*/         

#ifndef __TU2_H
#define __TU2_H

/* MODULE TU2. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */

#include "FTM_PDD.h"
#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 


#ifndef __BWUserType_TU2_TValueType
#define __BWUserType_TU2_TValueType
  typedef uint32_t TU2_TValueType ;    /* Type for data parameters of methods */
#endif
#define TU2_CNT_INP_FREQ_U_0 0x000B71B0UL /* Counter input frequency in Hz */
#define TU2_CNT_INP_FREQ_R_0 750000.1875000468F /* Counter input frequency in Hz */
#define TU2_CNT_INP_FREQ_COUNT 0U      /* Count of predefined counter input frequencies */
#define TU2_PERIOD_TICKS   0x00010000UL /* Initialization value of period in 'counter ticks' */
#define TU2_NUMBER_OF_CHANNELS 0x00U   /* Count of predefined channels */
#define TU2_COUNTER_WIDTH  0x10U       /* Counter width in bits  */
#define TU2_COUNTER_DIR    DIR_UP      /* Direction of counting */
/*! Peripheral base address of a device allocated by the component. This constant can be used directly in PDD macros. */
#define TU2_PRPH_BASE_ADDRESS  0x40039000U
  
/* Methods configuration constants - generated for all enabled component's methods */
#define TU2_Init_METHOD_ENABLED        /*!< Init method of the component TU2 is enabled (generated) */
#define TU2_Enable_METHOD_ENABLED      /*!< Enable method of the component TU2 is enabled (generated) */
#define TU2_Disable_METHOD_ENABLED     /*!< Disable method of the component TU2 is enabled (generated) */
#define TU2_SetPeriodTicks_METHOD_ENABLED /*!< SetPeriodTicks method of the component TU2 is enabled (generated) */
#define TU2_GetPeriodTicks_METHOD_ENABLED /*!< GetPeriodTicks method of the component TU2 is enabled (generated) */
#define TU2_ResetCounter_METHOD_ENABLED /*!< ResetCounter method of the component TU2 is enabled (generated) */
#define TU2_GetCounterValue_METHOD_ENABLED /*!< GetCounterValue method of the component TU2 is enabled (generated) */

/* Events configuration constants - generated for all enabled component's events */
#define TU2_OnCounterRestart_EVENT_ENABLED /*!< OnCounterRestart event of the component TU2 is enabled (generated) */



/*
** ===================================================================
**     Method      :  TU2_Init (component TimerUnit_LDD)
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
LDD_TDeviceData* TU2_Init(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  TU2_Enable (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Enables the component - it starts the signal generation.
**         Events may be generated (see SetEventMask). The method is
**         not available if the counter can't be disabled/enabled by HW.
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
LDD_TError TU2_Enable(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  TU2_Disable (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Disables the component - it stops signal generation and
**         events calling. The method is not available if the counter
**         can't be disabled/enabled by HW.
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
LDD_TError TU2_Disable(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  TU2_SetPeriodTicks (component TimerUnit_LDD)
*/
/*!
**     @brief
**         The method sets timer re-initialization period (in timer
**         ticks). This method is available only if the property
**         ["Counter restart"] is switched to 'on-match' value.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Ticks           - Number of counter ticks before counter
**                           re-initialization. Value 0 means maximal
**                           period value the same as "free-running
**                           mode", e.g. counter overflow or underflow
**                           without any explicit re-initialization.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK 
**                           ERR_PARAM_TICKS - Ticks parameter is out of
**                           possible range.
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError TU2_SetPeriodTicks(LDD_TDeviceData *DeviceDataPtr, TU2_TValueType Ticks);

/*
** ===================================================================
**     Method      :  TU2_GetPeriodTicks (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Returns the number of counter ticks before re-initialization.
**         See also method [SetPeriodTicks]. This method is available
**         only if the property ["Counter restart"] is switched to
**         'on-match' value.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         TicksPtr        - Pointer to return value of the
**                           number of counter ticks before
**                           re-initialization
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK 
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError TU2_GetPeriodTicks(LDD_TDeviceData *DeviceDataPtr, TU2_TValueType *TicksPtr);

/*
** ===================================================================
**     Method      :  TU2_ResetCounter (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Resets counter. If counter is counting up then it is set to
**         zero. If counter is counting down then counter is updated to
**         the reload value.
**         The method is not available if HW doesn't allow resetting of
**         the counter.
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
LDD_TError TU2_ResetCounter(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  TU2_GetCounterValue (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Returns the content of counter register. This method can be
**         used both if counter is enabled and if counter is disabled.
**         The method is not available if HW doesn't allow reading of
**         the counter.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Counter value (number of counted ticks).
*/
/* ===================================================================*/
TU2_TValueType TU2_GetCounterValue(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  TU2_Interrupt (component TimerUnit_LDD)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
/* {Default RTOS Adapter} ISR function prototype */
PE_ISR(TU2_Interrupt);

/* END TU2. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif
/* ifndef __TU2_H */
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
