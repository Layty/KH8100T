/* **************************************************
* Copyright(c) 2011-, JNKH. All rights reserved.
*
* File��translogger.ice
* 
*****************************************************/ 
 
#ifndef _TRANSLOGGER_ICE
#define _TRANSLOGGER_ICE
 
[["java:package:com.gridnt.translogger"]]
/**
* 
* ����ʵʱ����־�ļ�
* 
*/
module TransferRdbLogger
{ 
    sequence<byte> Bytes;
    
    const string TransferRdbLoggerTopic = "transaction_logger";  // ����
    interface TransferRdbLoggerInfo
    {
        void transferRdbLoggerBinary(string title, Bytes datas);

        // �ļ��������
        void transferFinished(string title);

        // ʵʱ��ͬ����������
        void syncRdbFinished();
    };
};
 
#endif 