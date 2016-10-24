#ifndef _CURRENT_BUFFER_
#define _CURRENT_BUFFER_

#include "globalvars.h"

#define CURR_BUFF_MAX 80
typedef struct{
	unsigned char head; //表示队头
	unsigned char  tail;  //表示队尾
	unsigned char cnt;  //队列的有效数据长度
	unsigned char reserve;
	unsigned int max;
	unsigned int buffer[CURR_BUFF_MAX];
}tagCurrentBuffer, *ptrCurrentBuffer;

extern tagCurrentBuffer gCurrentBuffer;

int currBuff_Clear(tagCurrentBuffer *pBuf);
int currBuff_Push(tagCurrentBuffer *pBuf, unsigned int current);
int currBuff_Average(tagCurrentBuffer *pBuf);

#endif
