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

/*定时相关*/
extern unsigned int       gAlignmentTimerCnt;  //DRV_ALIGNMENT状态下的对齐时间计数（基于T1的基本定时）

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

/*通信相关*/
#define SCI_RX_MAX  7
#define SCI_TX_MAX  12
extern unsigned char gSCIRxBuf[SCI_RX_MAX];  //串口接收数据缓冲区
extern unsigned char gSCITxBuf[SCI_TX_MAX];  //串口发送数据缓冲区

extern unsigned char gRxHead, gRxTail;       //串口接收的环形缓冲区的首尾指针

/*电机控制相关*/
extern unsigned char  gMotorPhase;            //电机的换向相位，取值0~5
extern unsigned int     gLastZCTime;             //上一次的检测到过零电压的时刻，以T1内部的定时器的当时的Counter计数值为时刻值
extern unsigned int     gZCDetectPeriod[24];      //每次检测到过零时刻，与上一个过零时刻之间的时间间隔，以T1内部的定时器的计数间隔值为时间间隔单位

extern unsigned char 	gStateStableStep;
extern unsigned int  	gZCMonitorWait;
extern unsigned int  	gVoltage;
extern unsigned int  	gCurrent;
extern unsigned int  	gAveCurrent;

extern unsigned int  	gMCUTemper;
//extern signed   char gInsideTemperature;
void globalParameter_init(void);
#endif
