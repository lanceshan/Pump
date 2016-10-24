/*!
**  commprotocol.h
**  version 1.1
*/         

#ifndef _COMM_PROTOCOL_
#define _COMM_PROTOCOL_

typedef struct{
	unsigned char new_cmd_flag;	   //0: slave control 1:return version
	unsigned char cmd_type;		   //0: slave control 1:return version
	unsigned char direction;       //方向
	unsigned int  targetSpeed;  //速度比值
}controlMessage;

 //receviedData_FromD_rive      //接收数据结构体
typedef struct{
	unsigned char head0;                     //接收数据头0，正确时为'Y'
	unsigned char head1;                     //接收数据头1，正确时为'L'
//	char slaveaddr;                 //驱动板返回地址1或2
	unsigned char state;                     //风机状态0~9:0x03风机运行 0x04风机停止，等等（后期修改可将正反转标志与风机状态合并）
	union 
	{
		unsigned char flagByte;
		struct
		{
			unsigned char perdrivefaultFlag :2; //预驱动报错值FF1、FF2
			unsigned char zcdetecfaultFlag  :1; //零点检测失败标志0：无；1：有，目前未用
			unsigned char currentfaultFlag  :1; //过流标志        0：无；1：过流，目前未用
			unsigned char voltagefaultFlag  :2; //电压标志        0：正常；1：欠压；2：过压
			unsigned char homebackFlag      :1; //回家模式标志驱动板检测的0：无；1：回家模式按键按下，目前未用
			unsigned char direction         :1; //正反转标志      0：正转；1：反转
		} flagbits;
	}flags;
	unsigned char currentValueHi;                        //电流值高位
	unsigned char currentValueLo;                        //电流值低位
	unsigned char speedValueHi;                          //速度值高位
	unsigned char speedValueLo;                          //速度值低位
	unsigned char dutyCycleHi;                           //占空比值高位
	unsigned char dutyCycleLo;                           //占空比值低位
	signed   char mcuTenperature;
	unsigned char crcData;                               //CRC校验值：目前未用
}tSlaveMCUStatus;

extern tSlaveMCUStatus *gStatusData;
extern controlMessage   gMessageOfControl;

unsigned char RxMessage(unsigned char buf[]);  //解析从串口收到的命令数据包，包括效验码解析、参数提取，返回收到的有效数据包的数据长度

void TxMessage(unsigned char buf[], unsigned char len); //从串口发送命令数据包，包括参数核对、校验码编码
#endif
