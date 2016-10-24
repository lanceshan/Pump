#include "globalvars.h"
#include "midfunction.h"
#include "currentbuffer.h"
#include "motor.h"
#include "error.h"
#include "FF1.h"
#include "FF2.h"

#define underCurrent(current, min) ((current < min) ? 1 : 0)
#define overCurrent(current, max) ((current > max) ? 1 : 0)
#define predriverError() (FF2_GetVal() || FF1_GetVal())

#define setErrorVal(v, err) 	\
	do{						\
		if(err > v) v = err;	\
	}while(0)
		

void clearMotorState(void)
{	
	gMotorPara.targetSpeed=0;
	gMotorPara.curSpeed=0;
	gMotorPara.enable = 0;
	
	gClosedLoop = 0;
	gZCDetectEnable = 0;
	gMotorPhase = 0;
	gZCLostFlag=0;
	gCommutationWaiting = 0;
}
 
//欠电流-1，过流-2，正常0
int checkCurrent(unsigned int current, unsigned int minCurrent, unsigned int maxCurrent)
{
	//static unsigned char no_current_counter=0;
	//static unsigned char over_current_counter=0;
	if(underCurrent(current, minCurrent))
	{
		return -1;
	}

	if(overCurrent(current, maxCurrent))
	{
		return -2;
	}

	return 0;
}

void rdPredriverError(void)
{
	int i;
	
	if(FF2_GetVal()||FF1_GetVal())
	{
		if(!FF2_GetVal()) //FF2 0; FF1 1
		{
			//高温
			//reset_pre_driver();
		}
		else
		{
			FF2_SetOutput();
			delay(2);
			for(i=1;i<=10;i++)
			{
				FF2_ClrVal();
				delay(4);
				FF2_SetVal();	
				if(FF1_GetVal())
				{
					;//gFaultValue|=(uint16)((uint16)1<<i);
				}
				delay(4);
			}
			FF2_SetInput();
			delay(4);
			//reset_pre_driver();
		}
	}
	
}

DRV_ERROR_VAL checkGeneralError()
{
	DRV_ERROR_VAL retError = error_null;
	
	if(checkVoltage()==1)
	{
		setErrorVal(retError, error_undervoltage);
	}

	if(checkVoltage()==2)
	{
		setErrorVal(retError, error_overvoltage);
	}

	if(gClosedLoop && gZCLostFlag)
	{
		setErrorVal(retError, error_lostzc);
	}

	return retError;
	
}

DRV_ERROR_VAL errorCheck(DRV_STATE curState)
{
	int flag=0;
	DRV_ERROR_VAL err, retError = error_null;
	int i, aveCurrent = 0;
	//static int errContinuous = 0;
	//static DRV_ERROR_VAL lastErr = error_null;
	static DRV_ERROR_VAL errArr[5] = {error_null};
	static int errIndex = 0;

	retError = checkGeneralError();
	
	switch(curState)
	{
	case DRV_NULL:
	case DRV_HALT:
	case DRV_ALIGNMENT:
		break;
	case DRV_START:
		flag = checkCurrent(gCurrent, MIN_INST_CURRENT, MAX_INST_CURRENT); 
		if(flag == -2) setErrorVal(retError, error_overcurrent);
		//else if(flag == -1) setErrorVal(retError, error_undercurrent);
		
		break;
	case DRV_STABLE:
		flag = checkCurrent(gCurrent, MIN_INST_CURRENT, MAX_INST_CURRENT); 
		if(flag == -2) setErrorVal(retError, error_overcurrent);
		//else if(flag == -1) setErrorVal(retError, error_undercurrent);
		
		if(predriverError() && (retError < error_FFpin))
		{
			rdPredriverError();
			setErrorVal(retError, error_FFpin);
		}
		
		break;
	case DRV_RUN:
	case DRV_NOWATER:
		aveCurrent = currBuff_Average(&gCurrentBuffer);
		if(aveCurrent != -1) gAveCurrent = aveCurrent;
		flag = checkCurrent(gAveCurrent, MIN_AVE_CURRENT, MAX_AVE_CURRENT); 
		if(flag == -2) setErrorVal(retError, error_overcurrent);
		else if(flag == -1) setErrorVal(retError, error_undercurrent);

		flag = checkCurrent(gCurrent, MIN_INST_CURRENT, MAX_INST_CURRENT); 
		if(flag == -2) setErrorVal(retError, error_overcurrent);
		else if(flag == -1) setErrorVal(retError, error_undercurrent);

		if(predriverError() && (retError < error_FFpin))
		{
			rdPredriverError();
			setErrorVal(retError, error_FFpin);
		}
		
		break;
	case DRV_DOWN:
		aveCurrent = currBuff_Average(&gCurrentBuffer);
		if(aveCurrent != -1) gAveCurrent = aveCurrent;
		flag = checkCurrent(gAveCurrent, MIN_AVE_CURRENT, MAX_AVE_CURRENT); 
		if(flag == -2) setErrorVal(retError, error_overcurrent);
		//else if(flag == -1) setErrorVal(retError, error_undercurrent);

		flag = checkCurrent(gCurrent, MIN_INST_CURRENT, MAX_INST_CURRENT); 
		if(flag == -2) setErrorVal(retError, error_overcurrent);
		//else if(flag == -1) setErrorVal(retError, error_undercurrent);

		if(predriverError() && (retError < error_FFpin))
		{
			rdPredriverError();
			setErrorVal(retError, error_FFpin);
		}
		
		break;
	case DRV_ERROR:
		break;
	default:
		break;
	}

	errArr[errIndex++] = retError;
	if(errIndex >= 5) errIndex = 0;

	err = error_null;
	for(i = 0;i < 5;i++)  //如果最近的5个连续的错误都不是空错误，从中选出优先级最高的错误，保证错误至少连续检测到5次，避免错误检测过于敏感
	{
		if(errArr[i] == error_null)
		{
			err = error_null;
			break;
		}
		else
		{
			if(err < errArr[i]) err = errArr[i];
		}
	}
	
	//以下代码切记不可以打开，否则可能导致水泵驱动中发生状态的错误切换（无水干转-->运行）
	//if(err != error_null)
	//{
	//	for(i = 0;i < 5;i++)
	//		errArr[i] = error_null;
	//}

	retError = err;
	
	return retError;
}

DRV_ERROR_VAL errorFilter(DRV_STATE curState, DRV_ERROR_VAL error)
{
	DRV_ERROR_VAL retError = error;

	switch(curState)
	{
	case DRV_NULL:
		retError = error_null;
		break;
	case DRV_HALT:
		if((error != error_overvoltage)&&(error != error_undervoltage))
		{
			retError = error_null;
		}
		break;
	case DRV_ALIGNMENT:
		if((error != error_overvoltage)&&(error != error_undervoltage)&(error != error_FFpin))
		{
			retError = error_null;
		}
		break;
	case DRV_START:
		if((error != error_overvoltage)&&(error != error_undervoltage)&&(error != error_FFpin))
		{
			retError = error_null;
		}
		break;
	case DRV_STABLE:
	case DRV_RUN:
	case DRV_DOWN:
	case DRV_NOWATER:
		if((error != error_overvoltage)&&(error != error_undervoltage)&&(error != error_FFpin)&&
			(error != error_lostzc)&&(error != error_overcurrent))
		{
			retError = error_null;
		}
		break;
#if 0
	case DRV_NOWATER:
		if((error != error_overvoltage)&&(error != error_undervoltage)&&(error != error_FFpin)&&
			(error != error_lostzc)&&(error != error_overcurrent)&&(error != error_undercurrent))
		{
			retError = error_null;
		}
		break;
#endif
	case DRV_ERROR:
		break;
	}
	
	return retError;
}

DRV_STATE errorHandle(DRV_STATE curState, DRV_ERROR_VAL error)
{
	DRV_STATE nextState =curState ;

	if(error == error_null) return nextState;

	switch(curState)
	{
	case DRV_NULL:
		break;
	case DRV_HALT:
		if((error == error_overvoltage)||(error == error_undervoltage))
		{
			motor_disable();
			clearMotorState();
			
			gErrorPeriodCnt = 0;
			nextState = DRV_ERROR;
		}
		break;
	case DRV_ALIGNMENT:
		if((error == error_overvoltage)||(error == error_undervoltage)||(error == error_FFpin))
		{
			motor_disable();
			clearMotorState();
			
			//motor_brake();
			gErrorPeriodCnt = ERROR_STATE_PERIOD;
			nextState = DRV_ERROR;
		}
		break;
	case DRV_START:
		if((error == error_overvoltage)||(error == error_undervoltage)||(error == error_FFpin))
		{
			motor_disable();
			clearMotorState();

			//motor_brake();
			gErrorPeriodCnt = ERROR_STATE_PERIOD;
			nextState = DRV_ERROR;
		}
		break;
	case DRV_STABLE:
	case DRV_RUN:
	case DRV_NOWATER:
	case DRV_DOWN:
		if((error == error_overvoltage)||(error == error_undervoltage)||(error == error_FFpin)||
			(error == error_lostzc)||(error == error_overcurrent))
		{
			motor_disable();
			clearMotorState();

			//motor_brake();
			gErrorPeriodCnt = ERROR_STATE_PERIOD;
			if(error == error_overcurrent) gErrorPeriodCnt = ERROR_OVERCURRENT_PERIOD;
			
			nextState = DRV_ERROR;
		}
		break;
	case DRV_ERROR:
		break;
	}
	
	return nextState;
}



