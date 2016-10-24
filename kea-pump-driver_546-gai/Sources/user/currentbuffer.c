#include "cpu.h"
#include "currentbuffer.h"

static int enCritical = 0;

int currBuff_Clear(tagCurrentBuffer *pBuf)
{
	int i;

	if(enCritical != 0) return -1; // -1表示缓冲区被占用
	else enCritical++;
	
	if(NULL != pBuf)
	{
		pBuf->head = 0;
		pBuf->tail = 0;
		pBuf->cnt = 0;
		pBuf->max = 0;

		for(i = 0;i < CURR_BUFF_MAX;i++) pBuf->buffer[i] = 0;
	}

	if(enCritical != 0) enCritical = 0;
	return 0;
	
}

int currBuff_Average(tagCurrentBuffer *pBuf)
{
	int i, j;
	unsigned int sum = 0;
	unsigned int ret = 0;

	if(enCritical != 0) return -1; // -1表示缓冲区被占用
	else enCritical++;
	
	if((NULL == pBuf) || (pBuf->cnt == 0)) 
	{
		ret = 0;
	}
	else
	{
		for(i = 0;i < pBuf->cnt;i++)
		{
			j = ((pBuf->head+i)>= CURR_BUFF_MAX) ? (pBuf->head+i-CURR_BUFF_MAX) : (pBuf->head+i);
			sum += pBuf->buffer[j];
		}

		ret = sum/pBuf->cnt;
	}

	if(enCritical != 0) enCritical = 0;
	return ret;
	
}


int currBuff_Push(tagCurrentBuffer *pBuf, unsigned int current)
{
	if(enCritical != 0) return -1; // -1表示缓冲区被占用
	else enCritical++;
	
	if(NULL != pBuf) 
	{
		if(pBuf->cnt != 0)
		{
			pBuf->tail++;
			if(pBuf->tail >= CURR_BUFF_MAX) pBuf->tail = 0;

			if(pBuf->tail == pBuf->head) pBuf->head++;
			if(pBuf->head >= CURR_BUFF_MAX) pBuf->head = 0;
		}

		pBuf->buffer[pBuf->tail] = current;
		if(current >= pBuf->max) pBuf->max = current;

		pBuf->cnt++;
		if(pBuf->cnt > CURR_BUFF_MAX) pBuf->cnt = CURR_BUFF_MAX;
	}

	if(enCritical != 0) enCritical = 0;
	return current;

}

int currBuff_Pop(tagCurrentBuffer *pBuf)
{
	unsigned int current = 0;
	int i, j;

	if(enCritical != 0) return -1;  // -1表示缓冲区被占用
	else enCritical++;
	
	if((NULL == pBuf) || (pBuf->cnt == 0)) 
	{
		current = 0;
	}
	else
	{
		if(pBuf->cnt > 0) pBuf->cnt--;
		
		current = pBuf->buffer[pBuf->tail];

		if(pBuf->cnt != 0)
		{
			if(0 == pBuf->tail) pBuf->tail = CURR_BUFF_MAX-1;
			else pBuf->tail--;
		}
		
	
		if(current == pBuf->max) 
		{
			pBuf->max = 0;
			for(i = 0;i < pBuf->cnt;i++)
			{
				j = ((pBuf->head+i) >= CURR_BUFF_MAX) ? (pBuf->head+i-CURR_BUFF_MAX) : (pBuf->head+i);
				if(pBuf->max <= pBuf->buffer[j]) pBuf->max = pBuf->buffer[j];
			}
		}
	}

	if(enCritical != 0) enCritical = 0;
	return current;

}






