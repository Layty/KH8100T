
#include "transferfileserver.h"
#include "transloggerI.h"
#include "FileHandler.h"
#include "BaseIceStorm.h"

#include <Ice/Ice.h>
#include <IceUtil/IceUtil.h>
#include <IceStorm/IceStorm.h>

TransferFileServer::TransferFileServer(int argc, char* argv[])
{
	m_argc = argc;
	m_argv = argv;

	m_publishFilePrx = 0;
	m_subscriberFilePrx = 0;
}

TransferFileServer::~TransferFileServer()
{

}

int TransferFileServer::run( int argc, char* argv[] )
{
	try 
	{
		m_communicatorPtr = communicator();
		QString endPoints("default -h 192.168.3.25 -p %1");

		// ��������
		endPoints = endPoints.arg(10006);
		m_objectAdapterPtr = communicator()->createObjectAdapterWithEndpoints("pubAdatpter", 
			endPoints.toStdString());
			
		m_objectAdapterPtr->activate();

		communicator()->waitForShutdown();

		communicator()->shutdown();
		communicator()->destroy();
	}
	catch(const Ice::Exception& ex)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void TransferFileServer::start()
{
	main(m_argc, m_argv);
}

void TransferFileServer::publishFile(bool isStart)
{
	if (isStart)
	{
		emit outputOperationInfo(QStringLiteral("��ʼ�����ļ�..."));

		// ��ȡ�����ӿ�
		if (!getPublisherPtr())
		{
			return;
		}

		// ��ȡ�ļ�����
		string fileName = "source.log";
		string content = "";
		CFileHandler fileHandler;
		if (!fileHandler.readFileWithQDataStream(fileName, content))
		{
			emit outputOperationInfo(QStringLiteral("��ȡ�ļ�����"));
		}

		m_publishFilePrx->transferRdbLogger(fileName, content);

		emit outputOperationInfo(QStringLiteral("��ɷ����ļ�..."));
	}
	else
	{

		emit outputOperationInfo(QStringLiteral("ֹͣ�����ļ�..."));
	}
}

void TransferFileServer::subscriberFile(bool isStart)
{
	// �������Ľӿ�
	if (m_subscriberFilePrx == NULL)
	{
		m_subscriberFilePrx = m_objectAdapterPtr->add(new TransferRdbLoggerInfoI(), 
			m_communicatorPtr->stringToIdentity("file-subscriber"));
	}

	if (isStart)
	{
		emit outputOperationInfo(QStringLiteral("��ʼ�����ļ�..."));

		//������صĽӿ�
		std::string strTopic = "";
		std::string strDeliverModel = "oneway";
		std::string strReliability = "";
		std::string strRetryCount = "";

		//����ʵʱ������������
		strTopic = TransferRdbLogger::TransferRdbLoggerTopic;
		bool result = BaseIceStorm::Subscriber(communicator(), m_subscriberFilePrx, strTopic, strDeliverModel, 
			strReliability, strRetryCount);
		if (!result)
		{
			emit outputOperationInfo(QStringLiteral("�����ļ�ʧ��..."));
			return;
		}

		emit outputOperationInfo(QStringLiteral("��ɶ����ļ�..."));
	}
	else
	{
		emit outputOperationInfo(QStringLiteral("ֹͣ�����ļ�..."));

		bool result = true;

		//ȡ������ 
		std::string strTopic = TransferRdbLogger::TransferRdbLoggerTopic;
		result = BaseIceStorm::UnSubscriber(communicator(), m_subscriberFilePrx, strTopic);
		if (!result)
		{
			emit outputOperationInfo(QStringLiteral("ȡ�������ļ�ʧ��..."));
			return;
		}

		emit outputOperationInfo(QStringLiteral("���ֹͣ�����ļ�..."));
	}
}

// ��ȡ�����ӿ�
bool TransferFileServer::getPublisherPtr()
{
	if (m_publishFilePrx != 0)
		return true;

	try
	{
		std::string strTopic;
		std::string strDeliverModel;
		Ice::ObjectPrx objPrx;

		//���"��������"�����ӿ�
		strTopic = TransferRdbLogger::TransferRdbLoggerTopic;
		strDeliverModel = "oneway";
		objPrx = BaseIceStorm::GetPublisher(communicator(), strTopic, strDeliverModel);

		if (objPrx != 0)
		{
			m_publishFilePrx = TransferRdbLogger::TransferRdbLoggerInfoPrx::uncheckedCast(objPrx);
			emit outputOperationInfo(QStringLiteral("��ȡ�������ݽӿڳɹ�"));
			return true;
		}
		else
		{
			m_publishFilePrx = NULL;
			emit outputOperationInfo(QStringLiteral("��ȡ�������ݽӿ�ʧ��"));
			return false;
		}

	} catch (Ice::Exception& e)
	{
		emit outputOperationInfo(QStringLiteral("��ȡ�������ݽӿ��쳣:%1").arg(e.what()));

		m_publishFilePrx = 0;
		return false;
	}
}

// �Ƴ������ӿ�
bool TransferFileServer::removePublisherPtr()
{
	return true;
}
