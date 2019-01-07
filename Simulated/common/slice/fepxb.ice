/* **************************************************
* Copyright(c) 2010, KHDQ,Inc. All rights reserved.
*
* File��Fepxb.ice
* 
* ǰ�����в�ģ�����ݽ�����slice�ӿڶ����ļ���
*****************************************************/ 

#ifndef _FEP_XB_ICESTORM
#define _FEP_XB_ICESTORM

module FepXbData 
{
	["java:type:java.util.ArrayList<Byte>"] sequence<byte>		byteSeq;
	["java:type:java.util.ArrayList<String>"] sequence<string>	stringSeq;
	["java:type:java.util.ArrayList<Short>"] sequence<short>		shortSeq;
	
	//��ֵ
	struct SettingValueInfo
	{
		short		unitNo;					//�ն˱��
		byteSeq tdu100Cfg;	    //tdu100����
	};
	
	//ͨ�����ͼ��Ƿ�Խ��SAC�ֽ�
	struct SAC
	{
		bool			bIsOverLimit;		//�Ƿ�Խ��
		int				nBelongToLine;		//������·
		int				nMeasureType;		//1-8:Ia,Ib,Ic,Va,Vb,Vc,DC+,DC-.
	};
	
	//ͨ����Ϣ 
	struct SChannelData
	{
		SAC				sSAC;				//ͨ�����ͼ��Ƿ�Խ��
		short  wFreqCurrentM;		//��Ƶ������ֵ
	};
	["java:type:java.util.ArrayList<SChannelData>"] sequence<SChannelData>		SChannelDataSeq;
	
	//���ϴ���ʱ��
	struct STriggerTime
	{
		int				nTimeType;			//0��GPSʱ�䣻1���ڲ�ʱ��
		string		szTimeString;	//ʱ���ַ�����YYYYMMDDHHMMSS
		double		dUs;				//΢��
	};
	
	//���ϼ�
	struct TduBrief
	{
		short  unitNo;//��Ԫ��
		int				FileType;
		bool			bIsDial;			//���ͷ�ʽ��true-���ţ�false-����
		STriggerTime	sTriggerTime;		//����ʱ��
		int				nTriggerType;		//0:��·������1���˹�����
		int				nStartChannel;		//��ʼͨ����
		int				nTriggerChannel;	//����ͨ��	1-24
		bool			bIsOverLimit;		//����ͨ����Ƶ�Ƿ�Խ��
		int				nFaultPhase;		//������	1-A��;2-B��;3-C��;4-AB��;5-BC��;6-AC��;7-ABC��.
		SChannelDataSeq	sChannelInfo;	//ͨ����Ϣ
	};
	
	sequence<TduBrief>	TduBriefSeq;
	
	//ʱ��
	struct AlarmTime
	{
		int year;
		int month; 
		int day;
		int hour;
		int minute;
		int second;
		int milliseconds;
	};
	
	//soe
	struct XbSOE
	{
		short unitNo;//��Ԫ��
		AlarmTime soeTime; //ʱ��
		short Di1;//di1
		short Di2;//di2
		short Val;//ֵ
		bool Alarm;//�Ƿ�澯
		bool Update;//�Ƿ����
	};
	sequence<XbSOE>	XbSOESeq;
	
	//ң��
	struct XbDiscrete
	{
		short unitNo;//��Ԫ��
		AlarmTime disTime; //ʱ��
		short No;//���
		short Val;//ֵ
		bool Alarm;//�Ƿ�澯
		bool Update;//�Ƿ����
	};
	sequence<XbDiscrete>	XbDiscreteSeq;
	
	//��Ԫ״̬
	struct XbUnitStatus
	{
		short	type;
		short unitNo;//��Ԫ��
		AlarmTime disTime; //ʱ��
		short UnitState;
		short ChannelState;
		short ErrorRate;
	};
	sequence<XbUnitStatus>	XbUnitStatusSeq;
	
	//����
	struct XbWave
	{
		short unitNo;//��Ԫ��
		string FileName;//�ļ�����
		byteSeq Wave;//����
		bool Start;//�Ƿ�ʼ
		bool End;//�Ƿ����
	};
	
	
	
	//�����ݴ���Ľ���
	const string FepXbTopic = "fep_xb_data";
	interface CFepXb
	{
		void sendSettingValue(SettingValueInfo settingVal);//��ֵ
		void sendBrief(TduBriefSeq briefSeq);//��
		void sendSoe(XbSOESeq soeSeq);//soe
		void sendDiscrete(XbDiscreteSeq discreteSeq);//ң��
		void sendUnitStatus(XbUnitStatusSeq usSeq);//��Ԫ״̬
		void sendWave(XbWave wave);//����
	};
	

};

#endif  