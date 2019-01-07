/* **************************************************
* Copyright(c) 2011-, KHDQ, inc. All rights reserved.
*
* File��manualdata.ice
* �ֶ������в�����slice�ӿڶ����ļ���
*
*****************************************************/ 

#ifndef _FEP_MANUALDATA_ICESTORM
#define _FEP_MANUALDATA_ICESTORM

[["java:package:com.kh.icestorm"]]

module ManualData
{
    struct ManualTime
    {
        string year;
        string month;
        string day;
        string hour;
    };

    struct ManualMsg
    {
        string deviceId;
        string bz;//0:���� 1:��ǰ�������� 2������ʱ��� 3:����
        string day;
        ManualTime beginTime;
        ManualTime endTime;
    };
    sequence<ManualMsg> manualMsgSeq;

    struct ReceiveMsg
    {
        string requestId;
        string deviceId;
        string bz;//������־��0���� 1����
        string message;
    };
    sequence<ReceiveMsg> receiveMsgSeq;

    //ȡ���������ݶ���
    ["java:type:java.util.ArrayList<String>"] sequence<string> stringSeq;

    // �ļ���Ϣ
    struct ManualFile
    {
        string fileName;     // �ļ�����
        string fileSize;     // �ļ���С
        string fileTime;     // �ļ�ʱ��
        string fileResult;   // �����ʶ 0=������1=������2=ʧ��
    };

    // �ļ�������Ϣ
    struct ManualSegment
    {
        string fileName;     // �ļ�����
        string fileSegment;  // �Ѵ����С
		string fileCount;    // ֡����
		string fileData;     // �ļ���������
        string fileResult;   // �����ʶ 0=������1=������2=ʧ��
    };
    
    /**
    * �ֶ���ȡ����
    * ManualDataManager
    */
    const string ManualDataRequestTopic = "manualdata_operation_Request";
    const string ManualDataResponseTopic = "manualdata_operation_Response";
    interface ManualDataManagerRequest
    {
        // �����ٻ��ļ��б�����
        void send(string requestId, manualMsgSeq dataSeq);
        // ����ȡ���ٻ��ļ�����
        void cancalManual(string requestId, stringSeq deviceSeq);
        // ���������ļ��б�����
        void sendFileList(string requestId, string deviceId, stringSeq fileSeq);
    };

    interface ManualDataManagerResponse
    {
        // �����ļ����ؽ��
        void receive(receiveMsgSeq recSeq);
        // �����ļ��б�
        void receiveFileList(string requestId, string deviceId, ManualFile fileSeq);
        // �����ļ�������Ϣ
        void receiveSegment(string requestId, string deviceId, ManualSegment fileSegment);
    };
};

#endif  //  _FEP_MANUALDATA_ICESTORM