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


static unsigned char stateAlignStep = ALIGNMENT_STEP_NUMBER;       //����״̬�е��Ѿ���ɵĶ���׶Σ�0-δ��ʼ��ȡֵΪ0��1��2��3
static unsigned char stateStartStep = START_CMT_NUMBER;            //��ʼ״̬�е��Ѿ���ɵĿ������ƵĽ׶Σ�0-δ��ʼ��ȡֵΪ0��1��2��3
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
*������    ��void stateVoidProcess()
*����        ��NULL
*����ֵ    ��NULL
*ȫ�ֱ�����NULL
*����       ��
*�޸�       ��NULL
*��ע       ��NULL
*����       ������ΰ
*����       ��2014/10/16
*************************************************************/
void stateVoidProcess()
{  
	motor_disable();
	clearMotorState();
	
	return;
}

/*************************************************************
*������    ��void stateHaltProcess()
*����        ��NULL
*����ֵ    ��NULL
*ȫ�ֱ�����NULL
*����       ��
*�޸�       ��NULL
*��ע       ��NULL
*����       ������ΰ
*����       ��2014/10/16
*************************************************************/
void stateHaltProcess()//HALT״̬����
{  
	return;//�ȴ��ⲿָ��
}
/*************************************************************
*������    ��void stateAlignmentProcess() 
*����        ��NULL
*����ֵ    ��NULL
*ȫ�ֱ�����gAlignmentTimerCntӦ����Timer�еݼ���stateAlignStep���䲽�������������ж�3��������û�н���
*����       ��
*�޸�       ��NULL
*��ע       ��NULL
*����       ������ΰ
*����       ��2014/10/16
*************************************************************/
void stateAlignmentProcess()
{
	if(gAlignmentTimerCnt == 0)
	{
		switch (stateAlignStep)
		 {
			 case 3://����׶�1
				gAlignmentTimerCnt = ALIGNMENT_I_TIME;
				 break;
			 case 2://����׶�2
				gAlignmentTimerCnt = ALIGNMENT_II_TIME;
				 break;
			 case 1://����׶�3
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
*������    ��void stateStartProcess() 
*����        ��NULL
*����ֵ    ��NULL
*ȫ�ֱ�����gStartTimerCnt����Timer�ıȽϼĴ�����gStartStepCnt�����������ں궨���пɳ�ʼ����������Ҳ�����жϿ��������Ƿ����
*����       ��
*�޸�       ��NULL
*��ע       ��NULL
*����       ������ΰ
*����       ��2014/10/16
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
					
					//start_timer2_for_openloop(START_PERIOD_I);//��һ�� 
					
					start_timer2_for_openloop(OPENLOOP_START_PERIOD);  //֮ǰ��6���𶯸ĳ�1��
					
					break;
				case 1:
					gCommutationWaiting = 1;
					
					gLastZCDetectTime=gZCDetectTime;
					gZCDetectTime = gTime+ ((unsigned int)(START_PERIOD_II * T2TICK_TO_T1TICK_COEFF)>>1);
					gZCDetectPeriod[gMotorPhase] = gZCDetectTime-gLastZCDetectTime;
					
					start_timer2_for_openloop(START_PERIOD_II);//�ڶ��� 
					break;
				case 2:
					gCommutationWaiting = 1;
					
					gLastZCDetectTime=gZCDetectTime;
					gZCDetectTime = gTime+ ((unsigned int)(START_PERIOD_III * T2TICK_TO_T1TICK_COEFF)>>1);
					gZCDetectPeriod[gMotorPhase] =gZCDetectTime-gLastZCDetectTime;
					
					start_timer2_for_openloop(START_PERIOD_III);//������ 1
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
*������    ��void stateStableProcess() 
*����        ��NULL
*����ֵ    ��NULL
*ȫ�ֱ�����NULL
*����       ��
*�޸�       ��NULL
*��ע       ��NULL
*����       ������ΰ
*����       ��2014/10/16
*************************************************************/
void stateStableProcess()
{
	if(gStateStableStep == 0) return;
	if(gSpeedUpdateCnt == 0)
	{
		gSpeedUpdateCnt = 1;
		gMotorPara.curSpeed = getCurSpeed();
		
		//ʵ����ǰ�������仯,�����ٶ�����
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
*������    ��void stateRunProcess() 
*����        ��NULL
*����ֵ    ��NULL
*ȫ�ֱ�����NULL
*����       ��
*�޸�       ��NULL
*��ע       ��NULL
*����       ������ΰ
*����       ��2014/10/16
*************************************************************/
void stateRunProcess()
{
	unsigned int dutyCycle = 0;
	
	if(gSpeedUpdateCnt == 0) 
	{
		gSpeedUpdateCnt = 1; //��ǰת��ֵ�ĸ���ʱ����1*50ms
		gMotorPara.curSpeed = getCurSpeed();
		
		//ʵ����ǰ�������仯,�����ٶ�����
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
		
/*		//����Ϊ�ϰ汾������ǰ��Ϊ����ʽ�仯���˷���������㴦�����ٶȲ���
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
		gDutyCycleUpdateCnt = 2; // ռ�ձȵ��ڵ�ʱ����2*50ms, ������С�ڻ��ߵ���ת��ֵ���µ�ʱ����
		dutyCycle =  modifyDutyCycle(gMotorPara.curSpeed, gMotorPara.targetSpeed, gMotorPara.dutyCycle);
		gMotorPara.dutyCycle = dutyCycle;	
	}
}

void stateNoWaterProcess()
{
	unsigned int dutyCycle = 0;
	
	if(gSpeedUpdateCnt == 0) 
	{
		gSpeedUpdateCnt = 1; //��ǰת��ֵ�ĸ���ʱ����1*50ms
		gMotorPara.curSpeed = getCurSpeed();
		
		//ʵ����ǰ�������仯,�����ٶ�����
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
		gDutyCycleUpdateCnt = 2; // ռ�ձȵ��ڵ�ʱ����2*50ms, ������С�ڻ��ߵ���ת��ֵ���µ�ʱ����
		dutyCycle =  modifyDutyCycle(gMotorPara.curSpeed, gMotorPara.targetSpeed, gMotorPara.dutyCycle);
		gMotorPara.dutyCycle = dutyCycle;	
	}	
	
}

/*************************************************************
*������    ��void stateDownProcess() 
*����        ��NULL
*����ֵ    ��NULL
*ȫ�ֱ�����NULL
*����       ��
*�޸�       ��NULL
*��ע       ��NULL
*����       ������ΰ
*����       ��2014/10/16
*************************************************************/
void stateDownProcess()
{
	unsigned int dutyCycle = 0;

	gMotorPara.targetSpeed = 100;
	
	if(gSpeedUpdateCnt == 0) 
	{
		gSpeedUpdateCnt = 1; //��ǰת��ֵ�ĸ���ʱ����1*50ms
		gMotorPara.curSpeed = getCurSpeed();
		
		//ʵ����ǰ�������仯,�����ٶ�����
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
		gDutyCycleUpdateCnt = 2; // ռ�ձȵ��ڵ�ʱ����2*50ms, ������С�ڻ��ߵ���ת��ֵ���µ�ʱ����
		dutyCycle =  modifyDutyCycle(gMotorPara.curSpeed, gMotorPara.targetSpeed, gMotorPara.dutyCycle);
		gMotorPara.dutyCycle = dutyCycle;	
	}
	
}



/*************************************************************
*������    ��DRV_EVT getOutsideEvt(char msg[],DRV_STATE curState)  
*����        ��NULL
*����ֵ    ��NULL
*ȫ�ֱ�����NULL
*����       ��
*�޸�       ��NULL
*��ע       ��ͨ��Э���SVN��msg�ṹ�޸�
*����       ������ΰ
*����       ��2014/10/16
*************************************************************/
DRV_EVT getOutsideEvt(DRV_STATE curState)        //��ȡ���ⲿ�Ĵ����������������״̬Ǩ�ƵĴ����¼���msg[]Ϊͨ�����ڽ��յ������curStateΪ��ǰ״̬
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
*������    ��DRV_EVT getInsideEvt(DRV_STATE curState)
*����        ��NULL
*����ֵ    ��NULL
*ȫ�ֱ�����NULL
*����       ��
*�޸�       ��NULL
*��ע       ��NULL
*����       ������ΰ
*����       ��2014/10/16
*************************************************************/
DRV_EVT getInsideEvt(DRV_STATE curState)                    //��ȡ���ڲ���״̬��������в�����״̬Ǩ�ƵĴ����¼�������ڲ�ĳ��״̬�Ƿ�����������źţ���alignment�����������ʼ״̬�Ŀ�������ʱ���������curStateΪ��ǰ״̬���涨getInsideEvt()���������¼������ȼ���getOutsideEvt()����Ӧ���ȼ���
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
			if((stateAlignStep == 0) && (gAlignmentTimerCnt == 0))//����N������
			{		
				retEvt = ev_align_finish;
			}
			break;
		case DRV_START    :
			if((stateStartStep == 0) && (gCommutationWaiting == 0))//N��������������
			{
				retEvt = ev_start_finish;
			}
			break;
		case DRV_STABLE:
			if(gStateStableStep == 0)//N����̬����
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
			if(gMotorPara.curSpeed < 1000)//���ٵ�1000rpm����
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


DRV_STATE stateTransition(DRV_STATE curState, DRV_EVT event, DRV_ERROR_VAL error)//״̬Ǩ�ƴ���event�����ǵ�ǰ״̬curState����״̬Ǩ�ƵĴ����¼���Ǩ����ɺ󣬷���Ǩ��֮���״̬,ȥ��״̬����
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
			{//����״̬�У���⵽�����´������Դ���
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
					gMotorPhase = 3;  //ע���жϴ�����Ż������е���һ��(gMotorPhase+1)
					start_timer2_for_openloop(1);  //���ϴ����ж�ʹ��ͨ��λ�е���һ��
					
				    	//gMotorPhase = 4;	//B������
				    	//motor_setPhase(gMotorPhase,gMotorPara.direction);  //������һ�ƶ���

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
					//gMotorPara.targetSpeed = 250;//Ŀ���ٶȽ���
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

	if(curState != DRV_ERROR)//��״̬������DRV_ERRORʱ,�����´��󲻴���,�����Ҫ���벻����DRV_ERROR���ж�
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
