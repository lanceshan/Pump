#ifndef _ERROR_
#define _ERROR_
#include "statemachine.h"

#define ERROR_STATE_PERIOD      			10  // 10*50ms = 500ms
#define ERROR_OVERCURRENT_PERIOD      	300  // 300*50ms = 15s

void clearMotorState(void);

DRV_ERROR_VAL errorCheck(DRV_STATE curState);
DRV_ERROR_VAL errorFilter(DRV_STATE curState, DRV_ERROR_VAL error);
DRV_STATE errorHandle(DRV_STATE curState,DRV_ERROR_VAL error);

#endif
