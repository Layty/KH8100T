#ifndef RDBTABLEDEFINE_H
#define RDBTABLEDEFINE_H

#include <QtCore/QtCore>

#include "xmlStreamReader.h"

// ʵʱ�������
class RdbTableFactory
{
public:
	// ��ʼ��ʵʱ��ṹ
	static bool initRdbStruct();

	// ��ȡʵʱ���б�ĸ���
	static int getTableCount();

	// ��ȡʵʱ���б���
	static QString getTableName(int index);

	// ��ȡʵʱ�������еı���
	static QStringList getTableNames();

	// ��ȡʵʱ���б���ֶ���
	static QStringList getTableFields(const QString& tableName);

private:
	static RdbStruct	_rdbStruct;
};

#endif