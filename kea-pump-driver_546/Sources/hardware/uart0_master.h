#ifndef __UART2_Master_H
#define __UART2_Master_H

//ռ��PTB0&PTB1

void uart0_master_init(void);

void uart0_master_wr(unsigned char buf[], unsigned char len);

//����0��ʾĿǰ�����ϻ�û�����ݣ�����len��ʾ�ɹ����յ�Ԥ�ڵĳ��ȵ�����
unsigned char uart0_master_rd(unsigned char buf[], unsigned char len);

#endif

