#include "workstationserverthread.h"
#include "BaseIceStorm.h"
#include "OperationInfo.h"
#include "RdbAlarmDataI.h"

#include <string>

using namespace std;

template<class T> string transferToString(const T& value);

void WorkStationServerThread::setCommunicatorPtr( Ice::CommunicatorPtr ptr )
{
	m_communicatorPtr = ptr;
}

void WorkStationServerThread::setObjectAdapterPtr( Ice::ObjectAdapterPtr ptr )
{
	m_objectAdapterPtr = ptr;
}

void WorkStationServerThread::outputWarningData( const QString& text )
{
	emit outputReceiveData(text);
}

void WorkStationServerThread::run()
{
	// �������Ľӿ�
	m_alarmDataPrx = m_objectAdapterPtr->add(new RdbAlarmDataI(this), 
		m_communicatorPtr->stringToIdentity("alarm-subscriber"));

	// ��������
	subscribeData();
	
}

bool WorkStationServerThread::getRdbRealDataRequestPublisher()
{
	if (m_rdbRealDataRequestPrx)
	{
		return true;
	}

	// ��ȡǰ�û����ݵķ�����
	string topicName = RdbRealData::strRealRequestTopic;
	string strDeliverModel = "";
	try 
	{
		Ice::ObjectPrx proxy = BaseIceStorm::GetPublisher(m_communicatorPtr, topicName, strDeliverModel);
		if (!proxy)
		{
			OperationInfo info(TYPE_CLIENT);
			info.setOperation("��ȡ�������󷢲�����ʧ��");
			info.setOperTime();
			info.setResult(false);
			info.setReason("ʧ��ԭ��δ֪");
			emit executeOperation(info);
			return false;
		}
		else
		{
			m_rdbRealDataRequestPrx = RdbRealData::RdbRealDataRequestPrx::uncheckedCast(proxy);
		}
	}
	catch(const Ice::Exception& ex)
	{
		OperationInfo info(TYPE_CLIENT);
		info.setOperation("��ȡ�������󷢲�����ʧ��");
		info.setOperTime();
		info.setResult(false);
		info.setReason(ex.what());
		emit executeOperation(info);
		return false;
	}
	catch(...)
	{
		OperationInfo info(TYPE_CLIENT);
		info.setOperation("��ȡ�������󷢲�����ʧ��");
		info.setOperTime();
		info.setResult(false);
		info.setReason("ʧ��ԭ��δ֪");
		emit executeOperation(info);
		return false;
	}

	OperationInfo info(TYPE_CLIENT);
	info.setOperation("��ȡ�������󷢲�����ɹ�");
	info.setOperTime();
	info.setResult(true);
	emit executeOperation(info);
	return true;
}

bool WorkStationServerThread::subscribeData()
{
	string strTopic = "";
	string strDeliverModel = "oneway";
	string strReliability = "";
	string strRetryCount = "";

	//����ʵʱ������������
	strTopic = RdbWarningData::strAlarmDataTopic;
	bool one_result = BaseIceStorm::Subscriber(m_communicatorPtr, m_alarmDataPrx, strTopic, strDeliverModel, strReliability,
		strRetryCount);
	if (!one_result)
	{
		return false;
	}

	return true;
}
