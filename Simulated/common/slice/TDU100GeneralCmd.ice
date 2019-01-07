/* **************************************************
* Copyright(c) 2011-, KHDQ, inc. All rights reserved.
*
* File��TDU100GeneralCmd.ice
* tdu100һ������slice�ӿڶ����ļ���
*
*****************************************************/ 

#ifndef _FEP_TDU100GENERALCMD_ICESTORM
#define _FEP_TDU100GENERALCMD_ICESTORM

[["java:package:com.kh.icestorm"]]

module TDU100GeneralCmd
{

		
    struct TDU100GeneralCmdMsg
    {
    	string deviceId;
			string inf;//��Ϣ���--1���ֶ�����;2��Զ�̸�λװ�ã�
			string triggerTime;//10:59:02 102340
    };
    ["java:type:java.util.ArrayList<TDU100GeneralCmdMsg>"] sequence<TDU100GeneralCmdMsg>	tduReqSeq;
    
    struct TDU100GeneralCmdReplyMsg
    {
    	string deviceId;
    	string bz;//��Ϣ���
    	string message;
   	};
	["java:type:java.util.ArrayList<TDU100GeneralCmdReplyMsg>"]sequence<TDU100GeneralCmdReplyMsg> replyMsgSeq;
	
	struct TDUProtocolMsg
	{
		string deviceId;//��Ԫ��
		string name;//����
		short protocolType;//��Լ��
		short channelNum;//ͨ������
		short	noResponTime;//����Ӧʱ��
		string extParam;//��չ����
		short faultNum;//ʧ�ܴ���
		string deviceType;//�豸����
		string used;//�Ƿ�����
		string param;//ͨ������
		short updateBz;//0:update 1:add
	};
	["java:type:java.util.ArrayList<TDUProtocolMsg>"]sequence<TDUProtocolMsg> protocolMsgSeq;
    
    /**
    * tdu100һ������
    * TDU100GeneralCmdManager
    */
    const string TDU100GeneralCmdRequestTopic = "tdu100generalcmd_operation_Request";
    const string TDU100GeneralCmdResponseTopic = "tdu100generalcmd_operation_Response";
    interface TDU100GeneralCmdManagerRequest
    {
    	void TDU100GeneralCmdRoute(tduReqSeq reqSeq);	
    	void updateProtocolParam(protocolMsgSeq protocolSeq);
    };
    
    interface TDU100GeneralCmdManagerResponse
    {
    	void TDU100GeneralCmdReply(replyMsgSeq replySeq);
    };
};

#endif  //  _FEP_TDU100GENERALCMD_ICESTORM