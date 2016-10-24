/* ###################################################################
**     Filename    : Events.c
**     Project     : kea_bldc_pe
**     Processor   : SKEAZ128MLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-10-09, 10:45, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMI - void Cpu_OnNMI(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "Init_Config.h"
#include "PDD_Includes.h"
#include "user/globalvars.h"
#include "user/midfunction.h"
#include "user/motor.h"
#include "hardware/timer.h"
#include "hardware/HWmacro.h"
//#include "hardware/uart.h"
#include "hardware/uart0_master.h"
#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */
#include "user/motor.h"
#include "user/statemachine.h"
#include "user/globalvars.h"


static unsigned int   timer1CntFor50ms = 50000/T1_INT_PERIOD_ACTUAL;       // 50ms
static unsigned short cmtDischargeCnt = COMMUTATION_DISCHARGE_CNT;  

/*
** ===================================================================
**     Event       :  TU2_OnCounterRestart (module Events)
**
**     Component   :  TU2 [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void TU2_OnCounterRestart(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	timer2_disable();
	if(gCommutationWaiting == 1)
	{		
		gMotorPhase++;
		if(gMotorPhase >= 24) gMotorPhase = 0;
		
		//if(gClosedLoop == 1) motor_setDischarge(gMotorPhase,gMotorPara.direction);
		//else motor_setPhase(gMotorPhase,gMotorPara.direction);
		motor_setPhase(gMotorPhase,gMotorPara.direction);
	    	
//		if(gCurSpeed>2700)
//			CmtDischargeCnt = 2;	//放电时间始终设置为200us，实测低转速没问题
//		else
			cmtDischargeCnt = COMMUTATION_DISCHARGE_CNT;

//		gZCDetectEnable = 1;
		
		if(gStateStableStep > 0) gStateStableStep--;
		
		gCommutationWaiting = 0;
	}

}

/*
** ===================================================================
**     Event       :  PWM1_OnEnd (module Events)
**
**     Component   :  PWM1 [PWM_LDD]
*/
/*!
**     @brief
**         This event is called when the specified number of cycles has
**         been generated. Component and OnEnd event must be enabled.
**         See [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt service/event] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/

void PWM1_OnEnd(void)
{
  /* Write your code here ... */
	//static unsigned int ForZcdetectTime=0; 
  	static unsigned int zcLostCnt = 0; 
  
	//unsigned char curr_phase = gMotorPhase%6;
	uint32 periodNextCommutation = 0;
	
	gTime = gTime + T3_FTM_MOD_SET;	
		
	if((cmtDischargeCnt == 0) && (gZCDetectEnable == 1) && (gCommutationWaiting == 0))
	{		
		if(gClosedLoop && (0 == gZCMonitorWait)) zcLostCnt++;  //已经进入闭环状态,且避开了刚开始的极低速时间
		
		if(1 == zeroCrossDetect(gMotorPhase%6))
		{   
			gZCLostFlag=0;
			zcLostCnt = 0;
			
			gZCDetectTime = gTime + FTM2_CNT;
			gZCDetectPeriod[gMotorPhase] = gZCDetectTime - gLastZCDetectTime;
			gLastZCDetectTime = gZCDetectTime;
			
			if(gClosedLoop)
			{
				gCommutationWaiting = 1;
//				periodNextCommutation=(uint32)((double)gZCDetectPeriod[gMotorPhase]*T1TICK_TO_T2TICK_COEFF*gMotorPara.advanceAngle/256) ;
				periodNextCommutation=(((uint32)gZCDetectPeriod[gMotorPhase]*gMotorPara.advanceAngle)>>12);
				start_timer2_for_closedloop(periodNextCommutation);
			}

		}

		if(zcLostCnt > 400)  // 400*62.5us = 25ms, 对应100rpm的转速
		{
			gZCLostFlag = 1;
			zcLostCnt = 0;
		}
		
	}

	if(gMotorPara.enable) mcuMeasure();
	
	if(!gClosedLoop)  zcLostCnt = 0;

}



/*
** ===================================================================
**     Event       :  Timer1_OnInterrupt (module Events)
**
**     Component   :  Timer1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Timer1_OnInterrupt(void)
{
  /* Write your code here ... */
	motor_setDutyCycle(gMotorPara.dutyCycle);

  	// if pwm is disabled, then measure mcu here
  	if(!gMotorPara.enable) mcuMeasure();
	
	if(timer1CntFor50ms > 0) timer1CntFor50ms--;
	if(timer1CntFor50ms == 0) //次级定时器50ms到
	{	
		timer1CntFor50ms = 50000/T1_INT_PERIOD_ACTUAL;
		
		if(gAlignmentTimerCnt > 0) gAlignmentTimerCnt--;
		if(gSpeedUpdateCnt > 0) gSpeedUpdateCnt--;
		if(gDutyCycleUpdateCnt > 0) gDutyCycleUpdateCnt--;
		if(gErrorPeriodCnt > 0) gErrorPeriodCnt--;
		if(gZCMonitorWait > 0) gZCMonitorWait--;
		
#if (LOAD_TYPE == LOAD_PUMP)
		if(gNoWaterPeriodCnt > 0) gNoWaterPeriodCnt--;
		if(gLEDUpateCnt > 0) gLEDUpateCnt--;
#endif

	}
	
	if(cmtDischargeCnt > 0) 
	{
		cmtDischargeCnt--;
		if(cmtDischargeCnt == 0)
		{
			//if(gClosedLoop == 1) motor_setPhase(gMotorPhase, gMotorPara.direction);
		}
	}	
}

/*
** ===================================================================
**     Event       :  AS1_OnBlockReceived (module Events)
**
**     Component   :  AS1 [Serial_LDD]
*/
/*!
**     @brief
**         This event is called when the requested number of data is
**         moved to the input buffer.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void AS1_OnBlockReceived(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	//uart1RxInInterrupt();
}

/*
** ===================================================================
**     Event       :  AS1_OnBlockSent (module Events)
**
**     Component   :  AS1 [Serial_LDD]
*/
/*!
**     @brief
**         This event is called after the last character from the
**         output buffer is moved to the transmitter. 
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void AS1_OnBlockSent(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  IFsh1_OnWritePageEnd (module Events)
**
**     Component   :  IFsh1 [IntFLASH]
*/
/*!
**     @brief
**         Event is called after entire virtual page is written to
**         FLASH (see [SetPage]). This event is available only if
**         [Virtual page] property is selected and an [Interrupt
**         service/event] is selected.
*/
/* ===================================================================*/
void IFsh1_OnWritePageEnd(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  IFsh1_OnWriteEnd (module Events)
**
**     Component   :  IFsh1 [IntFLASH]
*/
/*!
**     @brief
**         Event is called after a write operation to FLASH memory is
**         finished (except [SetPage]). This event is available only if
**         an [Interrupt service/event] is selected.
*/
/* ===================================================================*/
void IFsh1_OnWriteEnd(void)
{
  /* Write your code here ... */
}

/* END Events */

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
