#include "AS1.h"
#include "uart0_master.h"


void uart0_master_init(void)
{
	//pUART2Device = UART_0_Init(NULL);
	//UART_PDD_SetBaudRate(UART0_BASE_PTR, 156U); 	

  /* SIM_SCGC: UART0=1 */
  SIM_SCGC |= SIM_SCGC_UART0_MASK;
  /* SIM_PINSEL0: UART0PS=0 */
  SIM_PINSEL0 &= 0xffffff7f;  //(uint32_t)~(uint32_t)(SIM_PINSEL_UART0PS_MASK);
  /* SIM_SOPT0: RXDFE=0 */
  SIM_SOPT0 &= (uint32_t)~(uint32_t)(SIM_SOPT0_RXDFE(0x03));
  
  UART0_C2 &= ~(0x0C); //0x00;
  //UART_PDD_EnableTransmitter(UART0_BASE_PTR, PDD_DISABLE); /* Disable transmitter. */
  //UART_PDD_EnableReceiver(UART0_BASE_PTR, PDD_DISABLE); /* Disable receiver. */

  /* UART0_C1: LOOPS=0,UARTSWAI=0,RSRC=0,M=0,WAKE=0,ILT=0,PE=0,PT=0 */
  UART0_C1 = 0x00U;                    /*  Set the C1 register */
  /* UART0_C3: R8=0,T8=0,TXDIR=0,TXINV=0,ORIE=0,NEIE=0,FEIE=0,PEIE=0 */
  UART0_C3 = 0x00U;                    /*  Set the C3 register */
  /* UART0_S2: LBKDIF=0,RXEDGIF=0,??=0,RXINV=0,RWUID=0,BRK13=0,LBKDE=0,RAF=0 */
  UART0_S2 = 0x00U;                    /*  Set the S2 register */

UART0_BDH = 0; // (156>>8)&0xff;   //156 = 24Mhz/16/9600
UART0_BDL = 3; // 156;
  //UART_PDD_SetBaudRate(UART0_BASE_PTR, 156U); /* Set the baud rate register. */

  UART0_C2 |= 0x0C;
  //UART_PDD_EnableTransmitter(UART0_BASE_PTR, PDD_ENABLE); /* Enable transmitter */
  //UART_PDD_EnableReceiver(UART0_BASE_PTR, PDD_ENABLE); /* Enable receiver */
  
	
	
}

void uart0_master_wr(unsigned char buf[], unsigned char len)
{
	//UART_1_SendBlock(pUART2Device, buf, len);
	unsigned char i = 0;
	
	for(i = 0;i < len;i++)
	{
		while(!(UART0_S1 & UART_S1_TDRE_MASK));
		UART0_D = buf[i];
	}
	
	return;
}

//返回0表示目前串口上还没有数据，返回len表示成功接收到预期的长度的数据
unsigned char uart0_master_rd(unsigned char buf[], unsigned char len)
{
	unsigned char i;
	unsigned int timeout = 0;
	
	if(!(UART0_S1 & UART_S1_RDRF_MASK)) return 0;

	for(i = 0;i < len;i++)
	{
		while(!(UART0_S1 & UART_S1_RDRF_MASK))
		{
			timeout++;
			if(timeout == 3000) break;
		}

		if(timeout == 3000) return 0;
		else timeout = 0;
		
		buf[i] = UART0_D;
	}
	
	return len;
}



