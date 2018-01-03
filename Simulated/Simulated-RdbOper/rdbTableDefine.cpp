
#include <QtWidgets/QtWidgets>

#include "rdbTableDefine.h"

string RdbTableFactory::sat_table_names[] = 
{
	"GeographicalRegion",
	"SubGeographicalRegion",
	"Area",
	"RemoteUnit",
	"AnalogUnitPoint",
	"DiscreteUnitPoint",
	"ControlUnitPoint",
	"Analog",
	"Discrete",
	"Accumulator",
	"Command",
	"AnalogCurveData",
	"BaseVoltage",
	"Substation",
	"VoltageLevel",
	"BusbarSection",
	"Line",
	"ACLineSegment",
	"Breaker",
	"Disconnector",
	"PowerTransformer",
	"TransformerWinding",
	"ConnectivityNode",
	"Terminal",
	"FormulaDefinition",
	"VariableDefinition"
};

RdbStruct RdbTableFactory::_rdbStruct = RdbStruct();

// ��ȡ������
std::string RdbTableFactory::getTableName(int index)
{
	//if (index < 0 || index >= RdbTable_Count)
	//{
	//	throw "getTableName() out of range";
	//}

	//return sat_table_names[index];

	initRdbStruct();
	return _rdbStruct.tables[index].name.toStdString();
}

void RdbTableFactory::initRdbStruct()
{
	if (!_rdbStruct.isEmpty())
	{
		return;
	}

	XmlStreamReader reader;
	if(!reader.readFile("conf/rdbtable.xml", _rdbStruct))
	{
		QMessageBox::warning(0, QStringLiteral("��ʼʵʱ��ṹ"), QStringLiteral("��ʼʧ��"));
		return;
	}
}

