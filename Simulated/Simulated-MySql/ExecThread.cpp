#include "ExecThread.h"

CExecThread::CExecThread( QObject* parent /*= 0*/ )
	: QThread(parent), m_stop(false), m_mutex(QMutex::NonRecursive)
{
	m_sqlExecPtr = CSqlExecInstance::getSqlExecInstance();
}

void CExecThread::setStop( bool stop )
{
	m_stop = stop;
}

void CExecThread::run()
{
	emit outputOperInfo(getOperInfo(QStringLiteral("��ʼִ���߳�")));

	while(!m_stop)
	{
		selectRecord();

		QThread::sleep(1);
	}

	m_stop = false;
	emit outputOperInfo(getOperInfo(QStringLiteral("����ִ���߳�")));
}

bool CExecThread::selectRecord()
{
	//QMutexLocker locker(&m_mutex);

	if (m_sqlExecPtr.isNull())
	{
		emit outputOperInfo(getOperInfo(QStringLiteral("���ݿ��ѯָ��Ϊ�գ��޷�����")));
		return false;
	}

	QString sql = "select * from city";
	QSqlQuery query;
	if (!m_sqlExecPtr->exec(sql))
	{
		QString error = QString(QStringLiteral("ִ�в�ѯ��������: %1")).arg(m_sqlExecPtr->getError());
		emit outputOperInfo(getOperInfo(error));
		return false;
	}

	emit outputOperInfo(getOperInfo(QStringLiteral("ִ�в�ѯ����")));
	return true;
}

QString CExecThread::getOperInfo( const QString& text )
{
	return QString(QStringLiteral("�߳�Id(%1): %2\n")).arg((unsigned long)(QThread::currentThreadId())).arg(text);
}
