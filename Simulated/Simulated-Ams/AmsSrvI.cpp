#include "AmsSrvI.h"
#include "AmlConst.h"
#include "AmsServerThread.h"
#include "OperationInfo.h"

using namespace Amssrv;
using namespace std;

CAmsAppI::CAmsAppI( AmsServerThread* threadPtr )
	: m_threadPtr(threadPtr)
{
	// ��ʼ�����ݷ������ڵ���Ϣ
	dataSrvInfo.name = "�����ݷ���";
	dataSrvInfo.type = TYPE_DATASRV;
	dataSrvInfo.ip = "192.168.3.25";
	dataSrvInfo.port = DATASRV_ADAPTER_PORT;
}

std::string CAmsAppI::Register( const string& strType, const Strings& ipVect, ::Ice::Int num, 
	ServerNode& serverInfo, const ::Ice::Current& /* = ::Ice::Current */ )
{
	serverInfo = dataSrvInfo;

	OperationInfo info(QString().fromStdString(strType).toInt(), "����ע��", true);
	m_threadPtr->putMessage(info);

	return ROLE_MASTER;
}

void CAmsAppI::FinishRegister( const string& strServerName, const string& strRole, const string& district, 
	const string& section, const ::Ice::Current& /* = ::Ice::Current */ )
{

}

std::string CAmsAppI::GetRole( const string& strServerName, const ::Ice::Current& /* = ::Ice::Current */ ) const
{
	return ROLE_MASTER;
}

void CAmsAppI::Quit( const ::Amssrv::ServerNode&, const ::Ice::Current& /* = ::Ice::Current() */ )
{

}

void CAmsAppI::HeartBeat( const ::std::string&, const ::Ice::Current& /* = ::Ice::Current() */ )
{

}

void CAmsAppI::setDataSrvInfo( const string& ip, int port )
{
	dataSrvInfo.ip = ip;
	dataSrvInfo.port = port;
}
