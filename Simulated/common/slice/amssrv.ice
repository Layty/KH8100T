
/*
* Copyright (c) 2010,GridNT,Inc*All rights reserved.
*
* �ļ����ƣ�amssrv.ice* ժҪ��AMS Manager ice�ļ�
*/


#ifndef AMSSRV_ICE
#define AMSSRV_ICE

#include "aml.ice"

[["java:package:com.kh.ams"]] 
module Amssrv{
	["java:type:java.util.ArrayList<String>"]sequence<string> Strings;
	/**
	 *
	 * AMS�쳣
	 *
	 **/
	exception CAmsException
	{
		/**
		*
		*�쳣ԭ��
		*
		**/
	    string reason;
	};
	
	//�ڵ���Ϣ
	struct ServerNode
	{
		string name;//�ڵ�����
		int type;//�ڵ�����
		string ip;//ip
		int port;//�˿�
		string partitionId;//����id
		string partitionName;//��������
		string sectionId;//�ֶ�id
		string sectionName;//�ֶ�����
		string preRole;//Ԥ����ɫ
	};
	
	
	/**
	 *
	 * AMS Manager�Լ��ӿ�
	 *
	 **/
	interface CAmsManager
	{ 	    	    
	    /**
	     *
	     * AMS Managerע��
	     *
	     **/
	    void Register(string strServerName, string strRole) throws CAmsException;
	    
	    //�˳�
	    void Quit();
	    
	    //��������
	    void AmsHeartBeat(string strServerName);
	};
	
	
	/**
	 *
	 * AMS Manager����ӿ�
	 *
	 **/
	interface CAmsApp
	{ 	    	    
	    /**
	     *
	     * Ԥ��ע�ᣬ�õ�Ԥ����ɫ
	     *
	     * @parameter strType:�ڵ�����
	     * @parameter ipVect:ע��ڵ��ip�б�
	     * @parameter num:ע�����
	     * @parameter ServerNode:���ؽڵ����Ϣ
	     * @return Ԥ����ɫ(unknow/master/slave)
	     * @throws CAmsException:δ֪�쳣
	     *
	     **/
	    string Register(string strType, Strings ipVect, int num, out ServerNode serverInfo)throws CAmsException;
	    
	    /**
	     *
	     * ���ע��
	     *
	     * @parameter strServerName:Server����
	     * @parameter strRole:ȷ�Ͻ�ɫ
	     * @parameter district:����
	     * @parameter section:�ֶ�
	     * @parameter districtName:��������
	     * @parameter sectionName:�ֶ����� 
	     * @return void
	     * @throws CAmsException:δ֪�쳣
	     *
	     **/
	    void FinishRegister(string strServerName, string strRole, string district, string section)throws CAmsException;
	    
	    /**
	     *
	     * �˳�
	     *
	     * @parameter serverInfo:Server��Ϣ
	     * @return void
	     *
	     **/
	    void Quit(ServerNode serverInfo);
	    
	    /**
	     *
	     * ��ѯָ��Server���ƵĽ�ɫ
	     *
	     * @return string:���ؽ�ɫֵ,master������,slave����ӣ�unknow����δ֪
	     * @throws Exception:����ԭ��
	     *
	     **/
	    ["cpp:const","nonmutating"] string GetRole(string strServerName)throws CAmsException;
	    
	    
	    //��������
	    void HeartBeat(string strServerName);
	};
};

#endif
