/*
 * motor.c
 * version 1.0
 */
#include "../hardware/gpio.h"
#include "../user/globalvars.h"
#include "../user/statemachine.h"

#define led_greenOn() GREENLED_ClrVal()
#define led_greenOff() GREENLED_SetVal()
#define led_greenToggle() GREENLED_Toggle()

#define led_redOn() REDLED_ClrVal()
#define led_redOff() REDLED_SetVal()
#define led_redToggle() REDLED_Toggle()

void led_init()
{
	REDLED_SetOutput();
	GREENLED_SetOutput();
}

void led_updateDisplay(DRV_ERROR_VAL error)
{
	switch(error)
	{
	case error_null:
		led_greenOn();
		led_redOff();
		break;
	case error_overcurrent:
		led_greenToggle();
		led_redOff();
		break;
	case error_overvoltage:
		led_greenOn();
		led_redOn();
		break;
	case error_undervoltage:
		led_greenOff();
		led_redOn();
		break;
	case error_undercurrent:
		led_greenOff();
		led_redToggle();
		break;
	default:
		led_greenOff();
		led_redOff();
		break;
	}
}


