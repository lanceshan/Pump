/*!
**  stubheader.h
**  version 1.1
*/         
#ifndef _STUB_HEADER_
#define _STUB_HEADER_

//#define _STATE_MACHINE_STUB_ENABLE_
//#define _MID_FUNCTION_STUB_ENABLE_
//#define _MODULE1_STUB_ENABLE_


#ifdef _STATE_MACHINE_STUB_ENABLE_
#include "statemachine_stub.h"
#endif

#ifdef _MID_FUNCTION_STUB_ENABLE_
#include "midfunction_stub.h"
#endif

#ifdef _MODULE1_STUB_ENABLE_
#include "module1_stub.h"
#endif

#endif
