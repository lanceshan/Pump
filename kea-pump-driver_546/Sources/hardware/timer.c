/*
 * timer.c
 * version1.0
 */
#include "cpu.h"
#include "../hardware/timer.h"

static LDD_TDeviceData *TU2_ptr = NULL;	//timer2 data pointer

void timer_init(void)
{
	timer1_init();
	timer2_init();
	timer_pwm_init();

	timer1_enable();
	timer2_disable();
	timer_pwm_disable();		
}

//T1 - 100us
void timer1_init(void)
{
	timer1_set_centerAlign();
	return;
}

void timer1_enable(void)
{
	Timer1_Enable();
}

void timer1_disable(void)
{
	Timer1_Disable();
}

void timer1_set_centerAlign(void)
{
	FTM0_SC |= 1<<5;
}

//T2 - 可调定时器
void timer2_init(void)
{
	TU2_ptr = TU2_Init(NULL);
	timer2_set_centerAlign();
}

void timer2_enable(void)
{
	TU2_Enable(TU2_ptr);
}

void timer2_disable(void)
{
	TU2_Disable(TU2_ptr);
}

void timer2_set_centerAlign(void)
{
	FTM1_SC|= 1<<5;
}
void timer_pwm_set_centerAlign(void)
{
	FTM2_SC |= 1<<5;		   //center-alignment PWM mode
//	FTM2_C4SC = (FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK);
}
void timer_pwm_set_leftAlign(void)
{
	//FTM2_SC |= 1<<5;		   //center-alignment PWM mode
	FTM2_C4SC = (FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK);
}
//T3 - 16KHz
void timer_pwm_init(void)
{
	timer_pwm_set_leftAlign();
	return;
}
void timer_pwm_enable(void)
{
	PWM1_Enable();
}
void timer_pwm_disable(void)
{
	PWM1_Disable();
}
//PWM: ratio 0~32767
void pwm_init(void)
{
	pwm_clear_duty_cycle();
}

void pwm_set_duty_cycle(uint16 ratio)
{
	if(ratio<=32768)
		PWM1_SetRatio16(32767+ratio);
	else
		return;
}

void pwm_clear_duty_cycle(void)
{
	PWM1_SetRatio16(0);
}

void start_timer2_for_closedloop(uint32 period)
{
	timer2_disable();
	TU2_ResetCounter(TU2_ptr);
	TU2_SetPeriodTicks(TU2_ptr, period);
	timer2_enable();
}

void start_timer2_for_openloop(uint32 period)
{
	timer2_disable();
	TU2_ResetCounter(TU2_ptr);
	TU2_SetPeriodTicks(TU2_ptr, period);
	timer2_enable();
}


