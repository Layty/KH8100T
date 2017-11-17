/* **************************************************
* Copyright(c) 2011-, KHDQ, inc. All rights reserved.
*
* File��yk.ice
* ң�ز���slice�ӿڶ����ļ���
*
*****************************************************/ 

#ifndef _FEP_YK_ICESTORM
#define _FEP_YK_ICESTORM

[["java:package:com.gridnt.icestorm"]]

module Yk
{
    enum YkValue
    {
        Open,  // ��բ  
        Close  // ��բ
    };

    /**
    *  1. AppSrv����Select��Execute��Cancel��FEP��FEP��ʱ��Ӧ�Ƿ���ȷ�������
    *  2. FEP��������ĸ�Unitʱ����Echo֪ͨAppSrv��
    *  3. FEP���յ�Unit��У���ģ���Return֪ͨAppSrv��
    */
    enum YkStep  // ң�ز���
    {
	    Select,         // ѡ��
	    FepRecvSelect,  // ǰ��ѡ��ȷ��
	    SelectReturn,   // �ն�ѡ��У
	    Execute,        // ִ��
	    FepRecvExecute, // ǰ��ִ��ȷ�� 
	    ExecuteReturn,  // �ն�ִ�з�У
	    Cancel,         // ����
	    FepRecvCancel,  // ǰ�ó���ȷ������
	    CancelReturn    // ������У
    };

    enum YkType  // ң������
    {
        SelectBeforeOperate,  // ѡ��
        DirectlyOperate       // ֱ��
    };

    /**
    * ����Ա�ڵ���Ա����վ��ִ��һ�����(ѡ��/ִ��/����)��Ӧ�÷�����
    * ��������ת��ǰ�û���ǰ�û��ٽ�����͸��նˡ�
    */
    struct YkCommand  // ң������
    {
        YkStep    step;     // ֱ��ʱ��step = Execute
        YkType    type;          
	    int    requestId;
        string    rID;      // ����rID
        short     unitNo;   // �ն˱��
        short     ykNo;     // ң�غ�
        short     yxIndex;  // ң�ŵ��
	    YkValue   value;    // ң��ֵ
    };
    /**
	*ң����˷�����ܻ�
	*/
	struct YkRequestMsg
	{
	    int    requestId;
	    short    unitNo;
	    YkStep   step;     // ֱ��ʱ��step = Execute
	    string   breakerRid;   
	    short    breakerControlID;
	    YkValue  breakerNormalValue;
	    string    oper; //����Ա
	    bool   isAgree;     
		string  yxType;
	};
	/**
	*�˻����淢���������
	*
	*/
	const string YkMmiTopic = "yk_mmi_operation";
	interface YkMmiManager
	{
	   void sendYkRequest(YkRequestMsg msg);
	   void sendValidateRequest(YkRequestMsg msg);
	};
    /**
    * �������У�WKS->AppSrv->FEP->Unit����AppSrvΪpublisher��FEPΪsubscriber
    * ��ʵ�ֽӿ�YkFepManager��
    */
    const string YkFepTopic = "yk_fep_operation";
    interface YkFepManager
    {
        /**
        * @param: cmd - ң�����
        */
        void select(YkCommand cmd);   // ѡ��
        void execute(YkCommand cmd);  // ִ��
        void cancel(YkCommand cmd);   // ����
    };
    
    /**
    * �������У�Unit->FEP->AppSrv->WKS����FEPΪpublisher��AppSrvΪsubscriber
    * ��ʵ�ֽӿ�YkAppManager��
    */
    const string YkAppTopic = "yk_app_operation";
    interface YkAppManager
    {
        /**
        * @param: cmd - ң�����
        * @param: flag - true��ʾ����������false��ʾ�����쳣��
        * @param: tip - flag=true��tip=""��flag=false��tip��ʾ����ԭ��
        */
        void selectEcho(YkCommand cmd, bool flag, string tip);    // ѡ��ȷ��
        void selectReturn(YkCommand cmd, bool flag, string tip);  // ѡ��У
        void executeEcho(YkCommand cmd, bool flag, string tip);   // ִ��ȷ��
        void executeReturn(YkCommand cmd, bool flag, string tip); // ִ�з�У
        void cancelEcho(YkCommand cmd, bool flag, string tip);    // ����ȷ��
        void cancelReturn(YkCommand cmd, bool flag, string tip);  // ������У
    };
};

#endif  //  _FEP_YK_ICESTORM