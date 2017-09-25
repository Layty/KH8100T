#include "workstationserver.h"
#include "BaseIceStorm.h"
#include "AmlConst.h"
#include "OperationInfo.h"
#include "workstationserverthread.h"

WorkStationServer::WorkStationServer( int argc, char* argv[] )
	: m_argc(argc), m_argv(argv)
{

}

int WorkStationServer::run( int argc, char* argv[] )
{
	try 
	{
		m_communicatorPtr = communicator();
		OperationInfo info(TYPE_CLIENT);
		info.setOperation("�����������ɹ�");
		info.setOperTime();
		info.setResult(true);
		emit executeOperation(info);

		QString endPoints("default -h localhost -p %1");
		endPoints = endPoints.arg(WORKSTATION_ADAPTER_PORT);
		Ice::ObjectAdapterPtr adapter = m_communicatorPtr->createObjectAdapterWithEndpoints("workStationAdatpter", 
			endPoints.toStdString());
		info.setOperation("��ȡ�������ɹ�");
		info.setOperTime();
		info.setResult(true);
		emit executeOperation(info);

		// �������߳����ڷ������������
		if (m_threadPtr)
		{
			m_threadPtr->setCommunicatorPtr(m_communicatorPtr);
		}

		adapter->activate();
		info.setOperation("����������");
		info.setOperTime();
		info.setResult(true);
		emit executeOperation(info);

		m_communicatorPtr->waitForShutdown();
		info.setOperation("�ر�Ice����");
		info.setOperTime();
		info.setResult(true);
		emit executeOperation(info);

		communicator()->shutdown();
		communicator()->destroy();
	}
	catch(const Ice::Exception& ex)
	{
		OperationInfo info(TYPE_CLIENT);
		info.setOperation("����Ice����");
		info.setOperTime();
		info.setResult(false);
		info.setReason(ex.what());
		emit executeOperation(info);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void WorkStationServer::setThreadPtr( WorkStationServerThread* ptr )
{
	m_threadPtr = ptr;
}

void WorkStationServer::startServer()
{
	main(m_argc, m_argv);
}
