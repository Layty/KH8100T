
#include "common.h"

const char* DatabaseName = "Test-Db";

const char* LoggerPathName = "./logger";

const int OPERATE_SPAN = 2;

QMutex	g_mutex;


QString getServiceType(ServiceType type)
{
	switch(type)
	{
	case MasterService:
		return QStringLiteral("������");
	case SlaveService:
		return QStringLiteral("������");
	case FrameService:
		return QStringLiteral("�����");
	default:
		return QStringLiteral("δ֪����");
	}
}

QString LoggerInfo::getLoggerInfo( QString text, ServiceType type )
{
	QTime currTime = QDateTime::currentDateTime().time();
	return QString("%1:%2:%3\t%4\t%5\n").arg(currTime.hour()).arg(currTime.minute()).arg(currTime.second()).
		arg(getServiceType(type)).arg(text);
}
