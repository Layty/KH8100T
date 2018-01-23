/* **************************************************
* Copyright(c) 2011-, JNKH. All rights reserved.
*
* File��transtrendfile.ice
* 
*****************************************************/ 
 
#ifndef _TRANSTRENDFILE_ICE
#define _TRANSTRENDFILE_ICE
 
[["java:package:com.gridnt.transtrendfile"]]
/**
* 
* �������������ļ�
* 
*/
module TransferTrendFile
{ 
	// �������ݰ�(ֻ��һ�������ļ���һ�δ�һ����
	sequence<byte> Bytes;	
	struct TrendPacket 
	{
        byte         id;       // ���ݰ�ID
        string       fepNode;  // ����ǰ�û� 
		string       filename;  // ���������ļ���
		int			 filelength;//���������ļ�����
		Bytes        datas;//��������
    };
    
    
    /**
    * �������У�Unit->FEP->WKS����FEPΪpublisher
    * ��ʵ�ֽӿ�TrendAppManager��
    */
    const string TrendAppTopic = "trend_app_operation"; 
    interface TrendAppManager
    {
        void processTrendFile(TrendPacket aTrendPacket);  // �����ļ����� 
    };
	
	/**
    * �������У�WKS->FEP����FEPΪsubscriber
    * TrendFepManager
    */
    const string TrendFepTopic = "trend_fep_operation";
    interface TrendFepManager
    {
        /**
        * @param: filename - ���������ļ���
        */
       void trendExecute( string filename );
    };
};
 
#endif //_TRANSTRENDFILE_ICE