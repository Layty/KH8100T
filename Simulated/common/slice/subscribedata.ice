/* **************************************************
* Copyright(c) 2011-, JNKH. All rights reserved.
*
* File��SubscribeData.ice
* 
*****************************************************/ 
 
#ifndef _SUBSCRIBEDATA_ICE
#define _SUBSCRIBEDATA_ICE
 
[["java:package:com.gridnt.subscribedata"]]
/**
* 
* �Ƿ��ж�������
* 
*/
module SubData
{
     struct DataInfo
     {
        string modulename;
        bool isSubscribe;
     };
	 
	 struct PartSec
     {
        string partition;
        string section;
     };
	 
	 /**
	 *
	 *ǰ�û�ͨѶ��Ϣ
	 *
	 **/
	struct CommInfo
	{
		int  flag;  //��־   
		int  no;    //���
		int  used;  //�Ƿ�����
		int  type;  //����
		string paramLine; //ͨ������
	};
	
	sequence<CommInfo> CommInfoSeq;
	
	/**
	 *
	 *ǰ�û���Լ��Ԫ��Ϣ
	 *
	 **/
	struct PiUnitInfo
	{
		//��ԪID
		string unitId;
		
		//��Ԫ�ڵ�
		string unitNode;
	};
	
	sequence<PiUnitInfo> PiUnitInfoSeq;
	
	/**
	 *
	 *ǰ�û���Լ��Ϣ
	 *
	 **/
	struct FepProtocolInfo
	{
		int  flag;  //��־
		int  no;  //��Լ���
		int  used; // ʹ�ñ�־
		int  type; //��Լ����
		int  active;  //����
		int  runCount;  //���и���
		int  needWatch; //��Ҫ����
		string name;  //��Լ����
		int  unitCount;  //��Ԫ����
		PiUnitInfoSeq piunitSeq;
		int  commCount;  //ͨѶ����
		CommInfoSeq commSeq;
		string paramLine;     //����
	};
	
	sequence<FepProtocolInfo> FepProtocolInfoSeq;
	

	struct UnitInfo
	{
		int   refCount;             // ���ü���
		string  name;  // ��Ԫ����
		int   no;                   // ��Ԫ��
		int   used;                 // ʹ�ñ�־
		int   type;                 // ����
		int   stationNo;            // վַ��������ն�һ��
		int   nodeCount;            // ͨ������
		int   mainNodeNo;           // ���ڵ��?
		int   replyTimeouts;        // ��ʱʱ��
		int   faultJudgeCount;      // �����϶�����
		int   isTrans;              // �Ƿ�ת����Ԫ��0-��1-�ǡ�
		string  res;              // ����
		int   manuGetRFW;           // �Զ���ȡ¼����־  
		string  paramLine;            // ��չ����
		int   facNo;    // ���� �������������Ȱ����������������
		int   facType;  // ��վ����
		int   yxNum;    // ң�Ÿ���
		int   ycNum;    // ң�����
		int   ddNum;    // ��ȸ���
	};
	
	sequence<UnitInfo> UnitInfoSeq;
	
	sequence<short> UnitQsSeq;
	struct UnitQsInfo
	{
		int   no;                   // ��Ԫ��
		UnitQsSeq	qsSeq;			// ���Ʋ���
	};
	sequence<UnitQsInfo> UnitQsInfoSeq;
 
    const string SubscribeDataTopic = "subscribe_data";  // ����
    interface SubscribeDataInfo
    {
        void procSub(DataInfo data);
		void refreshParam(PartSec data,FepProtocolInfoSeq piSeq, UnitInfoSeq unitSeq,UnitQsInfoSeq qsSeq);
    };
};
 
#endif 