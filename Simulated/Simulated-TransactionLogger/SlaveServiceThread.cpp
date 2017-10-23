
#include "SlaveServiceThread.h"
#include "common.h"

SlaveServiceThread::SlaveServiceThread(QObject* parent)
	: QThread(parent), m_isStop(false), m_lastOperTime(QDateTime::currentDateTime())
{

}

SlaveServiceThread::~SlaveServiceThread()
{
}

void SlaveServiceThread::setStop( bool stop )
{
	m_isStop = stop;
}

void SlaveServiceThread::close()
{
	m_db.close();
	tl.close();
	
	emit outputOperationInfo(LoggerInfo::getLoggerInfo(QStringLiteral("�ر�ʵʱ���������־�ļ��ɹ�"), SlaveService));
}

void SlaveServiceThread::run()
{
	if(!m_db.open(DatabaseName))
	{
		emit outputOperationInfo(LoggerInfo::getLoggerInfo(QStringLiteral("��ʵʱ��ʧ��"), SlaveService));

		return;
	}
	if(!tl.open(_T("testtl.log"), dbFile::read_only))
	{
		emit outputOperationInfo(LoggerInfo::getLoggerInfo(QStringLiteral("��������־�ļ�ʧ��"), SlaveService));

		return;
	}

	emit outputOperationInfo(LoggerInfo::getLoggerInfo(QStringLiteral("��������־�ļ��ɹ�"), SlaveService));
	
	restoreDb();

	while(!m_isStop)
	{
		if (isNeedDeal())
		{
		}
	}

	m_isStop = false;
	close();
}

void SlaveServiceThread::restoreDb()
{
	try 
	{
		size_t n;
		dbFileTransactionLogger::RestoreStatus status = tl.restore(m_db, n);
		if (status == dbFileTransactionLogger::rsOK)
		{
			emit outputOperationInfo(LoggerInfo::getLoggerInfo(QStringLiteral("�ָ�ʵʱ��ɹ�"), SlaveService));
		}
		else
		{
			tl.rollback();
			QString text = QStringLiteral("�ָ�ʵʱ��ʧ��\t����ԭ��: %1").arg(getRestoreStatus(status));
			emit outputOperationInfo(LoggerInfo::getLoggerInfo(text, SlaveService));
		}
	}
	catch(const dbException& ex)
	{
		QString text = QStringLiteral("�ָ�ʵʱ���쳣\t�쳣ԭ��: %1").arg(QString().fromStdString(ex.what()));
		emit outputOperationInfo(LoggerInfo::getLoggerInfo(text, SlaveService));
	}
}

bool SlaveServiceThread::isNeedDeal()
{
	QDateTime currTime = QDateTime::currentDateTime();
	if ((currTime.toTime_t() - m_lastOperTime.toTime_t()) > OPERATE_SPAN)
	{
		m_lastOperTime = currTime;
		return true;
	}
	return false;
}

QString SlaveServiceThread::getRestoreStatus( dbFileTransactionLogger::RestoreStatus status )
{
	switch(status)
	{
	case dbFileTransactionLogger::rsOK:
		return QStringLiteral("rsOK");
	case dbFileTransactionLogger::rsCRCMismatch:
		return QStringLiteral("rsCRCMismatch");
	case dbFileTransactionLogger::rsReadFailed:
		return QStringLiteral("rsReadFailed");
	case dbFileTransactionLogger::rsTableNotFound:
		return QStringLiteral("rsTableNotFound");
	case  dbFileTransactionLogger::rsOIDMismatch:
		return QStringLiteral("rsOIDMismatch");
	default:
		return QStringLiteral("Unknown");
	}
}
