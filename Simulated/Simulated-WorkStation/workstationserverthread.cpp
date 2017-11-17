#include "workstationserverthread.h"
#include "BaseIceStorm.h"
#include "OperationInfo.h"
#include "RdbAlarmDataI.h"
#include "RdbRealDataI.h"
#include "FepDataManagerI.h"
#include "YkDataManagerI.h"
#include "rdbdata.h"
#include "fepdata.h"
#include "ykdata.h"

#include <string>

using namespace std;

template<class T> string transferToString(const T& value);

WorkStationServerThread::WorkStationServerThread( QObject* parent /*= 0*/ )
	: QThread(parent)
{
	m_rdbRequestSubIdentity = "rdbrequest-subscriber";
	m_rdbRespondSubIdentity = "rdbrespond-subscriber";
	m_alarmSubIdentity = "alarm-subscriber";
	m_fepDataSubIdentity = "fepdata-subscriber";
	m_ykFepSubIdentity = "ykfep-subscriber";
	m_ykAppSubIdentity = "ykapp-subscriber";
}

void WorkStationServerThread::setCommunicatorPtr( Ice::CommunicatorPtr ptr )
{
	m_communicatorPtr = ptr;
}

void WorkStationServerThread::setObjectAdapterPtr( Ice::ObjectAdapterPtr ptr )
{
	m_objectAdapterPtr = ptr;
}

void WorkStationServerThread::outputOperationData( const QString& text )
{
	emit outputReceiveData(text);
}

// ң��ѡ��
void WorkStationServerThread::select()
{
	if (!getYkFepPublisher())
	{
		return;
	}

	QTime currTime = QDateTime::currentDateTime().time();
	QString strTime = QString("%1:%2:%3.%4").arg(currTime.hour()).arg(currTime.minute()).arg(currTime.second()).
		arg(currTime.msec());

	YkCommand command;
	command.step = Execute;
	command.type = DirectlyOperate;
	command.requestId = 1;
	command.rID = strTime.toStdString();
	command.unitNo = currTime.hour();
	command.ykNo = currTime.minute();
	command.yxIndex = currTime.second();
	command.value = Yk::Open;
	m_ykFepManagerPrx->select(command);

	QString text = QString("%1:%2:%3.%4 ���� %5 ���� %6\t%7").arg(currTime.hour()).arg(currTime.minute()).arg(currTime.second()).
		arg(currTime.msec()).arg("select").arg(command.requestId).arg(QString().fromStdString(command.rID));

	outputOperationData(text);
}

// ѡ��ȷ��
void WorkStationServerThread::selectEcho( YkCommand cmd, bool flag, string tip )
{
	if (!getYkAppPublisher())
	{
		return;
	}

	cmd.rID = "Simulated";
	m_ykAppManagerPrx->selectEcho(cmd, flag, tip);

	QTime currTime = QDateTime::currentDateTime().time();
	QString text = QString("%1-%2-%3 ���� %4 ���� %5\t%6").arg(currTime.hour()).arg(currTime.minute()).arg(currTime.second()).
		arg("echo").arg(cmd.requestId).arg(QString().fromStdString(cmd.rID));

	outputOperationData(text);
}

// ѡ��У
void WorkStationServerThread::selectReturn( YkCommand cmd, bool flag, string tip )
{
	if (!getYkAppPublisher())
	{
		return;
	}

	cmd.rID = "Simulated";
	m_ykAppManagerPrx->selectReturn(cmd, flag, tip);

	QTime currTime = QDateTime::currentDateTime().time();
	QString text = QString("%1-%2-%3 ���� %4 ���� %5\t%6").arg(currTime.hour()).arg(currTime.minute()).arg(currTime.second()).
		arg("return").arg(cmd.requestId).arg(QString().fromStdString(cmd.rID));

	outputOperationData(text);
}

void WorkStationServerThread::run()
{
	try 
	{
		connect(&m_ykSelectTimer, SIGNAL(timeout()), this, SLOT(select()));
	}
	catch(const Ice::Exception& ex)
	{
		string error = ex.what();
	}
	
}

bool WorkStationServerThread::getRdbRealDataRequestPublisher()
{
	if (m_rdbRealDataRequestPrx)
	{
		return true;
	}

	// ��ȡʵʱ��������ķ�����
	string topicName = Yk::YkFepTopic;
	QString type = "ʵʱ��������";
	Ice::ObjectPrx proxy;
	if (!getPublisher(topicName, type, proxy))
	{
		return false;
	}
	m_rdbRealDataRequestPrx = RdbRealData::RdbRealDataRequestPrx::uncheckedCast(proxy);
	return true;
}

// ��ȡң�ط�������
bool WorkStationServerThread::getYkFepPublisher()
{
	if (m_ykFepManagerPrx)
	{
		return true;
	}

	// ��ȡң�ز����ķ�����
	string topicName = Yk::YkFepTopic;
	QString type = "ң�ز���";
	Ice::ObjectPrx proxy;
	if (!getPublisher(topicName, type, proxy))
	{
		return false;
	}
	m_ykFepManagerPrx = Yk::YkFepManagerPrx::uncheckedCast(proxy);
	return true;
}

// ��ȡң�ط��ط�������
bool WorkStationServerThread::getYkAppPublisher()
{
	if (m_ykAppManagerPrx)
	{
		return true;
	}

	// ��ȡң������ķ�����
	string topicName = Yk::YkAppTopic;
	QString type = "ң������";
	Ice::ObjectPrx proxy;
	if (!getPublisher(topicName, type, proxy))
	{
		return false;
	}
	m_ykAppManagerPrx = Yk::YkAppManagerPrx::uncheckedCast(proxy);
	return true;
}

// ����IceStorm����
bool WorkStationServerThread::subscribeTopic( Ice::ObjectPrx &objectPrx, const std::string &topic, const QString& type )
{
	try 
	{
		string strTopic = topic;
		string strDeliverModel = "oneway";
		string strReliability = "";
		string strRetryCount = "";

		//����ʵʱ������������
		bool result = BaseIceStorm::Subscriber(m_communicatorPtr, objectPrx, strTopic, strDeliverModel, strReliability,
			strRetryCount);
		if (!result)
		{
			OperationInfo info(TYPE_CLIENT);
			info.setOperationInfo(QStringLiteral("����%1ʧ��").arg(type), QDateTime(), false, "");
			emit executeOperation(info);
			return false;
		}

		OperationInfo info(TYPE_CLIENT);
		info.setOperationInfo(QStringLiteral("����%1�ɹ�").arg(type));
		emit executeOperation(info);
		return true;
	}
	catch(const Ice::Exception& ex)
	{
		OperationInfo info(TYPE_CLIENT);
		info.setOperationInfo(QStringLiteral("����/ȡ������%1ʧ��").arg(type), QDateTime(), false, ex.what());
		emit executeOperation(info);
		return false;
	}
}

// ȡ������IceStorm����
bool WorkStationServerThread::unSubscribeTopic( Ice::ObjectPrx &objectPrx, const std::string &topic, const QString& type )
{
	try 
	{
		string strTopic = topic;

		bool result = BaseIceStorm::UnSubscriber(m_communicatorPtr, objectPrx, strTopic);
		if (!result)
		{
			OperationInfo info(TYPE_CLIENT);
			info.setOperationInfo(QStringLiteral("ȡ������%1ʧ��").arg(type), QDateTime(), false, "");
			emit executeOperation(info);
			return false;
		}

		OperationInfo info(TYPE_CLIENT);
		info.setOperationInfo(QStringLiteral("ȡ������%1�ɹ�").arg(type));
		emit executeOperation(info);
		return true;
	}
	catch(const Ice::Exception& ex)
	{
		OperationInfo info(TYPE_CLIENT);
		info.setOperationInfo(QStringLiteral("����/ȡ������%1ʧ��").arg(type), QDateTime(), false, ex.what());
		emit executeOperation(info);
		return false;
	}
}

// ��ȡ��������
bool WorkStationServerThread::getPublisher( const std::string& topic, const QString& type, Ice::ObjectPrx& objectPrx )
{
	// ��ȡǰ�û����ݵķ�����
	string topicName = topic;
	string strDeliverModel = "";
	try 
	{
		objectPrx = BaseIceStorm::GetPublisher(m_communicatorPtr, topicName, strDeliverModel);
		if (!objectPrx)
		{
			OperationInfo info(TYPE_CLIENT);
			info.setOperationInfo(QStringLiteral("��ȡ%1��������ʧ��").arg(type), QDateTime(), false, "ʧ��ԭ��δ֪");
			emit executeOperation(info);
			return false;
		}
	}
	catch(const Ice::Exception& ex)
	{
		OperationInfo info(TYPE_CLIENT);
		info.setOperationInfo(QStringLiteral("��ȡ%1��������ʧ��").arg(type), QDateTime(), false, ex.what());
		emit executeOperation(info);
		return false;
	}
	catch(...)
	{
		OperationInfo info(TYPE_CLIENT);
		info.setOperationInfo(QStringLiteral("��ȡ%1��������ʧ��").arg(type), QDateTime(), false, "ʧ��ԭ��δ֪");
		emit executeOperation(info);
		return false;
	}

	OperationInfo info(TYPE_CLIENT);
	info.setOperationInfo(QStringLiteral("��ȡ%1��������ɹ�").arg(type));
	emit executeOperation(info);
	return true;
}

void WorkStationServerThread::requestCompleteData()
{
	try 
	{
		int count = 0;
		// ÿ��30s����һ������
		while(count == 0)
		{
			if (++count > 120)
			{
				break;
			}

			if (!getRdbRealDataRequestPublisher())
			{
				return;
			}

			RdbRealData::RequestCompleteDataSeq requestSeq;
			requestSeq.id = 1;
			requestSeq.requestId = 1;
			requestSeq.requestNode = "test";
			requestSeq.isStop = false;
			requestSeq.refreshFreq = 3;

			RdbRealData::RequestCompleteData requestData;
			requestData.tableName = "Substation";
			requestData.fieldName = "name";
			requestData.fieldValue = "�ƻ�վ";
			requestSeq.seq.push_back(requestData);
			requestSeq.dataCount = requestSeq.seq.size();

			// ��ȡʵʱ��������Ķ�����
			string strTopic = ::RdbRealData::strRealRequestTopic;
			IceStorm::TopicPrx topic = BaseIceStorm::GetTopicProxy(m_communicatorPtr, strTopic);
			if (topic)
			{
				::Ice::IdentitySeq identitySeq = topic->getSubscribers();

				QTime currTime = QDateTime::currentDateTime().time();
				QString text = QString("%1-%2-%3").arg(currTime.hour()).arg(currTime.minute()).arg(currTime.second());
				emit outputReceiveData(text);

				if (identitySeq.empty())
				{
					emit outputReceiveData("\t�����ڶ�����");
				}
				for (size_t i = 0; i < identitySeq.size(); ++i)
				{
					Ice::Identity identity = identitySeq.at(i);
					emit outputReceiveData(QString("\t%1\t%2").arg(QString().fromStdString(identity.category)).
						arg(QString().fromStdString(identity.name)));
				}
			}

			m_rdbRealDataRequestPrx->RequestCompleteData(requestSeq);
			
			QString text("%1 ����ȫ��ʵʱ���� %2-%3-%4");
			QTime currTime = QDateTime::currentDateTime().time();
			text = text.arg(count).arg(currTime.hour()).arg(currTime.minute()).arg(currTime.second());
			emit outputReceiveData(text);

			IceUtil::ThreadControl::sleep(IceUtil::Time::seconds(2));
		}
	}
	catch(const Ice::Exception& ex)
	{
		QString error = QString().fromStdString(ex.what());
		emit outputReceiveData(QString("����ȫ��ʵʱ����ʧ��:%1").arg(error));
	}
}

void WorkStationServerThread::selectCompleteData()
{
	RdbRealData::RdbDataOptPrx rdbOptPrx = RdbRealData::RdbDataOptPrx::checkedCast(
		m_communicatorPtr->stringToProxy("rdb-opt:default -h 192.168.3.25 -p 10003 -t 5000"));
	if (rdbOptPrx)
	{
		RdbRealData::RequestCompleteDataSeq requestSeq;
		requestSeq.id = 0;
		requestSeq.requestId = 0;
		requestSeq.requestNode = "workstation";
		requestSeq.isStop = false;
		requestSeq.refreshFreq = 0;
		RdbRealData::RequestCompleteData	request;
		request.tableName = "SubGeographicalRegion";

		RdbRealData::RespondCompleteDataSeq respondSeq;
		rdbOptPrx->SelectCompleteData(requestSeq, respondSeq);
	}
}

void WorkStationServerThread::subscriberRdbRequest(bool isStop)
{
	try 
	{
		if (m_rdbDataPrx == NULL)
		{
			// �������Ľӿ�
			m_rdbDataPrx = m_objectAdapterPtr->add(new RdbRealDataRequestI(this), 
				m_communicatorPtr->stringToIdentity(m_rdbRequestSubIdentity));
		}

		string strTopic = RdbRealData::strRealRequestTopic;
		QString type = "ʵʱ��������";

		if (isStop)
		{
			unSubscribeTopic(m_rdbDataPrx, strTopic, type);
		}
		else
		{
			subscribeTopic(m_rdbDataPrx, strTopic, type);
		}
	}
	catch(const Ice::Exception& ex)
	{
		OperationInfo info(TYPE_CLIENT);
		info.setOperationInfo(QStringLiteral("����/ȡ������ʵʱ��������ʧ��"), QDateTime(), false, ex.what());
		emit executeOperation(info);
		return;
	}	
}

void WorkStationServerThread::subscriberRdbRespond( bool isStop )
{
	try 
	{
		if (m_rdbRespondDataPrx == NULL)
		{
			m_rdbRespondDataPrx = m_objectAdapterPtr->add(new RdbRealDataRespondI(this), 
				m_communicatorPtr->stringToIdentity(m_rdbRespondSubIdentity));
		}

		string strTopic = "mmi192.168.3.26";
		QString type = "ʵʱ������Ӧ";

		if (isStop)
		{
			unSubscribeTopic(m_rdbRespondDataPrx, strTopic, type);
		}
		else
		{
			subscribeTopic(m_rdbRespondDataPrx, strTopic, type);
		}
	}
	catch(const Ice::Exception& ex)
	{
		OperationInfo info(TYPE_CLIENT);
		info.setOperationInfo(QStringLiteral("����/ȡ������ʵʱ������Ӧʧ��"), QDateTime(), false, ex.what());
		emit executeOperation(info);
		return;
	}
}

void WorkStationServerThread::subscriberAlarmData( bool isStop )
{
	try 
	{
		// �������Ľӿ�
		if (m_alarmDataPrx == NULL)
		{
			m_alarmDataPrx = m_objectAdapterPtr->add(new RdbAlarmDataI(this), 
				m_communicatorPtr->stringToIdentity(m_alarmSubIdentity));
		}

		string strTopic = RdbWarningData::strAlarmDataTopic;
		QString type = "��������";

		if (isStop)
		{
			unSubscribeTopic(m_alarmDataPrx, strTopic, type);
		}
		else
		{
			subscribeTopic(m_alarmDataPrx, strTopic, type);
		}
	}
	catch(const Ice::Exception& ex)
	{
		OperationInfo info(TYPE_CLIENT);
		info.setOperationInfo(QStringLiteral("����/ȡ�����ı�������ʧ��"), QDateTime(), false, ex.what());
		emit executeOperation(info);
		return;
	}
}

void WorkStationServerThread::subscriberFepData(bool isStop)
{
	try 
	{
		// �������Ľӿ�
		if (m_fepDataPrx == NULL)
		{
			m_fepDataPrx = m_objectAdapterPtr->add(new FepDataManagerI(this), 
				m_communicatorPtr->stringToIdentity(m_fepDataSubIdentity));
		}

		string strTopic = FepData::strDataTopic;
		QString type = "ǰ�û�����";

		if (isStop)
		{
			unSubscribeTopic(m_fepDataPrx, strTopic, type);
		}
		else
		{
			subscribeTopic(m_fepDataPrx, strTopic, type);
		}
	}
	catch(const Ice::Exception& ex)
	{
		OperationInfo info(TYPE_CLIENT);
		info.setOperationInfo(QStringLiteral("����/ȡ������ǰ�û���������ʧ��"), QDateTime(), false, ex.what());
		emit executeOperation(info);
		return;
	}
}

void WorkStationServerThread::subscriberYkFep( bool isStop )
{
	try 
	{
		// �������Ľӿ�
		if (m_ykFepPrx == NULL)
		{
			m_ykFepPrx = m_objectAdapterPtr->add(new YkFepManagerI(this), 
				m_communicatorPtr->stringToIdentity(m_ykFepSubIdentity));
		}

		string strTopic = Yk::YkFepTopic;
		QString type = "ң������";

		if (isStop)
		{
			unSubscribeTopic(m_ykFepPrx, strTopic, type);
		}
		else
		{
			subscribeTopic(m_ykFepPrx, strTopic, type);
		}
	}
	catch(const Ice::Exception& ex)
	{
		OperationInfo info(TYPE_CLIENT);
		info.setOperationInfo(QStringLiteral("����/ȡ������ң����������ʧ��"), QDateTime(), false, ex.what());
		emit executeOperation(info);
		return;
	}

}

void WorkStationServerThread::subscriberYkApp( bool isStop )
{
	try 
	{
		// �������Ľӿ�
		if (m_ykAppPrx == NULL)
		{
			m_ykAppPrx = m_objectAdapterPtr->add(new YkAppManagerI(this), 
				m_communicatorPtr->stringToIdentity(m_ykAppSubIdentity));
		}

		string strTopic = Yk::YkAppTopic;
		QString	type = "ң����Ӧ";
		if (isStop)
		{
			unSubscribeTopic(m_ykAppPrx, strTopic, type);
		}
		else
		{
			subscribeTopic(m_ykAppPrx, strTopic, type);
		}
	}
	catch(const Ice::Exception& ex)
	{
		OperationInfo info(TYPE_CLIENT);
		info.setOperationInfo(QStringLiteral("����/ȡ������ң����Ӧʧ��"), QDateTime(), false, ex.what());
		emit executeOperation(info);
		return;
	}
}

void WorkStationServerThread::ykSelect( bool isStop )
{
	if (isStop)
	{
		m_ykSelectTimer.stop();
	}
	else
	{
		m_ykSelectTimer.start(10000);
	}
}

