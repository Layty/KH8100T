
#include <IceUtil/IceUtil.h>

#include "rdbTableFactory.h"

#define AreaCountPerSubGeographicalRegion		1		// ÿ��������������������
#define SubstationCountPerSubGeographicalRegion	2		// ÿ������������ı��վ����
#define SubstationCountPerArea					8		// ÿ����������ı��վ����
#define BusbarCountPerSubstation				2		// ÿ�����վ������ĸ�߸���
#define BreakerCountPerSubstation				4		// ÿ�����վ�����Ķ�·������
#define DisconnectorCountPerSubstation			4		// ÿ�����վ�����ĵ�բ����
#define PowerTransCountPerSubstation			2		// ÿ�����վ�����ı�ѹ������
#define TransformCountPerSubstation				4		// ÿ�����վ�������������
#define TransformCountPerPowerTrans				2		// ÿ����ѹ���������������
#define LineCountPerSubstation					2		// ÿ�����վ��������·����
#define DeviceTypeCountPerManufacture			5		// ÿ���豸���Ұ������豸���͸���
#define PointCountPerRemoteUnit					1000	// ÿ����Ԫ�ĵ�Ÿ���

/************************************************************************/
/* �����                                                               */
/************************************************************************/
void BaseTable::getRandomValues( StringVector& values )
{
	QString tableName = getTableName();
	// ���ݱ�����ȡ����ֶ���Ϣ
	RdbFieldStructList fields;
	RdbTableFactory::getTableFields(tableName, fields);

	getRandomValuesImpl(fields, values);
}

void BaseTable::getRandomValuesImpl( const RdbFieldStructList& fields, StringVector& values )
{
	// Ϊ�ֶθ������ֵ
	foreach(const RdbFieldStruct& field, fields)
	{
		QString fieldType = field.fieldType;
		QString fieldName = field.fieldName;

		generateCommonRandomValue(field, values);
	}
}

void BaseTable::generateCommonRandomValue( const RdbFieldStruct& field, StringVector& values )
{
	QString tableName = getTableName();
	QString fieldType = field.fieldType;
	QString fieldName = field.fieldName;
	if (fieldType == "string")
	{
		if (fieldName == "mRID")
		{
			values.push_back(generateMRID());
		}
		else if (fieldName == "name")
		{
			values.push_back(generateName());
		}
		else if (fieldName == "pathName")
		{
			values.push_back(generateMRID());
		}
		else
		{
			QString text = QString("%1-%2").arg(tableName).arg(qrand());
			values.push_back(text.toStdString());
		}
	}
	else if (fieldType == "int")
	{
		int value = qrand();
		values.push_back(QString::number(value).toStdString());
	}
	else if (fieldType == "double")
	{
		double value = ((double)qrand() * 5.0) / 3.0;
		values.push_back(QString::number(value).toStdString());
	}
	else if (fieldType == "bool")
	{
		bool value = (qrand() % 2 == 0);
		values.push_back(QString::number(value).toStdString());
	}
	else
	{
		if (fieldName == "ec_type" || fieldName == "psrType")
		{
			values.push_back(fieldType.toStdString());
		}
		else
		{
			QVector<string> tableMRIDs = RdbTableFactory::getTableMRIDs(fieldType);
			if (!tableMRIDs.isEmpty())
			{
				int index = qrand() % tableMRIDs.size();
				values.push_back(tableMRIDs.at(index));
			}
			else
			{
				values.push_back("");
			}
		}		
	}
}

// ����mRID
std::string BaseTable::generateMRID()
{
	return IceUtil::generateUUID();
}

// ����name
std::string BaseTable::generateName()
{
	QDateTime current = QDateTime::currentDateTime();
	QDate currentDate = current.date();
	QTime currentTime = current.time();
	QString displayName = getTableDisplayName();
	QString name = QStringLiteral("%1-%2%3%4%5%6%7").arg(displayName).arg(currentDate.month()).arg(currentDate.day())
					.arg(currentTime.hour()).arg(currentTime.minute()).arg(currentTime.second())
					.arg(currentTime.msec());
	return name.toLocal8Bit().toStdString();
}

// ��ȡ���õĶ����mRID
std::string BaseTable::getMRIDOfReferenceObject( const QString& tableName, int index, int perValue )
{
	QVector<string> tableMRIDs = RdbTableFactory::getTableMRIDs(tableName);
	if (!tableMRIDs.isEmpty())
	{
		int i = ((index -1) / perValue) + 1;
		if (i < tableMRIDs.size())
		{
			return tableMRIDs[i];
		}
		else
		{
			return tableMRIDs[0];
		}
	}
	
	return "";
}

/************************************************************************/
/* �����                                                               */
/************************************************************************/
QString GeographicalRegionTable::getTableName() const
{
	return "GeographicalRegion";
}

QString GeographicalRegionTable::getTableDisplayName() const
{
	return QStringLiteral("����");
}

void GeographicalRegionTable::getRandomValuesImpl( const RdbFieldStructList& fields, StringVector& values )
{
	BaseTable::getRandomValuesImpl(fields, values);
}

/************************************************************************/
/* �������                                                             */
/************************************************************************/
QString SubGeographicalRegionTable::getTableName() const
{
	return "SubGeographicalRegion";
}

QString SubGeographicalRegionTable::getTableDisplayName() const
{
	return QStringLiteral("������");
}

void SubGeographicalRegionTable::getRandomValuesImpl( const RdbFieldStructList& fields, StringVector& values )
{
	BaseTable::getRandomValuesImpl(fields, values);
}

/************************************************************************/
/* �����                                                             */
/************************************************************************/
QString AreaTable::getTableName() const
{
	return "Area";
}

QString AreaTable::getTableDisplayName() const
{
	return QStringLiteral("����");
}

void AreaTable::getRandomValuesImpl( const RdbFieldStructList& fields, StringVector& values )
{
	static int areaCount = 0;
	areaCount++;

	// Ϊ�ֶθ������ֵ
	foreach(const RdbFieldStruct& field, fields)
	{
		QString fieldType = field.fieldType;
		QString fieldName = field.fieldName;
		if (fieldName == "ec_rid")
		{
			values.push_back(getMRIDOfReferenceObject(fieldType, areaCount, AreaCountPerSubGeographicalRegion));
		}
		else
		{
			generateCommonRandomValue(field, values);
		}
	}
}
/************************************************************************/
/* ���վ��                                                             */
/************************************************************************/
QString SubstationTable::getTableName() const
{
	return "Substation";
}

QString SubstationTable::getTableDisplayName() const
{
	return QStringLiteral("���վ");
}

void SubstationTable::getRandomValuesImpl( const RdbFieldStructList& fields, StringVector& values )
{
	static int substationCount = 0;
	substationCount++;

	// Ϊ�ֶθ������ֵ
	foreach(const RdbFieldStruct& field, fields)
	{
		QString fieldType = field.fieldType;
		QString fieldName = field.fieldName;
		if (fieldName == "ec_type")
		{
			if (substationCount <= 200)
			{
				values.push_back("SubGeographicalRegion");
			}
			else
			{
				values.push_back("Area");
			}
		}
		else if (fieldName == "ec_rid")
		{
			if (substationCount <= 200)
			{
				values.push_back(getMRIDOfReferenceObject("SubGeographicalRegion", substationCount, 
					SubstationCountPerSubGeographicalRegion));
			}
			else
			{
				values.push_back(getMRIDOfReferenceObject("Area", substationCount - 200, 
					SubstationCountPerArea));
			}
		}
		else
		{
			generateCommonRandomValue(field, values);
		}
	}
}

/************************************************************************/
/* ĸ�߱�                                                             */
/************************************************************************/
QString BusbarSectionTable::getTableName() const
{
	return "BusbarSection";
}

QString BusbarSectionTable::getTableDisplayName() const
{
	return QStringLiteral("ĸ��");
}

void BusbarSectionTable::getRandomValuesImpl( const RdbFieldStructList& fields, StringVector& values )
{
	static int busbarCount = 0;
	busbarCount++;

	// Ϊ�ֶθ������ֵ
	foreach(const RdbFieldStruct& field, fields)
	{
		QString fieldType = field.fieldType;
		QString fieldName = field.fieldName;
		if (fieldName == "ec_rid")
		{
			values.push_back(getMRIDOfReferenceObject(fieldType, busbarCount, 
				BusbarCountPerSubstation));
		}
		else
		{
			generateCommonRandomValue(field, values);
		}
	}
}

/************************************************************************/
/* ��·��                                                             */
/************************************************************************/
QString LineTable::getTableName() const
{
	return "Line";
}

QString LineTable::getTableDisplayName() const
{
	return QStringLiteral("��·");
}

void LineTable::getRandomValuesImpl( const RdbFieldStructList& fields, StringVector& values )
{
	static int lineCount = 0;
	lineCount++;

	// Ϊ�ֶθ������ֵ
	foreach(const RdbFieldStruct& field, fields)
	{
		QString fieldType = field.fieldType;
		QString fieldName = field.fieldName;
		if (fieldName == "ec_rid")
		{
			values.push_back(getMRIDOfReferenceObject(fieldType, lineCount, 
				LineCountPerSubstation));
		}
		else
		{
			generateCommonRandomValue(field, values);
		}
	}
}

/************************************************************************/
/* ��·����                                                             */
/************************************************************************/
QString BreakerTable::getTableName() const
{
	return "Breaker";
}

QString BreakerTable::getTableDisplayName() const
{
	return QStringLiteral("��·��");
}

void BreakerTable::getRandomValuesImpl( const RdbFieldStructList& fields, StringVector& values )
{
	static int breakerCount = 0;
	breakerCount++;

	// Ϊ�ֶθ������ֵ
	foreach(const RdbFieldStruct& field, fields)
	{
		QString fieldType = field.fieldType;
		QString fieldName = field.fieldName;
		if (fieldName == "ec_rid")
		{
			values.push_back(getMRIDOfReferenceObject(fieldType, breakerCount, 
				BreakerCountPerSubstation));
		}
		else
		{
			generateCommonRandomValue(field, values);
		}
	}
}

/************************************************************************/
/* ��բ��                                                             */
/************************************************************************/
QString DisconnectorTable::getTableName() const
{
	return "Disconnector";
}

QString DisconnectorTable::getTableDisplayName() const
{
	return QStringLiteral("��բ");
}

void DisconnectorTable::getRandomValuesImpl( const RdbFieldStructList& fields, StringVector& values )
{
	static int disconnectorCount = 0;
	disconnectorCount++;

	// Ϊ�ֶθ������ֵ
	foreach(const RdbFieldStruct& field, fields)
	{
		QString fieldType = field.fieldType;
		QString fieldName = field.fieldName;
		if (fieldName == "ec_rid")
		{
			values.push_back(getMRIDOfReferenceObject(fieldType, disconnectorCount, 
				DisconnectorCountPerSubstation));
		}
		else
		{
			generateCommonRandomValue(field, values);
		}
	}
}

/************************************************************************/
/* ��ѹ����                                                             */
/************************************************************************/
QString PowerTransformerTable::getTableName() const
{
	return "PowerTransformer";
}

QString PowerTransformerTable::getTableDisplayName() const
{
	return QStringLiteral("��ѹ��");
}

void PowerTransformerTable::getRandomValuesImpl( const RdbFieldStructList& fields, StringVector& values )
{
	static int powerTransCount = 0;
	powerTransCount++;

	// Ϊ�ֶθ������ֵ
	foreach(const RdbFieldStruct& field, fields)
	{
		QString fieldType = field.fieldType;
		QString fieldName = field.fieldName;
		if (fieldName == "ec_rid")
		{
			values.push_back(getMRIDOfReferenceObject(fieldType, powerTransCount, 
				PowerTransCountPerSubstation));
		}
		else
		{
			generateCommonRandomValue(field, values);
		}
	}
}

/************************************************************************/
/* �����                                                             */
/************************************************************************/
QString TransformerWindingTable::getTableName() const
{
	return "TransformerWinding";
}

QString TransformerWindingTable::getTableDisplayName() const
{
	return QStringLiteral("����");
}

void TransformerWindingTable::getRandomValuesImpl( const RdbFieldStructList& fields, StringVector& values )
{
	static int transFormCount = 0;
	transFormCount++;

	// Ϊ�ֶθ������ֵ
	foreach(const RdbFieldStruct& field, fields)
	{
		QString fieldType = field.fieldType;
		QString fieldName = field.fieldName;
		if (fieldName == "ec_rid")
		{
			values.push_back(getMRIDOfReferenceObject(fieldType, transFormCount, 
				TransformCountPerSubstation));
		}
		else if (fieldName == "power_tranformer")
		{
			values.push_back(getMRIDOfReferenceObject(fieldType, transFormCount, 
				TransformCountPerPowerTrans));
		}
		else
		{
			generateCommonRandomValue(field, values);
		}
	}
}

/************************************************************************/
/* ��Ԫ��                                                             */
/************************************************************************/
QString RemoteUnitTable::getTableName() const
{
	return "RemoteUnit";
}

QString RemoteUnitTable::getTableDisplayName() const
{
	return QStringLiteral("��Ԫ");
}

void RemoteUnitTable::getRandomValuesImpl( const RdbFieldStructList& fields, StringVector& values )
{
	static int remoteCount = 0;
	remoteCount++;
	// Ϊ�ֶθ������ֵ
	foreach(const RdbFieldStruct& field, fields)
	{
		QString fieldType = field.fieldType;
		QString fieldName = field.fieldName;
		if (fieldName == "IEDID")
		{
			values.push_back(QString().number(remoteCount).toStdString());
		}
		else if (fieldName == "IEDName")
		{
			values.push_back(QStringLiteral("��Ԫ%1").arg(remoteCount).toLocal8Bit().toStdString());
		}
		else if (fieldName == "ec_rid")
		{
			QVector<string> mRIDs = RdbTableFactory::getTableMRIDs("Substation");
			if (mRIDs.size() >= remoteCount)
			{
				values.push_back(mRIDs.at(remoteCount - 1));
			}
			else
			{
				values.push_back("");
			}
		}
		else if (fieldName == "yxNum")
		{
			values.push_back("10000");
		}
		else if (fieldName == "ycNum")
		{
			values.push_back("10000");
		}
		else if (fieldName == "ddNum")
		{
			values.push_back("10000");
		}
		else
		{
			generateCommonRandomValue(field, values);
		}
	}
}

/************************************************************************/
/* ң����                                                             */
/************************************************************************/
QString AnalogUnitPointTable::getTableName() const
{
	return "AnalogUnitPoint";
}

QString AnalogUnitPointTable::getTableDisplayName() const
{
	return QStringLiteral("ң���");
}

void AnalogUnitPointTable::getRandomValuesImpl( const RdbFieldStructList& fields, StringVector& values )
{
	static int analogUnitPointCount = 0;
	analogUnitPointCount++;

	int value1 = analogUnitPointCount / PointCountPerRemoteUnit;
	int value2 = analogUnitPointCount % PointCountPerRemoteUnit;
	int iedIndex = value1 + 1;
	int ycIndex = value2 + 1;

	// Ϊ�ֶθ������ֵ
	foreach(const RdbFieldStruct& field, fields)
	{
		QString fieldType = field.fieldType;
		QString fieldName = field.fieldName;
		if (fieldName == "IEDID")
		{
			values.push_back(QString().number(iedIndex).toStdString());
		}
		else if (fieldName == "YcIndex")
		{
			values.push_back(QString().number(ycIndex).toStdString());
		}
		else if (fieldName == "YcName")
		{
			values.push_back(QStringLiteral("ң��-%1-%2").arg(iedIndex).arg(ycIndex).toLocal8Bit().toStdString());
		}
		else
		{
			generateCommonRandomValue(field, values);
		}
	}
}

/************************************************************************/
/* ң�ŵ��                                                             */
/************************************************************************/
QString DiscreteUnitPointTable::getTableName() const
{
	return "DiscreteUnitPoint";
}

QString DiscreteUnitPointTable::getTableDisplayName() const
{
	return QStringLiteral("ң�ŵ�");
}

void DiscreteUnitPointTable::getRandomValuesImpl( const RdbFieldStructList& fields, StringVector& values )
{
	static int discreteUnitPointCount = 0;
	discreteUnitPointCount++;

	int value1 = discreteUnitPointCount / PointCountPerRemoteUnit;
	int value2 = discreteUnitPointCount % PointCountPerRemoteUnit;
	int iedIndex = value1 + 1;
	int yxIndex = value2 + 1;

	// Ϊ�ֶθ������ֵ
	foreach(const RdbFieldStruct& field, fields)
	{
		QString fieldType = field.fieldType;
		QString fieldName = field.fieldName;
		if (fieldName == "IEDID")
		{
			values.push_back(QString().number(iedIndex).toStdString());
		}
		else if (fieldName == "YcIndex")
		{
			values.push_back(QString().number(yxIndex).toStdString());
		}
		else if (fieldName == "YcName")
		{
			values.push_back(QStringLiteral("ң��-%1-%2").arg(iedIndex).arg(yxIndex).toLocal8Bit().toStdString());
		}
		else
		{
			generateCommonRandomValue(field, values);
		}
	}
}

/************************************************************************/
/* ң�ص��                                                             */
/************************************************************************/
QString ControlUnitPointTable::getTableName() const
{
	return "ControlUnitPoint";
}

QString ControlUnitPointTable::getTableDisplayName() const
{
	return QStringLiteral("ң�ص�");
}

void ControlUnitPointTable::getRandomValuesImpl( const RdbFieldStructList& fields, StringVector& values )
{
	static int controlUnitPointCount = 0;
	controlUnitPointCount++;

	int value1 = controlUnitPointCount / PointCountPerRemoteUnit;
	int value2 = controlUnitPointCount % PointCountPerRemoteUnit;
	int iedIndex = value1 + 1;
	int ykIndex = value2 + 1;

	// Ϊ�ֶθ������ֵ
	foreach(const RdbFieldStruct& field, fields)
	{
		QString fieldType = field.fieldType;
		QString fieldName = field.fieldName;
		if (fieldName == "IEDID")
		{
			values.push_back(QString().number(iedIndex).toStdString());
		}
		else if (fieldName == "CommandID")
		{
			values.push_back(QString().number(ykIndex).toStdString());
		}
		else if (fieldName == "CommandName")
		{
			values.push_back(QStringLiteral("ң��-%1-%2").arg(iedIndex).arg(ykIndex).toLocal8Bit().toStdString());
		}
		else
		{
			generateCommonRandomValue(field, values);
		}
	}
}

/************************************************************************/
/* �豸���ұ�                                                             */
/************************************************************************/
QString DevManufacturerTable::getTableName() const
{
	return "DevManufacturer";
}

QString DevManufacturerTable::getTableDisplayName() const
{
	return QStringLiteral("�豸����");
}

/************************************************************************/
/* �豸���ͱ�                                                             */
/************************************************************************/
QString DevDeviceTypeTable::getTableName() const
{
	return "DevDeviceType";
}

QString DevDeviceTypeTable::getTableDisplayName() const
{
	return QStringLiteral("�豸����");
}

void DevDeviceTypeTable::getRandomValuesImpl( const RdbFieldStructList& fields, StringVector& values )
{
	static int deviceTypeCount = 0;
	deviceTypeCount++;

	// Ϊ�ֶθ������ֵ
	foreach(const RdbFieldStruct& field, fields)
	{
		QString fieldType = field.fieldType;
		QString fieldName = field.fieldName;
		if (fieldName == "manufacturer")
		{
			values.push_back(getMRIDOfReferenceObject(fieldType, deviceTypeCount, DeviceTypeCountPerManufacture));
		}
		else
		{
			generateCommonRandomValue(field, values);
		}
	}
}
