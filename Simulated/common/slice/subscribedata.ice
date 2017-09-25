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
 
    const string SubscribeDataTopic = "subscribe_data";  // ����
    interface SubscribeDataInfo
    {
        void procSub(DataInfo data);
    };
};
 
#endif 