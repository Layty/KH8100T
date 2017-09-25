#include "workstationserverthread.h"
#include "BaseIceStorm.h"
#include "OperationInfo.h"

#include <string>

using namespace std;

void WorkStationServerThread::setCommunicatorPtr( Ice::CommunicatorPtr ptr )
{
	m_communicatorPtr = ptr;
}

void WorkStationServerThread::run()
{

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

bool WorkStationServerThread::subscribeRdbRealData()
{
	return true;
}
