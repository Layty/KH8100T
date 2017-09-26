#ifndef TABLEOPERATION_H
#define TABLEOPERATION_H

#include "fastdb.h"
#include "rdbtable.h"

#include <QtCore/QtCore>

class TableOperation
{
public:
	TableOperation(dbDatabase* dbPtr);

	// ���ݱ�����ȡ�������ָ��
	bool	getTablePtrByTableName(const QString& tableName);

	// ��ȡ����ֶ���
	QStringList getTableFieldNames(const QString& tableName);

	// ��ȡ�������
	QList<QStringList>	selectDatas(const QString& tableName);

	// �����µ�����
	bool	insertData(const QString& tableName);

	// ɾ��ָ��������
	bool	deleteData(const QString& tableName, const QString& mRID);

	// �޸�ָ��������
	bool	updateData();

private:

	
private:
	dbDatabase*	m_dbPtr;
	BaseTable*	m_tablePtr;
};
#endif