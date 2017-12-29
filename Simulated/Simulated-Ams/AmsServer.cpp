
#include "AmsServer.h"
#include "AmsServerThread.h"
#include "OperationInfo.h"

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
		info.setOperationInfo("����������");
		m_threadPtr->putMessage(info);
		
		::Ice::PropertiesPtr props = communicator()->getProperties();
		string adapterName = "AmsApp";
		string amsAppName = "amsApp";
		if (props)
		{
			adapterName = props->getProperty("AdapterName");
			amsAppName = props->getProperty("AmsAppName");
		}
		
		Ice::ObjectAdapterPtr adapter = communicator()->createObjectAdapter(adapterName);
		info.setOperationInfo("��ȡ����������");
		m_threadPtr->putMessage(info);

		amsApp = new CAmsAppI(m_threadPtr);
		adapter->add(amsApp, communicator()->stringToIdentity(amsAppName));

		// ͨ�������������ݷ������ڵ���Ϣ
		if (props)
		{
			string dataSrvIp = props->getPropertyWithDefault("DataSrvIp", "192.168.3.25");
			int dataSrvPort = props->getPropertyAsIntWithDefault("DataSrvPort", DATASRV_ADAPTER_PORT);
			((CAmsAppI*)amsApp.get())->setDataSrvInfo(dataSrvIp, dataSrvPort);
		}

		adapter->activate();
		info.setOperationInfo("�������������");
		m_threadPtr->putMessage(info);
	}
	catch(const ::Ice::Exception& ex)
	{
		OperationInfo info(TYPE_AMS);
		info.setOperationInfo("����Ice����", QDateTime(), false, ex.what());
		m_threadPtr->putMessage(info);
		return EXIT_FAILURE;
	}

	communicator()->waitForShutdown();
	OperationInfo info(TYPE_AMS);
	info.setOperationInfo("AmsServer�����˳�!");
	m_threadPtr->putMessage(info);
	
	return EXIT_SUCCESS;
}

void AmsServer::setRole( const string& role )
{
	((CAmsAppI*)amsApp.get())->setRole(role);
}

void AmsServer::setHostPort( const string& host, int port )
{
	((CAmsAppI*)amsApp.get())->setDataSrvInfo(host, port);
}
