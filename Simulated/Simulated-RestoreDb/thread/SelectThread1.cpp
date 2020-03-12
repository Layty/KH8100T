
#include "SelectThread1.h"
#include "FastdbTableDefine.h"
#include "../common.h"

CSelectThread1::CSelectThread1(dbDatabase* db, QObject* parent /*= 0*/)
	: QThread(parent)
{
	m_db = db;
}

void CSelectThread1::run()
{
	QDateTime time1 = QDateTime::currentDateTime();

	m_db->attach();

	dbCursor<AnalogUnitPoint> analogPointCursor;
	dbCursor<Analog> analogCursor;
	
	int count = analogPointCursor.select();
	if (count > 0)
	{
		QDateTime startTime = QDateTime::currentDateTime();
		do 
		{
		} while (analogPointCursor.next());
		QDateTime endTime = QDateTime::currentDateTime();

		QString str = QStringLiteral("��ѯ %1 ��ɣ�����: %2, ��ʱ: %3ms").arg("AnalogUnitPoint")
					.arg(count).arg(startTime.msecsTo(endTime));
		emit outputThreadInfo(LoggerInfo::getLoggerInfo(str, FrameService));
	}

	count = analogCursor.select();
	if (count > 0)
	{
		QDateTime startTime = QDateTime::currentDateTime();
		do 
		{
		} while (analogCursor.next());
		QDateTime endTime = QDateTime::currentDateTime();

		QString str = QStringLiteral("��ѯ %1 ��ɣ�����: %2, ��ʱ: %3ms").arg("Analog")
			.arg(count).arg(startTime.msecsTo(endTime));
		emit outputThreadInfo(LoggerInfo::getLoggerInfo(str, FrameService));
	}
	
	m_db->detach();

	QDateTime time2 = QDateTime::currentDateTime();
	QString str = QStringLiteral("�߳�1��ѯ��ɺ�ʱ: %1ms").arg(time1.msecsTo(time2));
	emit outputThreadInfo(LoggerInfo::getLoggerInfo(str, FrameService));
}
