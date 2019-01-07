/* **************************************************
* Copyright(c) 2018, KHDQ,Inc. All rights reserved.
*
* File��FepCommState.ice
* 
* ǰ�������ܻ�������slice�ӿڶ����ļ���
*****************************************************/ 

#ifndef _FEP_COMSTATE_ICESTORM
#define _FEP_COMSTATE_ICESTORM
[["java:package:com.kh.icestorm"]]
module FepCommState {
    
    // ͨ��״̬  
    enum StateValue {
        disconnection,     // 0-ͨ���ж�
        cutoff,    		   // 1-����ͨ������
	connection,  	   // 2-ͨ������
        unknown   		   // 3-δ֪״̬
    };
    
    
    // �ն�/ͨ��״̬��������
    struct UnitChannel {
        short    	  unitNo;          // �ն˱��
	byte		  channelNo;	   // ͨ�����,��ǰֻʹ��0������˫ͨ��ʱ����Ϊ1�� 20180918
	string		  unitName;		   // �ն�����
	string		  gateWay;		   // ��������
	string		  rtuAddr;		   // �ն�IP
        StateValue    unitState;       // �ն�ͨ��״̬
    };

    ["java:type:java.util.ArrayList<UnitChannel>"]
    sequence<UnitChannel>  UnitChannelSeq;        // �ն�ͨ��״̬
    
	
    struct StateDataPacket {
        byte        	id;       // ���ݰ�ID
        string        	fepNode;  // ����ǰ�û�    
		int			requestId;
        UnitChannelSeq	unitchannels;           // �ն�ͨ��״̬
    };
	
	const string CommStateValueAppTopic = "commstatevalue_app_operation";
	interface CComStateApp
	{
		void processCommState(StateDataPacket csInfo);
	};
	
	const string CommStateValueFepTopic  = "commstatevalue_fep_operation";
	interface CComStateFep
	{
		void processCommState(StateDataPacket csInfo);
	};
    
    // ǰ��ͨ�����ݶ���
    const string strCommStateTopic = "fep_commdata_state";
    interface FepCommStateManager {
        void processData(StateDataPacket aPacket);     // ʵʱͨ��״̬����
    };  
    
};

#endif  // _FEP_COMSTATE_ICESTORM