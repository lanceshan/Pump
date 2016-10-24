/*
 * midfunction.c
 * version 1.0
 */
#include "cpu.h"
#include "globalvars.h"
#include "midfunction.h"
#include "currentbuffer.h"
#include "commprotocol.h"
#include "motor.h"
#include "hardware/adc.h"
#include "hardware/HWmacro.h"
#include "hardware/gpio.h"
#include "hardware/eeprom.h"
#include "cstdlib"

/*************************************************************
*������    ��delay(unsigned int x)
*����        ��x
*����ֵ    ��NULL
*ȫ�ֱ�����NULL
*����       ��������ʱ������FF�����ȡ�γ�������
*�޸�       ��NULL
*��ע       ��NULL
*����       ������ΰ
*����       ��2014/10/16
*************************************************************/
void delay(unsigned int x)
{
	unsigned int i=0;
	for(i=x;i>0;i--)
		PE_NOP();   //0.25us
}
unsigned char genCRC8(unsigned char dataBuf[], unsigned char n)
{
	unsigned char i, x, crcbuff, crc = 0;
	
	for(x = 0; x <n; x++)
	{
		crcbuff = dataBuf[x];
		for(i = 0;i < 8;i++)
		{
			if(((crc ^ crcbuff) & 0x01) == 0)
				crc >>= 1;
			else
			{
				crc ^= 0x18;   //CRC=X8+X5+X4+1
				crc >>= 1;
				crc |= 0x80;
			}
			
			crcbuff >>= 1;
		}
	}
	return crc;
}

 //�ɼ������ǰ��λ��δͨ����ķ��綯�ƣ�phase�ǵ�ǰ��λ
uint16 getBEMFVolt(unsigned char phase)
{
	uint16 ret_val = 0;
	switch(phase)
	{
		case 0:
		case 3:
			ret_val = adc_rd(BEMF_C_ADC_PORT);
			break;
		case 1:
		case 4:
			ret_val = adc_rd(BEMF_B_ADC_PORT);
			break;
		case 2:
		case 5:
			ret_val = adc_rd(BEMF_A_ADC_PORT);
			break;
		default:
			ret_val = 0;
			break;
	}
	return ret_val;
}

 //�ɼ�26V�����ߵ�ѹ
uint16 getDCBusVolt(void)
{
	return adc_rd(VBB_ADC_PORT);
}

 //�ɼ�26V�����ߵ���
uint16 getCurrent(void)
{
	return adc_rd(CURRENT_ADC_PORT);
}

//�ɼ�MCU�����¶ȴ�������ADֵ
uint16 getMCUTemper(void)
{
	return adc_rd(Temperatur_ADC_PORT);
}

 //�Ե�ǰ��λ�������⣬phase�ǵ�ǰ��λ������ֵΪ0��δ��⵽���㣬����ֵΪ1���⵽���㣬�������ڲ���⵽����󣬲������κζ�ʱ�������ö�����
unsigned char zeroCrossDetect(unsigned char phase)
{
	static unsigned char zcCounter=0;
	unsigned int curBEMFVolt = 0;
	unsigned int vsVolt = 0, centerVolt = 0, lowerLimit = 0, higherLimit = 0;
	unsigned int offsetVolt=0;

	unsigned char edgeRising = 0; 
	unsigned char zcDetected = 0;
	vsVolt = gVoltage&0xfff0;//ȥ�����λ����
	centerVolt = vsVolt>>1;
	lowerLimit = vsVolt/5; //test vsVolt>>2; // vsVolt/5;
	higherLimit = vsVolt-lowerLimit; // vsVolt*4/5;
	if(0 == gMotorPara.direction)
	{
		switch(phase)
		{
			case 2:
			case 5:
				curBEMFVolt = adc_rd(BEMF_A);		//BEMF_A
				break;
			case 1:
			case 4:
				curBEMFVolt = adc_rd(BEMF_B);		//BEMF_B
				break;
			case 0:
			case 3:
				curBEMFVolt = adc_rd(BEMF_C);		//BEMF_C
				break;		
		}
	}
	else
	{
		switch(phase)
		{
			case 0:
			case 3:
				curBEMFVolt = adc_rd(BEMF_A);		//BEMF_A
				break;
			case 1:
			case 4:
				curBEMFVolt = adc_rd(BEMF_B);		//BEMF_B
				break;
			case 2:
			case 5:
				curBEMFVolt = adc_rd(BEMF_C);		//BEMF_C
				break;
		}
	}
	if((curBEMFVolt < higherLimit) && (curBEMFVolt > lowerLimit))
	{
		//if(phase % 2 == 0) edgeRising = 0;
		//else edgeRising = 1;
		edgeRising = phase & 0x1;  //���������д����Ч
		
		if(edgeRising)
		{
			if(curBEMFVolt>(centerVolt-offsetVolt)) //tmp
			{
				zcCounter++;
				if(zcCounter>1)
				{
					zcDetected = 1;
					zcCounter=0;
				}
				else
					zcDetected = 0;
			}
			else
			{
				zcCounter=0;
				zcDetected = 0;
			}
		}
		else
		{
			if(curBEMFVolt<(centerVolt+offsetVolt))		//tmp
			{
				zcCounter++;
				if(zcCounter>1)
				{
					zcDetected = 1;
					zcCounter=0;
				}	
				else
					zcDetected = 0;
			}
			else
			{
				zcCounter=0;
				zcDetected = 0;
			}
		}
	}
	else
	{
		zcCounter=0;
	}
	return zcDetected;	
}

unsigned int T1CntToSpeed(unsigned long int sumPeriod)
{
	return (sumPeriod == 0) ? 0 : (60000/(sumPeriod*T1TICK_TO_MS_COEFF));   // 60s/time
}

#if 0
unsigned int getInstSpeed(void) //�������µĹ�����״�������T1�м�⵽�����ѹ�������6����λ�Ĺ���ʱ����������˲ʱת�٣�����ֵ��rmsΪ��λ����ת��ֵ
{
	unsigned long int sumPeriod = 0;
	unsigned char i = 0;
	unsigned char tmp_phase = gMotorPhase;
	
	for(i = 0; i < 6; i++)
	{
		if(tmp_phase < 5)
		{
			if((tmp_phase-i)>=0)
			{
				sumPeriod += gZCDetectPeriod[tmp_phase - i];
			}
			else
			{
				sumPeriod += gZCDetectPeriod[23 + tmp_phase - i];
			}
		}
		else
		{
			sumPeriod += gZCDetectPeriod[tmp_phase - i];
		}
	}
	
	return T1CntToSpeed(sumPeriod*4);	
}
#else
 //�������µĹ�����ʱ�䣬������˲ʱת�٣�����ֵ��rmsΪ��λ����ת��ֵ
unsigned int getInstSpeed(void)
{
	return T1CntToSpeed(gZCDetectPeriod[gMotorPhase] * 24);	
}
#endif

 //��ȡ��ǰ�ٶȣ����������24�ι���ʱ�̵�˲ʱ�ٶ���ƽ��ֵ��Ϊ��ǰ�ٶȣ���һ����ǰ�ٶȱ���ȵ���һ�ֵ�24�ι���ʱ������ʱ�Ÿ��£�ʵ������Ҫ����һ����̬�ľֲ���������������24�ι���ʱ��˲ʱ�ٶ���ƽ����
unsigned int getCurSpeed(void)
{
	unsigned long int sumPeriod = 0;
	unsigned char i = 0;
	
	for(i = 0; i < 24;i++)
		sumPeriod += gZCDetectPeriod[i];   //gZCDetectPeriod[]�б����������24��ĸ��ԵĻ���ʱ����

	return T1CntToSpeed(sumPeriod);	
}

//�Ƚ��ٶȣ�����Ǽ����򷵻�-1������Ǽ����򷵻�1�������ά���򷵻�0�������ٶȵıȽϲ��ܼ򵥵����Ƿ�������ж���Ӧ���񸡵����ıȽ�һ�������������ֵ��ĳ����Χ�ھ���Ϊ�ٶ���ȡ�
int speedCompare(unsigned int curSpeed, unsigned int targetSpeed) 
{
	int cmp = 0;
	int diff = curSpeed - targetSpeed;

	if(diff < -50)  //-50�д�����
	{
		cmp = 1;
	}
	else if(diff > 50)  //50�д�����
	{
		cmp = -1;
	}
	else
		cmp = 0;

	return cmp;	
}

#ifdef FAST_PID_Ctrl_SPEED
/*************************************************************
*������    ��modifyDutyCycle(unsigned int curSpeed, unsigned int targetSpeed, unsigned int dutyCycle)
*�������  curSpeed-ʵ��ת��   targetSpeed-Ŀ��ת��   
* ����        ��      pidE[0]-��ǰת�����         pidE[1]-ǰһʱ��ת����� 
* 		   Fek[0]~Fek[1]-���ٻ���ϵ��     
* 		   ALimit~BLimit-���ٻ�����ֵ
* 		   U_max-ռ�ձ�������Ӳ���
* 		   U_min-ռ�ձ���󽵵Ͳ���
*����ֵ    ��  dutyCycle-ռ�ձ�
*����ʽ���ٻ���pid�㷨��out=kp*(e0-e1)+ki*(e1+fek[0]*e0-fek[1]*e1)
*ȫ�ֱ�����Kp-����ϵ��    Ki-����ϵ��    
*����       ��ת�ٵ���
*�޸�       ��NULL
*��ע       ��NULL
*����       ����
*����       ��2016/08/11
*************************************************************/

unsigned int modifyDutyCycle(unsigned int curSpeed, unsigned int targetSpeed, unsigned int dutyCycle) 
{
	static signed int pidE[3] = {0};  			//pidE[0],pidE[1],pidE[2]�ֱ��Ӧe(k), e(k-1), e(k-2)
	static signed int pidU[2] = {0};  			//pidU[0],pidU[1]�ֱ��Ӧu(k), u(k-1)
	static float  	  Fek[2]  = {0};			//Fek[0],Fek[1]�ֱ��Ӧfe(k),fe(k-1)
	unsigned int out;//ռ�ձȱ仯��
	int delta;
	float P=0;
	float I=0;
	
    // �����Ա��ٻ���pi	
    pidE[0] =  targetSpeed - curSpeed;
    if(dutyCycle>=MAXDutyCycle)
    {
    	 if(pidE[0]>0)
    	    out=dutyCycle;
    	 else
    	 {
    		 if(abs(pidE[0])<=BLimit)
    	    	Fek[0]=1;
    		 else if(abs(pidE[0])<=(ALimit+BLimit))
    	    	Fek[0]=(float)((ALimit+BLimit)-abs(pidE[0]))/ALimit;
    		 else 
    	    	Fek[0]=0;
    	    			    	
    		 P=Kp*(pidE[0]-pidE[1]);
    		 I=Ki*(pidE[1]+Fek[0]*pidE[0]-Fek[1]*pidE[1]);
    	     pidU[0]=(int)(P+I);
    	     if(pidU[0]>=UMAX)
    	    	 pidU[0]=UMAX;
    	     else if(pidU[0]<=UMIN)
    	    	 pidU[0]=UMIN;
    	     delta=(int)pidU[0];
    	     if(delta<0)
    	    	out=dutyCycle-abs(delta);
    	     else if(delta>=0)
    	    	out=dutyCycle+delta;
    	 } 			
   }
   else if(dutyCycle<=MINDutyCycle)
   {
	   if(pidE[0]<0)
		   out=dutyCycle;
	   else
    	 {
    	  	if(abs(pidE[0])<=BLimit)
    	    	Fek[0]=1;
    	  	else if(abs(pidE[0])<=(ALimit+BLimit))
    	    	Fek[0]=(float)((ALimit+BLimit)-abs(pidE[0]))/ALimit;
    	  	else 
    	    	Fek[0]=0;
    	  	P=Kp*(pidE[0]-pidE[1]);
    	  	I=Ki*(pidE[1]+Fek[0]*pidE[0]-Fek[1]*pidE[1]);
    	  	pidU[0]=(int)(P+I);
    	  	if(pidU[0]>=UMAX)
    	  		pidU[0]=UMAX;
    	    else if(pidU[0]<=UMIN)
    	    	pidU[0]=UMIN;
    	  	delta=(int)pidU[0];
    	    if(delta<0)
    	    	out=dutyCycle-abs(delta);
    	    else if(delta>=0)
    	    	out=dutyCycle+delta;
    	   }
   }
   else
   {
	   if(abs(pidE[0])<=BLimit)
		   Fek[0]=1;
	   else if(abs(pidE[0])<=(ALimit+BLimit))
		   Fek[0]=(float)((ALimit+BLimit)-abs(pidE[0]))/ALimit;
	   else 
		   Fek[0]=0;
	   P=Kp*(pidE[0]-pidE[1]);
	   I=Ki*(pidE[1]+Fek[0]*pidE[0]-Fek[1]*pidE[1]);
	   pidU[0]=(int)(P+I);
	   if(pidU[0]>=UMAX)
		   pidU[0]=UMAX;
	   else if(pidU[0]<=UMIN)
		   pidU[0]=UMIN;
	   delta=(int)pidU[0];
	   if(delta<0)
		   out=dutyCycle-abs(delta);
	   else if(delta>=0)
		   out=dutyCycle+delta;
    }
    	if(out>=MAXDutyCycle)
    		out=MAXDutyCycle;
    	else if(out<=MINDutyCycle)
    		out=MINDutyCycle;
    	pidE[1]=pidE[0];
    	Fek[1]=Fek[0];
    	return out;//����ת�ٱ���	
}
#else
unsigned int modifyDutyCycle(unsigned int curSpeed, unsigned int targetSpeed, unsigned int dutyCycle)
{
	float Fek=0;
	unsigned int MaxDeDuty=0;
	signed int diff = targetSpeed-curSpeed;
	unsigned int absdiff=abs(diff);
	if(curSpeed<=sDownLimit)
	{
		MaxDeDuty=(unsigned int)((float)UMAX_DELTA/4);
	}
	else if(curSpeed<=sMidLimit)
	{
		MaxDeDuty=(unsigned int)(0.85*UMAX_DELTA);
	}
	else if(curSpeed<=sUpLimit)
	{
		MaxDeDuty=UMAX_DELTA;
	}
	else if(curSpeed<=MAXSpeed)
	{
		MaxDeDuty=(unsigned int)((float)UMAX_DELTA/5);
	}
	
    if(absdiff==0)
    {
    	Fek=0;
    }
    else
    {
    	if(diff>0)
    		Fek=(float)absdiff/targetSpeed;
    	else
    		Fek=(float)absdiff/curSpeed;
    	
    	if(Fek>1)Fek=1;
    }
    
    if((dutyCycle<UMAX)||(absdiff>MINDiffSpeed))
    {
		if(diff>0)
			dutyCycle += (unsigned int)(Fek*MaxDeDuty);   
		else if(diff<0)
			dutyCycle -= (unsigned int)(Fek*MaxDeDuty);    
    }
    else
    {
    	
    	if(diff>0)
		{
			if(dutyCycle>=UMAX)
				dutyCycle += 1;
			else
				dutyCycle += (uint16)((absdiff*10)/MINDiffSpeed);
		}   
		else if(diff<0)
		{
			if(dutyCycle>=UMAX)
				dutyCycle -= 1;
			else
				dutyCycle -= (uint16)((absdiff*10)/MINDiffSpeed);  
		}
    }
    if(dutyCycle>MAXDutyCycle)dutyCycle = MAXDutyCycle;
    if(dutyCycle<MINDutyCycle)dutyCycle = MINDutyCycle;
	return dutyCycle;
	
}
#endif

void mcuMeasure(void)
{
	typedef  enum{ meas_null = 0, meas_busVolt, meas_busCurrent, meas_mcuTemper } meas_type;
	static meas_type meas = meas_busVolt;

	switch(meas)
	{
	case meas_null:
		break;
	case meas_busVolt:
		gVoltage = getDCBusVolt();
		meas = meas_busCurrent;
		break;
	case meas_busCurrent:
		gCurrent = getCurrent();
		currBuff_Push(&gCurrentBuffer, gCurrent);
		meas = meas_mcuTemper;
		break;
	case meas_mcuTemper:
		gMCUTemper = getMCUTemper();
		meas = meas_busVolt;
		break;
	}
	
}


#if 0
char noCurrent(unsigned int nCurrent)
{
	return ((nCurrent < MIN_CURRENT) ? 1 : 0);
}
 //����Ƿ��й��������򷵻�1�����򷵻�0
char overCurrent(unsigned int nCurrent,unsigned int maxCurrent)
{
	return ((nCurrent > maxCurrent) ? 1 : 0);
}
 
//�޵���1������2������0
char checkCurrent(unsigned int nCurrent,unsigned int maxCurrent)
{
	static unsigned char no_current_counter=0;
	static unsigned char over_current_counter=0;
	if(noCurrent(nCurrent))
	{
		if(no_current_counter++>5)
		{

			return (1);
		}
		else
		{
			return (0);
		}
	}
	else if(overCurrent(nCurrent,maxCurrent))
	{
		if(over_current_counter++>5)
		{
			return (2);
		}
		else
		{
			return (0);
		}
	}
	else
	{
		no_current_counter   =0;
		over_current_counter =0;
		return (0);
	}
}
#endif

//����Ƿ��й�ѹ�����򷵻�1�����򷵻�0
unsigned char overVoltage(void)
{
	return ((gVoltage > MAX_VOLTAGE) ? 1 : 0);
}

unsigned char underVoltage(void)
{
	return ((gVoltage < MIN_VOLTAGE) ? 1 : 0);
}
//��ѹ2��Ƿѹ1������0
unsigned char checkVoltage(void)
{
	static unsigned char over_voltage_counter=0;
	static unsigned char under_voltage_counter=0;
	if(overVoltage())
	{
		if(over_voltage_counter>5)over_voltage_counter=6;
		if(over_voltage_counter++>5)
		{
			gStatusData->flags.flagbits.voltagefaultFlag=2;
			return (2);
		}
		else
		{
			return (0);
		}
	}
	else if(underVoltage())
	{
		if(under_voltage_counter>5)under_voltage_counter=6;
		if(under_voltage_counter++>5)
		{
			gStatusData->flags.flagbits.voltagefaultFlag=1;
			return (1);
		}
		else
		{
			return (0);
		}
	}
	else
	{
		gStatusData->flags.flagbits.voltagefaultFlag=0;
		
		over_voltage_counter=0;under_voltage_counter=0;
		return (0);
	}
}

int convTemperature(unsigned int Temperature)
{
	float TemperatureOf25_Value=1143.6032;//(uint16)(1.396/5*4096);
	if(Temperature<=TemperatureOf25_Value)
		return (signed char)(25+((float)((TemperatureOf25_Value-Temperature)/2.9802496)));//3 // 3.638 mV/��C	>25��	
	else
		return (signed char)(25-((float)((Temperature-TemperatureOf25_Value)/2.6755072)));//3 // 3.266 mV/��C    <25��
}

unsigned char overTemperature(void)
{
	return ((convTemperature(gMCUTemper) > MAX_TEMP) ? 1 : 0);
}

unsigned int getPumpSpeed(void)
{
	static unsigned int pumpSpeed = 0;
/*	unsigned char buffer[1] = {0};
	
	if(pumpSpeed == 0)
	{
		if(eeprom_rd(EEPROM_PUMP_SPEED_ADDRESS, buffer, 1) == 0)
		{
			pumpSpeed = NormalMAXSpeed; // 0;
		}
		else
		{
			if(buffer[0] == 255)
				pumpSpeed = MAXSpeed;
			else
				pumpSpeed = NormalMAXSpeed* ((unsigned int)buffer[0] + 1) / 255;
		}
	}
*/  
	pumpSpeed = 4700;
	return pumpSpeed;	
}


