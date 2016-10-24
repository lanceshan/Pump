/*!
**  led.h
**  version 1.1
*/         

#ifndef _LED_
#define _LED_

#include "../user/statemachine.h"

void led_init(void);
void led_updateDisplay(DRV_ERROR_VAL error);

#endif
