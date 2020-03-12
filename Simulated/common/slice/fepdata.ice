/* **************************************************
* Copyright(c) 2010, KHDQ,Inc. All rights reserved.
*
* File��FepData.ice
* 
* ǰ�������ݷ��������ݽ�����slice�ӿڶ����ļ���
*****************************************************/ 

#ifndef _FEP_DATA_ICESTORM
#define _FEP_DATA_ICESTORM

module FepData {
    
    // ң��״̬  
    enum DiscreteValue {
        Open,     // 0-��բ
        Close,    // 1-��բ
		DblOpen,  // 2-˫��
		DblClose, // 3-˫��
        Unknown   // 4-δ֪״̬
    };
    
    // �仯ң��
    struct ChangedAnalog {
        long     timeStamp;  // ʱ��
        short    unitNo;     // �ն˱��
        short    index;      // ���
        int      value;      // ֵ
    };    
    
    // �ն�״ֵ̬
    enum State {
        NotInstall,    // 0-δ��װ����ͨ��������ʱ��Ĭ��ֵ
        OffLine,       // 1-���ߣ�ϵͳ��ʼ��ʱ�ն�/ͨ����Ĭ��ֵ
        New,           // 2-Ͷ�ˣ��ն˳���Ͷ��
        Run,           // 3-����
        Stop,          // 4-�˳����ն�/ͨ�����к����˳�
        HighErrorRate  // 5-�����ʸ�
    };
    
    // �ն�/ͨ��״̬��������
    struct Unit {
        short    unitNo;          // �ն˱��
        State    unitState;       // ��Ԫ״̬�����ߡ����С��˳�
        State    channelState1;   // ��ͨ��״̬
        State    channelState2;   // ��ͨ��״̬
        byte     errorRate;       // �����ʣ�0~100������С��
    };
    
    /**
    * �������ͣ�
    *   AllDataType - unitNo��analogs��discretes��accmulators��Ч��
    *   ChangedAnalogType - changedAnalogs��Ч��
    *   AccumulatorType - unitNo��accmulators��Ч��
    *   UnitStateType - units��Ч��
    */
    enum DataType {
        AllDataType,        // 0-ȫ����
        ChangedAnalogType,  // 1-�仯ң��
        AccumulatorType,    // 2-���
        UnitStateType       // 3-�ն�״̬
    };
    
    sequence<Unit>  UnitSeq;        // �ն�״̬
    sequence<int>   AnalogSeq;      // ң��
    sequence<int>  DiscreteSeq;    // ң��
    sequence<int>   AccmulatorSeq;  // ���
    sequence<ChangedAnalog> ChangedAnalogSeq;  // �仯ң��
    struct DataPacket {
        byte        id;       // ���ݰ�ID
        string        fepNode;  // ����ǰ�û�    
        DataType    type;     // ��������
        short       unitNo;   // ��Ԫ��
        UnitSeq             units;           // �ն�״̬
        AnalogSeq           analogs;         // ң��
        DiscreteSeq         discretes;       // ң��
        AccmulatorSeq       accmulators;     // ���
        ChangedAnalogSeq    changedAnalogs;  // �仯ң��
    };
    
    // �����������FA��С�����ӵع���
    sequence<short>   FaultValueSeq;
    struct FaultEvent {
	    short    unitNo;         // ��Ԫ���
	    long     timeStamp;      // ʱ��
	    short    source;         // ����Դ
	    short    eventType;      // �������͡�0-��·��1-�ӵأ�2-ѡ�ߣ�3-���Ͻ���
	    short    directionFlag;  // ����ϵ����־��0-��Ч��1-��Ч
        short    faultType;      // ��������
	    short    lineNo;         // ������·��
	    short    duration;       // ����ʱ�䡣��·-���룻�ӵ�-��
	    short    direction;      // ���Ϸ���0x000F=����0x00F0=����
	    short    distance;       // ���Ͼ��롣��λ��KM
	    short    directionMultiplier;  // ����ϵ��
	    short    credibility;          // ���Ŷ�
	    short    v0Amp;                // �����ѹ��ֵ
	    short    waveType;             // ��������
	    FaultValueSeq    values;
    };

    // �����������ݰ�
    sequence<FaultEvent>  FaultEvents;
    struct FaultPacket {
         byte         id;       // ���ݰ�ID
         string         fepNode;  // ����ǰ�û�    
         FaultEvents  events;   // ��������
    };
    
    // ң�ű�λ
    struct ChangedDigital
    {
        short            unitNo;     // �ն˱��
        short            index;      // ң�ŵ��
        DiscreteValue    value;      // ң��ֵ
        long             timeStamp;  // ʱ��
    };
    
    /**
    * SOE
    * Soe��ʽ����ң�ű�λ��ȫһ����ֻ����time���ն��ϱ���
    */
    struct Soe
    {
        short            unitNo;     // �ն˱��
        short            index;      // ң�ŵ��
        DiscreteValue    value;      // ң��ֵ
        long             timeStamp;  // ʱ��
    };
    
    enum ProEventType
    {
        ProtectAction,  // 0-��������
        ProtectAlarm    // 1-�������ź�
    };
    
    struct ProValue
    {
        short index;
        double value;
    };
    
    sequence<ProValue> ProValues;
    
    // ��������
    struct ProtectEvent {
       short         unitNo;     // �ն˱�� 
       ProEventType  Type;       // ����
       long          timeStamp;  // ʱ��
       short         moduleNo;   // ģ���� 
       short         moduleType; // ģ������ 
       short         infoNo;     // ��Ϣ���
       short         state;      // 1-������0-����
       ProValues     values;     // ����ֵ
     };
     
     // �仯���ն�״̬
     struct ChangedUnit {
        short    unitNo;          // �ն˱��
        State    unitState;       // �ն�״̬�����ߡ����С��˳�
        State    channelState1;   // ��ͨ��״̬
        State    channelState2;   // ��ͨ��״̬
        byte     errorRate;       // �����ʣ�0~100������С��
        long     timeStamp;       // ʱ��
     };
	 
	 enum ChannelEventType
    {
        ChannelSwitch,  // 0-ͨ���л�
        ChannelRun      // 1-ͨ��Ͷ���˳�
    };
	
	 // ͨ���������ͨ���л���ͨ��Ͷ���˳�
	 struct UnitChannel {
        short    			 unitNo;          // �ն˱��
        ChannelEventType	 type;			  // ����
		byte				 channelNo;		  // ԭʼͨ���ţ�	ͨ����
		byte				 channelState;	  // �л���ͨ���ţ�	ͨ��״̬��Ͷ��or�˳���
		long     			 timeStamp;       // ʱ��
     };
    
    // ��������
    enum EventType {
        YxType,     // 0-ң�ű�λ
        SoeType,    // 1-SOE
        UnitType,   // 2-�ն�״̬
        ProType,    // 3-��������
		ChannelType	// 4-ͨ������
    }; 
    
    sequence<ChangedDigital> ChangedDigitalSeq;
    sequence<Soe> SoeSeq;
    sequence<ProtectEvent> ProtectEventSeq;
    sequence<ChangedUnit> ChangedUnitSeq;
	sequence<UnitChannel> ChangedUnitChannelSeq;

    // �������ݰ�
    struct EventPacket {
        int       id;          // ��ʶ��
        string      fepNode;     // ����ǰ�û�
        EventType type;        // �澯����
        ChangedDigitalSeq digitals;  // ң�ű�λ����
        SoeSeq   soes;               // SOE����
        ProtectEventSeq  protects;   // ������������
        ChangedUnitSeq   units;      // �仯���ն�����
		ChangedUnitChannelSeq	channels; // ͨ����������
    };
	
	  sequence<short>   WaveValueSeq;
    struct WaveEvent {
	    short    unitNo;         // ��Ԫ���
	    long     timeStamp;      // ʱ��
	    short    source;         // ����Դ
	    short    eventType;      // �������͡�0-��·��1-�ӵأ�2-ѡ�ߣ�3-���Ͻ���
	    short    directionFlag;  // ����ϵ����־��0-��Ч��1-��Ч
        short    faultType;      // ��������
	    short    lineNo;         // ������·��
	    short    duration;       // ����ʱ�䡣��·-���룻�ӵ�-��
	    short    direction;      // ���Ϸ���0x000F=����0x00F0=����
	    short    distance;       // ���Ͼ��롣��λ��KM
	    short    directionMultiplier;  // ����ϵ��
	    short    credibility;          // ���Ŷ�
	    short    v0Amp;                // �����ѹ��ֵ
	    short    waveType;             // ��������
	    WaveValueSeq    values;
    };

    // �����������ݰ�
    sequence<WaveEvent>  WaveEvents;
	//��ӱ����������¼���������ݰ�	
	struct WavePacket {
         byte         id;       // ���ݰ�ID
         string       fepNode;  // ����ǰ�û�    
         WaveEvents  events;   // ��������
    };
    
    // ǰ�����ݺ�����ӿڶ���
    const string strDataTopic = "fep_data_event";
    interface FepDataManager {
        void processData(DataPacket aDataPacket);     // ʵʱ����
        void processFault(FaultPacket aFaultPacket);  // ����
        void processEvent(EventPacket aEventPacket);  // ͨ������
		void processWave(WavePacket aWavePacket);  // ����¼������ 
    };  
    
};

#endif  // _FEP_DATA_ICESTORM