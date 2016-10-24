/*!
**  midfunction.h
**  version 1.1
*/         

#ifndef _MID_FUNCTION_
#define _MID_FUNCTION_
#include "statemachine.h"
//#include "../hardware/adc.h"
#include "PE_Types.h"

#define FAST_PID_Ctrl_SPEED

#define MINDiffSpeed  	MAXSpeed/50 //С����Χ
#define MAXDutyCycle  	32768
#define MINDutyCycle  	4000        // �޸���ʱ��Ӧ��500rpm����

#define ALimit  		(0.2*MAXSpeed)
#define BLimit   		(0.1*MAXSpeed)

#define sUpLimit      	(0.9*MAXSpeed)
#define sMidLimit     	(0.5*MAXSpeed)
#define sDownLimit    	(0.3*MAXSpeed)

#ifdef FAST_PID_Ctrl_SPEED
#define UMIN			(-1000)		
#define UMAX			1000		
#else
#define UMIN			MINDutyCycle
#define UMAX			(MAXDutyCycle-50)
#endif

#define Kp 				5       
#define Ki 				1.7     	//(Kp*Ts/Ti)
//#define Kd 			0.2      	//(Kp*Td/Ts)

#define UMAX_DELTA  	655			//���ռ�ձ�����Ϊ 0.1%
#define UMIN_DELTA 		(-655)		//��Сռ�ձ�����Ϊ-0.1%

#define BEMF_A_ADC_PORT		BEMF_A
#define BEMF_B_ADC_PORT		BEMF_B
#define BEMF_C_ADC_PORT		BEMF_C
#define VBB_ADC_PORT		VS
#define CURRENT_ADC_PORT	CS
#define Temperatur_ADC_PORT	TS

#define MIN_VOLTAGE			1370 // 18V  x*(10/107.6)/5*4096
#define MAX_VOLTAGE      	2436 // 32V  x*(10/107.6)/5*4096

#define MAX_INST_CURRENT    3000 // 3782 	//����˲ʱֵ�����ֵ, 2721��Ӧ35A,���㹫ʽ��Value = (A*R*current + V_offset)/5*4096��ʵ����A*R=0.081, V_offset=1.782v
									//ԭ�������㹫ʽ��(current*0.003*28.612+1.941)/5*4096
#define MIN_INST_CURRENT	200 // 1460 	//����˲ʱֵ�����ֵ, 1460��Ӧ  0A,���㹫ʽ��Value = (A*R*current + V_offset)/5*4096��ʵ����A*R=0.081, V_offset=1.782v

#define MAX_AVE_CURRENT		2339 // 3118 	//����˲ʱֵ�����ֵ, 2360��Ӧ25A,���㹫ʽ��Value = (A*R*current + V_offset)/5*4096��ʵ����A*R=0.081, V_offset=1.782v
#define MIN_AVE_CURRENT     700 // 1493 	//����˲ʱֵ�����ֵ, 1478��Ӧ0.5A,���㹫ʽ��Value =(A*R*current + V_offset)/5*4096��ʵ����A*R=0.081, V_offset=1.782v

//31A Cin=15.72Vout-14.49    
#define MIN_CURRENT     	0

#define MIN_TEMP			-40 //  ��
#define MAX_TEMP			115 //  ��

void delay(unsigned int x);
unsigned char genCRC8(unsigned char dataBuf[], unsigned char n);

uint16      getBEMFVolt(unsigned char phase);         //�ɼ������ǰ��λ��δͨ����ķ��綯�ƣ�phase�ǵ�ǰ��λ
uint16      getDCBusVolt(void);              //�ɼ�26V�����ߵ�ѹ
uint16      getCurrent(void);                //�ɼ�26V�����ߵ���
uint16      getMCUTemper(void);//��ȡMCU�ڲ��¶ȴ�����ADֵ

unsigned char          zeroCrossDetect(unsigned char phase);

unsigned int  getInstSpeed(void);              //�������µĹ�����״�������T1�м�⵽�����ѹ�������6����λ�Ĺ���                         
											   //ʱ����������˲ʱת�٣�����ֵ�ԣ�����Ϊ��λ����ת��ֵ

unsigned int  getCurSpeed(void);               //��ȡ��ǰ�ٶȣ����������24�ι���ʱ�̵�˲ʱ�ٶ���ƽ��ֵ��Ϊ��ǰ�ٶȣ�                        
											   //��һ����ǰ�ٶȱ���ȵ���һ�ֵ�24�ι���ʱ������ʱ�Ÿ��£�ʵ������Ҫ����һ����̬        
											   //�ľֲ���������������24�ι���ʱ��˲ʱ�ٶ���ƽ����

int   speedCompare(unsigned int curSpeed, unsigned int targetSpeed); //�Ƚ��ٶȣ�����Ǽ����򷵻�-1��                     
																			 //����Ǽ����򷵻�1�������ά���򷵻�0��        
																			 //�����ٶȵıȽϲ��ܼ򵥵����Ƿ�������ж���  
																			 //Ӧ���񸡵����ıȽ�һ�������������ֵ��ĳ��   
																			 //��Χ�ھ���Ϊ�ٶ���ȡ�

unsigned int  modifyDutyCycle(unsigned int curSpeed, unsigned int targetSpeed, unsigned int dutyCycle);  
																	//���ݵ�ǰ�ٶ��ж��Ƿ���Ҫ�Ӽ��٣�����ռ�ձȵĵ��ڼ��㣬
																	//����ֵΪ����֮���ռ�ձȣ���������ĵ��ñ�����                    
																	//����PWMռ�ձ�ʱ����Ҫ�Ķ�ʱ�ﵽ�˲Ž��С�                            

unsigned int  pidIncDutyCycle(unsigned int curSpeed, unsigned int targetSpeed, unsigned int dutyCycle);

void mcuMeasure(void);

#if 0
char          noCurrent(unsigned int nCurrent);
char          overCurrent(unsigned int nCurrent,unsigned int maxCurrent); //����Ƿ��й��������򷵻�1�����򷵻�0
char          checkCurrent(unsigned int nCurrent,unsigned int maxCurrent);
#endif

unsigned char          overVoltage(void); //����Ƿ��й�ѹ�����򷵻�1�����򷵻�0
unsigned char          underVoltage(void);//����Ƿ���Ƿѹ�����򷵻�1�����򷵻�0
unsigned char          checkVoltage(void);//����Ƿ��й�ѹ�����򷵻�1�����򷵻�0

int   convTemperature(unsigned int Temperature);//�¶Ȼ���

unsigned int getPumpSpeed(void);

#endif
