#include "RandomOperateDb.h"
#include "FastdbTableDefine.h"


RandomOperateDb::RandomOperateDb(dbDatabase* dbPtr)
	: m_dbPtr(dbPtr), m_operInfo(QStringLiteral(""))
{

}

RandomOperateDb::~RandomOperateDb()
{

}

void RandomOperateDb::startOperate(OperateMode mode)
{
	if (!m_dbPtr)
	{
		m_operInfo += QStringLiteral("ʵʱ��ָ��Ϊ�գ��޷�����ʵʱ��");
		return;
	}
	if (!m_dbPtr->isAttached())
	{
		m_dbPtr->attach();
	}

	mode = (mode != ModeCount) ? mode : (OperateMode)(getRandValue() % ModeCount);
	switch(mode)
	{
	case InsertMode:
		insertData();
		break;
	case UpdateMode:
		updateData();
		break;
	case DeleteMode:
		//deleteData();
		break;
	case SelectMode:
		selectData();
		break;
	default:
		break;
	}

	if (m_dbPtr->isAttached())
	{
		m_dbPtr->detach();
	}
	return;
}

QString RandomOperateDb::getOperateInfo()
{
	return m_operInfo;
}

void RandomOperateDb::insertData()
{
	QMutexLocker locker(&m_mutex);

	// ÿ�β���ָ����Ŀ������
	const int count = 20;
	m_operInfo += QStringLiteral("�������ݣ�");
	for (int i = 0; i < count; ++i)
	{
		Record record;
		record.id = QUuid::createUuid().toString().toStdString();
		record.iValue = getRandValue();
		record.dValue = getRandValue() / 5.0;
		insert(record);

		QString text = QString().fromStdString(record.output());
		m_operInfo += text + QStringLiteral("\n");

		QThread::msleep(2);
	}
	m_dbPtr->commit();
}

void RandomOperateDb::updateData()
{
	QMutexLocker locker(&m_mutex);

	dbCursor<Record> cursor(dbCursorForUpdate);
	int count = cursor.select();
	m_operInfo += QStringLiteral("�������ݣ� ");
	if (count > 0)
	{
		int value = getRandValue() % 5;
		do 
		{
			cursor->iValue += value;
			cursor->dValue *= value;
			cursor.update();

			QString text = QString().fromStdString(cursor->output());
			m_operInfo += text + QStringLiteral("\n");
		} while (cursor.next());
	}
	else
	{
		m_operInfo += QStringLiteral("������");
	}
	m_dbPtr->commit();
}

void RandomOperateDb::deleteData()
{
	QMutexLocker locker(&m_mutex);

	// ɾ��iValue����ָ��ֵ�ļ�¼
	const int SpecValue = 2500;
	dbCursor<Record> cursor(dbCursorForUpdate);
	int count = cursor.select();
	m_operInfo += QStringLiteral("ɾ�����ݣ� ");
	if (count > 0)
	{
		do 
		{
			if (cursor->iValue > SpecValue)
			{
				QString text = QString().fromStdString(cursor->output());
				m_operInfo += text + QStringLiteral("\n");
			
				cursor.remove();
			}
		} while (cursor.next());
	}
	else
	{
		m_operInfo += QStringLiteral("������");
	}
	m_dbPtr->commit();
}

void RandomOperateDb::selectData()
{
	QMutexLocker locker(&m_mutex);

	dbCursor<Record> cursor(dbCursorViewOnly);
	int count = cursor.select();
	QString text = QString(QStringLiteral("����(%1)")).arg(count);
	m_operInfo += QStringLiteral("��ѯ���ݣ� ") + text;
	if (count > 0)
	{
		do 
		{
			text = QString().fromStdString(cursor->output());
			m_operInfo += text + QStringLiteral("\n");
		} while (cursor.next());
	}
	else
	{
		m_operInfo += QStringLiteral("������");
	}
}

int RandomOperateDb::getRandValue()
{
	qsrand(QDateTime::currentDateTime().toTime_t()); 
	return qrand();
}
