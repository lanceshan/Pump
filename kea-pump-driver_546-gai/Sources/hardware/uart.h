#ifndef __UART_H
#define __UART_H

extern unsigned char recevieBuffer1[11];
extern unsigned char checkData1_OK;
//ռ��PTD7&PTD6

void uart1_init(void);

void uart1_clear_Rxbuf(void);

void uart1_wr(unsigned char buf[], unsigned char len);

//����0��ʾĿǰ�����ϻ�û�����ݣ�����len��ʾ�ɹ����յ�Ԥ�ڵĳ��ȵ�����
unsigned char uart1_rd(unsigned char buf[], unsigned char len);

void uart1RxInInterrupt(void);
#endif

