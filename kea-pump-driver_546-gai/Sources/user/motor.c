/*
 * motor.c
 * version 1.0
 */
#include "../hardware/gpio.h"
#include "../hardware/timer.h"
#include "globalvars.h"
#include "motor.h"
#include "midfunction.h"


static void phaseAC_(void);
static void phaseAB_(void);
static void phaseBC_(void);
static void phaseBA_(void);
static void phaseCA_(void);
static void phaseCB_(void);

static void phaseACB_(void);
static void phaseAB_C_(void);
static void phaseABC_(void);
static void phaseBA_C_(void);
static void phaseBCA_(void);
static void phaseCA_B_(void);

static  const tSetPhase set_phase_func[][6] = {
	{phaseAB_, phaseAC_, phaseBC_, phaseBA_, phaseCA_, phaseCB_},
	{phaseCB_, phaseCA_, phaseBA_, phaseBC_, phaseAC_, phaseAB_}
};

static  const tSetDischarge set_discharge_func[][6] = {
	{phaseAB_C_, phaseABC_, phaseBA_C_, phaseBCA_, phaseCA_B_, phaseACB_},
	{phaseCA_B_, phaseBCA_, phaseBA_C_, phaseABC_, phaseAB_C_, phaseACB_}
};

static void phaseAB_C_(void)
{
	ALO_ClrVal();
	BHI_ClrVal();
	CHI_ClrVal();
	
	AHI_SetVal();
	BLO_SetVal();
	CLO_SetVal();
}

static void phaseABC_(void)
{
	ALO_ClrVal();
	BLO_ClrVal();
	CHI_ClrVal();
	
	AHI_SetVal();
	BHI_SetVal();
	CLO_SetVal();
}

static void phaseBA_C_(void)
{
	AHI_ClrVal();
	BLO_ClrVal();
	CHI_ClrVal();
	
	ALO_SetVal();
	BHI_SetVal();
	CLO_SetVal();
}

static void phaseBCA_(void)
{
	AHI_ClrVal();
	BLO_ClrVal();
	CLO_ClrVal();
	
	ALO_SetVal();
	BHI_SetVal();
	CHI_SetVal();
}

static void phaseCA_B_(void)
{
	AHI_ClrVal();
	BHI_ClrVal();
	CLO_ClrVal();
	
	ALO_SetVal();
	BLO_SetVal();
	CHI_SetVal();
}

static void phaseACB_(void)
{
	ALO_ClrVal();
	BHI_ClrVal();
	CLO_ClrVal();
	
	AHI_SetVal();
	BLO_SetVal();
	CHI_SetVal();
}

static void phaseAB_(void)
{
	//AHI_SetVal();//1
	ALO_ClrVal();//0
	BHI_ClrVal();//0
	//BLO_SetVal();//1
	CHI_ClrVal();//0
	CLO_ClrVal();//0
	
	AHI_SetVal();
	BLO_SetVal();
	
}

static void phaseAC_(void)
{
//	AHI_SetVal();//1
	ALO_ClrVal();//0
	BHI_ClrVal();//0
	BLO_ClrVal();//0
	CHI_ClrVal();//0
//	CLO_SetVal();//1
	
	AHI_SetVal();
	CLO_SetVal();
	
	
}

static void phaseBC_(void)
{	
	AHI_ClrVal();//0
	ALO_ClrVal();//0
//	BHI_SetVal();//1
	BLO_ClrVal();//0
	CHI_ClrVal();//0
//	CLO_SetVal();//1
	
	BHI_SetVal();//1
	CLO_SetVal();//1
	
}

static void phaseBA_(void)
{		
	AHI_ClrVal();//0
//	ALO_SetVal();//1
//	BHI_SetVal();//1
	BLO_ClrVal();//0
	CHI_ClrVal();//0
	CLO_ClrVal();//0
	
	ALO_SetVal();
	BHI_SetVal();
}

static void phaseCA_(void)
{
	AHI_ClrVal();//0
//	ALO_SetVal();//1
	BHI_ClrVal();//0
	BLO_ClrVal();//0
//	CHI_SetVal();//1
	CLO_ClrVal();//0
	
	ALO_SetVal();//1
	CHI_SetVal();//1
}

static void phaseCB_(void)
{
	AHI_ClrVal();//0
	ALO_ClrVal();//0
	BHI_ClrVal();//0
//	BLO_SetVal();//1
//	CHI_SetVal();//1
	CLO_ClrVal();//0
	
	BLO_SetVal();//1
	CHI_SetVal();//1
}

static void reset_pre_driver(void)
{
	gpio_wr(GPIO2, RST_A4935, 0);
	delay(15);
	gpio_wr(GPIO2, RST_A4935, 1);
	delay(15000);
}

static void pre_driver_enable(void)
{
	gpio_wr(GPIO2, RST_A4935, 1);
	gpio_wr(GPIO2, ESF      , 1);
	gpio_wr(GPIO2, COAST    , 1);
}

static void pre_driver_disable(void)
{
	gpio_wr(GPIO2, RST_A4935, 0);	
	gpio_wr(GPIO2, ESF      , 0);
	gpio_wr(GPIO2, COAST    , 0);
}



void motor_setPhase(unsigned char phase,unsigned char direction)
{
	//phase=phase%6;
	//if(phase >= 6) return;
	set_phase_func[direction][phase%6]();
}

void motor_setDischarge(unsigned char phase,unsigned char direction)
{
	set_discharge_func[direction][phase%6]();
}

void motor_disable(void)
{
	pre_driver_disable();
	pwm_clear_duty_cycle();
	timer_pwm_disable();
}

void motor_enable(void)
{
	timer_pwm_enable();
	reset_pre_driver();
	pre_driver_enable();
}

//dutyCycle: 0~32768
void motor_setDutyCycle(uint16 dutyCycle)
{
	pwm_set_duty_cycle(dutyCycle);
}

void motor_setAlign(void)
{
//	AHI_SetVal();//1
	BLO_ClrVal();//0
	AHI_ClrVal();//0
//	BLO_SetVal();//1
	CHI_ClrVal();//0
//	CLO_SetVal();//1
	
	BHI_SetVal();//1
	ALO_SetVal();//1
	CLO_SetVal();//1
}

void motor_brake(void)
{
	AHI_ClrVal();//0
	BHI_ClrVal();//0
	CHI_ClrVal();//0

	ALO_SetVal();
	BLO_SetVal();//0
	CLO_SetVal();//0
}



