/*!
**  timer.h
**  version 1.1
*/         

#ifndef _TIMER_
#define _TIMER_
#include "Timer1.h"
#include "TU3.h"
#include "TU1.h"
#include "TU2.h"
#include "PWM1.h"
#include "PE_Types.h"
/*
 * timer.c
 * version1.0
 */
#include "cpu.h"
#include "timer.h"

void timer_init(void);

//T1 - 100us
void timer1_init(void);
void timer1_enable(void);
void timer1_disable(void);
void timer1_set_centerAlign(void);

//T2 - 可调定时器
void timer2_init(void);
void timer2_enable(void);
void timer2_disable(void);
void timer2_set_centerAlign(void);

//T3 - 16KHz
void timer_pwm_init(void);
void timer_pwm_enable(void);
void timer_pwm_disable(void);
void timer_pwm_set_centerAlign(void);

//PWM: ratio 0~32767
void pwm_init(void);
void pwm_set_duty_cycle(uint16 ratio);
void pwm_clear_duty_cycle(void);

void start_timer2_for_openloop(uint32 period);
void start_timer2_for_closedloop(uint32 period);


#endif
