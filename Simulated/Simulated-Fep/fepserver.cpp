#include "fepserver.h"
#include "fepserverthread.h"
#include "BaseIceStorm.h"
#include "fepdata.h"
#include "AmlConst.h"
#include "OperationInfo.h"

#include <string>
using namespace std;

FepServer::FepServer( int argc, char* argv[] )
	: m_argc(argc), m_argv(argv)
{

}

int FepServer::run( int argc, char* argv[] )
{
	try 
	{
		m_communicatorPtr = communicator();
		OperationInfo info(TYPE_FEP);
		info.setOperationInfo(QStringLiteral("����������"));
		emit executeOperation(info);
		
		string adapterName = "FepAdatpter";
		::Ice::PropertiesPtr props = m_communicatorPtr->getProperties();
		if (props)
		{
			adapterName = props->getPropertyWithDefault("AdapterName", adapterName);
		}

		Ice::ObjectAdapterPtr adapter = m_communicatorPtr->createObjectAdapter(adapterName);
		info.setOperationInfo(QStringLiteral("��ȡ�������ɹ�"));
		emit executeOperation(info);

		// �������߳����ڷ������������
		m_threadPtr->setCommunicatorPtr(m_communicatorPtr);

		adapter->activate();
		info.setOperationInfo(QStringLiteral("����������"));
		emit executeOperation(info);

		m_communicatorPtr->waitForShutdown();
		info.setOperationInfo(QStringLiteral("�ر�Ice����"));
		emit executeOperation(info);

		communicator()->shutdown();
		communicator()->destroy();
	}
	catch(const Ice::Exception& ex)
	{
		OperationInfo info(TYPE_FEP);
		info.setOperationInfo(QStringLiteral("����Ice����"), QDateTime(), false, ex.what());
		emit executeOperation(info);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void FepServer::setThreadPtr( FepServerThread* ptr )
{
	m_threadPtr = ptr;
}

void FepServer::startServer()
{
	main(m_argc, m_argv, "config.server");
}
