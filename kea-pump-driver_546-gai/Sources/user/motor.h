/*!
**  motor.h
**  version 1.1
*/         

#ifndef _MOTOR_
#define _MOTOR_

#include "PE_Types.h"
#include "globalvars.h"

typedef void (*tSetPhase)(void);
typedef void (*tSetDischarge)(void);

typedef struct{
	unsigned char enable;
	unsigned char direction;
	unsigned char advanceAngle;  //提前角，实际上是以过零点时刻开始到电机换向之间的时间间隔，以前一个过零时间间隔的1/256为时间单位
	unsigned char reserve;
	unsigned int  dutyCycle; //占空比
	unsigned int targetSpeed; //目标转速
	unsigned int curSpeed; //当前转速
}tagMotorParams, *ptrMotorParams;


extern tagMotorParams gMotorPara;            //电机的运转参数


void motor_setPhase(unsigned char phase,unsigned char direction);
void motor_setDischarge(unsigned char phase,unsigned char direction);

void motor_disable(void);
void motor_enable(void);

void motor_setDutyCycle(uint16 dutyCycle);

void motor_setAlign(void);
void motor_brake(void);

#endif
