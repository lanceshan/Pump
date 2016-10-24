#ifndef __UART_H
#define __UART_H

extern unsigned char recevieBuffer1[11];
extern unsigned char checkData1_OK;
//占用PTD7&PTD6

void uart1_init(void);

void uart1_clear_Rxbuf(void);

void uart1_wr(unsigned char buf[], unsigned char len);

//返回0表示目前串口上还没有数据，返回len表示成功接收到预期的长度的数据
unsigned char uart1_rd(unsigned char buf[], unsigned char len);

void uart1RxInInterrupt(void);
#endif

