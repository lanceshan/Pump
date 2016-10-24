#ifndef _CURRENT_BUFFER_
#define _CURRENT_BUFFER_

#include "globalvars.h"

#define CURR_BUFF_MAX 80
typedef struct{
	unsigned char head; //��ʾ��ͷ
	unsigned char  tail;  //��ʾ��β
	unsigned char cnt;  //���е���Ч���ݳ���
	unsigned char reserve;
	unsigned int max;
	unsigned int buffer[CURR_BUFF_MAX];
}tagCurrentBuffer, *ptrCurrentBuffer;

extern tagCurrentBuffer gCurrentBuffer;

int currBuff_Clear(tagCurrentBuffer *pBuf);
int currBuff_Push(tagCurrentBuffer *pBuf, unsigned int current);
int currBuff_Average(tagCurrentBuffer *pBuf);

#endif
