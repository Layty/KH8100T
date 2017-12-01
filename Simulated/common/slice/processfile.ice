/* **************************************************
* Copyright(c) 2011-, JNKH. All rights reserved.
*
* File��translogger.ice
* 
*****************************************************/ 
 
#ifndef _PROCESSFILE_ICE
#define _PROCESSFILE_ICE
 
[["java:package:com.gridnt.processfile"]]
/**
* 
* �����ļ�
* 
*/
module ProcessFile
{ 
    ["java:type:java.util.ArrayList<byte>"]   sequence<byte> Bytes;
    /**
    *
    *�ļ�����
    *
    **/
    struct FileContent
    {
        //��ȡ�ļ�λ��
        long pos;
        
        //����
        Bytes content;

        //�ļ�״̬
        bool status;
    };

    interface ProcessFileManager
    {
       // �����ļ�
       FileContent requestFile(string title, long pos);

       // �����ļ�
       bool sendFile(string title, Bytes datas);
    };
};
 
#endif 