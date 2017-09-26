
#include "AmsServer.h"
#include "AmsSrvI.h"
#include "AmsServerThread.h"
#include "OperationInfo.h"

#include <QtWidgets/QMessageBox>

using namespace Amssrv;

AmsServer::AmsServer(AmsServerThread* threadPtr)
	: Ice::Application(Ice::NoSignalHandling),
	  m_threadPtr(threadPtr)
{

}

int AmsServer::run( int argc, char* argv[] )
{
	try 
	{
		callbackOnInterrupt();

		OperationInfo info(TYPE_AMS);

		Ice::CommunicatorPtr communicatorPtr = communicator();
		info.setOperation("����������");
		info.setResult(true);
		m_threadPtr->putMessage(info);

		QString endPoints("tcp -h localhost -p %1");
		endPoints = endPoints.arg(AMS_ADAPTER_PORT);
		Ice::ObjectAdapterPtr adapter = communicator()->createObjectAdapterWithEndpoints("AmsAdapter", 
			endPoints.toStdString());
		info.setOperation("��ȡ����������");
		info.setOperTime();
		info.setResult(true);
		m_threadPtr->putMessage(info);

		Amssrv::CAmsAppPtr amsApp = new CAmsAppI(m_threadPtr);
		adapter->add(amsApp, communicator()->stringToIdentity("amsAdapter"));

		adapter->activate();
		info.setOperation("�������������");
		info.setOperTime();
		info.setResult(true);
		m_threadPtr->putMessage(info);
	}
	catch(const ::Ice::Exception& ex)
	{
		OperationInfo info(TYPE_AMS);
		info.setOperation("����Ice����");
		info.setOperTime();
		info.setResult(false);
		info.setReason(ex.what());
		m_threadPtr->putMessage(info);
		return EXIT_FAILURE;
	}

	communicator()->waitForShutdown();
	OperationInfo info(TYPE_AMS);
	info.setOperation("AmsServer�����˳�!");
	info.setOperTime();
	info.setResult(true);
	m_threadPtr->putMessage(info);
	
	return EXIT_SUCCESS;
}
