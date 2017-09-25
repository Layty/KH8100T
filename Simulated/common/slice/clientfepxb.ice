/* **************************************************
* Copyright(c) 2010, KHDQ,Inc. All rights reserved.
*
* File��clientfepxb.ice
* 
* �������в�ģ�����ݽ�����slice�ӿڶ����ļ���
*****************************************************/ 

#ifndef _CLIENT_FEP_XB_ICESTORM
#define _CLIENT_FEP_XB_ICESTORM

module FepXbData 
{
	["java:type:java.util.ArrayList<Byte>"] sequence<byte>		byteSeq;
	["java:type:java.util.ArrayList<String>"] sequence<string>	stringSeq;
	["java:type:java.util.ArrayList<Short>"] sequence<short>		shortSeq;
	
	struct TduCfg
	{
		string SettingFlag;           			//��ֵ������־	"TDUCFG"  6b
		byte Version;  //�������ݽṹ�汾�� ��ʼΪ��0x01  1b
		byte ChannelCheckCode;      			//ͨ��У����  1---�����棻2---�û���
		byte FilterWidth;				//�˲����
		byte FilterCtrlCode;				//�˲�������
		byte ChannelNum;				//ͨ����	1~24
		byte SamplingRate;          			//����Ƶ�� 36MHz,12MHz,8MHz,6MHz,4.8 MHz,4 MHz, 3MHz, 2.4MHz,1.5 MHz,1MHz,500kHz
		byte Rs;
		byte RecordLength;	                        //��¼����	1ms��20ms
		short TriggerInterval;				//������� 10ms,20ms, 50ms, 100ms, 200ms, 500ms, 1s		
		byte WorkFrequence;//��ƵƵ��	50---50Hz,60---60Hz  		
		byte YearL;
		byte YearH;
		byte IrigB;                                     //1---��Ч��2---��Ч
		byte Flash;//1000����2000������5000��
		byte TDUStaAddr;						//tduվַ
		string DevID;							//װ�� ID (12 bytes)
		string StatName;						//���վ��(20bytes)
		stringSeq LineName;					//��·��(8*16)
		byteSeq ChnlsLineNum;					//ͨ��������·��(24��Ԫ��)		0~5
		byte TimeZoneHour;							//ʱ��
		byte TimeZoneMinute;
		byte Rsved;								//����1


		byteSeq EnChAndIsInvertPhase;					//�Ƿ���0~1(24��Ԫ��)
		byteSeq AIBoardTypeAndMesures;   		//AI������&������(48��Ԫ��)		1~8
		byteSeq DI;//(8��Ԫ��)
		byteSeq DI2;//ī����˫DI 2014-9-17
		shortSeq VarRatio; //CT/PT���ԭ��ֵ(2*8��Ԫ��)
		byteSeq VarRatioVice;//  CT/PT��ȸ���ֵ(1*8��Ԫ��)
		shortSeq VolLevel;						//��ѹ�ȼ�(2*8��Ԫ��)
		byteSeq ChannelGain;			//ͨ������(24��Ԫ��)   1~255
		byteSeq TriggerThreshold;		//�����ż�(24��Ԫ��) 4-20
		byteSeq LineCurrent;//��·����ֵ(���Ƶֵ)(8��Ԫ��) 5A��1A
		byteSeq LineVICorrection;//��·����ֵУ��ֵ(8��Ԫ��)
		byteSeq StartPara;//��������ֵ,ÿͨ��ռ��12bit(36��Ԫ��)
		byteSeq GainPara;//ͨ����������ֵ��װ��ʹ��(24��Ԫ��)

		byteSeq MACAddr1;						//(6��Ԫ��)
		byteSeq IPAddr1;						//(4��Ԫ��)
		byteSeq NetMask1;						//(4��Ԫ��)
		byteSeq Gateway1;						//(4��Ԫ��)
		short Port1;							//(2��Ԫ��)
		byteSeq MACAddr2;						//(6��Ԫ��)
		byteSeq IPAddr2;						//(4��Ԫ��)		
		byteSeq NetMask2;						//(4��Ԫ��)
		byteSeq Gateway2;						//(4��Ԫ��)
		short Port2;							//(2��Ԫ��)
		short NetReserve;						//Net����(2��Ԫ��)
		byteSeq remoteIP1;                                               //(4��Ԫ��)
		short remotePort1;                                             //(4��Ԫ��)
		byteSeq remoteIP2;                                               //(4��Ԫ��)
		short remotePort2;                                             //(2��Ԫ��)
		byte Com1ProtocolType; //COM1��Լ����
		byteSeq Com1ProtocolPara;				//COM1��Լ����(6��Ԫ��)
		byte LinkAddr103; //103��·��ַ��
		byte FunType103;//103��������
		byte Com2ProtocolType; //COM1��Լ����
		byteSeq Com2ProtocolPara;				//COM1��Լ����(6��Ԫ��)
		byte LinkAddr2103; //103��·��ַ��
		byte FunType2103;//103��������
		string ModemPhone;//ModemԶ�˵绰����(20 bytes)
		string ModemInitCmd;					//MODEM��ʼ������(20 bytes)
		byte ModemState;//Modem����״̬ 0����ʹ�ã�1��������2������
		byte Rsved3;	//����3
	};
	
	struct SettingValueInfo
	{
		string		deviceId;					//�ն˱��
		TduCfg 		tdu100Cfg;	    			//tdu100����
	};
	
	//�ֶ�����
	struct ManualTrigger
	{
		short UnitNo;//��Ԫ
		long 	Time;//ʱ��
		float distant;//����
	};
	sequence<ManualTrigger> ManualTriggerSeq;
	
	//ǰ�û����ͻ���
	const string FepClientTopic = "fep_client_data";
	interface CFepClientApp
	{
		void readSettingValueReply(SettingValueInfo settingVal,bool flag,string tip); //����ֵ�������,,,flag���ɹ�ʧ�ܣ�tip������
		void writeSettingValueReply(string deviceId,bool flag,string tip); //д��ֵ�������
		void manTriggerReply(string deviceId, bool flag, string tip);//�ֶ���������
		void resetReply(string deviceId, bool flag, string tip);//Զ�̸�λ���
	};
	
	//�ͻ��˵�ǰ�û�
	const string ClientFepTopic  = "client_fep_operation";
	interface CSettingValueFep
	{
		void readSettingValue(string deviceId);//����ֵ
		void writeSettingValue(SettingValueInfo settingVal);//д��ֵ
		void sendManTrigger(ManualTriggerSeq manTriggerSeq);//�����ֶ���������
		void sendReset(string deviceId);//Զ�̸�λ
	};
	

};

#endif  