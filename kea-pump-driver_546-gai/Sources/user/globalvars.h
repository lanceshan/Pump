/*!
**  globlavals.h
**  version 1.1
*/         

#ifndef _GLOBAL_VALS_
#define _GLOBAL_VALS_

#define Debug_Speed 2000

#define LOAD_NULL 		0
#define LOAD_305FAN 	1
#define LOAD_385FAN 	2
#define LOAD_PUMP		3

#define LOAD_TYPE 		LOAD_PUMP

/*��ʱ���*/
extern unsigned int       gAlignmentTimerCnt;  //DRV_ALIGNMENT״̬�µĶ���ʱ�����������T1�Ļ�����ʱ��

extern unsigned char      gCommutationWaiting;

extern unsigned long int  gZCDetectTime, gLastZCDetectTime;
extern unsigned char      gZCLostFlag;
extern unsigned long int  gTime;
extern unsigned char      gClosedLoop;
extern unsigned char      gZCDetectEnable;
extern unsigned int       gSpeedUpdateCnt ;
extern unsigned int       gDutyCycleUpdateCnt ;

extern signed int gNoWaterPeriodCnt;
extern unsigned int gErrorPeriodCnt;
extern unsigned int gLEDUpateCnt;

/*ͨ�����*/
#define SCI_RX_MAX  7
#define SCI_TX_MAX  12
extern unsigned char gSCIRxBuf[SCI_RX_MAX];  //���ڽ������ݻ�����
extern unsigned char gSCITxBuf[SCI_TX_MAX];  //���ڷ������ݻ�����

extern unsigned char gRxHead, gRxTail;       //���ڽ��յĻ��λ���������βָ��

/*����������*/
extern unsigned char  gMotorPhase;            //����Ļ�����λ��ȡֵ0~5
extern unsigned int     gLastZCTime;             //��һ�εļ�⵽�����ѹ��ʱ�̣���T1�ڲ��Ķ�ʱ���ĵ�ʱ��Counter����ֵΪʱ��ֵ
extern unsigned int     gZCDetectPeriod[24];      //ÿ�μ�⵽����ʱ�̣�����һ������ʱ��֮���ʱ��������T1�ڲ��Ķ�ʱ���ļ������ֵΪʱ������λ

extern unsigned char 	gStateStableStep;
extern unsigned int  	gZCMonitorWait;
extern unsigned int  	gVoltage;
extern unsigned int  	gCurrent;
extern unsigned int  	gAveCurrent;

extern unsigned int  	gMCUTemper;
//extern signed   char gInsideTemperature;
void globalParameter_init(void);
#endif
