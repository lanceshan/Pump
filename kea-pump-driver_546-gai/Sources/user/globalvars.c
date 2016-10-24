/*
 * globalvars.c
 * version 1.0
 */
#include "globalvars.h"
#include "currentbuffer.h"
#include "commprotocol.h"
#include "statemachine.h"
#include "motor.h"
#include "PE_Types.h"
/*定时相关*/
unsigned int       gAlignmentTimerCnt=0;       //DRV_ALIGNMENT状态下的对齐时间计数（基于T1的基本定时）

unsigned long int  gZCDetectTime = 0, gLastZCDetectTime = 0; 
unsigned char      gZCLostFlag=0;
unsigned long int  gTime = 0;

/*通信相关*/
unsigned char    gSCIRxBuf[SCI_RX_MAX];    //串口接收数据缓冲区
unsigned char    gSCITxBuf[SCI_TX_MAX];    //串口发送数据缓冲区
tSlaveMCUStatus *gStatusData = NULL;
unsigned char    gRxHead, gRxTail;         //串口接收的环形缓冲区的首尾指针
controlMessage   gMessageOfControl;
/*电机控制相关*/
tagMotorParams gMotorPara;            //电机的运转参数

unsigned char    gMotorPhase;              //电机的换向相位，取值0~23

unsigned int     gLastZCTime;              //上一次的检测到过零电压的时刻，以T1内部的定时器的当时的Counter计数值为时刻值
unsigned int     gZCDetectPeriod[24];       //每次检测到过零时刻，与上一个过零时刻之间的时间间隔，以T1内部的定时器的计数间隔值为时间间隔单位

unsigned char    gStateStableStep = 0;
unsigned int    gZCMonitorWait = 0;

unsigned int     gSpeedUpdateCnt = 0;
unsigned int     gDutyCycleUpdateCnt = 0;

unsigned char    gClosedLoop = 0;
unsigned char    gZCDetectEnable = 0;
unsigned char    gCommutationWaiting = 0;    //是否等待换相，每次换相之后，必须马上设置为0，在需要的地方置1  

unsigned int     gVoltage = 0;
unsigned int     gCurrent = 0;
unsigned int 	 gAveCurrent = 0;

unsigned int     gMCUTemper = 0;

tagCurrentBuffer gCurrentBuffer;

signed int gNoWaterPeriodCnt = 0;  // 保留在无水状态的持续时间,-1表示已经完成了一次无水干转过程

unsigned int gErrorPeriodCnt = 0;  // 保留在错误状态的持续时间,一旦进入错误状态,出于保护的目的,必须等待一段时间以使得前面的错误处理有足够的时间发挥作用

unsigned int gLEDUpateCnt = 0;  
DRV_ERROR_VAL gLatestError = error_null;

void globalParameter_init(void)
{
	  gStatusData->flags.flagByte = 0;
	  
	  gMotorPara.direction = 0;
	  gMotorPara.dutyCycle = 0;
	  gMotorPara.enable = 0;
	  gMotorPara.advanceAngle = 0;
	  
	  gMessageOfControl.targetSpeed = 0;
	  gMessageOfControl.direction = 0;
	  
	  gZCDetectTime = 0;
	  gLastZCDetectTime = 0; 
	  gZCLostFlag=0;
	  gTime = 0;
	  gStateStableStep = 0;
	  gZCMonitorWait = 0;
	  gSpeedUpdateCnt = 0;
	  gDutyCycleUpdateCnt = 0;
	  gClosedLoop=0;
	  gZCDetectEnable = 0;
	  gCommutationWaiting = 0;     
	  gVoltage = 0;
	  gCurrent = 0;
	  gAveCurrent = 0;
	  gMCUTemper = 0;

	  currBuff_Clear(&gCurrentBuffer);
	  gNoWaterPeriodCnt = 0;
	  gErrorPeriodCnt = 0;
	  gLEDUpateCnt = 0;
	  gLatestError = error_null;	  
	  
}
