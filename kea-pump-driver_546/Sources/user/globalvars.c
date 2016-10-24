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
/*��ʱ���*/
unsigned int       gAlignmentTimerCnt=0;       //DRV_ALIGNMENT״̬�µĶ���ʱ�����������T1�Ļ�����ʱ��

unsigned long int  gZCDetectTime = 0, gLastZCDetectTime = 0; 
unsigned char      gZCLostFlag=0;
unsigned long int  gTime = 0;

/*ͨ�����*/
unsigned char    gSCIRxBuf[SCI_RX_MAX];    //���ڽ������ݻ�����
unsigned char    gSCITxBuf[SCI_TX_MAX];    //���ڷ������ݻ�����
tSlaveMCUStatus *gStatusData = NULL;
unsigned char    gRxHead, gRxTail;         //���ڽ��յĻ��λ���������βָ��
controlMessage   gMessageOfControl;
/*����������*/
tagMotorParams gMotorPara;            //�������ת����

unsigned char    gMotorPhase;              //����Ļ�����λ��ȡֵ0~23

unsigned int     gLastZCTime;              //��һ�εļ�⵽�����ѹ��ʱ�̣���T1�ڲ��Ķ�ʱ���ĵ�ʱ��Counter����ֵΪʱ��ֵ
unsigned int     gZCDetectPeriod[24];       //ÿ�μ�⵽����ʱ�̣�����һ������ʱ��֮���ʱ��������T1�ڲ��Ķ�ʱ���ļ������ֵΪʱ������λ

unsigned char    gStateStableStep = 0;
unsigned int    gZCMonitorWait = 0;

unsigned int     gSpeedUpdateCnt = 0;
unsigned int     gDutyCycleUpdateCnt = 0;

unsigned char    gClosedLoop = 0;
unsigned char    gZCDetectEnable = 0;
unsigned char    gCommutationWaiting = 0;    //�Ƿ�ȴ����࣬ÿ�λ���֮�󣬱�����������Ϊ0������Ҫ�ĵط���1  

unsigned int     gVoltage = 0;
unsigned int     gCurrent = 0;
unsigned int 	 gAveCurrent = 0;

unsigned int     gMCUTemper = 0;

tagCurrentBuffer gCurrentBuffer;

signed int gNoWaterPeriodCnt = 0;  // ��������ˮ״̬�ĳ���ʱ��,-1��ʾ�Ѿ������һ����ˮ��ת����

unsigned int gErrorPeriodCnt = 0;  // �����ڴ���״̬�ĳ���ʱ��,һ���������״̬,���ڱ�����Ŀ��,����ȴ�һ��ʱ����ʹ��ǰ��Ĵ��������㹻��ʱ�䷢������

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
