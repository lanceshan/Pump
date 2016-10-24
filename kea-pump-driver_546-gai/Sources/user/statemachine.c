#include "globalvars.h"
#include "error.h"
#include "statemachine.h"
#include "midfunction.h"
#include "commprotocol.h"
#include "motor.h"
#include "currentbuffer.h"
#include "hardware/led.h"
#include "hardware/timer.h"
#include "hardware/HWmacro.h"


static unsigned char stateAlignStep = ALIGNMENT_STEP_NUMBER;       //对齐状态中的已经完成的对齐阶段，0-未开始，取值为0、1、2、3
static unsigned char stateStartStep = START_CMT_NUMBER;            //开始状态中的已经完成的开环控制的阶段，0-未开始，取值为0、1、2、3
static DRV_ERROR_VAL ledError = error_null; 

static const tStateProcess StateProcessArr[] = {
	stateVoidProcess, 
	stateErrorProcess, 
	stateHaltProcess, 
	stateAlignmentProcess, 
	stateStartProcess, 
	stateStableProcess, 
	stateRunProcess, 
	stateNoWaterProcess, 
	stateDownProcess
};

void stateErrorProcess()
{	
	return;
}


/*************************************************************
*函数名    ：void stateVoidProcess()
*参数        ：NULL
*返回值    ：NULL
*全局变量：NULL
*作用       ：
*修改       ：NULL
*备注       ：NULL
*作者       ：吴益伟
*日期       ：2014/10/16
*************************************************************/
void stateVoidProcess()
{  
	motor_disable();
	clearMotorState();
	
	return;
}

/*************************************************************
*函数名    ：void stateHaltProcess()
*参数        ：NULL
*返回值    ：NULL
*全局变量：NULL
*作用       ：
*修改       ：NULL
*备注       ：NULL
*作者       ：吴益伟
*日期       ：2014/10/16
*************************************************************/
void stateHaltProcess()//HALT状态处理
{  
	return;//等待外部指令
}
/*************************************************************
*函数名    ：void stateAlignmentProcess() 
*参数        ：NULL
*返回值    ：NULL
*全局变量：gAlignmentTimerCnt应放在Timer中递减，stateAlignStep对其步数计数，用作判断3步对其有没有结束
*作用       ：
*修改       ：NULL
*备注       ：NULL
*作者       ：吴益伟
*日期       ：2014/10/16
*************************************************************/
void stateAlignmentProcess()
{
	if(gAlignmentTimerCnt == 0)
	{
		switch (stateAlignStep)
		 {
			 case 3://对其阶段1
				gAlignmentTimerCnt = ALIGNMENT_I_TIME;
				 break;
			 case 2://对其阶段2
				gAlignmentTimerCnt = ALIGNMENT_II_TIME;
				 break;
			 case 1://对其阶段3
				gAlignmentTimerCnt = ALIGNMENT_III_TIME;
				 break;
			 default:
				 break;
		 }
	   	if(stateAlignStep > 0)  stateAlignStep--;
	}
	else
	{   
		switch (stateAlignStep)
		 {
			 case 2:
				 gMotorPara.dutyCycle = (unsigned int)(ALIGNED_VOLTAGE_INCREMENT_I*(ALIGNMENT_I_TIME-gAlignmentTimerCnt)) ;
				 break;
			 case 1:
				 gMotorPara.dutyCycle = ALIGNMENT_I_VOLTAGE+(unsigned int)(ALIGNED_VOLTAGE_INCREMENT_II*(ALIGNMENT_II_TIME-gAlignmentTimerCnt)) ;
				 break;
			 case 0:
				 gMotorPara.dutyCycle = ALIGNMENT_II_VOLTAGE+(unsigned int)(ALIGNED_VOLTAGE_INCREMENT_III*(ALIGNMENT_III_TIME-gAlignmentTimerCnt));
				 break;
			 default:
				 break;
		 }
		
	}
}

/*************************************************************
*函数名    ：void stateStartProcess() 
*参数        ：NULL
*返回值    ：NULL
*全局变量：gStartTimerCnt赋给Timer的比较寄存器，gStartStepCnt开环步数，在宏定义中可初始开环步数，也用作判断开环操作是否结束
*作用       ：
*修改       ：NULL
*备注       ：NULL
*作者       ：吴益伟
*日期       ：2014/10/16
*************************************************************/
void stateStartProcess()
{
	if(gCommutationWaiting == 0)
   	{ 
   		if(stateStartStep > 0)
	   	{
	   	
			switch ((START_CMT_NUMBER - stateStartStep))
			{
				case 0: 
					gCommutationWaiting = 1;

					gLastZCDetectTime = gZCDetectTime;
					//gZCDetectTime = gTime+ ((unsigned int)(START_PERIOD_I * T2TICK_TO_T1TICK_COEFF)>>1);
					gZCDetectTime = gTime+ ((unsigned int)(OPENLOOP_START_PERIOD * T2TICK_TO_T1TICK_COEFF)>>1);
					gZCDetectPeriod[gMotorPhase] = gZCDetectTime-gLastZCDetectTime;
					
					//start_timer2_for_openloop(START_PERIOD_I);//第一步 
					
					start_timer2_for_openloop(OPENLOOP_START_PERIOD);  //之前的6步起动改成1步
					
					break;
				case 1:
					gCommutationWaiting = 1;
					
					gLastZCDetectTime=gZCDetectTime;
					gZCDetectTime = gTime+ ((unsigned int)(START_PERIOD_II * T2TICK_TO_T1TICK_COEFF)>>1);
					gZCDetectPeriod[gMotorPhase] = gZCDetectTime-gLastZCDetectTime;
					
					start_timer2_for_openloop(START_PERIOD_II);//第二步 
					break;
				case 2:
					gCommutationWaiting = 1;
					
					gLastZCDetectTime=gZCDetectTime;
					gZCDetectTime = gTime+ ((unsigned int)(START_PERIOD_III * T2TICK_TO_T1TICK_COEFF)>>1);
					gZCDetectPeriod[gMotorPhase] =gZCDetectTime-gLastZCDetectTime;
					
					start_timer2_for_openloop(START_PERIOD_III);//第三步 1
					break;
				case 3:
					gCommutationWaiting = 1;
					
					gLastZCDetectTime=gZCDetectTime;
					gZCDetectTime = gTime+ ((unsigned int)(START_PERIOD_IV * T2TICK_TO_T1TICK_COEFF)>>1);
					gZCDetectPeriod[gMotorPhase] =gZCDetectTime-gLastZCDetectTime;
					
					start_timer2_for_openloop(START_PERIOD_IV);
					break;
				case 4:
					gCommutationWaiting = 1;
					
					gLastZCDetectTime=gZCDetectTime;
					gZCDetectTime = gTime+ ((unsigned int)(START_PERIOD_V * T2TICK_TO_T1TICK_COEFF)>>1);
					gZCDetectPeriod[gMotorPhase] =gZCDetectTime-gLastZCDetectTime;
					
					start_timer2_for_openloop(START_PERIOD_V);
					break;
				case 5:
					gCommutationWaiting = 1;
					
					gLastZCDetectTime=gZCDetectTime;
					gZCDetectTime = gTime+ ((unsigned int)(START_PERIOD_VI * T2TICK_TO_T1TICK_COEFF)>>1);
					gZCDetectPeriod[gMotorPhase] =gZCDetectTime-gLastZCDetectTime;
					
					start_timer2_for_openloop(START_PERIOD_VI);
					break;
				case 6:
					gCommutationWaiting = 1;
					
					gLastZCDetectTime=gZCDetectTime;
					gZCDetectTime = gTime+ ((unsigned int)(START_PERIOD_VII * T2TICK_TO_T1TICK_COEFF)>>1);
					gZCDetectPeriod[gMotorPhase] =gZCDetectTime-gLastZCDetectTime;
					
					start_timer2_for_openloop(START_PERIOD_VII);
					break;
				default:
					break;
		   	} 

   			//start_timer2_for_openloop(OPENLOOP_START_PERIOD);
   			//gCommutationWaiting = 1;
			
			stateStartStep--;
		}
	}
}
/*************************************************************
*函数名    ：void stateStableProcess() 
*参数        ：NULL
*返回值    ：NULL
*全局变量：NULL
*作用       ：
*修改       ：NULL
*备注       ：NULL
*作者       ：吴益伟
*日期       ：2014/10/16
*************************************************************/
void stateStableProcess()
{
	if(gStateStableStep == 0) return;
	if(gSpeedUpdateCnt == 0)
	{
		gSpeedUpdateCnt = 1;
		gMotorPara.curSpeed = getCurSpeed();
		
		//实现提前角连续变化,避免速度跳变
		if(gMotorPara.curSpeed > 3000)		
			gMotorPara.advanceAngle = 5;
		else if(gMotorPara.curSpeed > 2500)
			gMotorPara.advanceAngle = 35 - gMotorPara.curSpeed/100;
		else if(gMotorPara.curSpeed > 1800)
			gMotorPara.advanceAngle = 260 - gMotorPara.curSpeed/10;
		else if(gMotorPara.curSpeed > 1000)
			gMotorPara.advanceAngle = 170 - gMotorPara.curSpeed/20;
		else
			gMotorPara.advanceAngle = 120;		
	}
}
/*************************************************************
*函数名    ：void stateRunProcess() 
*参数        ：NULL
*返回值    ：NULL
*全局变量：NULL
*作用       ：
*修改       ：NULL
*备注       ：NULL
*作者       ：吴益伟
*日期       ：2014/10/16
*************************************************************/
void stateRunProcess()
{
	unsigned int dutyCycle = 0;
	
	if(gSpeedUpdateCnt == 0) 
	{
		gSpeedUpdateCnt = 1; //当前转速值的更新时间间隔1*50ms
		gMotorPara.curSpeed = getCurSpeed();
		
		//实现提前角连续变化,避免速度跳变
		if(gMotorPara.curSpeed > 3000)		
			gMotorPara.advanceAngle = 5;
		else if(gMotorPara.curSpeed > 2500)
			gMotorPara.advanceAngle = 35 - gMotorPara.curSpeed/100;
		else if(gMotorPara.curSpeed > 1800)
			gMotorPara.advanceAngle = 260 - gMotorPara.curSpeed/10;
		else if(gMotorPara.curSpeed > 1000)
			gMotorPara.advanceAngle = 170 - gMotorPara.curSpeed/20;
		else
			gMotorPara.advanceAngle = 120;
		
/*		//以下为老版本程序，提前角为阶梯式变化，此法会在跳变点处引起速度不稳
		if(gCurSpeed > 2800)
			gMotorPara.advanceAngle = ADVANCE_ANGLE8;
		else if(gCurSpeed > 2500) //HIGH_SPEED6
			gMotorPara.advanceAngle = ADVANCE_ANGLE7;
		else if(gCurSpeed > 2300) //HIGH_SPEED5
			gMotorPara.advanceAngle = ADVANCE_ANGLE6;
		else if(gCurSpeed > 2000) //HIGH_SPEED4
			gMotorPara.advanceAngle = ADVANCE_ANGLE5;
		else if(gCurSpeed > 1700) //HIGH_SPEED3
			gMotorPara.advanceAngle = ADVANCE_ANGLE4;
		else if(gCurSpeed > 1500) //HIGH_SPEED2
			gMotorPara.advanceAngle = ADVANCE_ANGLE3;
		else if(gCurSpeed > 1200) //HIGH_SPEED1
			gMotorPara.advanceAngle = ADVANCE_ANGLE2;
		else
			gMotorPara.advanceAngle = ADVANCE_ANGLE1;
*/
	}
	if(gDutyCycleUpdateCnt == 0)
	{
		gDutyCycleUpdateCnt = 2; // 占空比调节的时间间隔2*50ms, 不可以小于或者等于转速值更新的时间间隔
		dutyCycle =  modifyDutyCycle(gMotorPara.curSpeed, gMotorPara.targetSpeed, gMotorPara.dutyCycle);
		gMotorPara.dutyCycle = dutyCycle;	
	}
}

void stateNoWaterProcess()
{
	unsigned int dutyCycle = 0;
	
	if(gSpeedUpdateCnt == 0) 
	{
		gSpeedUpdateCnt = 1; //当前转速值的更新时间间隔1*50ms
		gMotorPara.curSpeed = getCurSpeed();
		
		//实现提前角连续变化,避免速度跳变
		if(gMotorPara.curSpeed > 3000)		
			gMotorPara.advanceAngle = 5;
		else if(gMotorPara.curSpeed > 2500)
			gMotorPara.advanceAngle = 35 - gMotorPara.curSpeed/100;
		else if(gMotorPara.curSpeed > 1800)
			gMotorPara.advanceAngle = 260 - gMotorPara.curSpeed/10;
		else if(gMotorPara.curSpeed > 1000)
			gMotorPara.advanceAngle = 170 - gMotorPara.curSpeed/20;
		else
			gMotorPara.advanceAngle = 120;
	}
	if(gDutyCycleUpdateCnt == 0)
	{
		gDutyCycleUpdateCnt = 2; // 占空比调节的时间间隔2*50ms, 不可以小于或者等于转速值更新的时间间隔
		dutyCycle =  modifyDutyCycle(gMotorPara.curSpeed, gMotorPara.targetSpeed, gMotorPara.dutyCycle);
		gMotorPara.dutyCycle = dutyCycle;	
	}	
	
}

/*************************************************************
*函数名    ：void stateDownProcess() 
*参数        ：NULL
*返回值    ：NULL
*全局变量：NULL
*作用       ：
*修改       ：NULL
*备注       ：NULL
*作者       ：吴益伟
*日期       ：2014/10/16
*************************************************************/
void stateDownProcess()
{
	unsigned int dutyCycle = 0;

	gMotorPara.targetSpeed = 100;
	
	if(gSpeedUpdateCnt == 0) 
	{
		gSpeedUpdateCnt = 1; //当前转速值的更新时间间隔1*50ms
		gMotorPara.curSpeed = getCurSpeed();
		
		//实现提前角连续变化,避免速度跳变
		if(gMotorPara.curSpeed > 3000)		
			gMotorPara.advanceAngle = 5;
		else if(gMotorPara.curSpeed > 2500)
			gMotorPara.advanceAngle = 35 - gMotorPara.curSpeed/100;
		else if(gMotorPara.curSpeed > 1800)
			gMotorPara.advanceAngle = 260 - gMotorPara.curSpeed/10;
		else if(gMotorPara.curSpeed > 1000)
			gMotorPara.advanceAngle = 170 - gMotorPara.curSpeed/20;
		else
			gMotorPara.advanceAngle = 120;
	}
	
	if(gDutyCycleUpdateCnt == 0)
	{
		gDutyCycleUpdateCnt = 2; // 占空比调节的时间间隔2*50ms, 不可以小于或者等于转速值更新的时间间隔
		dutyCycle =  modifyDutyCycle(gMotorPara.curSpeed, gMotorPara.targetSpeed, gMotorPara.dutyCycle);
		gMotorPara.dutyCycle = dutyCycle;	
	}
	
}



/*************************************************************
*函数名    ：DRV_EVT getOutsideEvt(char msg[],DRV_STATE curState)  
*参数        ：NULL
*返回值    ：NULL
*全局变量：NULL
*作用       ：
*修改       ：NULL
*备注       ：通信协议见SVN，msg结构修改
*作者       ：吴益伟
*日期       ：2014/10/16
*************************************************************/
DRV_EVT getOutsideEvt(DRV_STATE curState)        //获取由外部的串口总线命令产生的状态迁移的触发事件，msg[]为通过串口接收到的命令，curState为当前状态
{
	DRV_EVT retEvt = ev_null;

	if(gMessageOfControl.new_cmd_flag==1)
	{
		switch (curState)
		{
			case DRV_NULL:
				break;
			case DRV_ERROR:
				break;
			case DRV_HALT:
				if(gMessageOfControl.targetSpeed >= 500)
				{
					gMotorPara.direction=gMessageOfControl.direction;
					retEvt = ev_activate;
				}
				break;
			case DRV_ALIGNMENT:
				break;
			case DRV_START:
				break;
			case DRV_STABLE:
				break;
			case DRV_RUN:
				 if(gMotorPara.direction!=gMessageOfControl.direction)
				 {
					 retEvt = ev_down;
				 }
				 else if(gMessageOfControl.targetSpeed < 500)
				 {
					 retEvt = ev_down; 
				 }
				 else if(gMessageOfControl.targetSpeed >= 500)
				 {
			
					 gMotorPara.targetSpeed= gMessageOfControl.targetSpeed;
					 retEvt = ev_set_speed; 
				 }
				break;
			case DRV_DOWN :
				 if((gMessageOfControl.targetSpeed >= 500) && (gMotorPara.direction == gMessageOfControl.direction))
				 {
					 retEvt = ev_set_speed; 
				 }
				break;
			default:
				break;
		}
		gMessageOfControl.new_cmd_flag=0;
	}
	return retEvt;
}

/*************************************************************
*函数名    ：DRV_EVT getInsideEvt(DRV_STATE curState)
*参数        ：NULL
*返回值    ：NULL
*全局变量：NULL
*作用       ：
*修改       ：NULL
*备注       ：NULL
*作者       ：吴益伟
*日期       ：2014/10/16
*************************************************************/
DRV_EVT getInsideEvt(DRV_STATE curState)                    //获取由内部的状态处理过程中产生的状态迁移的触发事件，检查内部某个状态是否处理结束产生信号（如alignment处理结束、开始状态的开环控制时间结束），curState为当前状态，规定getInsideEvt()所产生的事件的优先级比getOutsideEvt()的响应优先级高
{
	DRV_EVT retEvt = ev_null;
	switch (curState)
	{
		case DRV_ERROR:
			if(gErrorPeriodCnt == 0)
			{
				retEvt = ev_error_finish;
			}
			break;
		case DRV_NULL:
			retEvt = ev_null;
			break;
		case DRV_HALT:
			if(getPumpSpeed() > 500)
				retEvt = ev_activate; //ev_null;
			break;
		case DRV_ALIGNMENT:
			if((stateAlignStep == 0) && (gAlignmentTimerCnt == 0))//对其N步结束
			{		
				retEvt = ev_align_finish;
			}
			break;
		case DRV_START    :
			if((stateStartStep == 0) && (gCommutationWaiting == 0))//N步开环启动结束
			{
				retEvt = ev_start_finish;
			}
			break;
		case DRV_STABLE:
			if(gStateStableStep == 0)//N步稳态结束
			{
				retEvt = ev_stable_finish;
			}
			break;
		case DRV_RUN:
			if((gLatestError == error_undercurrent) && (gMotorPara.curSpeed >  (getPumpSpeed() -400)))
			{
				retEvt = ev_nowater;
			}
			break;
		case DRV_NOWATER:
			if(gNoWaterPeriodCnt == 0)
			{
				retEvt = ev_nowater_finish;
			}
			else
			{
				if((gLatestError == error_undercurrent) && (gMotorPara.curSpeed >  (getPumpSpeed() -400)))
				{
					retEvt = ev_nowater;
				}
				else
				{
					retEvt = ev_nowater_terminate;
				}
			}
			break;
		case DRV_DOWN:
			if(gMotorPara.curSpeed < 1000)//减速到1000rpm以下
			{
				if(gMotorPara.direction!=gMessageOfControl.direction) gMotorPara.direction=gMessageOfControl.direction;
				retEvt = ev_down_finish;
			}
			break;
		default:
			break;
	}
	return retEvt;
}


DRV_STATE stateTransition(DRV_STATE curState, DRV_EVT event, DRV_ERROR_VAL error)//状态迁移处理，event参数是当前状态curState发生状态迁移的触发事件，迁移完成后，返回迁移之后的状态,去除状态参数
{
	unsigned char i = 0;
	DRV_STATE nextState = curState;
	
	switch (curState)
	{
		case DRV_ERROR:
			if(event==ev_error_finish)
			{
				motor_disable();
				clearMotorState();
				nextState = DRV_HALT;
			}
			else if(event == ev_error)
			{//错误状态中，检测到的最新错误不予以处理
				nextState = DRV_ERROR;
			}
			break;
		case DRV_NULL:
			nextState = DRV_NULL;
			break;
		case DRV_HALT:
				if(event==ev_activate)
				{
					gMotorPhase=0;
					gClosedLoop = 0;
					gZCDetectEnable = 0;
					gAlignmentTimerCnt=0;
					while(currBuff_Clear(&gCurrentBuffer) == -1);
					gCurrent=0;
					gAveCurrent = 0;
					stateAlignStep   = ALIGNMENT_STEP_NUMBER;
					
					motor_setAlign();		
					motor_enable();
					gMotorPara.enable = 1;
					gTime = 0; 

					nextState = DRV_ALIGNMENT;
					
				}
				else if(event == ev_error)
				{
					nextState = errorHandle(curState, error);
				}
			break;
		case DRV_ALIGNMENT:
				if(event==ev_align_finish)
				{		
					gZCDetectEnable = 1;
					
					for(i = 0;i < 24;i++)
						gZCDetectPeriod[i] = 65535;
					
//					gCommutationWaiting = 0;
					stateStartStep      =START_CMT_NUMBER;

					gZCDetectTime = 0;
				    	gLastZCDetectTime= 0;

					gCommutationWaiting = 1;
					gMotorPhase = 3;  //注意中断触发后才会真正切到下一相(gMotorPhase+1)
					start_timer2_for_openloop(1);  //马上触发中断使导通相位切到下一相
					
				    	//gMotorPhase = 4;	//B相启动
				    	//motor_setPhase(gMotorPhase,gMotorPara.direction);  //对其后第一推动力

					nextState = DRV_START;
				}
				else if(event == ev_error)
				{
					nextState = errorHandle(curState, error);
				}
			break;
		case DRV_START    :
				if(event==ev_start_finish)
				{
					gMotorPara.advanceAngle = ADVANCE_ANGLE1;  //temp
					
					//gLastZCDetectTime= 0;
					gZCMonitorWait = ZC_MONITOR_WAIT_TIME;
					gClosedLoop = 1;
					gStateStableStep = STABLE_STEP_NUMBER; 
					
					nextState = DRV_STABLE;
				}
				else if(event == ev_error)
				{
					nextState = errorHandle(curState, error);
				}
			break;
		case DRV_STABLE:
				if(event==ev_stable_finish)
				{
					gMotorPara.advanceAngle = ADVANCE_ANGLE1; 
					
#if (LOAD_TYPE == LOAD_PUMP)
					gMotorPara.targetSpeed = getPumpSpeed();
#else
					gMotorPara.targetSpeed = 500;    
#endif
					
					nextState = DRV_RUN;
				}
				else if(event == ev_error)
				{
					nextState = errorHandle(curState, error);
				}
			break;
		case DRV_RUN:
				if(event==ev_down)
				{
					//gMotorPara.targetSpeed = 250;//目标速度降低
					nextState = DRV_DOWN;
				}
				else if(event==ev_set_speed)
				{
					nextState = DRV_RUN;
				}
				else if(event == ev_nowater)
				{
					gNoWaterPeriodCnt = 30*60*1000/50;  // 30min
					nextState = DRV_NOWATER;
				}
				else if(event == ev_error)
				{
					nextState = errorHandle(curState, error);
				}
			break;
		case DRV_NOWATER:
			if(event == ev_nowater)
			{
				nextState = DRV_NOWATER;
			}else if(event == ev_nowater_terminate)
			{
				nextState = DRV_RUN;
			}else if(event == ev_nowater_finish)
			{
				nextState = DRV_DOWN;
				gNoWaterPeriodCnt = -1;
			}else if(event == ev_error)
			{
				nextState = errorHandle(curState, error);
			}
			break;
		case DRV_DOWN:
				if(event==ev_down_finish)
				{
					motor_disable();
					clearMotorState();
					//gMotorPara.enable = 0;
					nextState = DRV_HALT;
					if(gNoWaterPeriodCnt == -1) nextState = DRV_NULL;
				}
				else if(event==ev_set_speed)
				{
					nextState = DRV_RUN;
				}
				else if(event == ev_error)
				{
					nextState = errorHandle(curState, error);
				}
			break;
		default:
			break;
	}

	if(curState != DRV_ERROR)//因状态机处于DRV_ERROR时,所有新错误不处理,因此需要加入不等于DRV_ERROR的判断
	{
		if(event == ev_error) ledError = error;
		else ledError = error_null;
	}
	
	return nextState;
}


void AppStateMachine(DRV_STATE curState)
{
	DRV_ERROR_VAL ledErr = error_null;
	
	StateProcessArr[curState]();

	if(0 == gLEDUpateCnt)
	{
		switch(curState)
		{
		case DRV_NULL:
			ledErr = -1;
			break;
		case DRV_ERROR:
			ledErr = ledError;
			break;
		case DRV_HALT:
		case DRV_ALIGNMENT:
		case DRV_START:
		case DRV_STABLE:
		case DRV_RUN:
		case DRV_DOWN:
			//ledErr = error_null;
			ledErr = ledError;
			break;
		case DRV_NOWATER:
			ledErr = error_undercurrent;
			break;
		default:
			ledErr = -1;
			break;
		}
		
		gLEDUpateCnt = 10; // 10*50ms = 500ms
		led_updateDisplay(ledErr);
		
	}
	
}
