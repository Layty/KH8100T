/* **************************************************
* Copyright(c) 2011-, KHDQ, inc. All rights reserved.
*
* File��eventData.ice
* �澯slice�ӿڶ����ļ���
*
*****************************************************/ 

#ifndef _FEP_EVENTDATA_ICESTORM
#define _FEP_EVENTDATA_ICESTORM

[["java:package:com.kh.icestorm"]]

module EventData
{
	struct eventContent
	{
		string strTime;
		string type;
		string deviceId;
		string deviceType;
		string content;
	};
	
	["java:type:java.util.ArrayList<eventContent>"]sequence<eventContent> eventContentSeq;
	
	/**
    * �ֶ���ȡ����
    * ManualDataManager
    */
    const string EventDataTopic = "eventdata_operation";
    interface EventDataManager
    {
    	void send(eventContentSeq eventMsgSeq);
    };
};

#endif  //  _FEP_EVENTDATA_ICESTORM