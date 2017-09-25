#include "fepserverthread.h"
#include "BaseIceStorm.h"

#include <string>

using namespace std;

void FepServerThread::setCommunicatorPtr( Ice::CommunicatorPtr ptr )
{
	m_communicatorPtr = ptr;
}

void FepServerThread::run()
{

}

void FepServerThread::processData()
{
	// ��ȡ�����߶���
	if (!getFepDataPublisher())
	{
		return;
	}

	FepData::DataPacket packet;
	packet.id = 1000;
	packet.fepNode = "��ǰ�û�";
	packet.type = FepData::AllDataType;
	packet.unitNo = 1;

	m_fepDataManagerPrx->processData(packet);

	emit executeOperation("�������ݳɹ�");
}

bool FepServerThread::getFepDataPublisher()
{
	if (m_fepDataManagerPrx)
	{
		return true;
	}

	// ��ȡǰ�û����ݵķ�����
	string topicName = FepData::strDataTopic;
	string strDeliverModel = "";
	try 
	{
		Ice::ObjectPrx proxy = BaseIceStorm::GetPublisher(m_communicatorPtr, topicName, strDeliverModel);
		if (!proxy)
		{
			emit executeOperation("��ȡǰ�û����ݵķ�������ʧ��");
			return false;
		}
		else
		{
			m_fepDataManagerPrx = FepData::FepDataManagerPrx::uncheckedCast(proxy);
		}
	}
	catch(const Ice::Exception& ex)
	{
		QString error = "��ȡǰ�û����ݵķ�������ʧ��: ";
		emit executeOperation(error + ex.what());
		return false;
	}
	catch(...)
	{
		QString error = "��ȡǰ�û����ݵķ�������ʧ��: ";
		emit executeOperation("δ֪�쳣");
		return false;
	}

	emit executeOperation("��ȡǰ�û����ݷ�������ɹ�");
	return true;
}
