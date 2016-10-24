/*!
**  HWmacro.h
**  version 1.1
*/         

#ifndef _HW_MACRO_
#define _HW_MACRO_

////////////////////////////
#define T1_INT_PEROID_SET 				100.0    			// us
#define T1_TICK_PEROID_SET 				(1.0/24.0) 	 //us
#define T1_FTM_MOD_SET 					2400

#define T1_INT_PERIOD_ACTUAL 			(float)100.0 		//us
#define T1_TICK_PEROID_ACTUAL 			(float)(T1_INT_PERIOD_ACTUAL/T1_FTM_MOD_SET)  		//us

////////////////////////////
#define T2_TICK_FREQ_SET 				(0.75*2)  	// MHz
#define T2_TICK_PERIOD_SET 				(1.0/T2_TICK_FREQ_SET)  		//us

#define T2_TICK_PEROID_ACTUAL 			(float)0.6667  		//us
#define T2_TICK_FREQ_ACTUAL 			(float)(1/T2_TICK_PEROID_ACTUAL)  //MHz

////////////////////////////
#define T3_INT_PEROID_SET 				62.5 //62.5    			// us
#define T3_TICK_PEROID_SET 				(1.0/24.0) 	 //us
#define T3_FTM_MOD_SET 					1500 //1500

#define T3_INT_PERIOD_ACTUAL 			(float)62.5 //62.5 		//us

////////////////////////////
#define T1INT_TO_T2TICK_COEFF 			(float)(T1_INT_PERIOD_ACTUAL*T2_TICK_FREQ_ACTUAL)   
#define T2TICK_TO_T1INT_COEFF 			(float)(1/T1INT_TO_T2TICK_COEFF)
#define T1TICK_TO_T2TICK_COEFF 			(float)(T1_TICK_PEROID_ACTUAL*T2_TICK_FREQ_ACTUAL)
#define T2TICK_TO_T1TICK_COEFF 			(float)(1/T1TICK_TO_T2TICK_COEFF)

#define T1TICK_TO_MS_COEFF 				(float)(T1_TICK_PEROID_ACTUAL/1000)   //T1 tick to ms

#define COMMUTATION_DISCHARGE_PERIOD 	(float)200  			//us
#define COMMUTATION_DISCHARGE_CNT 		(COMMUTATION_DISCHARGE_PERIOD/T1_INT_PERIOD_ACTUAL)

#endif
