#ifndef RDBTABLEDEFINE_H
#define RDBTABLEDEFINE_H

#include <QtCore/QtCore>
#include <string>
#include <vector>

#include "xmlStreamReader.h"

using namespace std;
typedef vector<string> StringVector;

/************************************************************************/
/* �����                                                               */
/************************************************************************/
class BaseTable
{
public:
	virtual QString getTableName() const = 0;
	virtual QString getTableDisplayName() const = 0;

	virtual void getRandomValues(StringVector& values);
	virtual void getRandomValuesImpl(const RdbFieldStructList& fields, StringVector& values);

protected:
	void generateCommonRandomValue(const RdbFieldStruct& field, StringVector& values);

	// ����mRID
	string generateMRID();

	// ����name
	string generateName();

	// ��ȡ���õĶ����mRID
	string getMRIDOfReferenceObject(const QString& tableName, int index, int perValue);

};
typedef QSharedPointer<BaseTable> BaseTablePtr;

/************************************************************************/
/* �����                                                               */
/************************************************************************/
class GeographicalRegionTable : public BaseTable
{
public:
	virtual QString getTableName() const;
	virtual QString getTableDisplayName() const;

	virtual void getRandomValuesImpl(const RdbFieldStructList& fields, StringVector& values);
};
typedef QSharedPointer<GeographicalRegionTable> GeographicalRegionTablePtr;

/************************************************************************/
/* �������                                                             */
/************************************************************************/
class SubGeographicalRegionTable : public BaseTable
{
public:
	virtual QString getTableName() const;
	virtual QString getTableDisplayName() const;

	virtual void getRandomValuesImpl(const RdbFieldStructList& fields, StringVector& values);
};
typedef QSharedPointer<SubGeographicalRegionTable> SubGeographicalRegionTablePtr;

/************************************************************************/
/* �����                                                             */
/************************************************************************/
class AreaTable : public BaseTable
{
public:
	virtual QString getTableName() const;
	virtual QString getTableDisplayName() const;

	virtual void getRandomValuesImpl(const RdbFieldStructList& fields, StringVector& values);
};
typedef QSharedPointer<AreaTable> AreaTablePtr;

/************************************************************************/
/* ���վ��                                                             */
/************************************************************************/
class SubstationTable : public BaseTable
{
public:
	virtual QString getTableName() const;
	virtual QString getTableDisplayName() const;

	virtual void getRandomValuesImpl(const RdbFieldStructList& fields, StringVector& values);
};
typedef QSharedPointer<SubstationTable> SubstationTablePtr;

/************************************************************************/
/* ĸ�߱�                                                             */
/************************************************************************/
class BusbarSectionTable : public BaseTable
{
public:
	virtual QString getTableName() const;
	virtual QString getTableDisplayName() const;

	virtual void getRandomValuesImpl(const RdbFieldStructList& fields, StringVector& values);
};
typedef QSharedPointer<BusbarSectionTable> BusbarSectionTablePtr;

/************************************************************************/
/* ��·��                                                             */
/************************************************************************/
class LineTable : public BaseTable
{
public:
	virtual QString getTableName() const;
	virtual QString getTableDisplayName() const;

	virtual void getRandomValuesImpl(const RdbFieldStructList& fields, StringVector& values);
};
typedef QSharedPointer<LineTable> LineTablePtr;

/************************************************************************/
/* ��·����                                                             */
/************************************************************************/
class BreakerTable : public BaseTable
{
public:
	virtual QString getTableName() const;
	virtual QString getTableDisplayName() const;

	virtual void getRandomValuesImpl(const RdbFieldStructList& fields, StringVector& values);
};
typedef QSharedPointer<BreakerTable> BreakerTablePtr;

/************************************************************************/
/* ��բ��                                                             */
/************************************************************************/
class DisconnectorTable : public BaseTable
{
public:
	virtual QString getTableName() const;
	virtual QString getTableDisplayName() const;

	virtual void getRandomValuesImpl(const RdbFieldStructList& fields, StringVector& values);
};
typedef QSharedPointer<DisconnectorTable> DisconnectorTablePtr;

/************************************************************************/
/* ��ѹ����                                                             */
/************************************************************************/
class PowerTransformerTable : public BaseTable
{
public:
	virtual QString getTableName() const;
	virtual QString getTableDisplayName() const;

	virtual void getRandomValuesImpl(const RdbFieldStructList& fields, StringVector& values);
};
typedef QSharedPointer<PowerTransformerTable> PowerTransformerTablePtr;

/************************************************************************/
/* �����                                                             */
/************************************************************************/
class TransformerWindingTable : public BaseTable
{
public:
	virtual QString getTableName() const;
	virtual QString getTableDisplayName() const;

	virtual void getRandomValuesImpl(const RdbFieldStructList& fields, StringVector& values);
};
typedef QSharedPointer<TransformerWindingTable> TransformerWindingTablePtr;

/************************************************************************/
/* ��Ԫ��                                                             */
/************************************************************************/
class RemoteUnitTable : public BaseTable
{
public:
	virtual QString getTableName() const;
	virtual QString getTableDisplayName() const;

	virtual void getRandomValuesImpl(const RdbFieldStructList& fields, StringVector& values);

};
typedef QSharedPointer<RemoteUnitTable> RemoteUnitTablePtr;

/************************************************************************/
/* ң����                                                             */
/************************************************************************/
class AnalogUnitPointTable : public BaseTable
{
public:
	virtual QString getTableName() const;
	virtual QString getTableDisplayName() const;

	virtual void getRandomValuesImpl(const RdbFieldStructList& fields, StringVector& values);
};
typedef QSharedPointer<AnalogUnitPointTable> AnalogUnitPointTablePtr;

/************************************************************************/
/* ң�ŵ��                                                             */
/************************************************************************/
class DiscreteUnitPointTable : public BaseTable
{
public:
	virtual QString getTableName() const;
	virtual QString getTableDisplayName() const;

	virtual void getRandomValuesImpl(const RdbFieldStructList& fields, StringVector& values);
};
typedef QSharedPointer<DiscreteUnitPointTable> DiscreteUnitPointTablePtr;

/************************************************************************/
/* ң�ص��                                                             */
/************************************************************************/
class ControlUnitPointTable : public BaseTable
{
public:
	virtual QString getTableName() const;
	virtual QString getTableDisplayName() const;

	virtual void getRandomValuesImpl(const RdbFieldStructList& fields, StringVector& values);
};
typedef QSharedPointer<ControlUnitPointTable> ControlUnitPointTablePtr;

/************************************************************************/
/* �豸���ұ�                                                             */
/************************************************************************/
class DevManufacturerTable : public BaseTable
{
public:
	virtual QString getTableName() const;
	virtual QString getTableDisplayName() const;

};
typedef QSharedPointer<DevManufacturerTable> DevManufacturerTablePtr;

/************************************************************************/
/* �豸���ͱ�                                                             */
/************************************************************************/
class DevDeviceTypeTable : public BaseTable
{
public:
	virtual QString getTableName() const;
	virtual QString getTableDisplayName() const;

	virtual void getRandomValuesImpl(const RdbFieldStructList& fields, StringVector& values);

};
typedef QSharedPointer<DevDeviceTypeTable> DevDeviceTypeTablePtr;

#endif