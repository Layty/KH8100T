/* **************************************************
* Copyright(c) 2011-, JNKH. All rights reserved.
*
* File��realdbsync.ice
* 
*****************************************************/ 
 
#ifndef _REALDBSYNC_ICE
#define _REALDBSYNC_ICE
 
[["java:package:com.gridnt.realdbsync"]]
/**
* 
* ʵʱ��ͬ��
* 
*/
module RealdbSyncSpace
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


    interface RealdbSync
    {
       // ����ʵʱ��
       bool requestRealdb();

       // ����ʵʱ������
       FileContent requestRealdbContent(string fileName, long pos);
    };
};
 
#endif 