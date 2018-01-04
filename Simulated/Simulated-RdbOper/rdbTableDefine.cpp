
#include <QtWidgets/QtWidgets>

#include "rdbTableDefine.h"

RdbStruct RdbTableFactory::_rdbStruct = RdbStruct();

bool RdbTableFactory::initRdbStruct()
{
	if (!_rdbStruct.isEmpty())
	{
		return true;
	}

	XmlStreamReader reader;
	if(!reader.readFile("conf/rdbtable.xml", _rdbStruct))
	{
		QMessageBox::warning(0, QStringLiteral("��ʼʵʱ��ṹ"), QStringLiteral("��ʼʧ��"));
		return false;
	}

	return true;
}

// ��ȡ��������
int RdbTableFactory::getTableCount()
{
	if(!initRdbStruct())
	{
		return 0;
	}
	return _rdbStruct.getTableCount();
}

// ��ȡ������
QString RdbTableFactory::getTableName(int index)
{
	if(!initRdbStruct())
	{
		return "";
	}

	return _rdbStruct.getTableName(index);
}

// ��ȡʵʱ�������еı���
QStringList RdbTableFactory::getTableNames()
{
	if (!initRdbStruct())
	{
		return QStringList();
	}

	return _rdbStruct.getTableNames();
}

// ��ȡʵʱ���б���ֶ���
QStringList RdbTableFactory::getTableFields( const QString& tableName )
{
	if (!initRdbStruct())
	{
		return QStringList();
	}

	return _rdbStruct.getTableFields(tableName);
}

