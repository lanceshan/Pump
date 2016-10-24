/*!
**  commprotocol.h
**  version 1.1
*/         

#ifndef _COMM_PROTOCOL_
#define _COMM_PROTOCOL_

typedef struct{
	unsigned char new_cmd_flag;	   //0: slave control 1:return version
	unsigned char cmd_type;		   //0: slave control 1:return version
	unsigned char direction;       //����
	unsigned int  targetSpeed;  //�ٶȱ�ֵ
}controlMessage;

 //receviedData_FromD_rive      //�������ݽṹ��
typedef struct{
	unsigned char head0;                     //��������ͷ0����ȷʱΪ'Y'
	unsigned char head1;                     //��������ͷ1����ȷʱΪ'L'
//	char slaveaddr;                 //�����巵�ص�ַ1��2
	unsigned char state;                     //���״̬0~9:0x03������� 0x04���ֹͣ���ȵȣ������޸Ŀɽ�����ת��־����״̬�ϲ���
	union 
	{
		unsigned char flagByte;
		struct
		{
			unsigned char perdrivefaultFlag :2; //Ԥ��������ֵFF1��FF2
			unsigned char zcdetecfaultFlag  :1; //�����ʧ�ܱ�־0���ޣ�1���У�Ŀǰδ��
			unsigned char currentfaultFlag  :1; //������־        0���ޣ�1��������Ŀǰδ��
			unsigned char voltagefaultFlag  :2; //��ѹ��־        0��������1��Ƿѹ��2����ѹ
			unsigned char homebackFlag      :1; //�ؼ�ģʽ��־���������0���ޣ�1���ؼ�ģʽ�������£�Ŀǰδ��
			unsigned char direction         :1; //����ת��־      0����ת��1����ת
		} flagbits;
	}flags;
	unsigned char currentValueHi;                        //����ֵ��λ
	unsigned char currentValueLo;                        //����ֵ��λ
	unsigned char speedValueHi;                          //�ٶ�ֵ��λ
	unsigned char speedValueLo;                          //�ٶ�ֵ��λ
	unsigned char dutyCycleHi;                           //ռ�ձ�ֵ��λ
	unsigned char dutyCycleLo;                           //ռ�ձ�ֵ��λ
	signed   char mcuTenperature;
	unsigned char crcData;                               //CRCУ��ֵ��Ŀǰδ��
}tSlaveMCUStatus;

extern tSlaveMCUStatus *gStatusData;
extern controlMessage   gMessageOfControl;

unsigned char RxMessage(unsigned char buf[]);  //�����Ӵ����յ����������ݰ�������Ч���������������ȡ�������յ�����Ч���ݰ������ݳ���

void TxMessage(unsigned char buf[], unsigned char len); //�Ӵ��ڷ����������ݰ������������˶ԡ�У�������
#endif
