
/*
* Copyright (c) 2010,GridNT,Inc*All rights reserved.
*
* �ļ����ƣ�aml.ice* ժҪ��Ӧ�ù���ӿ�ice�ļ�
*/


#ifndef AML_ICE
#define AML_ICE


[["java:package:com.kh.framework"]] 
module Aml{
	/**
	 *
	 * AML�쳣
	 *
	 **/
	exception CAmlException
	{
		/**
		*
		*�쳣ԭ��
		*
		**/
	    string reason;
	};
	
	
	
	/**
	 *
	 * ��վ��Server�Ľ�ɫ�ӿ�
	 *
	 **/
	interface CAmlRole
	{   
	    
	    /**
	     *
	     * ��ѯ��ǰServer�Ľ�ɫ
	     *
	     * @return string:���ؽ�ɫֵ,master������,slave�����
	     * @throws AmlException:����ԭ��
	     *
	     **/
	    ["cpp:const","nonmutating"] string GetRole()throws CAmlException;
	    
	    /**
	     *
	     * ��ѯǰ�û���ǰServer�Ľ�ɫ
	     *
	     * @return string:���ؽ�ɫֵ,master������,slave�����
	     * @throws AmlException:����ԭ��
	     *
	     **/
	    ["cpp:const","nonmutating"] string GetFepRole(out string strPart, out string strSec)throws CAmlException;
	    
	    /**
	     *
	     * ���õ�ǰServer�Ľ�ɫ
	     *
	     * @parameter role:��ɫֵ,master������,slave�����
	     * @return void
	     * @throws AmlException:����ԭ��
	     *
	     **/
	    void SetRole(string role)throws CAmlException;
	    
	    /**
	     *
	     * ���õ�ǰServer�Ľ�ɫ�����ò���
	     *
	     * @parameter role:��ɫֵ,master������,slave�����
	     * @parameter strDistrict��strSection��strDistrictName��strSectionName:�����ֶ���Ϣ
	     * @return void
	     * @throws AmlException:����ԭ��
	     *
	     **/
	    void SetConfig(string role, string strDistrict, string strSection, string strDistrictName, string strSectionName, string isXbfep)throws CAmlException;
	};
};

#endif
