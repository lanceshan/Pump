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
*函数名    ：delay(unsigned int x)
*参数        ：x
*返回值    ：NULL
*全局变量：NULL
*作用       ：粗略延时，用作FF错误读取形成上下沿
*修改       ：NULL
*备注       ：NULL
*作者       ：吴益伟
*日期       ：2014/10/16
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

 //采集电机当前相位的未通电相的反电动势，phase是当前相位
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

 //采集26V的总线电压
uint16 getDCBusVolt(void)
{
	return adc_rd(VBB_ADC_PORT);
}

 //采集26V的总线电流
uint16 getCurrent(void)
{
	return adc_rd(CURRENT_ADC_PORT);
}

//采集MCU内置温度传感器的AD值
uint16 getMCUTemper(void)
{
	return adc_rd(Temperatur_ADC_PORT);
}

 //对当前相位做过零检测，phase是当前相位，返回值为0则未检测到过零，返回值为1则检测到过零，本函数内部检测到过零后，并不做任何定时器的设置动作。
unsigned char zeroCrossDetect(unsigned char phase)
{
	static unsigned char zcCounter=0;
	unsigned int curBEMFVolt = 0;
	unsigned int vsVolt = 0, centerVolt = 0, lowerLimit = 0, higherLimit = 0;
	unsigned int offsetVolt=0;

	unsigned char edgeRising = 0; 
	unsigned char zcDetected = 0;
	vsVolt = gVoltage&0xfff0;//去除最低位波动
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
		edgeRising = phase & 0x1;  //与以上两行代码等效
		
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
unsigned int getInstSpeed(void) //根据最新的过零检测状况，如果T1中检测到过零电压，则根据6个相位的过零时间间隔来计算瞬时转速，返回值以rms为单位表明转速值
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
 //根据最新的过零检测时间，来计算瞬时转速，返回值以rms为单位表明转速值
unsigned int getInstSpeed(void)
{
	return T1CntToSpeed(gZCDetectPeriod[gMotorPhase] * 24);	
}
#endif

 //获取当前速度，根据最近的24次过零时刻的瞬时速度求平均值作为当前速度，下一个当前速度必须等到下一轮第24次过零时刻来到时才更新，实现上需要定义一个静态的局部计数变量来控制24次过零时刻瞬时速度求平均。
unsigned int getCurSpeed(void)
{
	unsigned long int sumPeriod = 0;
	unsigned char i = 0;
	
	for(i = 0; i < 24;i++)
		sumPeriod += gZCDetectPeriod[i];   //gZCDetectPeriod[]中保存的是连续24相的各自的换相时间间隔

	return T1CntToSpeed(sumPeriod);	
}

//比较速度，如果是加速则返回-1，如果是减速则返回1，如果是维持则返回0，两个速度的比较不能简单的用是否相等来判定，应该像浮点数的比较一样，二者相减的值在某个范围内就认为速度相等。
int speedCompare(unsigned int curSpeed, unsigned int targetSpeed) 
{
	int cmp = 0;
	int diff = curSpeed - targetSpeed;

	if(diff < -50)  //-50有待调整
	{
		cmp = 1;
	}
	else if(diff > 50)  //50有待调整
	{
		cmp = -1;
	}
	else
		cmp = 0;

	return cmp;	
}

#ifdef FAST_PID_Ctrl_SPEED
/*************************************************************
*函数名    ：modifyDutyCycle(unsigned int curSpeed, unsigned int targetSpeed, unsigned int dutyCycle)
*输入参数  curSpeed-实际转速   targetSpeed-目标转速   
* 变量        ：      pidE[0]-当前转速误差         pidE[1]-前一时刻转速误差 
* 		   Fek[0]~Fek[1]-变速积分系数     
* 		   ALimit~BLimit-变速积分阈值
* 		   U_max-占空比最大增加步长
* 		   U_min-占空比最大降低步长
*返回值    ：  dutyCycle-占空比
*增量式变速积分pid算法：out=kp*(e0-e1)+ki*(e1+fek[0]*e0-fek[1]*e1)
*全局变量：Kp-比例系数    Ki-积分系数    
*作用       ：转速调节
*修改       ：NULL
*备注       ：NULL
*作者       ：吴
*日期       ：2016/08/11
*************************************************************/

unsigned int modifyDutyCycle(unsigned int curSpeed, unsigned int targetSpeed, unsigned int dutyCycle) 
{
	static signed int pidE[3] = {0};  			//pidE[0],pidE[1],pidE[2]分别对应e(k), e(k-1), e(k-2)
	static signed int pidU[2] = {0};  			//pidU[0],pidU[1]分别对应u(k), u(k-1)
	static float  	  Fek[2]  = {0};			//Fek[0],Fek[1]分别对应fe(k),fe(k-1)
	unsigned int out;//占空比变化量
	int delta;
	float P=0;
	float I=0;
	
    // 非线性变速积分pi	
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
    	return out;//返回转速比例	
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
 //检查是否有过流，有则返回1，否则返回0
char overCurrent(unsigned int nCurrent,unsigned int maxCurrent)
{
	return ((nCurrent > maxCurrent) ? 1 : 0);
}
 
//无电流1，过流2，正常0
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

//检查是否有过压，有则返回1，否则返回0
unsigned char overVoltage(void)
{
	return ((gVoltage > MAX_VOLTAGE) ? 1 : 0);
}

unsigned char underVoltage(void)
{
	return ((gVoltage < MIN_VOLTAGE) ? 1 : 0);
}
//过压2，欠压1，正常0
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
		return (signed char)(25+((float)((TemperatureOf25_Value-Temperature)/2.9802496)));//3 // 3.638 mV/°C	>25℃	
	else
		return (signed char)(25-((float)((Temperature-TemperatureOf25_Value)/2.6755072)));//3 // 3.266 mV/°C    <25℃
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


