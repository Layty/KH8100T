#ifndef RDBTABLEFACTORY_H
#define RDBTABLEFACTORY_H

#include <vector>
#include <QtCore/QtCore>
#include <string>
#include <vector>

#include "rdbTableDefine.h"
#include "xmlStreamReader.h"

using namespace std;
typedef vector<string> StringVector;

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

	// ��ȡʵʱ���б���ֶ���Ϣ
	static void getTableFields(const QString& tableName, RdbFieldStructList& fields);

	// ���ݱ��������������ָ��
	static bool createTablePtr(const QString& tableName, BaseTablePtr& tablePtr);

	// �������ļ��ж�ȡ�Ѽ�¼��mRID
	static void readTableMRIDs();

	// ����¼��mRID�����������ļ�
	static void saveTableMRIDs();

	// �����µ�mRID
	static void insertMRID(const QString& tableName, const string& mRID);

	// ��ȡָ���������mRID
	static QVector<string>& getTableMRIDs(const QString& tableName);

private:
	static RdbStruct	_rdbStruct;

	static QMap<QString, BaseTablePtr>	_tablePtrs;

	static QMap< QString, QVector<string> > _tableMRIDs;	// ���б��mRID
};

#endif