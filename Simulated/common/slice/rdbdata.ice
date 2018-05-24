/* **************************************************
* Copyright(c) 2010, GridNT,Inc. All rights reserved.
*
* File��rdbdata.ice
* ���ݷ�������Ӧ�÷������Ľӿڶ����ļ�
* 
*****************************************************/ 

#ifndef _REAL_DB_DATA_ICE
#define _REAL_DB_DATA_ICE

[["java:package:com.gridnt.icestorm"]]

//ʵʱ����
module RdbRealData
{
	["java:type:java.util.ArrayList<String>"]
	sequence<string> Strings;

	//����Ĭ��ֵ
	struct RequestDefaultData
	{
		string	tableName;//��ѯ����
		
		//���fieldNameΪ��,��ʾ��������(rid)��ѯ,fieldValueֵΪ����ֵ
		//������fieldName�ǿ�,��ʾ��ѯ��fieldNameֵΪ����,ֵΪfieldValue�ļ�¼
		string 	fieldName;//ָ������
		string	fieldValue;//ָ���в�ѯ����ֵ
	};
	["java:type:java.util.ArrayList<RequestDefaultData>"]
	sequence<RequestDefaultData> RequestDefaultDataSequence;
	
	struct RequestDefaultDataSeq
	{
		long		id;
		long		requestId; //������
		string 		requestNode;	//����ڵ�

		bool		isStop; //�Ƿ�ֹͣ����������,ice�ӿں��Ը���
		int			refreshFreq; //ˢ��Ƶ��,0��ʾֻһ������,ice�ӿں��Ը���
	
		long		dataCount; //�������еĸ���
		RequestDefaultDataSequence	seq;
	};
	
	
	//����ָ����
	struct RequestSpecficData
	{
		string	tableName;//��ѯ����
		Strings	fieldSeq;//����ָ������
		
		string 	fieldName;//ָ������
		string	fieldValue;//ָ���в�ѯ����ֵ
	};
	["java:type:java.util.ArrayList<RequestSpecficData>"]
	sequence<RequestSpecficData> RequestSpecficDataSequence;
	
	struct RequestSpecficDataSeq
	{
		long		id;
		long		requestId; //������
		string 		requestNode;	//����ڵ�

		bool		isStop; //�Ƿ�ֹͣ����������,ice�ӿں��Ը���
		int			refreshFreq; //ˢ��Ƶ��,0��ʾֻһ������,ice�ӿں��Ը���
	
		long		dataCount; //�������еĸ���
		RequestSpecficDataSequence	seq;
	};
	
	
	//����ȫ��
	struct RequestCompleteData
	{
		string	tableName;//��ѯ����
		
		string 	fieldName;//ָ������
		string	fieldValue;//ָ���в�ѯ����ֵ
	};
	["java:type:java.util.ArrayList<RequestCompleteData>"]
	sequence<RequestCompleteData> RequestCompleteDataSequence;
	
	struct RequestCompleteDataSeq
	{
		long		id;     
		long		requestId; //������
		string 		requestNode;	//����ڵ�

		bool		isStop; //�Ƿ�ֹͣ����������,ice�ӿں��Ը���
		int			refreshFreq; //ˢ��Ƶ��,0��ʾֻһ������,ice�ӿں��Ը���
	
		long		dataCount; //�������еĸ���
		RequestCompleteDataSequence	seq;
	};
	
	//����"����Ĭ��ֵ"�Ľ��
	struct RespondDefaultData
	{
		string	tableName;//��ѯ����
		
		string	dataRid;//���� rid
		string	dataValue;//Ĭ����ֵ
	};
	["java:type:java.util.ArrayList<RespondDefaultData>"]
	sequence<RespondDefaultData> RespondDefaultDataSequence;
	
	struct RespondDefaultDataSeq
	{
		long		id;   //
		long		requestId; //������
		string 		requestNode;	//����ڵ�

		long		dataCount; //�������еĸ���
		RespondDefaultDataSequence	seq;//��������
	};
	
	
	//����"����ָ����"�Ľ��
	struct RespondSpecficData
	{
		string	tableName;//��ѯ����
		Strings	fieldSeq;//����ָ��������
		
		string	dataRid;//���� rid
		Strings	dataValues;//ָ���е�ֵ����
	};
	["java:type:java.util.ArrayList<RespondSpecficData>"]
	sequence<RespondSpecficData> RespondSpecficDataSequence;
	
	struct RespondSpecficDataSeq
	{
		long		id;
		long		requestId; //������
		string 		requestNode;	//����ڵ�

		long		dataCount; //�������еĸ���
		RespondSpecficDataSequence	seq;//��������
	};
	
	
	//����"����ȫ��"�Ľ��
	struct RespondCompleteData
	{
		string	tableName;//��ѯ����
		
		string	dataRid;//���� rid
		Strings	dataValues;//ȫ�е�ֵ����
	};
	["java:type:java.util.ArrayList<RespondCompleteData>"]
	sequence<RespondCompleteData> RespondCompleteDataSequence;
	
	struct RespondCompleteDataSeq
	{
		long		id;
		long		requestId; //������
		string 		requestNode;	//����ڵ�

		long		dataCount; //�������еĸ���
		RespondCompleteDataSequence	seq;//��������
	};
	
	//���ز�ѯ�������¼�ĸ���
	struct RespondDataCount
	{
		string	tableName;//��ѯ����
		
		//���fieldNameΪ��,��ʾ��������(rid)��ѯ,fieldValueֵΪ����ֵ
		//������fieldName�ǿ�,��ʾ��ѯ��fieldNameֵΪ����,ֵΪfieldValue�ļ�¼
		string 	fieldName;//ָ������
		string	fieldValue;//ָ���в�ѯ����ֵ
		int 	dataCount;//�������¼�ĸ���
	};
	["java:type:java.util.ArrayList<RespondDataCount>"]
	sequence<RespondDataCount> RespondDataCountSequence;
	
	//��ѯ�豸�����б�ʱ���صĽṹ
	struct EquipTree
	{
		string parentRid;//���豸RID
		string parentName;//���豸����
		string parentType;//���豸����
		
		string equipRid;//�豸RID
		string equipName;//�豸����
		string equipType;//�豸����
	};
	["java:type:java.util.ArrayList<EquipTree>"]
	sequence<EquipTree> EquipTreeSequence;
	
	//�豸������·��վ��Ϣ
	struct LineAndStationInfo
	{
		string lineRid;
		string lineName;
		string linePath;
		
		string stationRid;
		string stationName;
		string stationPath;
	};
	
	//�����������ݵ���Ϣ
	struct  RequestTopoDataSeq 
	{
		long	id;
		long	requestId;   //������
		string 	requestNode;	//����ڵ�

		bool	isStop; //�Ƿ�ֹͣ���������󣬶���Ice�ӿڴ��ֶοɲ���
		int		refreshFreq; //ˢ��Ƶ�ʣ�ˢ��Ƶ��Ϊ����ζ������ICEStorm��һ��������
		Strings	ridSeq;//��Ҫ��ѯ�����ӵ�ID
	};
	
	//�������ݽṹ
	struct ConNodeState//���ӵ����״̬
	{
		string	rid;//���ӵ��      ���ӵ�ID�������豸Id
		byte	state;//����״̬��0-ʧ�� ��1-����
	};
	
	["java:type:java.util.ArrayList<ConNodeState>"]
	sequence<ConNodeState>  ConNodeStateSeq;

	struct  ReceiveTopoDataSeq 
	{
		long	id;
		long    requestId;   //������
		string 	requestNode;	//����ڵ�
		ConNodeStateSeq cnStateSeq;
 	};
 	
 	//��Դ������ķ�0ң����Ϣ
	struct PowerAnalogInfo
	{
		string analogRID;
		string analogName;
		double analogValue;
	};
	["java:type:java.util.ArrayList<PowerAnalogInfo>"]
	sequence<PowerAnalogInfo> PowerAnalogInfoSeq;
	
	//��Դ����Ϣ
	struct PowerInfo
	{
		string powerType;
		string powerRID;
		string powerName;
		
		PowerAnalogInfoSeq analogInfoes;
	};
	["java:type:java.util.ArrayList<PowerInfo>"]
	sequence<PowerInfo> PowerInfoSeq;
	
	//�˵���Ϣ
	struct TerminalInfo
	{
		string termRID;
		string deviceType;
		string deviceRID;
		string deviceName;
	};
	["java:type:java.util.ArrayList<TerminalInfo>"]
	sequence<TerminalInfo> TerminalInfoSeq;
	
	//���ӵ���Ϣ
	struct ConnectivityNodeInfo
	{
		string nodeRID;
		TerminalInfoSeq terminalInfoes;
	};
	["java:type:java.util.ArrayList<ConnectivityNodeInfo>"]
	sequence<ConnectivityNodeInfo> ConnectivityNodeInfoSeq;
	
	
	//���˵���Ϣ
	struct TopoIslandInfo
	{
		int islandID; 
		ConnectivityNodeInfoSeq nodeInfoes;
		PowerInfoSeq powerInfoes;
		bool powerStatus;
	};
	["java:type:java.util.ArrayList<TopoIslandInfo>"]
	sequence<TopoIslandInfo> TopoIslandInfoSeq;

	//����ʵʱ���ݽӿ�
	const string strRealRequestTopic = "rdb_real_request";
	interface RdbRealDataRequest
	{
		void RequestDefaultData(RequestDefaultDataSeq  seq); //����Ĭ������
		void RequestSpecificData(RequestSpecficDataSeq  seq);	//����ָ������
		void RequestCompleteData(RequestCompleteDataSeq  seq);	//����ȫ����
		void SendTopoDataRequest (RequestTopoDataSeq  seq); //������������
	};

	//��Ӧʵʱ���ݽӿ�
	const string strRealRespondTopic = "rdb_real_respond";
	interface RdbRealDataRespond
	{
		void RespondDefaultData (RespondDefaultDataSeq  seq); //��ӦĬ������
		void RespondSpecificData(RespondSpecficDataSeq  seq);	//��Ӧָ������
		void RespondCompleteData(RespondCompleteDataSeq  seq);	//��Ӧȫ����
		void SendTopoDataRespond (ReceiveTopoDataSeq  seq );//��Ӧ��������
	};

	//ʵʱ��ICE�ӿڶ���
	interface RdbDataOpt
	{
		//��������,errorSeqΪ����ʧ�ܵ�����
		//˵��:insertʱ�������������е�ֵ
		bool InsertData(RespondCompleteDataSeq dataSeq,out RespondCompleteDataSequence errorSeq);

		//��ѯ����
		bool SelectDefaultData(RequestDefaultDataSeq reqSeq,out RespondDefaultDataSeq repSeq);
		bool SelectSpecificData(RequestSpecficDataSeq reqSeq, out RespondSpecficDataSeq repSeq);
		bool SelectCompleteData(RequestCompleteDataSeq reqSeq, out RespondCompleteDataSeq repSeq);
		
		//��ѯ������ĸ���
		bool  SelectDataCount(RequestDefaultDataSeq reqSeq,out RespondDataCountSequence repSeq);

		//��������,errorSeqΪ����ʧ�ܵ�����
		bool UpdateCompleteData(RespondCompleteDataSeq reqSeq, out RespondCompleteDataSequence repSeq);

		//ɾ������,errorSeqΪ����ʧ�ܵ�����
		bool DeleteRdbData(RequestDefaultDataSeq dataSeq,out RequestDefaultDataSequence errorSeq);
		
		//��ѯ�豸�����б�
		bool GetEquipTree(string deviceType,string deviceRid,out EquipTreeSequence treeSeq);

		//��ѯָ���������豸�����б�
		bool GetSpecificEquipTree(string deviceType,string deviceRid,string specDeviceType,out EquipTreeSequence treeSeq);
		
		//����豸�����ı��վ����·
		bool GetEquipLineAndStationInfo(string deviceType,string deviceRid,out LineAndStationInfo info);
		
		//�ж�ָ��cimģ�ͼ�¼ �Ƿ�Ϊ�¶��ڵ�
		bool isOrphanNode(string dataType,string dataRid);
		
		//�ж�ָ��cimģ�ͼ�¼�Ƿ�Ϊ�սڵ�
		bool isEmptyNode(string dataType,string dataRid);
		
		//�жϸ�����¼�Ƿ�Ϊ�Ƿ�����
		bool IsInvalidDbData(string tableName,string dataRID);
		
		//������˽ṹ
		bool GetTopoData(RequestTopoDataSeq  inDataSeq,out ReceiveTopoDataSeq  outDataSeq);
		
		//��õ�ǰ���˵���Ϣ
		void GetTopoIslandInfo(out TopoIslandInfoSeq  islandInfoes);
		
		//ˢ�����˽ṹ
		void UpdateTopoData();

		//��ȡ��������
		bool GetSectionData(string deviceRid, out double analogValue, out int discreteValue);

	};
};

//�澯����
module RdbWarningData
{
	enum RdbWarningLevel {Critical,Major,Minor,Info};//�澯�ȼ�
	
	//LimitEvent Խ��, SoeEvent SOE, YxEvent ң�ű�λ, UnitEvent �ն�״̬, SysEvent ϵͳ����, OperEvent ��������, 
	//RelayEvent ��������, FaultEvent ��������, FaEvent FA�澯, GraphEvent ��������, RfwEvent¼������,AllEvent���и澯����(�ͻ��˲�ѯʱ��)
	enum RdbWarningType {LimitEvent,SoeEvent,YxEvent,UnitEvent,SysEvent,OperEvent,RelayEvent,FaultEvent,FaEvent,WaveEvent,GraphEvent, RfwEvent, AllEvent};//�澯����

	["java:type:java.util.ArrayList<String>"]
	sequence<string> Strings;

	//�������ݽṹ�Ķ���
	struct  WarningInfo
	{
		string				id; //m_id��ʶ��
		RdbWarningType	warnType; //�澯���ͣ�����Ϊö���ͣ�
		long			timeStamp; //�澯ʱ�䣬�Ժ����ʾ
		RdbWarningLevel	warningLevel; //�澯�ȼ�
		string			warnSource;// �澯Դ
		
		int				columnNum; //�澯�����ֶθ���
		Strings			contents;//�澯����
	};
	
	["java:type:java.util.ArrayList<WarningInfo>"]
	sequence< WarningInfo >  WarningInfoSeq;

	//�������ݽӿڶ���
	const string strAlarmDataTopic = "rdb_warning_data";
	interface RdbAlarmData
	{
		void SendAlarmData(WarningInfoSeq seq );
	};
};


#endif  // _REAL_DB_DATA_ICE

