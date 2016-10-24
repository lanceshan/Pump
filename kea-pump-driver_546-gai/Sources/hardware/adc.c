/*
 * adc.c
 * version 1.0
 */

//#include "AD1.h"
#include "SKEAZ1284.h"
#include "adc.h"

void adc_init(void)
{
	SIM_SCGC |= SIM_SCGC_ADC_MASK;
	ADC_SC1 = 0	;	
	ADC_SC3 = 0x29;  // 0b0010 1001, adiv = 2, mode = 12bit, adiclk = bus/2
	ADC_SC2 = 0x00;
	//ADC_APCTL1 &= 0xc73f; // ~(0b0011 1000 1100 0000), ch13/ch12/ch11/ch7/ch6;
	ADC_APCTL1 |= 0x38c0; // (0b0011 1000 1100 0000), ch13/ch12/ch11/ch7/ch6;
	
}

uint16 adc_rd(ADC_CHANNEL port)
{
	const unsigned char adch[] = {0x0d, 0x0c, 0x07, 0x06, 0x0b,0x16};
	
	ADC_SC1 = adch[port];
	
	while(!(ADC_SC1 & 0x80));
	
	return ADC_R & 0xffffffff;
}

void adc_rd_all(uint16 sample_buff[])
{
	ADC_CHANNEL port;
	for(port = BEMF_A; port <= CS; port++)
		sample_buff[port] = adc_rd(port);
	
	return;
}

/*
void adc_fifo_init(void)
{
	SIM_SCGC |= SIM_SCGC_ADC_MASK;
	ADC_APCTL1 |= 0x38c0; // (0b0011 1000 1100 0000), ch13/ch12/ch11/ch7/ch6;
	ADC_SC3 = 0x29;  // 0b0010 1001, high speed, adiv = 2, short sample, mode = 12bit, adiclk = bus/2
	ADC_SC2 = 0x00;  // 0b0000 0000
	//ADC_SC4 = 0x04|0x40;  // 0b0000 0100, 5-level FIFO
	ADC_SC4 = 0x04;  // 0b0000 0100, 5-level FIFO
	
	ADC_SC1 = 0x0d;	//BEMF_A
	ADC_SC1 = 0x0c;	//BEMF_B
	ADC_SC1 = 0x07;	//BEMF_C
	ADC_SC1 = 0x06;	//VS
	ADC_SC1 = 0x0b;	//CS
	//ADC_SC1 = 0x0b|0x20;	//CS, continuous mode	
	
}

uint16 adc_fifo_rd(ADC_CHANNEL port)
{
	//const unsigned char adch[] = {0x0d, 0x0c, 0x07, 0x06, 0x0b};
	uint16 adval[5] = {0};
	uint8_t i = 0;
	
	//ADC_SC1 = adch[port];
	
	while(!(ADC_SC1 & 0x80));
	
	for(i = 0;i < 5;i++)
		adval[i] = ADC_R & 0xffffffff;
	
	ADC_SC1 = 0x0d;	//BEMF_A
	ADC_SC1 = 0x0c;	//BEMF_B
	ADC_SC1 = 0x07;	//BEMF_C
	ADC_SC1 = 0x06;	//VS
	ADC_SC1 = 0x0b;	//CS
	
	return adval[port];
}

char adc_fifo_rd_all(uint16 sample_buff[])
{
	//const unsigned char adch[] = {0x0d, 0x0c, 0x07, 0x06, 0x0b};
	//uint16 adval[5] = {0};
	uint8_t i = 0;
		
	while(!(ADC_SC1 & 0x80));
		
	for(i = 0;i < 5;i++)
		sample_buff[i] = ADC_R & 0xffffffff;
		
	ADC_SC1 = 0x0d;	//BEMF_A
	ADC_SC1 = 0x0c;	//BEMF_B
	ADC_SC1 = 0x07;	//BEMF_C
	ADC_SC1 = 0x06;	//VS
	ADC_SC1 = 0x0b;	//CS
	
	return 1;
}
*/
