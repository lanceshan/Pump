/*!
**  adc.h
**  version 1.1
*/         

#ifndef _ADC_
#define _ADC_

#include "PE_Types.h"

//typedef unsigned short int  uint16_t;

typedef  enum{	
	BEMF_A = 0, 
	BEMF_B, 
	BEMF_C, 
	VS, 
	CS,
	TS
}ADC_CHANNEL;

void adc_init(void);
void adc_rd_all(uint16 sample_buff[]);
uint16 adc_rd(ADC_CHANNEL port);
/*
void adc_fifo_init(void);
uint16 adc_fifo_rd(ADC_CHANNEL port);
char adc_fifo_rd_all(uint16 sample_buff[]);
*/
#endif
