#ifndef XMLSTREAMREADER_H
#define XMLSTREAMREADER_H

#include <QtCore/QtCore>
#include <QtXml/QtXml>


// ʵʱ����ֶνṹ
struct RdbFieldStruct
{
	QString fieldName;
	QString	fieldType;
};
typedef QList<RdbFieldStruct>	RdbFieldStructList;

// ʵʱ���ṹ
struct RdbTableStruct
{
	QString	name;
	QVector<RdbFieldStruct>	fields;
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

private:
	QVector<RdbTableStruct>	tables;
};

class XmlStreamReader
{
public:
	bool readFile(const QString& fileName, RdbStruct& rdbStruct);

private:
	void readRdbElement(RdbStruct& rdbStruct);
	void readTableElement(RdbStruct& rdbStruct);
	void readFieldElement(RdbTableStruct& tableStruct);
	void skipUnknownElement();

private:
	QXmlStreamReader	reader;
};
#endif