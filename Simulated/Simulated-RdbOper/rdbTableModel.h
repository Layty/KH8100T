#ifndef RDBTABLEMODEL_H
#define RDBTABLEMODEL_H

#include <QtWidgets/QtWidgets>

/************************************************************************/
/* ʵʱ�����ģ��                                                       */
/************************************************************************/
class RdbTableNameModel : public QAbstractListModel
{
	Q_OBJECT

public:
	RdbTableNameModel(QObject* parent = 0);

	int rowCount(const QModelIndex &parent /* = QModelIndex() */) const;

	QVariant data(const QModelIndex &index, int role /* = Qt::DisplayRole */) const;
};

/************************************************************************/
/* ʵʱ����ֶ�ģ��                                                     */
/************************************************************************/

#endif