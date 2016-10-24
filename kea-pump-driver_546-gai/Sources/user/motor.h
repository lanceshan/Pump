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
	unsigned char advanceAngle;  //��ǰ�ǣ�ʵ�������Թ����ʱ�̿�ʼ���������֮���ʱ��������ǰһ������ʱ������1/256Ϊʱ�䵥λ
	unsigned char reserve;
	unsigned int  dutyCycle; //ռ�ձ�
	unsigned int targetSpeed; //Ŀ��ת��
	unsigned int curSpeed; //��ǰת��
}tagMotorParams, *ptrMotorParams;


extern tagMotorParams gMotorPara;            //�������ת����


void motor_setPhase(unsigned char phase,unsigned char direction);
void motor_setDischarge(unsigned char phase,unsigned char direction);

void motor_disable(void);
void motor_enable(void);

void motor_setDutyCycle(uint16 dutyCycle);

void motor_setAlign(void);
void motor_brake(void);

#endif
