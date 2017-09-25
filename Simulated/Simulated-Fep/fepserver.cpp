#include "fepserver.h"
#include "fepserverthread.h"
#include "BaseIceStorm.h"
#include "fepdata.h"
#include "AmlConst.h"

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
		emit executeOperation("�����������ɹ�");

		QString endPoints("default -h localhost -p %1");
		endPoints = endPoints.arg(FEP_ADAPTER_PORT);
		Ice::ObjectAdapterPtr adapter = m_communicatorPtr->createObjectAdapterWithEndpoints("fepAdatpter", 
			endPoints.toStdString());
		emit executeOperation("��ȡ�������ɹ�");

		// �������߳����ڷ������������
		m_threadPtr->setCommunicatorPtr(m_communicatorPtr);

		adapter->activate();
		emit executeOperation("����������");

		m_communicatorPtr->waitForShutdown();
		emit executeOperation("�ر�Ice����");

		communicator()->shutdown();
		communicator()->destroy();
	}
	catch(const Ice::Exception& ex)
	{
		QString error = "����Ice����ʧ�ܣ�";
		emit executeOperation(error + ex.what());
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
	main(m_argc, m_argv);
}
