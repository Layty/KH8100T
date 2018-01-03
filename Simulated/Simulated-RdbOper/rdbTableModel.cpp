
#include "rdbTableDefine.h"
#include "rdbTableModel.h"

/************************************************************************/
/* ʵʱ�����ģ��                                                       */
/************************************************************************/
RdbTableNameModel::RdbTableNameModel( QObject* parent /*= 0*/ )
	: QAbstractListModel(parent)
{

}

int RdbTableNameModel::rowCount( const QModelIndex &parent /* = QModelIndex() */ ) const
{
	return RdbTableFactory::RdbTable_Count;
}

QVariant RdbTableNameModel::data( const QModelIndex &index, int role /* = Qt::DisplayRole */ ) const
{
	if (role == Qt::DisplayRole)
	{
		return QString().fromStdString(RdbTableFactory::getTableName(index.row()));
	}

	return QVariant();
}