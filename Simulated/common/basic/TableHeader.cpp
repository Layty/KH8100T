#include "TableHeader.h"

QMap<Headers, QString> TableHeader::headerLabels = TableHeader::createTableHeaderLabels();

QMap<Headers, QString> TableHeader::createTableHeaderLabels()
{
	QMap<Headers, QString> labels;
	labels.insert(Header_Operation, QStringLiteral("����"));
	labels.insert(Header_OperTime, QStringLiteral("����ʱ��"));
	labels.insert(Header_Result, QStringLiteral("�������"));
	labels.insert(Header_Reason, QStringLiteral("ʧ��ԭ��"));

	return labels;
}

QStringList TableHeader::getTableHeaderLabels()
{
	QStringList list;
	list << "����" << "����ʱ��" << "�������" << "ʧ��ԭ��";

	return list;
}

//QMap<Headers, QString> TableHeader::getTableHeaderLabels()
//{
//	return TableHeader::headerLabels;
//}
