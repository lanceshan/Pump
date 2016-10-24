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

#define MINDiffSpeed  	MAXSpeed/50 //小调范围
#define MAXDutyCycle  	32768
#define MINDutyCycle  	4000        // 无负载时对应的500rpm左右

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

#define UMAX_DELTA  	655			//最大占空比增量为 0.1%
#define UMIN_DELTA 		(-655)		//最小占空比增量为-0.1%

#define BEMF_A_ADC_PORT		BEMF_A
#define BEMF_B_ADC_PORT		BEMF_B
#define BEMF_C_ADC_PORT		BEMF_C
#define VBB_ADC_PORT		VS
#define CURRENT_ADC_PORT	CS
#define Temperatur_ADC_PORT	TS

#define MIN_VOLTAGE			1370 // 18V  x*(10/107.6)/5*4096
#define MAX_VOLTAGE      	2436 // 32V  x*(10/107.6)/5*4096

#define MAX_INST_CURRENT    3000 // 3782 	//电流瞬时值的最大值, 2721对应35A,计算公式：Value = (A*R*current + V_offset)/5*4096，实验测得A*R=0.081, V_offset=1.782v
									//原电流计算公式：(current*0.003*28.612+1.941)/5*4096
#define MIN_INST_CURRENT	200 // 1460 	//电流瞬时值的最大值, 1460对应  0A,计算公式：Value = (A*R*current + V_offset)/5*4096，实验测得A*R=0.081, V_offset=1.782v

#define MAX_AVE_CURRENT		2339 // 3118 	//电流瞬时值的最大值, 2360对应25A,计算公式：Value = (A*R*current + V_offset)/5*4096，实验测得A*R=0.081, V_offset=1.782v
#define MIN_AVE_CURRENT     700 // 1493 	//电流瞬时值的最大值, 1478对应0.5A,计算公式：Value =(A*R*current + V_offset)/5*4096，实验测得A*R=0.081, V_offset=1.782v

//31A Cin=15.72Vout-14.49    
#define MIN_CURRENT     	0

#define MIN_TEMP			-40 //  ℃
#define MAX_TEMP			115 //  ℃

void delay(unsigned int x);
unsigned char genCRC8(unsigned char dataBuf[], unsigned char n);

uint16      getBEMFVolt(unsigned char phase);         //采集电机当前相位的未通电相的反电动势，phase是当前相位
uint16      getDCBusVolt(void);              //采集26V的总线电压
uint16      getCurrent(void);                //采集26V的总线电流
uint16      getMCUTemper(void);//获取MCU内部温度传感器AD值

unsigned char          zeroCrossDetect(unsigned char phase);

unsigned int  getInstSpeed(void);              //根据最新的过零检测状况，如果T1中检测到过零电压，则根据6个相位的过零                         
											   //时间间隔来计算瞬时转速，返回值以？？？为单位表明转速值

unsigned int  getCurSpeed(void);               //获取当前速度，根据最近的24次过零时刻的瞬时速度求平均值作为当前速度，                        
											   //下一个当前速度必须等到下一轮第24次过零时刻来到时才更新，实现上需要定义一个静态        
											   //的局部计数变量来控制24次过零时刻瞬时速度求平均。

int   speedCompare(unsigned int curSpeed, unsigned int targetSpeed); //比较速度，如果是加速则返回-1，                     
																			 //如果是减速则返回1，如果是维持则返回0，        
																			 //两个速度的比较不能简单的用是否相等来判定，  
																			 //应该像浮点数的比较一样，二者相减的值在某个   
																			 //范围内就认为速度相等。

unsigned int  modifyDutyCycle(unsigned int curSpeed, unsigned int targetSpeed, unsigned int dutyCycle);  
																	//根据当前速度判定是否需要加减速，并做占空比的调节计算，
																	//返回值为调节之后的占空比，这个函数的调用必须在                    
																	//调节PWM占空比时所需要的定时达到了才进行。                            

unsigned int  pidIncDutyCycle(unsigned int curSpeed, unsigned int targetSpeed, unsigned int dutyCycle);

void mcuMeasure(void);

#if 0
char          noCurrent(unsigned int nCurrent);
char          overCurrent(unsigned int nCurrent,unsigned int maxCurrent); //检查是否有过流，有则返回1，否则返回0
char          checkCurrent(unsigned int nCurrent,unsigned int maxCurrent);
#endif

unsigned char          overVoltage(void); //检查是否有过压，有则返回1，否则返回0
unsigned char          underVoltage(void);//检查是否有欠压，有则返回1，否则返回0
unsigned char          checkVoltage(void);//检查是否有过压，有则返回1，否则返回0

int   convTemperature(unsigned int Temperature);//温度换算

unsigned int getPumpSpeed(void);

#endif
