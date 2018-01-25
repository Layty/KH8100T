#ifndef XMLSTREAMREADER_H
#define XMLSTREAMREADER_H

#include <QtCore/QtCore>
#include <QtXml/QtXml>


// ʵʱ����ֶνṹ
struct RdbFieldStruct
{
	QString fieldName;
	QString	fieldValue;
};
typedef QList<RdbFieldStruct>	RdbFieldStructList;

// ʵʱ�������
struct RdbDataStruct
{
	RdbFieldStructList fields;
};
typedef QVector<RdbDataStruct>	RdbDataStructVct;

// ʵʱ���ṹ
struct RdbTableStruct
{
	QString	name;
	RdbDataStructVct	datas;
	QVector<RdbFieldStruct>  fields;
};

// ʵʱ��ṹ
class RdbStruct 
{
public:	
	RdbStruct();

	void addRdbTableStruct(const RdbTableStruct& table);

	int getTableCount() const;
	QString getTableName(int index) const;
	QStringList getTableNames() const;
	QStringList getTableFields(const QString& tableName) const;
	void getTableFields(const QString& tableName, RdbFieldStructList& fields) const;
	bool isEmpty() const;

public:
	QVector<RdbTableStruct>	tables;
};

class XmlStreamReader
{
public:
	bool readFile(const QString& fileName, RdbStruct& rdbStruct);

private:
	void readRdbElement(RdbStruct& rdbStruct);
	void readTableElement(RdbStruct& rdbStruct);
	void readDataElement(RdbTableStruct& tableStruct);
	void skipUnknownElement();

private:
	QXmlStreamReader	reader;
};
#endif