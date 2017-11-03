#include "workstationserverthread.h"
#include "BaseIceStorm.h"
#include "OperationInfo.h"
#include "RdbAlarmDataI.h"
#include "RdbRealDataI.h"
#include "FepDataManagerI.h"
#include "rdbdata.h"
#include "fepdata.h"

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

void WorkStationServerThread::outputOperationData( const QString& text )
{
	emit outputReceiveData(text);
}

void WorkStationServerThread::run()
{
	try 
	{

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

	// ��ȡǰ�û����ݵķ�����
	string topicName = RdbRealData::strRealRequestTopic;
	string strDeliverModel = "";
	try 
	{
		Ice::ObjectPrx proxy = BaseIceStorm::GetPublisher(m_communicatorPtr, topicName, strDeliverModel);
		if (!proxy)
		{
			OperationInfo info(TYPE_CLIENT);
			info.setOperationInfo("��ȡ�������󷢲�����ʧ��", QDateTime(), false, "ʧ��ԭ��δ֪");
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
		info.setOperationInfo("��ȡ�������󷢲�����ʧ��", QDateTime(), false, ex.what());
		emit executeOperation(info);
		return false;
	}
	catch(...)
	{
		OperationInfo info(TYPE_CLIENT);
		info.setOperationInfo("��ȡ�������󷢲�����ʧ��", QDateTime(), false, "ʧ��ԭ��δ֪");
		emit executeOperation(info);
		return false;
	}

	OperationInfo info(TYPE_CLIENT);
	info.setOperationInfo("��ȡ�������󷢲�����ɹ�");
	emit executeOperation(info);
	return true;
}

bool WorkStationServerThread::subscribeData()
{
	//string strTopic = "";
	//string strDeliverModel = "oneway";
	//string strReliability = "";
	//string strRetryCount = "";

	//����ʵʱ������������
	//strTopic = RdbRealData::strRealRequestTopic;
	//bool one_result = BaseIceStorm::Subscriber(m_communicatorPtr, m_rdbDataPrx, strTopic, strDeliverModel, strReliability,
	//	strRetryCount);
	//if (!one_result)
	//{
	//	return false;
	//}


	//����ʵ��������Ӧ
	//strTopic = "mmi192.168.3.26";
	//bool one_result = BaseIceStorm::Subscriber(m_communicatorPtr, m_rdbRespondDataPrx, strTopic, strDeliverModel, strReliability,
	//	strRetryCount);
	//if (!one_result)
	//{
	//	return false;
	//}

	//���ı�������
	//strTopic = RdbWarningData::strAlarmDataTopic;
	//bool one_result = BaseIceStorm::Subscriber(m_communicatorPtr, m_alarmDataPrx, strTopic, strDeliverModel, strReliability,
	//	strRetryCount);
	//if (!one_result)
	//{
	//	return false;
	//}

	return true;
}

void WorkStationServerThread::requestCompleteData()
{
	try 
	{
		int count = 0;
		// ÿ��30s����һ������
		while(true)
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
			requestSeq.refreshFreq = 0;

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
				m_communicatorPtr->stringToIdentity("rdbrequest-subscriber"));
		}

		string strTopic = RdbRealData::strRealRequestTopic;
		string strDeliverModel = "oneway";
		string strReliability = "";
		string strRetryCount = "";

		if (isStop)
		{
			bool result = BaseIceStorm::UnSubscriber(m_communicatorPtr, m_rdbDataPrx, strTopic);
			if (!result)
			{
				OperationInfo info(TYPE_CLIENT);
				info.setOperationInfo("ȡ������ʵʱ��������ʧ��", QDateTime(), false, "");
				emit executeOperation(info);
				return;
			}

			OperationInfo info(TYPE_CLIENT);
			info.setOperationInfo("ȡ������ʵʱ��������ɹ�");
			emit executeOperation(info);
		}
		else
		{
			//����ʵʱ������������
			bool result = BaseIceStorm::Subscriber(m_communicatorPtr, m_rdbDataPrx, strTopic, strDeliverModel, strReliability,
				strRetryCount);
			if (!result)
			{
				OperationInfo info(TYPE_CLIENT);
				info.setOperationInfo("����ʵʱ��������ʧ��", QDateTime(), false, "");
				emit executeOperation(info);
				return;
			}

			OperationInfo info(TYPE_CLIENT);
			info.setOperationInfo("����ʵʱ��������ɹ�");
			emit executeOperation(info);
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
				m_communicatorPtr->stringToIdentity("rdbrespond-subscriber"));
		}

		string strTopic = "mmi192.168.3.26";
		string strDeliverModel = "oneway";
		string strReliability = "";
		string strRetryCount = "";

		if (isStop)
		{
			bool result = BaseIceStorm::UnSubscriber(m_communicatorPtr, m_rdbRespondDataPrx, strTopic);
			if (!result)
			{
				OperationInfo info(TYPE_CLIENT);
				info.setOperationInfo("ȡ������ʵʱ������Ӧʧ��", QDateTime(), false, "");
				emit executeOperation(info);
				return;
			}

			OperationInfo info(TYPE_CLIENT);
			info.setOperationInfo("ȡ������ʵʱ������Ӧ�ɹ�");
			emit executeOperation(info);
		}
		else
		{
			//����ʵʱ������������
			bool result = BaseIceStorm::Subscriber(m_communicatorPtr, m_rdbRespondDataPrx, strTopic, strDeliverModel, strReliability,
				strRetryCount);
			if (!result)
			{
				OperationInfo info(TYPE_CLIENT);
				info.setOperationInfo("����ʵʱ������Ӧʧ��", QDateTime(), false, "");
				emit executeOperation(info);
				return;
			}

			OperationInfo info(TYPE_CLIENT);
			info.setOperationInfo("����ʵʱ������Ӧ�ɹ�");
			emit executeOperation(info);
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
				m_communicatorPtr->stringToIdentity("alarm-subscriber"));
		}

		string strTopic = RdbWarningData::strAlarmDataTopic;
		string strDeliverModel = "oneway";
		string strReliability = "";
		string strRetryCount = "";

		if (isStop)
		{
			bool result = BaseIceStorm::UnSubscriber(m_communicatorPtr, m_alarmDataPrx, strTopic);
			if (!result)
			{
				OperationInfo info(TYPE_CLIENT);
				info.setOperationInfo(QStringLiteral("ȡ�����ı�������ʧ��"), QDateTime(), false, "");
				emit executeOperation(info);
				return;
			}

			OperationInfo info(TYPE_CLIENT);
			info.setOperationInfo(QStringLiteral("ȡ�����ı������ݳɹ�"));
			emit executeOperation(info);
		}
		else
		{
			//����ʵʱ������������
			bool result = BaseIceStorm::Subscriber(m_communicatorPtr, m_alarmDataPrx, strTopic, strDeliverModel, strReliability,
				strRetryCount);
			if (!result)
			{
				OperationInfo info(TYPE_CLIENT);
				info.setOperationInfo(QStringLiteral("���ı�������ʧ��"), QDateTime(), false, "");
				emit executeOperation(info);
				return;
			}

			OperationInfo info(TYPE_CLIENT);
			info.setOperationInfo(QStringLiteral("���ı������ݳɹ�"));
			emit executeOperation(info);
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
				m_communicatorPtr->stringToIdentity("fepdata-subscriber"));
		}

		string strTopic = FepData::strDataTopic;
		string strDeliverModel = "oneway";
		string strReliability = "";
		string strRetryCount = "";

		if (isStop)
		{
			bool result = BaseIceStorm::UnSubscriber(m_communicatorPtr, m_fepDataPrx, strTopic);
			if (!result)
			{
				OperationInfo info(TYPE_CLIENT);
				info.setOperationInfo(QStringLiteral("ȡ������ǰ�û���������ʧ��"), QDateTime(), false, "");
				emit executeOperation(info);
				return;
			}

			OperationInfo info(TYPE_CLIENT);
			info.setOperationInfo(QStringLiteral("ȡ������ǰ�û���������ɹ�"));
			emit executeOperation(info);
		}
		else
		{
			//����ʵʱ������������
			bool result = BaseIceStorm::Subscriber(m_communicatorPtr, m_fepDataPrx, strTopic, strDeliverModel, strReliability,
				strRetryCount);
			if (!result)
			{
				OperationInfo info(TYPE_CLIENT);
				info.setOperationInfo(QStringLiteral("����ǰ�û���������ʧ��"), QDateTime(), false, "");
				emit executeOperation(info);
				return;
			}

			OperationInfo info(TYPE_CLIENT);
			info.setOperationInfo(QStringLiteral("����ǰ�û���������ɹ�"));
			emit executeOperation(info);
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

