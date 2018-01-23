#ifndef _FEP_RFW_ICESTORM
#define _FEP_RFW_ICESTORM
[["java:package:com.kh.scada"]] 
module wavefepapp
{
	enum RFWTYPE
	{
		RFWKHP = 0,			//������Ԫ¼��
		RFWKHSM = 1,			//�źŵ�Դ¼��
		RFWKHROD = 2,			//�źŵ�Դ�澯
		RFWKHHAVERFW = 3,		//��¼�����ݣ���Ҫ�ֹ���ȡ
		RFWKHRFWDIR = 4        //¼���ļ�Ŀ¼(zhanxg add 2008.9.3 for BJTG101)
	};
		
	struct SRFWSOE
	{
		long     		TimeStamp; //ʱ��
		short			yxNo;			 //ң�ź�
		short			value;		//ң��ֵ
	};
	sequence<SRFWSOE> SRFWSOESeq;
	
	struct SRFWHead
	{
		int			UnitNo;		//
		RFWTYPE	Type;		//¼������
		int			FaultType;	//�������ͣ�FRD��ROD.//mao 2004.6.3
		long		Time;		//ʱ�䣬PTU&STU
		int			Period;		//����ʱ�䣿����PTU
		int			Source;		//ID�ţ�PTU&STU
		int			Reason;		//�𶯷�ʽ��PTU
		int			Distance;	//���룬PTU
		int			ValueCount;	//��ĸ�����PTUӦ��Ϊ14400����STUΪ12��160=1920�� 
		int         IRate;      //���������̶�
		int         U1Rate;     //��һ·��ѹ�����̶�
		int         U2Rate;     //�ڶ�·��ѹ�����̶�
		int         SampeRate;  //ÿ�ܲ��Ĳ�������
		int         ChannelNum; //ͨ����
		int         DotNumBeforeFault;     //����ǰ����
		int         DotNumAfterFault;      //���Ϻ����
		SRFWSOESeq	soes; //�ƻ㱣�����Ա���12��Soe����
	};

	sequence<int>   SRFWDataSeq;
 struct SUnitRFW
	{
		SRFWHead    Head;
		SRFWDataSeq	Data; //8000T��������20000��int
	} ;

	
	// �������ݰ�(ֻ��һ�������ļ���һ�δ�һ����
	struct RFWPacket 
	{
         byte         id;       // ���ݰ�ID
         string       fepNode;  // ����ǰ�û�  
	 SUnitRFW     frw;
    };

    enum RfwOperateType // ��������
    {
			DUGRFWDIR,// ��ȡ¼��_Ŀ¼
			DUGRFWFIL,// ��ȡ¼��_�ļ�
			MANURFW // �˹�¼��
    };
    struct RfwOperate
    {
    	short 					unitno;
		short					lineno;
    	RfwOperateType  		operateType;
		short					filename;
    	int    					requestId;
    };
	
    struct RfwDir
	{
		short					lineno;
		short					filename;
		short 					filelength;
		short					filestate;
		long					filetime;
	};
	sequence<RfwDir>   SRFWDir;
	
	struct	RFWDirPacket
	{
		byte		id;	// ���ݰ�ID
		string      fepNode;  // ����ǰ�û� 
		short		unitno;	  
		SRFWDir		rfwDir;
	};
	
    /**
    * �������У�WKS->AppSrv->FEP->Unit����AppSrvΪpublisher��FEPΪsubscriber
    * RfwFepManager
    */
    const string RfwFepTopic = "rfw_fep_operation";
    interface RfwFepManager
    {
        /**
        * @param: unitno - �ն˺š�
        * @param: operateType - �������͡�
        */
       void rfwExecute( RfwOperate operate );
    };
    
    /**
    * �������У�Unit->FEP->AppSrv->WKS����FEPΪpublisher��AppSrvΪsubscriber
    * ��ʵ�ֽӿ�RfwAppManager��
    */
    const string RfwAppTopic = "rfw_app_operation"; 
    interface RfwAppManager
    {
         /**
        * @param: unitno - �ն˺š�
        * @param: operateType - �������͡�
        * @param: tip - flag=true��tip=""��flag=false��tip��ʾ����ԭ��
        */
        void rfwExecuteEcho(RfwOperate operate ,bool flag ,string tip);
		
        void processRfwDir(RFWDirPacket aRfwDirPacket);//¼���ļ�Ŀ¼
        void processRFW(RFWPacket aRFWPacket);  // ¼������ 
    };
    
    //ʵ�ֽ��չ���վ¼�����󣬲���������
    sequence<string>   FileDirSeq;
    sequence<byte>   	 ByteSeq;
    interface clientManager
    {
    	/*
    	*����ʱ��������ļ��б�
    	*@param unitNo:��Ԫ��
    	*@param startDate,endDate��������ʼ������ʱ��
    	*@param fileList:�����ļ��б�
    	* ����ֵ true���ɹ�,false��ʧ��
    	*/
    	bool getFileDirList(int unitNo, string startDate, string endDate, out FileDirSeq fileList);
    	
    	/*
    	*�����ļ��������ļ�����
    	*@param strFileName���ļ�����
    	*@param strInf, strcfg, rfwDatas:�ֱ�Ϊcomtrade�ļ���inf��cfg��dat�ļ�
    	* ����ֵ true���ɹ�,false��ʧ��
    	*/
    	bool getFileCont(int unitNo, string strFileName, out string strInf, out string strCfg, out ByteSeq rfwDatas);
   	};
};

#endif