/*!
**  statemachine.h
**  version 1.1
*/         

#ifndef _STATE_MACHINE_
#define _STATE_MACHINE_

#include "globalvars.h"

#if (LOAD_TYPE == LOAD_385FAN)
#define MAXSpeed            2800          //�����ת��Ϊ2800ת����
#define NormalMAXSpeed      2500          //385����ģʽ

#elif (LOAD_TYPE ==  LOAD_305FAN)
#define MAXSpeed            3700          //�����ת��Ϊ3300ת����
#define NormalMAXSpeed      3250          //305����ģʽ

#elif (LOAD_TYPE == LOAD_PUMP)
#define MAXSpeed            6000          //�����ת��Ϊ6000ת����
#define NormalMAXSpeed      4900          //ˮ������ģʽ

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

//����������������ֹ����K93���ʱ����˿��
#define ALIGNMENT_I_VOLTAGE             4260//6550//4260//�����ѹ1
#define ALIGNMENT_II_VOLTAGE            4915//7210//4915//�����ѹ2
#define ALIGNMENT_III_VOLTAGE           6550//8910//6550//20%,�����ѹ3
#define START_VOLTAGE		            6550//8910//6550//20%,������ѹ

#define ALIGNED_VOLTAGE_INCREMENT_I 	((float)ALIGNMENT_I_VOLTAGE/ALIGNMENT_I_TIME)
#define ALIGNED_VOLTAGE_INCREMENT_II 	((float)(ALIGNMENT_II_VOLTAGE  - ALIGNMENT_I_VOLTAGE) /ALIGNMENT_II_TIME)
#define ALIGNED_VOLTAGE_INCREMENT_III 	((float)(ALIGNMENT_III_VOLTAGE - ALIGNMENT_II_VOLTAGE)/ALIGNMENT_III_TIME)

#define ALIGNMENT_STEP_NUMBER           3  	//����̬����
#define START_CMT_NUMBER                1  	//��������
#define STABLE_STEP_NUMBER              240	//��̬,10Ȧ
#define ZC_MONITOR_WAIT_TIME					30	//��������1.5s��ʼ����ʧ�ܼ��
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
	DRV_NOWATER,  //��ˮ״̬����ȴ��������RUN״̬֮��,���������
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

//�������ͬʱ�������趨�����ȼ�, ������Ķ��岻����������Ĵ���
typedef  enum{	//����������ȼ����ն���ֵ�Ĵ�С��������
	error_null = 0, 	 //�޴�
	error_undercurrent,      //Ƿ����������ƽ��ֵ������˲ʱֵǷ����
	error_overtemperature, //��оƬ����
	error_FFpin,          //Ԥ����FF2��FF1����,�����޵���,Ԥ�������²����ǣ��ȱ�һ���Ĵ���
	error_lostzc,        //����ⲻ��
	error_undervoltage,  //Ƿѹ��ֱ��ͣ��,ֱ���ָ�����
	error_overvoltage,   //��ѹ��ֱ��ͣ��,ֱ���ָ�����
	error_overcurrent    //����, ����ƽ��ֵ������˲ʱֵ����
}DRV_ERROR_VAL;  

typedef void (*tStateProcess)(void);

extern DRV_ERROR_VAL gLatestError;

DRV_EVT   getOutsideEvt(DRV_STATE curState); //��ȡ���ⲿ�Ĵ����������������״̬Ǩ�ƵĴ����¼���msg[]Ϊͨ�����ڽ��յ������curStateΪ��ǰ״̬
DRV_EVT   getInsideEvt(DRV_STATE curState); //��ȡ���ڲ���״̬��������в�����״̬Ǩ�ƵĴ����¼�������ڲ�ĳ��״̬�Ƿ�����������źţ���alignment�����������ʼ״̬�Ŀ�������ʱ���������curStateΪ��ǰ״̬���涨getInsideEvt()���������¼������ȼ���getOutsideEvt()����Ӧ���ȼ���
DRV_STATE stateTransition(DRV_STATE curState, DRV_EVT event, DRV_ERROR_VAL error); //״̬Ǩ�ƴ���event�����ǵ�ǰ״̬curState����״̬Ǩ�ƵĴ����¼���Ǩ����ɺ󣬷���Ǩ��֮���״̬

void stateErrorProcess(void);
void stateVoidProcess(void); 
void stateHaltProcess(void);//HALT״̬����
void stateAlignmentProcess(void);//
void stateStartProcess(void);//
void stateStableProcess(void);//
void stateRunProcess(void);//
void stateNoWaterProcess(void);
void stateDownProcess(void);//

void AppStateMachine(DRV_STATE curState);
#endif
