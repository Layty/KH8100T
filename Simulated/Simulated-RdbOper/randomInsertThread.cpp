
#include "logger.h"
#include "randomInsertThread.h"
#include "rdbTableDefine.h"
#include "rdbTableFactory.h"

RandomInsertThread::RandomInsertThread(QObject* parent /*= 0*/ )
	: QThread(parent), m_stop(false), m_count(0)
{
	readTableMRIDs();
}

void RandomInsertThread::setStop( bool stop )
{
	m_stop = stop;
}

void RandomInsertThread::setTableName( const QString& tableName )
{
	m_tableName = tableName;
}

void RandomInsertThread::setCount( int count )
{
	m_count = count;
}

void RandomInsertThread::setRdbDataOptPrx( const RdbDataOptPrx& rdbDataOptPrx )
{
	m_rdbDataOptPrx = rdbDataOptPrx;
}

void RandomInsertThread::run()
{
	int count = 0;
	int successCount = 0;
	int failCount = 0;
	qsrand(QTime::currentTime().msec());
	while(!m_stop && count < m_count)
	{
		RespondCompleteDataSeq repSeq;
		repSeq.id = 1;
		repSeq.requestId = 1;
		repSeq.requestNode = "randomInsert";

		RespondCompleteData data;
		data.tableName = m_tableName.toStdString();
		getRandomDataValues(m_tableName, data.dataValues);

		repSeq.seq.push_back(data);
		repSeq.dataCount = repSeq.seq.size();

		logData(m_tableName, data.dataValues);
		
		RespondCompleteDataSequence repSequence;
		bool result = m_rdbDataOptPrx->InsertData(repSeq, repSequence);
		if (result)
		{
			++successCount;
			RdbTableFactory::insertMRID(m_tableName, data.dataValues.at(0));
			RdbLog(CLogger::Log_INFO, "����ɹ�");
		}
		else
		{
			++failCount;
			RdbLog(CLogger::Log_INFO, "!!!!!!!!!!!!!! ����ʧ�� !!!!!!!!!!!!!!!");
		}

		++count;
		emit updateInsertCount(count);
	}
	emit updateInsertCount(count);

	if (!m_stop)
	{
		// �������
		QString text = QStringLiteral("������ɣ����������� %1 ��: �ɹ� %2 ��, ʧ�� %3 ��")
						.arg(count).arg(successCount).arg(failCount);
		emit updateResultText(text);
	}
	else
	{
		// ����δ��ɣ���ǰ��ֹ
		QString text = QStringLiteral("�����˹���ֹ������������ %1 ��: �ɹ� %2 ��, ʧ�� %3 ��")
			.arg(count).arg(successCount).arg(failCount);
		emit updateResultText(text);
	}
	m_stop = false;
	saveTableMRIDs();
}

void RandomInsertThread::getRandomDataValues( const QString& tableName, RdbRealData::Strings& dataValues )
{
	BaseTablePtr tablePtr;
	if (!RdbTableFactory::createTablePtr(tableName, tablePtr) || tablePtr.isNull())
	{
		return;
	}

	tablePtr->getRandomValues(dataValues);
}

void RandomInsertThread::logData( const QString& tableName, RdbRealData::Strings& dataValues )
{
	string datas("");
	for (size_t i = 0; i < dataValues.size(); ++i)
	{
		datas += (i == 0 ? "" : ", ");
		datas += dataValues[i];
	}
	RdbLog(CLogger::Log_INFO, "ʵʱ��� %s �������� %s", tableName.toStdString().c_str(), datas.c_str());
}

void RandomInsertThread::readTableMRIDs()
{
	RdbTableFactory::readTableMRIDs();
}

void RandomInsertThread::saveTableMRIDs()
{
	RdbTableFactory::saveTableMRIDs();
}
