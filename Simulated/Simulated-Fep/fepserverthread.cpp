#include "fepserverthread.h"
#include "BaseIceStorm.h"
#include "OperationInfo.h"

#include <string>

using namespace std;

void FepServerThread::setCommunicatorPtr( Ice::CommunicatorPtr ptr )
{
	m_communicatorPtr = ptr;
}

void FepServerThread::run()
{

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
			OperationInfo info(TYPE_FEP);
			info.setOperation(QStringLiteral("��ȡǰ�û����ݵķ�������"));
			info.setOperTime();
			info.setResult(false);
			info.setReason(QStringLiteral("δ֪"));
			emit executeOperation(info);
			return false;
		}
		else
		{
			m_fepDataManagerPrx = FepData::FepDataManagerPrx::uncheckedCast(proxy);
		}
	}
	catch(const Ice::Exception& ex)
	{
		OperationInfo info(TYPE_FEP);
		info.setOperation(QStringLiteral("��ȡǰ�û����ݵķ�������"));
		info.setOperTime();
		info.setResult(false);
		info.setReason(ex.what());
		emit executeOperation(info);
		return false;
	}
	catch(...)
	{
		OperationInfo info(TYPE_FEP);
		info.setOperation(QStringLiteral("��ȡǰ�û����ݵķ�������"));
		info.setOperTime();
		info.setResult(false);
		info.setReason(QStringLiteral("δ֪"));
		emit executeOperation(info);
		return false;
	}

	OperationInfo info(TYPE_FEP);
	info.setOperation(QStringLiteral("��ȡǰ�û����ݵķ�������"));
	info.setOperTime();
	info.setResult(true);
	emit executeOperation(info);
	return true;
}

void FepServerThread::processData()
{
	// ��ȡ�����߶���
	if (!getFepDataPublisher())
	{
		return;
	}

	// ����ȫ����
	FepData::DataPacket packet;
	packet.id = 15;
	packet.fepNode = "fep36";
	packet.type = FepData::AllDataType;
	packet.unitNo = 1;
	for (int i = 0; i < 128; ++i)
	{
		packet.analogs.push_back(i);
		packet.discretes.push_back(i % 2);
		packet.accmulators.push_back(i+1);
	}
	m_fepDataManagerPrx->processData(packet);

	OperationInfo info(TYPE_FEP);
	info.setOperation(QStringLiteral("��������"));
	info.setOperTime();
	info.setResult(true);
	emit executeOperation(info);
}

void FepServerThread::processFault()
{
	// ��ȡ�����߶���
	if (!getFepDataPublisher())
	{
		return;
	}

	// ������������
	FepData::FaultPacket packet;
	packet.id = 15;
	packet.fepNode = "fep36";
	for (int i = 1; i < 5; ++i)
	{
		FepData::FaultEvent event;
		event.unitNo = i;
	}
	m_fepDataManagerPrx->processFault(packet);

	OperationInfo info(TYPE_FEP);
	info.setOperation(QStringLiteral("������������"));
	info.setOperTime();
	info.setResult(true);
	emit executeOperation(info);
}

void FepServerThread::processEvent()
{

}

void FepServerThread::processWave()
{

}
