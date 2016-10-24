/*!
**  statemachine.h
**  version 1.1
*/         

#ifndef _STATE_MACHINE_
#define _STATE_MACHINE_

#include "globalvars.h"

#if (LOAD_TYPE == LOAD_385FAN)
#define MAXSpeed            2800          //以最大转速为2800转考虑
#define NormalMAXSpeed      2500          //385正常模式

#elif (LOAD_TYPE ==  LOAD_305FAN)
#define MAXSpeed            3700          //以最大转速为3300转考虑
#define NormalMAXSpeed      3250          //305正常模式

#elif (LOAD_TYPE == LOAD_PUMP)
#define MAXSpeed            6000          //以最大转速为6000转考虑
#define NormalMAXSpeed      4900          //水泵正常模式

#endif


#if (LOAD_TYPE == LOAD_385FAN)
#define START_PERIOD_I			      (uint16)65535//43.6905ms
#define START_PERIOD_II			      (uint16)53249
#define START_PERIOD_III		      (uint16)35384
#define START_PERIOD_IV			      (uint16)28349
#define START_PERIOD_V			      (uint16)25249
#define START_PERIOD_VI			      (uint16)23849
#define START_PERIOD_VII		      (uint16)23248

#elif (LOAD_TYPE ==  LOAD_305FAN)
#define START_PERIOD_I			(uint16)39749 //65535 //43.6905ms
#define START_PERIOD_II			(uint16)30749 
#define START_PERIOD_III		(uint16)25649 
#define START_PERIOD_IV			(uint16)18149 
#define START_PERIOD_V			(uint16)14279 
#define START_PERIOD_VI			(uint16)13919 
#define START_PERIOD_VII		(uint16)13097 

#elif (LOAD_TYPE == LOAD_PUMP)
#define START_PERIOD_I			(uint16)39749 //65535 //43.6905ms
#define START_PERIOD_II			(uint16)30749 
#define START_PERIOD_III		(uint16)25649 
#define START_PERIOD_IV			(uint16)18149 
#define START_PERIOD_V			(uint16)14279 
#define START_PERIOD_VI			(uint16)13919 
#define START_PERIOD_VII		(uint16)13097 

#endif



#define ALIGNMENT_I_TIME               25//60  *50ms
#define ALIGNMENT_II_TIME              15//80  *50ms
#define ALIGNMENT_III_TIME             10//20  *50ms

//降低启动电流，防止启动K93电机时保险丝断
#define ALIGNMENT_I_VOLTAGE             4260//6550//4260//对其电压1
#define ALIGNMENT_II_VOLTAGE            4915//7210//4915//对其电压2
#define ALIGNMENT_III_VOLTAGE           6550//8910//6550//20%,对其电压3
#define START_VOLTAGE		            6550//8910//6550//20%,启动电压

#define ALIGNED_VOLTAGE_INCREMENT_I 	((float)ALIGNMENT_I_VOLTAGE/ALIGNMENT_I_TIME)
#define ALIGNED_VOLTAGE_INCREMENT_II 	((float)(ALIGNMENT_II_VOLTAGE  - ALIGNMENT_I_VOLTAGE) /ALIGNMENT_II_TIME)
#define ALIGNED_VOLTAGE_INCREMENT_III 	((float)(ALIGNMENT_III_VOLTAGE - ALIGNMENT_II_VOLTAGE)/ALIGNMENT_III_TIME)

#define ALIGNMENT_STEP_NUMBER           3  	//对其态步数
#define START_CMT_NUMBER                1  	//开环步数
#define STABLE_STEP_NUMBER              240	//稳态,10圈
#define ZC_MONITOR_WAIT_TIME					30	//开环启动1.5s后开始过零失败检测
#define OPENLOOP_START_PERIOD			6000

#define ADVANCE_ANGLE1			  	120//1200 down
#define ADVANCE_ANGLE2			  	90//1200-1500
#define ADVANCE_ANGLE3			  	85//1500-1700
#define ADVANCE_ANGLE4			  	80//1700-2000
#define ADVANCE_ANGLE5			  	50//2000-2300
#define ADVANCE_ANGLE6			  	35//2300-2500
#define ADVANCE_ANGLE7			  	10//2500-2800
#define ADVANCE_ANGLE8			  	5 //2800 up


typedef  enum{
	DRV_NULL = 0, 
	DRV_ERROR,
	DRV_HALT, 
	DRV_ALIGNMENT, 
	DRV_START, 
	DRV_STABLE, 
	DRV_RUN, 
#if (LOAD_TYPE == LOAD_PUMP)
	DRV_NOWATER,  //无水状态必须等待电机进入RUN状态之后,才允许进入
#endif
	DRV_DOWN
}DRV_STATE;

typedef  enum{	
	ev_null = 0, 
	ev_activate, 
	ev_align_finish, 
	ev_start_finish, 
	ev_stable_finish, 
	ev_set_speed, 
#if (LOAD_TYPE == LOAD_PUMP)
	ev_nowater,
	ev_nowater_terminate,
	ev_nowater_finish,
#endif
	ev_down, 
	ev_down_finish,
	ev_error,
	ev_error_finish
}DRV_EVT;

//错误可能同时发生，需定义优先级, 错误码的定义不允许随意更改次序
typedef  enum{	//错误处理的优先级按照定义值的大小依次升高
	error_null = 0, 	 //无错
	error_undercurrent,      //欠电流，包括平均值过流和瞬时值欠电流
	error_overtemperature, //主芯片高温
	error_FFpin,          //预驱动FF2，FF1错误,高于无电流,预驱动高温不考虑，先报一样的错误。
	error_lostzc,        //零点检测不到
	error_undervoltage,  //欠压，直接停机,直到恢复正常
	error_overvoltage,   //过压，直接停机,直到恢复正常
	error_overcurrent    //过流, 包括平均值过流和瞬时值过流
}DRV_ERROR_VAL;  

typedef void (*tStateProcess)(void);

extern DRV_ERROR_VAL gLatestError;

DRV_EVT   getOutsideEvt(DRV_STATE curState); //获取由外部的串口总线命令产生的状态迁移的触发事件，msg[]为通过串口接收到的命令，curState为当前状态
DRV_EVT   getInsideEvt(DRV_STATE curState); //获取由内部的状态处理过程中产生的状态迁移的触发事件，检查内部某个状态是否处理结束产生信号（如alignment处理结束、开始状态的开环控制时间结束），curState为当前状态，规定getInsideEvt()所产生的事件的优先级比getOutsideEvt()的响应优先级高
DRV_STATE stateTransition(DRV_STATE curState, DRV_EVT event, DRV_ERROR_VAL error); //状态迁移处理，event参数是当前状态curState发生状态迁移的触发事件，迁移完成后，返回迁移之后的状态

void stateErrorProcess(void);
void stateVoidProcess(void); 
void stateHaltProcess(void);//HALT状态处理
void stateAlignmentProcess(void);//
void stateStartProcess(void);//
void stateStableProcess(void);//
void stateRunProcess(void);//
void stateNoWaterProcess(void);
void stateDownProcess(void);//

void AppStateMachine(DRV_STATE curState);
#endif
