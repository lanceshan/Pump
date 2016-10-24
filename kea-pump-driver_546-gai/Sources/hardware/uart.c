//#include "UART_0.h"
#include "uart.h"
#include "Cpu.h"
#include "AS1.h"
#include "user/globalvars.h"
LDD_TDeviceData *MyUART1=NULL;
static unsigned char Rxbuff[7];
static unsigned char sReciveOkFlag=0;
void uart1_init(void)
{
	MyUART1=AS1_Init(NULL);
}
void uart1_wr(unsigned char buf[], unsigned char len)
{
	AS1_SendBlock(MyUART1, buf, len);
}

void uart1_clear_Rxbuf(void)
{
	AS1_ReceiveBlock(MyUART1,Rxbuff,7);
}

unsigned char uart1_rd(unsigned char buf[], unsigned char len)
{
	unsigned char i=0;
	if(sReciveOkFlag)
	{
		for(i=0;i<len;i++)
		{
			buf[i]=Rxbuff[i];
		}
		sReciveOkFlag=0;
		return len;
	}
	else
	{
		return 0;
	}
}
void uart1RxInInterrupt(void)
{
	LDD_TError ErrorFlag=NULL;
	ErrorFlag=AS1_ReceiveBlock(MyUART1,Rxbuff,7);
	if(ErrorFlag==ERR_OK)
	{
		sReciveOkFlag=1;
	}
}




