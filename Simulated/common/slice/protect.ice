/*
* Copyright (c) 2010,GridNT,Inc*All rights reserved.
*
* �ļ����ƣ�Protect.ice* ժҪ��������ֵice�ļ�
*/


#ifndef PROTECT_ICE
#define PROTECT_ICE


[["java:package:com.kh.scada.protect"]] 
module Protect{

	enum OPERTYPE
	{
		READSETTING = 0,			//��ȡ��ֵ
		WRITESETTING,				//�·���ֵ
		READGROUPNO,				//����ֵ��
		SWITCHGROUP					//�л���ֵ��
	};
	sequence<byte> Bytes;
	
	struct ProtectValueInfo
	{
		short		UnitNo;			//�ն˱��
		short		ProLine;		//������·��
		OPERTYPE	OperType;		//��������
		short		FuncCode;		//��ֵ������,0x91,0xCD,0xCE...
		short		GroupNo;		//��ֵ���
		short		ProNum;			//������ֵ����
		int			requestId;
		Bytes 		Vals;	    	//��ֵ����
	};

	const string ProtectValueAppTopic = "protectvalue_app_operation";
	interface CProtectApp
	{
		void processProtectSetting(ProtectValueInfo psInfo);
	};
	
	const string ProtectValueFepTopic  = "protectvalue_fep_operation";
	interface CProtectFep
	{
		void ProtectSettingExecute(ProtectValueInfo psInfo);
	};

};

#endif