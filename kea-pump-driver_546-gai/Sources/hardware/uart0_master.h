#ifndef __UART2_Master_H
#define __UART2_Master_H

//占用PTB0&PTB1

void uart0_master_init(void);

void uart0_master_wr(unsigned char buf[], unsigned char len);

//返回0表示目前串口上还没有数据，返回len表示成功接收到预期的长度的数据
unsigned char uart0_master_rd(unsigned char buf[], unsigned char len);

#endif

