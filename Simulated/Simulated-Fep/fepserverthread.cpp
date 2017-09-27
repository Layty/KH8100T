#include "fepserverthread.h"
#include "BaseIceStorm.h"
#include "OperationInfo.h"
#include "textelement.h"

#include <string>
#include <sstream>

using namespace std;

template<class T>
string transferToString(const T& value)
{
	stringstream str;
	str << value;
	return str.str();
}

// ��ȡң��״ֵ̬
string	getDiscreteValue(FepData::DiscreteValue value)
{
	switch(value)
	{
	case FepData::Open:
		return "��բ";
	case FepData::Close:
		return "��բ";
	case  FepData::Unknown:
	default:
		return "δ֪";
	}
}

// ��ȡ�ն�״ֵ̬
string getState(FepData::State value)
{
	switch(value)
	{
	case FepData::NotInstall:
		return "δ��װ";
	case FepData::OffLine:
		return "����";
	case FepData::New:
		return "Ͷ��";
	case FepData::Run:
		return "����";
	case FepData::Stop:
		return "�˳�";
	case FepData::HighErrorRate:
		return "�����ʸ�";
	default:
		return "δ֪";
	}
}

// ��ȡ��������
string getDataType(FepData::DataType value)
{
	switch(value)
	{
	case FepData::AllDataType:
		return "ȫ����";
	case FepData::ChangedAnalogType:
		return "�仯ң��";
	case FepData::AccumulatorType:
		return "���";
	case FepData::UnitStateType:
		return "�ն�״̬";
	default:
		return "δ֪";
	}
}

// ��ȡ������������
string getProEventType(FepData::ProEventType value)
{
	switch(value)
	{
	case FepData::ProtectAction:
		return "��������";
	case FepData::ProtectAlarm:
		return "�������ź�";
	default:
		return "δ֪";
	}
}

// ��ȡ��������
string getEventType(FepData::EventType value)
{
	switch(value)
	{
	case FepData::YxType:
		return "ң�ű�λ";
	case FepData::SoeType:
		return "SOE";
	case FepData::UnitType:
		return "�ն�״̬";
	case FepData::ProType:
		return "��������";
	default:
		return "δ֪";
	}
}

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
			info.setOperationInfo(QStringLiteral("��ȡǰ�û����ݵķ�������"), QDateTime(), false, QStringLiteral("δ֪"));
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
		info.setOperationInfo(QStringLiteral("��ȡǰ�û����ݵķ�������"), QDateTime(), false, ex.what());
		emit executeOperation(info);
		return false;
	}
	catch(...)
	{
		OperationInfo info(TYPE_FEP);
		info.setOperationInfo(QStringLiteral("��ȡǰ�û����ݵķ�������"), QDateTime(), false, QStringLiteral("δ֪"));
		emit executeOperation(info);
		return false;
	}

	OperationInfo info(TYPE_FEP);
	info.setOperationInfo(QStringLiteral("��ȡǰ�û����ݵķ�������"));
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
	// ����5������
	for (int i = 1; i < 6; ++i)
	{
		packet.analogs.push_back(i);
		packet.analogs.push_back(i * 2);

		packet.discretes.push_back(i);
		packet.discretes.push_back(i % 2);

		packet.accmulators.push_back(i);
		packet.accmulators.push_back(i+1);
	}
	m_fepDataManagerPrx->processData(packet);

	// ������͵�����
	QString text = outputFepData(packet);
	emit publishFepData(text);

	OperationInfo info(TYPE_FEP);
	info.setOperationInfo(QStringLiteral("��������"));
	emit executeOperation(info);
}

void FepServerThread::processDLFault()
{
	// ��ȡ�����߶���
	if (!getFepDataPublisher())
	{
		return;
	}

	// ������·��������
	FepData::FaultPacket packet;
	packet.id = 15;
	packet.fepNode = "fep36";
	FepData::FaultEvent event;
	event.unitNo = 1;
	event.lineNo = 1;
	event.timeStamp = IceUtil::Time::now().toMilliSeconds();
	event.eventType = 0;
	packet.events.push_back(event);

	m_fepDataManagerPrx->processFault(packet);

	OperationInfo info(TYPE_FEP);
	info.setOperationInfo(QStringLiteral("������·��������"));
	emit executeOperation(info);
}

void FepServerThread::processJDFault()
{
	// ��ȡ�����߶���
	if (!getFepDataPublisher())
	{
		return;
	}

	// �����ӵع�������--ѡ��
	FepData::FaultPacket packet;
	packet.id = 15;
	packet.fepNode = "fep36";
	FepData::FaultEvent event;
	event.unitNo = 2;
	event.lineNo = 2;
	event.timeStamp = IceUtil::Time::now().toMilliSeconds();
	event.eventType = 2;
	event.credibility = 30;
	packet.events.push_back(event);
	
	// �����ӵع�������--�ӵ�
	event.unitNo = 2;
	event.lineNo = 2;
	event.timeStamp = IceUtil::Time::now().toMilliSeconds();
	event.eventType = 1;
	event.directionFlag = 1;
	event.faultType = 0;
	event.directionMultiplier = 50;
	event.values.push_back(10);
	event.values.push_back(30);
	event.values.push_back(50);
	event.values.push_back(80);
	event.values.push_back(100);
	packet.events.push_back(event);
	
	// �����ӵع�������--ѡ�߽���
	event.unitNo = 2;
	event.lineNo = 2;
	event.timeStamp = IceUtil::Time::now().toMilliSeconds();
	event.eventType = 3;
	packet.events.push_back(event);

	m_fepDataManagerPrx->processFault(packet);

	OperationInfo info(TYPE_FEP);
	info.setOperationInfo(QStringLiteral("�����ӵع�������"));
	emit executeOperation(info);
}

void FepServerThread::processYxTypeEvent()
{
	// ��ȡ�����߶���
	if (!getFepDataPublisher())
	{
		return;
	}

	// ����ң�ű�λ����
	FepData::EventPacket packet;
	packet.id = 15;
	packet.fepNode = "fep36";
	packet.type = FepData::YxType;
	FepData::ChangedDigital changedDigital;
	changedDigital.unitNo = 1;
	changedDigital.index = 1;
	changedDigital.value = FepData::Close;
	changedDigital.timeStamp = IceUtil::Time::now().toMilliSeconds();
	packet.digitals.push_back(changedDigital);

	m_fepDataManagerPrx->processEvent(packet);

	OperationInfo info(TYPE_FEP);
	info.setOperationInfo(QStringLiteral("����ң�ű�λ����"));
	emit executeOperation(info);
}

void FepServerThread::processSoeTypeEvent()
{
	// ��ȡ�����߶���
	if (!getFepDataPublisher())
	{
		return;
	}

	// ����SOE����
	FepData::EventPacket packet;
	packet.id = 15;
	packet.fepNode = "fep36";
	packet.type = FepData::SoeType;
	FepData::Soe soe;
	soe.unitNo = 1;
	soe.index = 1;
	soe.value = FepData::Open;
	soe.timeStamp = IceUtil::Time::now().toMilliSeconds();
	packet.soes.push_back(soe);

	m_fepDataManagerPrx->processEvent(packet);

	OperationInfo info(TYPE_FEP);
	info.setOperationInfo(QStringLiteral("����SOE����"));
	emit executeOperation(info);
}

void FepServerThread::processUnitTypeEvent()
{
	// ��ȡ�����߶���
	if (!getFepDataPublisher())
	{
		return;
	}

	// ������Ԫ����
	FepData::EventPacket packet;
	packet.id = 15;
	packet.fepNode = "fep36";
	packet.type = FepData::UnitType;
	FepData::ChangedUnit changedUnit;
	changedUnit.unitNo = 1;
	changedUnit.unitState = FepData::Run;
	changedUnit.channelState1 = FepData::Run;
	changedUnit.channelState2 = FepData::NotInstall;
	changedUnit.errorRate = 6;
	changedUnit.timeStamp = IceUtil::Time::now().toMilliSeconds();
	packet.units.push_back(changedUnit);

	m_fepDataManagerPrx->processEvent(packet);

	OperationInfo info(TYPE_FEP);
	info.setOperationInfo(QStringLiteral("������Ԫ����"));
	emit executeOperation(info);
}

void FepServerThread::processProTypeEvent()
{
	// ��ȡ�����߶���
	if (!getFepDataPublisher())
	{
		return;
	}

	// ������������
	FepData::EventPacket packet;
	packet.id = 15;
	packet.fepNode = "fep36";
	packet.type = FepData::ProType;
	FepData::ProtectEvent protectEvent;
	protectEvent.unitNo = 1;
	protectEvent.Type = FepData::ProtectAlarm;
	protectEvent.timeStamp = IceUtil::Time::now().toMilliSeconds();
	protectEvent.moduleNo = 0;
	protectEvent.moduleType = 0;
	protectEvent.infoNo = 0;
	protectEvent.state = 0;
	packet.protects.push_back(protectEvent);

	m_fepDataManagerPrx->processEvent(packet);

	OperationInfo info(TYPE_FEP);
	info.setOperationInfo(QStringLiteral("������������"));
	emit executeOperation(info);
}

void FepServerThread::processWave()
{

}

QString FepServerThread::outputFepData( const FepData::DataPacket& packet )
{
	QString text;
	QString currTime = QDateTime::currentDateTime().toString(Qt::SystemLocaleLongDate);

	TextElement parent("ǰ�û���������", currTime.toStdString());
	parent.insertChild( TextElement("���ݰ�ID", transferToString<unsigned char>(packet.id)));
	parent.insertChild( TextElement("����ǰ�û�", packet.fepNode));
	parent.insertChild( TextElement("��������", getDataType(packet.type)));
	parent.insertChild( TextElement("��Ԫ��", transferToString<short>(packet.unitNo)));
	if (!packet.units.empty())
	{
		TextElement units("�ն�״̬", transferToString<size_t>(packet.units.size()), &parent);
		for (size_t i = 0; i < packet.units.size(); ++i)
		{
			units.insertChild(TextElement("�ն˱��", transferToString<short>(packet.units.at(i).unitNo)));
			units.insertChild(TextElement("��Ԫ״̬", getState(packet.units.at(i).unitState)));
			units.insertChild(TextElement("��ͨ��״̬", getState(packet.units.at(i).channelState1)));
			units.insertChild(TextElement("��ͨ��״̬", getState(packet.units.at(i).channelState2)));
			units.insertChild(TextElement("������", transferToString<unsigned char>(packet.units.at(i).unitNo)));
		}
	}
	if (!packet.analogs.empty())
	{
		TextElement analogs("ң������", transferToString<size_t>(packet.analogs.size()), &parent);

		string value;
		for (size_t i = 0; i < packet.analogs.size(); ++i)
		{
			value += transferToString<int>(packet.analogs.at(i)) + "\t";
		}
		analogs.insertChild(TextElement("ֵ", value));
	}
	if (!packet.discretes.empty())
	{
		TextElement discretes("ң������", transferToString<size_t>(packet.discretes.size()), &parent);

		string value;
		for (size_t i = 0; i < packet.discretes.size(); ++i)
		{
			value += transferToString<int>(packet.discretes.at(i)) + "\t";
		}
		discretes.insertChild(TextElement("ֵ", value));
	}
	if (!packet.accmulators.empty())
	{
		TextElement accmulators("�������", transferToString<size_t>(packet.accmulators.size()), &parent);

		string value;
		for (size_t i = 0; i < packet.accmulators.size(); ++i)
		{
			value += transferToString<int>(packet.accmulators.at(i)) + "\t";
		}
		accmulators.insertChild(TextElement("ֵ", value));
	}
	if (!packet.changedAnalogs.empty())
	{
		TextElement changedAnalogs("�仯ң������", transferToString<size_t>(packet.changedAnalogs.size()), &parent);

		for (size_t i = 0; i < packet.changedAnalogs.size(); ++i)
		{
			changedAnalogs.insertChild(TextElement("ʱ��", transferToString<long>(packet.changedAnalogs.at(i).timeStamp)));
			changedAnalogs.insertChild(TextElement("�ն˱��", transferToString<short>(packet.changedAnalogs.at(i).unitNo)));
			changedAnalogs.insertChild(TextElement("���", transferToString<short>(packet.changedAnalogs.at(i).index)));
			changedAnalogs.insertChild(TextElement("ֵ", transferToString<int>(packet.changedAnalogs.at(i).value)));
		}
	}

	return text.fromStdString(parent.toString());
}

QString FepServerThread::outputFepFault( const FepData::FaultPacket& packet )
{
	QString text;
	return text;
}

QString FepServerThread::outputFepEvent( const FepData::EventPacket& packet )
{
	QString text;
	return text;
}

QString FepServerThread::outputFepWave( const FepData::WavePacket& packet )
{
	QString text;
	return text;
}
