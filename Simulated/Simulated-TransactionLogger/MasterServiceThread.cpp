
#include "MasterServiceThread.h"
#include "RandomOperateDb.h"
#include "common.h"


MasterServiceThread::MasterServiceThread(QObject* parent)
	: QThread(parent), m_isStop(false), m_lastOperTime(QDateTime::currentDateTime())
{
}

MasterServiceThread::~MasterServiceThread()
{
}

void MasterServiceThread::setStop( bool stop )
{
	m_isStop = stop;
}

void MasterServiceThread::close()
{
	m_db.close();
	tl.close();

	emit outputOperationInfo(LoggerInfo::getLoggerInfo(QStringLiteral("�ر�ʵʱ���������־�ļ��ɹ�"), MasterService));
}

void MasterServiceThread::run()
{
	m_db.open(DatabaseName);
	tl.open(_T("testtl.log"), dbFile::truncate|dbFile::no_sync);
	m_db.setTransactionLogger(&tl);

	emit outputOperationInfo(LoggerInfo::getLoggerInfo(QStringLiteral("��ʵʱ���������־�ļ��ɹ�"), MasterService));

	while(!m_isStop)
	{
		// ÿ��ָ��ʱ�����һ�����ݿ�
		if (isNeedDeal())
		{
			RandomOperateDb operDb(&m_db);
			operDb.startOperate();

			emit outputOperationInfo(LoggerInfo::getLoggerInfo(operDb.getOperateInfo(), MasterService));
		}
	}

	m_isStop = false;
	close();
}

bool MasterServiceThread::isNeedDeal()
{
	QDateTime currTime = QDateTime::currentDateTime();
	if ((currTime.toTime_t() - m_lastOperTime.toTime_t()) > OPERATE_SPAN)
	{
		m_lastOperTime = currTime;
		return true;
	}
	return false;
}
