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

// ʵʱ���ṹ
struct RdbTableStruct
{
	QString	name;
	QVector<RdbFieldStruct>	fields;
};

// ʵʱ��ṹ
struct RdbStruct 
{
	QVector<RdbTableStruct>	tables;

	bool isEmpty() const
	{
		return tables.isEmpty();
	}
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