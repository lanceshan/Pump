/* ###################################################################
**     Filename    : main.c
**     Project     : net-drive-kea
**     Processor   : SKEAZ128MLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-12-19, 11:06, # CodeGen: 5
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "GPIO1.h"
#include "GPIO2.h"
#include "GPIO3.h"
#include "Timer1.h"
#include "TimerIntLdd1.h"
#include "PWM1.h"
#include "PwmLdd1.h"
#include "dbgPort1.h"
#include "FF2.h"
#include "BitIoLdd2.h"
#include "FF1.h"
#include "BitIoLdd4.h"
#include "IIC.h"
#include "IntI2cLdd1.h"
#include "IFsh1.h"
#include "IntFlashLdd1.h"
#include "BitIoLdd3.h"
#include "TU1.h"
#include "TU2.h"
#include "TU3.h"
#include "AS1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "hardware/HWinit.h"
#include "user/error.h"
#include "user/statemachine.h"
#include "user/globalvars.h"
#include "user/commprotocol.h"
//#include "hardware/uart.h"
#include "hardware/uart0_master.h"
#include "hardware/timer.h"
#include "hardware/eeprom.h"
#include "user/motor.h"  
#include "user/midfunction.h"  
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */

//#define ENGINEER_DEBUG 

const unsigned char Version_Buf[6] = {'P','U','M','C','1','0'};

int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  static DRV_STATE curState=DRV_NULL;
  static DRV_EVT   event=ev_null;
  static unsigned char errCount = 0;  //连续发生5次起动错误则不再尝试起动
  DRV_ERROR_VAL error=error_null;
  
  uint8 uartdataTransmit[10]; // only for test UART
  
  gStatusData = (tSlaveMCUStatus *) (&gSCITxBuf[0]);
  //*************************************************
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
  SaveVers(Version_Buf);
  sys_init();
  /* Write your code here */
  //20150603增加约500ms延时，上电延时以避开电源启动尖峰脉冲****************
  unsigned int i = 0,j = 0;
  for(i = 0;i < 1000; i++)
  {
	  for(j = 0;j < 2000; j++)
		  ;
  }
  
  	uartdataTransmit[0] = 'e';
  	uartdataTransmit[1] = 'n';
  	uartdataTransmit[2] = 't';
  	uartdataTransmit[3] = 'e';
  	uartdataTransmit[4] = 'r';
  	uartdataTransmit[5] = 'd';
  	uartdataTransmit[6] = 'r';
  	uartdataTransmit[7] = 'v';
  	uartdataTransmit[8] = ' ';
  	uartdataTransmit[9] = '\0';
  	uart0_master_wr(uartdataTransmit, 10);
  	
  	curState=DRV_HALT;
	while(1)
	{
#ifdef ENGINEER_DEBUG
		if(7 == RxMessage(gSCIRxBuf))
		{
			gStatusData->head0 = 'Y';
			gStatusData->head1 = 'L';
			gStatusData->state = curState;
			//gStatusData->flags.flagByte = 0x00;  //
			gStatusData->currentValueHi = (unsigned char) ((gAveCurrent>> 8) & 0x00ff);       
			gStatusData->currentValueLo = (unsigned char) (gAveCurrent & 0x00ff);
			gStatusData->speedValueHi   = (unsigned char) ((gMotorPara.curSpeed>> 8) & 0x00ff);
			gStatusData->speedValueLo   = (unsigned char) (gMotorPara.curSpeed & 0x00ff);
			gStatusData->dutyCycleHi    = (unsigned char) ((gMotorPara.dutyCycle >> 8) & 0x00ff); 
			gStatusData->dutyCycleLo    = (unsigned char) (gMotorPara.dutyCycle & 0x00ff); 
			gStatusData->mcuTenperature = convTemperature(gMCUTemper);
			gStatusData->crcData        = genCRC8(gSCITxBuf, (sizeof(tSlaveMCUStatus) - 1)); 
			TxMessage(gSCITxBuf, sizeof(tSlaveMCUStatus));
		}
#endif
		
		error = errorCheck(curState);
		gLatestError = error;
		
		error = errorFilter(curState, error);		
		if((error_null == error) || (error == error_undercurrent))
		{
			event = getInsideEvt(curState);
			
#ifdef ENGINEER_DEBUG
			if(ev_null == event) event = getOutsideEvt(curState);
#endif

			if(curState > DRV_STABLE) errCount = 0;  
		}
		else
		{
			event = ev_error;
			if((curState > DRV_ERROR) && (error != error_overvoltage) && (error != error_undervoltage) 
				&& (error != error_undercurrent) )   //对于过压,欠压,欠流错误,要求能在电压和电流恢复正常后,能够重新起动起来
				errCount++;	
		}
		
		curState = stateTransition(curState, event, error);
		if(errCount >= 5) curState = DRV_NULL;
		
		AppStateMachine(curState);
	}
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
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
