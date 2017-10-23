
#include "DbTransactionLoggerThread.h"
#include "FastdbManager.h"
#include "common.h"

DbTransactionLoggerThread::DbTransactionLoggerThread( QObject* parent /*= 0*/ )
	: QThread(parent), m_isStop(false),
	m_lastChangeLoggerTime(QDateTime::currentDateTime())
{
	m_fastdbManager = FastdbManagerInstance::getFastdbManagerInstance();
}

DbTransactionLoggerThread::~DbTransactionLoggerThread()
{

}

void DbTransactionLoggerThread::setStop( bool stop /*= true*/ )
{
	m_isStop = stop;
}

void DbTransactionLoggerThread::run()
{
	// ��ʼ����ʱΪʵʱ������������־�ļ�
	m_fastdbManager->setTransactionLogger(NULL);
	string loggerName = getTransLoggerName().toStdString();
	m_fastdbManager->setTransactionLogger(loggerName, dbFile::truncate|dbFile::no_sync);
	emit outputOperationInfo(QStringLiteral("����������־�ļ�:%1").arg(QString().fromStdString(loggerName)));

	while(!m_isStop)
	{
		// ÿ��ָ��ʱ�����һ����־�ļ�
		if (isNeedChangeTransLogger())
		{
			string loggerName = getTransLoggerName().toStdString();
			m_fastdbManager->setTransactionLogger(loggerName, dbFile::truncate|dbFile::no_sync);
			emit outputOperationInfo(QStringLiteral("����������־�ļ�:%1").arg(QString().fromStdString(loggerName)));
		}

		QThread::msleep(1);
	}

	m_fastdbManager->closeTransactionLogger();
	m_fastdbManager->setTransactionLogger(NULL);
}

bool DbTransactionLoggerThread::isNeedChangeTransLogger()
{
	// ����ָ��ʱ������Ҫ����  1min
	QDateTime currTime = QDateTime::currentDateTime();
	if ((currTime.toTime_t() - m_lastChangeLoggerTime.toTime_t()) >= 10)
	{
		m_lastChangeLoggerTime = currTime;
		return true;
	}
	return false;
}

QString DbTransactionLoggerThread::getTransLoggerName()
{
	QTime time = m_lastChangeLoggerTime.time();
	return QString("%1/%2-%3-%4.log").arg(LoggerPathName).arg(time.hour()).arg(time.minute()).arg(time.second());
}
