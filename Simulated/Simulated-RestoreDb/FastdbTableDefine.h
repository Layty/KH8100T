//-------------------------------------------------------------------*--------*
// FastDB���ݿ�ı�ṹ
//-------------------------------------------------------------------*--------*

/*
 * Copyright (c) 2010
 * All rights reserved.
 *
 * �ļ����ƣ�FdbTableDefine.h
 * �ļ���ʶ��FastDB���ݿ����ݿ�ṹ���ඨ��
 * ժҪ��FastDB���ݿ����ݿ�ṹ���ඨ��
 */

/* ��ǰ�汾��0.0.1
 * ���ߣ��ۺ�ǿ
 * ������ڣ�2011-3-8
 *
 */

#ifndef FAST_DB_TABLE_DEFINE_SHQ_H 
#define FAST_DB_TABLE_DEFINE_SHQ_H

#include <fastdb.h>
#include <stdio.h>

#include <iostream>

USE_FASTDB_NAMESPACE

//FA��������
class FATopo;

class IdentifiedObject;
class GeographicalRegion;
class SubGeographicalRegion;
class PowerSystemResource;
class ConnectivityNodeContainer;
class Equipment;

class RemoteUnit;

class EquipmentContainer;
class Terminal;
class ConductingEquipment;
class BaseVoltage;
class Substation;
class VoltageLevel;

class Control;
class Command;

class Measurement;
class Analog;
class Discrete;
class Accumulator;

class Line;

class ConnectivityNode;

class Connector;
class BusbarSection;

class Conductor;
class ACLineSegment;

class Switch;
class Disconnector;
class ProtectedSwitch;
class Breaker;

class PowerTransformer;
class TransformerWinding;

class AnalogCurveData;

class AnalogSectionData;
class DiscreteSectionData;
class AccumulatorSectionData;

class FormulaDefinition;
class VariableDefinition;

class DevManufacturer;
class DevDeviceType;
class DevSettingLine;
class DevSettingType;

class FepPartition;
class FepSection;
class FepProtocol;
class FepChannel;

class SystemRole;
class SystemUser;

class ProtectValueDesc;


//FA���������˱�
class FATopo
{
public:
	std::string mRID;
	std::string name;	//�����ļ���
	std::string configFile;	//��������
	std::string lastTime;	//����޸�ʱ��

	TYPE_DESCRIPTOR((
		KEY(mRID,INDEXED|HASHED),
		FIELD(name),
		FIELD(configFile),
		FIELD(lastTime)));
};

//Ϊ������Ҫ�������Ե����ṩһ��ͨ���������ԵĻ���
// This is a root class to provide common naming attributes for all classes
// needing naming attributes
class IdentifiedObject
{
public:
	// A Model Authority issues mRIDs. Given that each Model Authority has a
	// unique id and this id is part of the mRID, then the mRID is globally
	// unique.
	std::string mRID;

	// The name is a free text human readable name of the object. It may be non
	// unique and may not correlate to a naming hierarchy.
	std::string name;

	// The localName is a human readable name of the object. It is only used
	// with objects organized in a naming hierarchy. The simplest naming
	// hierarchy has just one parent (the root) giving a flat naming hierarchy.
	// However, the naming hierarchy usually has several levels, e.g.
	// Substation, VoltageLevel, Equipment etc. Children of the same parent
	// have names that are unique among them. If the uniqueness requirement
	// cannot be met IdentifiedObject.localName shall not be used, use
	// IdentifiedObject.name  instead.
	std::string localName;

	// The pathname is a system unique name composed from all
	// IdentifiedObject.localNames in a naming hierarchy path from the object
	// to the root.
	std::string pathName;

	// The aliasName is free text human readable name of the object alternative
	// to IdentifiedObject.name. It may be non unique and may not correlate to
	// a naming hierarchy.
	std::string aliasName;

	// The description is a free human readable text describing or naming the
	// object. It may be non unique and may not correlate to a naming
	// hierarchy.
	std::string description;

	TYPE_DESCRIPTOR((KEY(mRID, INDEXED|HASHED),
					KEY(name,INDEXED|HASHED),
					FIELD(localName),
					FIELD(pathName),
					FIELD(aliasName),
					FIELD(description)));

	//insert into IdentifiedObject values ('1','2','3','4','5','6');
};

// A power system resource can be an item of equipment such as a Switch, an
// EquipmentContainer containing many individual items of equipment such as a
// Substation, or an organisational entity such as Company or SubControlArea.
// This provides for the nesting of collections of PowerSystemResources within
// other PowerSystemResources. For example, a Switch could be a member of a
// Substation and a Substation could be a member of a division of a Company.
//##ModelId=35031B8E0006
class PowerSystemResource: public IdentifiedObject
{
public:
	// Classifying instances of the same class, e.g. overhead and underground
	// ACLineSegments. This classification mechanism is intended to provide
	// flexibility outside the scope of this standard, i.e. provide
	// customisation that is non standard.
	//##ModelId=4CF4562700BF
	std::string psrType;

	// The Measurements that are included in the naming hierarchy where the PSR
	// is the containing object
	//##ModelId=39FD839B00A9
	//dbArray< dbReference<Measurement> > measurements;
	//RELATION(measurements, powersystem_resource)

	TYPE_DESCRIPTOR((SUPERCLASS(IdentifiedObject),
					FIELD(psrType)));

};

// A base class for all objects that may contain ConnectivityNodes.
//##ModelId=463FCE6E031E
class ConnectivityNodeContainer: public PowerSystemResource
{
public:

	TYPE_DESCRIPTOR(( SUPERCLASS(PowerSystemResource)));
};

// The parts of a power system that are physical devices, electronic or
// mechanical
//##ModelId=3A8A6F9D007E
class Equipment: public PowerSystemResource
{
public:
	// The association is used in the naming hierarchy.
	//##ModelId=3A8BDEBD027B
	//dbReference<EquipmentContainer> equipment_container;

	std::string ec_type;//�豸�����豸������psrType
	std::string ec_rid;//�豸�����豸������RID

	TYPE_DESCRIPTOR((SUPERCLASS(PowerSystemResource),
					FIELD(ec_type),
					KEY(ec_rid, INDEXED|HASHED)));

};

// ����ɼ��豸����
enum RemoteUnitType
{
	RemoteUnit_Rtu = 0,		// RTU
	RemoteUnit_Prp,			// ����װ��
	RemoteUnit_Ftu,			// FTU
	RemoteUnit_Stu,			// STU
	RemoteUnit_Other,		// ����
	RemoteUnit_PRO_NEW,    //�±���װ�� //chenxin add 2006.6.22
	RemoteUnit_DTS,        //DTS //LJF ADD 2010.4.7
	RemoteUnit_XBJ_300,   
	RemoteUnit_STU_104,	 
	RemoteUnit_DTS_500
};

//����ɼ��豸
class RemoteUnit
{
public:
	std::string mRID;//��¼RID

	int4 IEDID;//IED�豸��
	std::string IEDName;//IED�豸����
	int4 IEDType;//IED�豸����

	std::string timeStamp;//״̬����ʱ��
	int4 status;//�ɼ���Ԫ״ֵ̬

	int4 channelState1;//ͨ��1״̬
	int4 channelState2;//ͨ��2
	int4 errorRate;//������

	int4 safeDays;	// ��ȫ������ÿ����ʱ�Զ���1
	real8	dayRate;	// ��Ͷ����
	real8	monthRate;	// ��Ͷ����

	std::string ec_type;	//�豸�����豸������psrType	
	std::string	ec_rid;		//�豸�����豸������RID

	int4	unitType;	// �豸����

	int			replyTimeouts;		// ����Ӧʱ��
	int			faultJudgeCount;	// �����ж�����
	std::string	paramLine;			// ����
	bool		isTrans;			// �Ƿ�ת��
	bool		manuGetRFW;			// �Ƿ��˹�¼��
	int			statNo;				// վַ
	int			yxNum;				// ң�Ÿ���
	int			ycNum;				// ң�����
	int			ddNum;				// ��ȸ���
	int			ykNum;				// ң�ظ���
	std::string	groupNo;			// ������
	std::string voltage;			// ��ѹ
	std::string electric;			// ����
	std::string facTime;			// ����ʱ��
	std::string runTime;			// Ͷ��ʱ��
	std::string reserved;			// ��ע

	bool	lockFlag;				// �Ƿ����
	bool	holdFlag;				// �Ƿ�������
	bool	holdFaFlag;				// �Ƿ���FA����

	std::string graph;				// ����ͼ��

	dbReference<DevManufacturer>	manufacturer;	// ��������
	dbReference<DevDeviceType>		deviceType;		// �豸�ͺ�

	std::string installTime;		// ��װ����
	std::string deviceModel;		// �豸ģ��

	int update_unitdata(std::string timeStamp, int status, int channelState1, int channelState2, int errorRate)
	{
		int  value_changed = 0;
		if (this->status != status)
			value_changed = 1;
		if ((this->channelState2 != channelState2) &&(channelState2==3 || channelState2==4))
			value_changed += 2;
		this->timeStamp = timeStamp;
		this->status = status;//�ɼ���Ԫ״ֵ̬

		this->channelState1 = channelState1;//ͨ��1״̬
		this->channelState2 = channelState2;//ͨ��2
		this->errorRate = errorRate;//������

		return value_changed;
	}

	TYPE_DESCRIPTOR((KEY(mRID,INDEXED|HASHED),
					KEY(IEDID,INDEXED|HASHED),
					FIELD(IEDName),
					FIELD(IEDType),

					FIELD(timeStamp),
					FIELD(status),

					FIELD(channelState1),
					FIELD(channelState2),
					FIELD(errorRate),
					FIELD(safeDays),
					FIELD(dayRate),
					FIELD(monthRate),
					FIELD(ec_type),
					FIELD(ec_rid),
					FIELD(unitType),
					FIELD(replyTimeouts),
					FIELD(faultJudgeCount),
					FIELD(paramLine),
					FIELD(isTrans),
					FIELD(manuGetRFW),
					FIELD(statNo),
					FIELD(yxNum),
					FIELD(ycNum),
					FIELD(ddNum),
					FIELD(ykNum),
					FIELD(groupNo),
					FIELD(voltage),
					FIELD(electric),
					FIELD(facTime),
					FIELD(runTime),
					FIELD(reserved),
					FIELD(lockFlag),
					FIELD(holdFlag),
					FIELD(holdFaFlag),
					FIELD(graph),
					RELATION(manufacturer, remoteUnits),
					RELATION(deviceType, remoteUnits),
					FIELD(installTime),
					FIELD(deviceModel)
					));
};

//ң����AnalogUnitPoint��
class AnalogUnitPoint
{
public:
	std::string mRID;//	string	��¼ID	Index

	int IEDID;//	int	IED�豸��
	int YcIndex;//	int	ң����
	std::string YcName;//	string	ң������

	TYPE_DESCRIPTOR((KEY(mRID,INDEXED|HASHED),

					FIELD(IEDID),
					FIELD(YcIndex),

					FIELD(YcName)
			));
};

//ң�ŵ��(DiscreteUnitPoint)
class DiscreteUnitPoint
{
public:
	std::string mRID;//	string	��¼ID	Index

	int IEDID;//	int	IED�豸��
	int YxIndex;//	int	ң�ŵ��
	std::string YxName;//	string	ң������

	TYPE_DESCRIPTOR((KEY(mRID,INDEXED|HASHED),

					FIELD(IEDID),
					FIELD(YxIndex),

					FIELD(YxName)
			));
};

//ң�ص��(ControlUnitPoint)
class ControlUnitPoint
{
public:
	std::string mRID;//	string	��¼ID	Index

	int IEDID;//	int	IED�豸��
	int CommandID;//	int	ң�غ�
	std::string CommandName;//	string	ң������

	TYPE_DESCRIPTOR((KEY(mRID,INDEXED|HASHED),

					FIELD(IEDID),
					FIELD(CommandID),

					FIELD(CommandName)
			));
};

//��ȵ��(AccumulatorUnitPoint)
class AccumulatorUnitPoint
{
public:
	std::string mRID;	//	��¼ID

	int IEDID;			//	IED�豸��
	int ddIndex;		//	��Ⱥ�
	std::string ddName;	//	�������

	TYPE_DESCRIPTOR((KEY(mRID,INDEXED|HASHED),
		FIELD(IEDID),
		FIELD(ddIndex),
		FIELD(ddName)
		));
};

// The kind of regulation model.   For example regulating voltage, reactive
// power, active power, etc.
//##ModelId=3748506400EC
// Masf add 20171025 �����QTextStream��fixed�����ı����ͻ�����������ռ�
namespace FdbTableDefine
{
	enum RegulatingControlModeKind
	{
		// Voltage is specified.
		//##ModelId=4CF46A490370
		voltage,

		// Active power is specified.
		//##ModelId=4CF46A5C00C4
		activePower,

		// Reactive power is specified.
		//##ModelId=4CF46A7A03C1
		reactivePower,

		// Current flow is specified.
		//##ModelId=4CF46A9102BD
		currentFlow,

		// The regulation mode is fixed, and thus not regulating.
		//##ModelId=4CF46AAD02D1
		fixed,

		// Admittance is specified
		//##ModelId=4CF46AC802D1
		admittance,

		// Control switches on/off by time of day. The times may change on the
		// weekend, or in different seasons.
		//##ModelId=4CF46AE20123
		timeScheduled,

		// Control switches on/off based on the local temperature (i.e., a
		// thermostat).
		//##ModelId=4CF46AFE0376
		temperature,

		//##ModelId=4CF46B1B0380
		powerFactor

	};
}

// Transformer tap changer type. Indicates the capabilities of the tap changer
// independent of the operating mode.
//##ModelId=3A8A8FE600F1
enum TapChangerKind
{
	//##ModelId=3A8A8FF3019A
	fix,

	//##ModelId=3A8A8FFE01FA
	voltageControl,

	//##ModelId=3A8A901E0296
	phaseControl,

	//##ModelId=3A8A902501EC
	voltageAndPhaseControl

};

// A modeling construct to provide a root class for all Equipment classes
//##ModelId=3A8A6ED701BA
class EquipmentContainer: public ConnectivityNodeContainer
{
public:
	// The association is used in the naming hierarchy.
	//##ModelId=3A8BDEBD026C
	//dbArray< dbReference<Equipment> > equipments;

	TYPE_DESCRIPTOR(( SUPERCLASS(ConnectivityNodeContainer)));

};

// A geographical region of a power system network model.
//##ModelId=4472BD2F0061
class GeographicalRegion: public IdentifiedObject
{
public:
	// The association is used in the naming hierarchy.
	//##ModelId=4472BDC3021D
	dbArray<dbReference<SubGeographicalRegion> > sub_regions;

	TYPE_DESCRIPTOR((SUPERCLASS(IdentifiedObject),
					RELATION(sub_regions, region)));

	//insert into GeographicalRegion values ('a','b','c','d','e','f',#0);
	//insert into GeographicalRegion values ("a");

};

// A subset of a geographical region of a power system network model.
//##ModelId=4472BC870272
class SubGeographicalRegion: public IdentifiedObject
{
public:
	// The association is used in the naming hierarchy.
	//##ModelId=4472BD3B0109
	//dbArray<dbReference<Substation> > stations;

	// The association is used in the naming hierarchy.
	//##ModelId=4472BDC3021F
	dbReference<GeographicalRegion> region;

	//##ModelId=4472C1340165
	//dbArray<dbReference<Line> > lines;

	TYPE_DESCRIPTOR((SUPERCLASS(IdentifiedObject),
					//RELATION(stations, sub_region),
					RELATION(region, sub_regions)
					//RELATION(lines, sub_region)
			));

};

class Area: public IdentifiedObject
{
public:
	std::string psrType;
	std::string ec_type;
	std::string ec_rid;
		
	TYPE_DESCRIPTOR((SUPERCLASS(IdentifiedObject),
		FIELD(psrType),
		FIELD(ec_type),
		FIELD(ec_rid)
		));

};

// An electrical connection point to a piece of conducting equipment. Terminals
// are connected at physical connection points called "connectivity nodes". 
//##ModelId=351588B4030C
class Terminal: public IdentifiedObject
{
public:
	/*
	 // The terminal connection status.   True implies the terminal is
	 // connected, and false implies the terminal is not connected. This is the
	 // result of topoplogical processing of a detailed Connectivity node and
	 // Switch model whether present in the model or not.   A terminal that is
	 // not connected cannot support a current flow.   A terminal that is
	 // connected may have flow.  In general a multi-terminal device may
	 // simultaneously have connected and disconnected terminals.  No other
	 // aspect of the algorithm
	 //##ModelId=4CF459090366
	 bool connected;

	 // The orientation of the terminal connections for a multiple terminal
	 // conducting equipment.  The sequence numbering starts with 1 and
	 // additional terminals should follow in increasing order.   The first
	 // terminal is the "starting point" for a two terminal branch.   In the
	 // case of class TransformerWinding only one terminal is used so its
	 // sequenceNumber must be 1.
	 //##ModelId=4CF4590C0075
	 int4 sequenceNumber;

	 // �����豸ID��
	 //##ModelId=4CF4590D0228
	 int4 deviceId;

	 // �����豸����
	 //##ModelId=4D00904303E4
	 int4 relatedDeviceType;//��Ҫע��:����Ϊenum����

	 // ConductingEquipment has 1 or 2 terminals that may be connected to other
	 // ConductingEquipment terminals via ConnectivityNodes
	 //##ModelId=351691CB024E
	 //dbReference<ConductingEquipment> conducting_equipment;
	 */

	//�˵���������豸��psrType
	std::string ce_type;

	//�˵���������豸��RID
	std::string ce_rid;

	// One or more measurements may be associated with a terminal in the
	// network
	//##ModelId=352FA37000DA
	//dbArray<dbReference<Measurement> > measurements;

	// Terminals interconnect with zero impedance at a node.  Measurements on a
	// node apply to all of its terminals.
	//##ModelId=3516909E021C
	dbReference<ConnectivityNode> connectivity_node;

	TYPE_DESCRIPTOR((SUPERCLASS(IdentifiedObject),

					//FIELD(connected),
					//FIELD(sequenceNumber),
					//FIELD(deviceId),
					//FIELD(relatedDeviceType),

					FIELD(ce_type),
					FIELD(ce_rid),

					//RELATION(conducting_equipment, terminals),
					//RELATION(measurements, terminal),
					RELATION(connectivity_node, terminals)));

};

// Enumeration of phase identifiers. Allows designation of phases for both
// transmission and distribution equipment, circuits and loads.
// Residential and small commercial loads are often served from single-phase,
// or split-phase, secondary circuits. Phases 1 and 2 refer to hot wires that
// are 180 degrees out of phase, while N refers to the neutral wire. Through
// single-phase transformer connections, these secondary circuits may be served
// from one or two of the primary phases A, B, and C. For three-phase loads,
// use the A, B, C phase codes instead of s12N.
//##ModelId=372FD56E0255
enum PhaseCode
{
	//##ModelId=372FD5B603B7
	ABCN,

	//##ModelId=45C20E7E0100
	ABC1,

	//##ModelId=45C20E8201CA
	ABN,

	//##ModelId=45C20E8700FA
	ACN,

	//##ModelId=45C20E89027D
	BCN,

	//##ModelId=45C20E8D02C4
	AB,

	//##ModelId=45C20E95004D
	AC,

	//##ModelId=45C20E990352
	BC,

	//##ModelId=45C20E9E030F
	AN,

	//##ModelId=45C20EA00351
	BN,

	//##ModelId=45C20EA202E8
	CN,

	//##ModelId=45C20EA40383
	A,

	//##ModelId=45C20EA60125
	B,

	//##ModelId=45C20EA702C3
	C,

	//##ModelId=45C20EA803AC
	N,

	// Secondary phase 1 and neutral.
	//##ModelId=4CF454D2020D
	s1N,

	// Secondary phase 2 and neutral.
	//##ModelId=4CF455860105
	s2N,

	// Secondary phases 1, 2, and neutral.
	//##ModelId=4CF455A001E5
	s12N

};

// The parts of the power system that are designed to carry current or that are
// conductively connected therewith. ConductingEquipment is contained within an
// EquipmentContainer that may be a Substation, or a VoltageLevel or a Bay
// within a Substation.
//##ModelId=350370600303
class ConductingEquipment: public Equipment
{
public:
	// Describes the phases carried by a conducting equipment. Possible values
	// { ABCN , ABC, ABN, ACN, BCN, AB, AC, BC, AN, BN, CN, A, B, C, N }.
	//##ModelId=372FD0DA028C
	int4 phase;//enum ����  PhaseCode

	bool powerPoint;//�Ƿ�Ϊ��Դ���豸

	// ConductingEquipment has 1 or 2 terminals that may be connected to other
	// ConductingEquipment terminals via ConnectivityNodes
	//##ModelId=351691CB024F
	//dbArray< dbReference<Terminal> > terminals;

	//##ModelId=3B5770B800C5
	//dbReference<BaseVoltage> base_voltage;
	std::string base_voltage;

	TYPE_DESCRIPTOR((SUPERCLASS(Equipment),
					FIELD(phase),
					FIELD(powerPoint),
					//RELATION(terminals, conducting_equipment),
					//RELATION(base_voltage, conducting_equipments)
					FIELD(base_voltage)

			));

};

// Combination of conducting material with consistent electrical
// characteristics, building a single electrical system, used to carry current
// between points in the power system.
//##ModelId=351578480122
class Conductor: public ConductingEquipment
{
public:
	// Segment length for calculating line section capabilities
	//##ModelId=3522E5BC033A
	real8 line_length;

	TYPE_DESCRIPTOR((SUPERCLASS(ConductingEquipment),
					FIELD(line_length)));
};

// Imaginary part of admittance.
//##ModelId=37A3A7630185
struct Susceptance
{
public:
	//##ModelId=37A3A797037F
	real8 value;

	//##ModelId=45C3786E032D
	//static UnitSymbol unit;

	//##ModelId=45C3786E0337
	int multiplier;

	TYPE_DESCRIPTOR((FIELD(value),
					FIELD(multiplier)));

};

// Factor by which voltage must be multiplied to give corresponding power lost
// from a circuit. Real part of admittance.
//##ModelId=37A3A35E037A
struct Conductance
{
public:
	//##ModelId=37A3A4470158
	real8 value;

	//##ModelId=3E232B5C0113
	//static UnitSymbol unit;

	//##ModelId=45C32D4F034A
	int multiplier;

	TYPE_DESCRIPTOR((FIELD(value),
					FIELD(multiplier)));

};

// Resistance (real part of impedance), in ohms
//##ModelId=350C6E0400F3
struct Resistance
{
public:
	//##ModelId=350C6E0F0153
	real8 value;

	//##ModelId=45C37691005F
	//static UnitSymbol unit;

	//##ModelId=45C376910060
	int multiplier;

	TYPE_DESCRIPTOR((FIELD(value),
					FIELD(multiplier)));

};

// Reactance (imaginary part of impedance), in ohms, at rated frequency
//##ModelId=350C6D01015F
struct Reactance
{
public:
	//##ModelId=350C6D14026A
	real8 value;

	//##ModelId=45C37582025E
	//static UnitSymbol unit;

	//##ModelId=45C37582025F
	int multiplier;

	TYPE_DESCRIPTOR((FIELD(value),
					FIELD(multiplier)));
};

// A wire or combination of wires, with consistent electrical characteristics,
// building a single electrical system, used to carry alternating current
// between points in the power system.
//##ModelId=35109047027F
class ACLineSegment: public Conductor
{
public:
	// Zero sequence shunt (charging) susceptance, uniformly distributed, of
	// the entire line section.
	//##ModelId=4CF489D00180
	//Susceptance b0ch;
	real8 b0ch;

	// Positive sequence shunt (charging) susceptance, uniformly distributed,
	// of the entire line section.
	//##ModelId=4CF489D20086
	//Susceptance bch;
	real8 bch;

	// Zero sequence shunt (charging) conductance, uniformly distributed, of
	// the entire line section.
	//##ModelId=4CF489D302A7
	//Conductance g0ch;
	real8 g0ch;

	// Positive sequence shunt (charging) conductance, uniformly distributed,
	// of the entire line section.
	//##ModelId=4CF489D501D5
	//Conductance gch;
	real8 gch;

	// Positive sequence series resistance of the entire line section.
	//##ModelId=4CF489DE019E
	//Resistance r;
	real8 r;

	// Zero sequence series resistance of the entire line section.
	//##ModelId=4CF489E5019E
	//Resistance r0;
	real8 r0;

	// Positive sequence series reactance of the entire line section.
	//##ModelId=4CF489E90185
	//Reactance x;
	real8 x;

	// Zero sequence series reactance of the entire line section.
	//##ModelId=4CF48D27035C
	//Reactance x0;
	real8 x0;

	TYPE_DESCRIPTOR((SUPERCLASS(Conductor),
					//FIELD(b0ch),
					FIELD(b0ch),
					//FIELD(b0ch_multiplier),
					//FIELD(bch),
					FIELD(bch),
					//FIELD(bch_multiplier),
					//FIELD(g0ch),
					FIELD(g0ch),
					//FIELD(g0ch_multiplier),
					//FIELD(gch),
					FIELD(gch),
					//FIELD(gch_multiplier),
					//FIELD(r),
					FIELD(r),
					//FIELD(r_multiplier),
					//FIELD(r0),
					FIELD(r0),
					//FIELD(r0_multiplier),
					//FIELD(x),
					FIELD(x),
					//FIELD(x_multiplier),
					//FIELD(x0)
					FIELD(x0)
					//FIELD(x0_multiplier)
			));

};

// Inductance, in millihenries
//##ModelId=350C5F6D019D
class Inductance
{
public:
	//##ModelId=350C5F9603B8
	real8 value;

	//##ModelId=45C35DC20142
	//static UnitSymbol unit;

	//##ModelId=45C35DC2014C
	int multiplier;

	TYPE_DESCRIPTOR((FIELD(value),
					FIELD(multiplier)));

};

// A conductor, or group of conductors, with negligible impedance, that serve
// to connect other conducting equipment within a single substation and are
// modelled with a single logical terminal.
//##ModelId=379BDF5F023B
class Connector: public ConductingEquipment
{
public:

	TYPE_DESCRIPTOR(( SUPERCLASS(ConductingEquipment)));
};

// A conductor, or group of conductors, with negligible impedance, that serve
// to connect other conducting equipment within a single substation. 
// Voltage measurements are typically obtained from VoltageTransformers that
// are connected to busbar sections. A bus bar section may have many physical
// terminals but for analysis is modelled with exactly one logical terminal.
// The typeName attribute indicates the type of bus bar section, e.g.: Main,
// Transfer.
//##ModelId=351574AF02E4
class BusbarSection: public Connector
{
public:

	TYPE_DESCRIPTOR(( SUPERCLASS(Connector)));

};

// The units defiend for usage in the CIM
//##ModelId=45C2107500CE
enum UnitSymbol
{
	// Apparent power in volt ampere
	//##ModelId=45C210B60058
	US_VA,

	// Active power in watt
	//##ModelId=45C210C90063
	US_W,

	// Reactive power in volt ampere reactive
	//##ModelId=45C210CA02E7
	US_VAr,

	// Apparent energy in volt ampere hours
	//##ModelId=45C2150C0195
	US_VAh,

	// Real energy in what hours
	//##ModelId=45C214E702CD
	US_Wh,

	// Reactive energy in volt ampere reactive hours
	//##ModelId=45C2153902C2
	US_VArh,

	// Voltage in volt
	//##ModelId=45C210CF015A
	US_V,

	// Resistance in ohm
	//##ModelId=45C211C801C1
	US_ohm,

	// Current in ampere
	//##ModelId=4638E374015E
	US_A,

	// Capacitance in farad
	//##ModelId=45C2126F031B
	US_F,

	// Inductance in henry
	//##ModelId=45C2148E0149
	US_H,

	// Relative temperature in degrees Celsius
	//##ModelId=45C213B100D3
	US_C,

	// Time in seconds
	//##ModelId=45C211350288
	US_s,

	// Time in minutes
	//##ModelId=463FC365015F
	US_min,

	// Time in hours
	//##ModelId=45C34586039A
	US_h,

	// Plane angle in degrees
	//##ModelId=45C2FF9500A7
	US_deg,

	// Plane angle in radians
	//##ModelId=45C214630113
	US_rad,

	// Energy in joule
	//##ModelId=45C214B801CE
	US_J,

	// Force in newton
	//##ModelId=45C2159401DD
	US_N,

	// Conductance in siemens
	//##ModelId=45C2FBBD0009
	US_S,

	// Dimension less quantity, e.g. count, per unit, etc.
	//##ModelId=45C30BB8017E
	US_none,

	// Frequency in hertz
	//##ModelId=45C3424602AB
	US_Hz,

	// Mass in kilogram
	//##ModelId=45C34CA5027B
	US_kg,

	// Pressure in pascal (n/m2)
	//##ModelId=45C371400050
	US_Pa,

	// Length in meter
	//##ModelId=45C361DB013F
	US_m,

	// Area in square meters
	//##ModelId=45C5B68E0206
	US_m2,

	// Volume in cubic meters
	//##ModelId=45C5B6990284
	US_m3,

	// Volt per volt ampere reactive
	//##ModelId=45C333780307
	US_V_VAr,

	// Watt per hertz
	//##ModelId=45C3423000C2
	US_W_Hz,

	// Joule per second
	//##ModelId=45C349070127
	US_J_s,

	// per second
	//##ModelId=4638E3580398
	US_s_1,

	// Mass per energy
	//##ModelId=4638E349031F
	US_kg_J,

	// Watt per second
	//##ModelId=45C36D9B0085
	US_W_s,

	//##ModelId=4CF4707000C0
	US_Hz_1

};

// The unit multipliers defined for the CIM
//##ModelId=45C210E00028
enum UnitMultiplier
{
	// Pico 10**-12
	//##ModelId=45C2134C0142
	p,

	// Nano 10**-9
	//##ModelId=45C21372039D
	n,

	// Micro 10**-6
	//##ModelId=45C2128C017D
	micro,

	// Milli 10**-3
	//##ModelId=45C210F60045
	m,

	// Centi 10**-2
	//##ModelId=45C21105004F
	c,

	// Deci 10**-1
	//##ModelId=45C2110A00AC
	d,

	// Kilo 10**3
	//##ModelId=45C21112009A
	k,

	// Mega 10**6
	//##ModelId=45C211190143
	M,

	// Giga 10**9
	//##ModelId=45C2111D0017
	G,

	// Tera 10**12
	//##ModelId=45C2111E01BE
	T,

	//##ModelId=45CA0C6A0109
	none

};

// Value representing kV
//##ModelId=3503727C02EB
struct Voltage
{
	// Value representing voltage
	//##ModelId=350372850398
	real8 value;

	//##ModelId=350C73570049
	//int4 unit;//enum ����  UnitSymbol ��λ

	//##ModelId=45C2177302B6
	int4 multiplier;//enum ����  UnitMultiplier ����

	TYPE_DESCRIPTOR((FIELD(value),
					FIELD(multiplier)));
};

// Collection of BaseVoltages which is used to verify that the
// BusbarSection.BaseVoltage and other voltage attributes in the CIM are given
// a value existing in the collection.
//##ModelId=379C01D60026
class BaseVoltage: public IdentifiedObject
{
public:
	// The PowerSystemResource's base voltage.
	//##ModelId=379C01EF0298
	//Voltage nominalVoltage;

	real8 nominalVoltage;
	//int4 nominalVoltage_multiplier;

	//##ModelId=3B5770B80093
	//dbArray<dbReference<ConductingEquipment> > conducting_equipments;

	//##ModelId=39FD93460126
	dbArray<dbReference<VoltageLevel> > voltage_levels;

	TYPE_DESCRIPTOR((SUPERCLASS(IdentifiedObject),
					//FIELD(nominalVoltage),
					FIELD(nominalVoltage),
					//FIELD(nominalVoltage_multiplier),
					//RELATION(conducting_equipments,base_voltage ),
					RELATION(voltage_levels,base_voltage )));

};

// A collection of equipment for purposes other than generation or utilization,
// through which electric energy in bulk is passed for the purposes of
// switching or modifying its characteristics. 
//##ModelId=35158764019A
class Substation: public EquipmentContainer
{
public:
	// The association is used in the naming hierarchy.
	//##ModelId=4472BD3B0113
	//dbReference<SubGeographicalRegion> sub_region;

	std::string ec_type;
	std::string ec_rid;

	// The association is used in the naming hierarchy.
	//##ModelId=39F98B9C0210
	//dbArray<dbReference<VoltageLevel> > voltage_levels;

	// The association is used in the naming hierarchy.
	//##ModelId=3A8929F703BE
	//dbArray<dbReference<Bay> > bays;

	TYPE_DESCRIPTOR((SUPERCLASS(EquipmentContainer),
					//RELATION(sub_region,stations ),
					FIELD(ec_type),
					FIELD(ec_rid)
					//RELATION(voltage_levels,substation )
					//RELATION(bays,substation )
			));

};

// A collection of equipment at one common system voltage forming a switchgear.
// The equipment typically consist of breakers, busbars, instrumentation,
// control, regulationand protection devices as well as assemblies of all
// these.
//##ModelId=39F9836D0193
class VoltageLevel: public EquipmentContainer
{
public:
	// The bus bar's high voltage limit
	//##ModelId=39FEC47D01F7
	//Voltage highVoltageLimit;
	real8 highVoltageLimit;
	//int4 highVoltageLimit_multiplier;

	// The bus bar's low voltage limit
	//##ModelId=39FEC48202E1
	//Voltage lowVoltageLimit;
	real8 lowVoltageLimit;
	//int4 lowVoltageLimit_multiplier;

	// The association is used in the naming hierarchy.
	//##ModelId=39F98B9C0211
	//dbReference<Substation> substation;

	std::string ec_type;
	std::string ec_rid;

	//##ModelId=39FD93460116
	dbReference<BaseVoltage> base_voltage;

	// The association is used in the naming hierarchy.
	//##ModelId=39F98BA10378
	//dbArray<dbReference<Bay> > bays;

	TYPE_DESCRIPTOR((SUPERCLASS(EquipmentContainer),
					//FIELD(highVoltageLimit),
					//FIELD(lowVoltageLimit),
					FIELD(highVoltageLimit),
					//FIELD(highVoltageLimit_multiplier),
					FIELD(lowVoltageLimit),
					//FIELD(lowVoltageLimit_multiplier),
					//RELATION(substation,voltage_levels ),
					FIELD(ec_type),
					FIELD(ec_rid),
					RELATION(base_voltage,voltage_levels )
					//RELATION(bays,voltage_level )
			));

};

// Switching arrangement for Bay. 
//##ModelId=37480C0B00B1
enum BreakerConfiguration
{
	//##ModelId=37480E2C0191
	singleBreaker,

	//##ModelId=37480E6F01B5
	breakerAndAHalf,

	//##ModelId=37480E8B0314
	doubleBreaker,

	//##ModelId=37480E9B008C
	noBreaker

};

// Busbar layout for Bay.
//##ModelId=37480ED90027
enum BusbarConfiguration
{

	//##ModelId=37480F3603D8
	singleBus,

	//##ModelId=37480F48010D
	doubleBus,

	//##ModelId=37480F570227
	mainWithTransfer,

	//##ModelId=37480F800370
	ringBus

};


// Date and time as "yyyy-mm-ddThh:mm:ss.sss", which conforms with ISO 8601.
// UTC time zone is specified as "yyyy-mm-ddThh:mm:ss.sssZ". A local timezone
// relative UTC is specified as "yyyy-mm-ddThh:mm:ss.sss-hh:mm".
// AbsoluteDateTime can be used both for calender time, e.g. 2007-02-07T10:30,
// and for relative time, e.g. 10:30.
//##ModelId=35036D32004F
struct AbsoluteDateTime
{
	// String representation of date and time, refer to description of the
	// class.
	//##ModelId=45C5B89B032D
	std::string value;

	TYPE_DESCRIPTOR(( FIELD(value)));

};

// Product of RMS value of the voltage and the RMS value of the quadrature
// component of the current (Megavoltamperes Reactive)
//##ModelId=350C6D4C03CA
struct ReactivePower
{
public:
	//##ModelId=350C6D570343
	real8 value;

	//##ModelId=45C32DB20191
	//static UnitSymbol unit;

	//##ModelId=45C216CC00C6
	int multiplier;

	TYPE_DESCRIPTOR((FIELD(value),
					FIELD(multiplier)));

};

// Phase angle in radians
//##ModelId=350C672C0072
struct AngleRadians
{
public:
	//##ModelId=350C674002D3
	real8 value;

	//##ModelId=45C338D00162
	//static UnitSymbol unit;

	//##ModelId=45C3001503BB
	int multiplier;

	TYPE_DESCRIPTOR((FIELD(value),
					FIELD(multiplier)));
};

// Product of RMS value of the voltage and the RMS value of the in-phase
// component of the current
//##ModelId=350890990101
struct ActivePower
{
public:
	//##ModelId=350890A700ED
	real8 value;

	//##ModelId=45C32D5503DE
	//static UnitSymbol unit;

	//##ModelId=45C20FCD013F
	int multiplier;

	TYPE_DESCRIPTOR((FIELD(value),
					FIELD(multiplier)));
};

// Control is used for supervisory/device control. It represents control
// outputs that are used to change the state in a process, e.g. close or open
// breaker, a set point value or a raise lower command.
//##ModelId=39DDD77502C4
class Control: public IdentifiedObject
{
public:
	// The last time a control output was sent
	//##ModelId=39DDD77502C8
	std::string timeStamp;

	// Indicates that a client is currently sending control commands that has
	// not completed
	//##ModelId=39DDD77502C9
	bool operationInProgress;

	int bilaFlag;//˫��ң�ر�־

	// Specifies the type of Control, e.g. BreakerOn/Off,
	// GeneratorVoltageSetPoint, TieLineFlow etc. The ControlType.name shall be
	// unique among all specified types and describe the type. The
	// ControlType.aliasName is meant to be used for localization.
	//##ModelId=4CF4AD99037D
	//std::string type;

	TYPE_DESCRIPTOR((SUPERCLASS(IdentifiedObject),
					FIELD(timeStamp),
					FIELD(operationInProgress),
					FIELD(bilaFlag)
					//FIELD(type)
			));

};

// A Command is a discrete control used for supervisory control.
//##ModelId=44731DDF01FD
class Command: public Control
{
public:
	std::string psr_type;//ң�ع����ĵ�����Դ��psrType
	std::string psr_rid;//ң�ع����ĵ�����Դ��RID

	int ftuUnitId;//IED�豸��Ԫ��
	int ftuPointId;//IED�豸ң�غ�
	std::string ftuVlDesc;//IED�豸61850ң������

	bool	directControl;	// ֱ�ر�־

	TYPE_DESCRIPTOR((SUPERCLASS(Control),
					KEY(psr_rid, INDEXED | HASHED),
					FIELD(psr_type),
					FIELD(ftuUnitId),
					FIELD(ftuPointId),
					FIELD(ftuVlDesc),
					FIELD(directControl)
			));
};

// A Measurement represents any measured, calculated or non-measured
// non-calculated quantity. Any piece of equipment may contain Measurements,
// e.g. a substation may have temperature measurements and door open
// indications, a transformer may have oil temperature and tank pressure
// measurements, a bay may contain a number of  power flow measurements and a
// Breaker may contain a switch status measurement. 
// The PSR - Measurement association is intended to capture this use of
// Measurement and is included in the naming hierarchy based on
// EquipmentContainer. The naming hierarchy typically has Measurements as
// leafs, e.g. Substation-VoltageLevel-Bay-Switch-Measurement.
// Some Measurements represent quantities related to a particular sensor
// location in the network, e.g. a voltage transformer (PT) at a busbar or a
// current transformer (CT) at the bar between a breaker and an isolator. The
// sensing position is not captured in the PSR - Measurement association.
// Instead it is captured by the Measurement - Terminal association that is
// used to define the sensing location in the network topology. The location is
// defined by the connection of the Terminal to ConductingEquipment. 
// Two possible paths exist:
// 1) Measurement-Terminal- ConnectivityNode-Terminal-ConductingEquipment
// 2) Measurement-Terminal-ConductingEquipment
// Alternative 2 is the only allowed use. 
// When the sensor location is needed both Measurement-PSR and
// Measurement-Terminal are used. The Measurement-Terminal association is never
// used alone.
//##ModelId=351580050154
class Measurement: public IdentifiedObject
{
public:
	// Specifies the type of Measurement, e.g. IndoorTemperature,
	// OutDoorTemperature, BusVoltage, GeneratorVoltage, LineFlow etc.
	//##ModelId=4CF4A22102D8
	//std::string measurementType; yening del in 2011.5.26�ַ���������ʽ���Ǻ�������Ŀǰ��Ӧ��
	int4 measurementType;

	// The unit multiplier of the measured quantity.
	//##ModelId=4CF4A2230085
	int4 unitMultiplier;//enum ����  UnitMultiplier ����

	// The unit of measure of the measured quantity.
	//##ModelId=4CF4A225000D
	int4 unitSymbol;//enum ����  UnitSymbol ��λ

	// ��׼ֵ�Ƿ�У׼���������ֵ�Ƿ���ȷ��
	//##ModelId=4CF4A3E30167
	bool badReference;

	// true��ʾ��ֵ��״̬�������滻��
	//##ModelId=4CF4A40D02C5
	bool estimatorReplaced;

	// �˱�ʶ����ʾ�ල�����Ѿ���⵽һ���ڲ����ⲿ���ϣ����磬ͨѶ���ϡ�
	//##ModelId=4CF4A42B02C0
	bool failure;

	// ��ָ����ʱ�����У�����ֵû�б��ɹ����£�����ֵ�Ǿɵ����ݣ����ҿ�������Ч�ġ�
	//##ModelId=4CF4A45D0220
	bool oldData;

	// ����ֵ�������䴫�䲻�ܽ��С�
	//##ModelId=4CF4A4800036
	bool operatorBlocked;

	// Ϊ�˷�ֹͨѶ�����ɣ����������񵴵ģ����ٱ仯�ģ��������������������ǵġ������һ���涨��ʱ�䣨tosc����ĳ���ź���ͬһ�����ϣ���0��1���1��0���仯�����Σ��ͼ����񵴣������������ʶ��"oscillatory"�ͱ���1�������⵽�񵴣��Ϳ����ӹ�Ԥ���˲ʱ�仯������ʱ��validity
	// ��״̬����Ϊ"questionable"���������һԤ��仯���󻹼���������״̬����Ӧ�ð�ֵ����Ϊ����ǰ���ȶ�ֵ�෴��״̬����������ΪԤ�����ȱʡֵ������������£�ֻҪ�񵴴��ڣ�validity״̬"questionable"����0��"invalid"����1���������õò�����˲ʱ�仯�ӹ����ڰѾ���������ʶ��
	// "oscillatory"��1��ֻ����״̬��Ϣ����ͬʱҲ������validity״̬"invalid"��1��
	//##ModelId=4CF4A4AF03CE
	bool oscillatory;

	// ����ֵ����Ԥ�����ֵ��Χ��
	//##ModelId=4CF4A4D90144
	bool outOfRange;

	// ����ֵ�����ܹ������ʾ�ķ�Χ�ڡ����磬�����������ֵ�������λ���㡣
	//##ModelId=4CF4A4FE020C
	bool overFlow;

	// Source��������ֵ��Դ��ص���Ϣ����ֵ���Դӹ����л�ȡ��������ȱʡֵ�������ֵ��
	//##ModelId=4CF4A51F02ED
	bool source;

	// һ���Աȹ��ܷ���ֵ������ֵ��һ�¡�ͨ��������״̬���������á�
	//##ModelId=4CF4A5560018
	bool suspect;

	// ����ֵ��Ϊ�˲��Ե�Ŀ�Ĵ��䡣
	//##ModelId=4CF4A5760374
	bool test;

	// Validity������good���õģ���questionable�����ɵģ�����invalid����Ч�ģ���
	//##ModelId=4CF4A5A1005E
	bool validity;

	// ���MeasurementValueSource��MeasurementValueSource describes the
	// alternative sources updating a MeasurementValue. User conventions for
	// how to use the MeasurementValueSource attributes are described in the
	// introduction to IEC 61970-301.
	//##ModelId=4CF4A5C3007C
	std::string valueSource;

	// The limit, expressed as a percentage of the sensor maximum, that errors
	// will not exceed when the sensor is used under  reference conditions.
	//##ModelId=4CF4A333019D
	real8 sensorAccuracy;

	// The time when the value was last updated
	//##ModelId=4CF4A3310026
	std::string timeStamp;

	// The PowerSystemResource that contains the Measurement in the naming
	// hierarchy
	//##ModelId=39FD839B00C8
	//dbReference<PowerSystemResource> powersystem_resource;

	//�Ƿ񱣴��������
	bool saveSection;

	//�Ƿ����
	bool lockFlag;

	//�Ƿ����Ƹ澯
	bool holdFlag;

	//PowerSystemResource���������
	std::string psr_type;

	// PowerSystemResource�����RID
	std::string psr_rid;

	// One or more measurements may be associated with a terminal in the
	// network
	//##ModelId=352FA37000CB
	//dbReference<Terminal> terminal;

	TYPE_DESCRIPTOR((SUPERCLASS(IdentifiedObject),
					//FIELD(measurementType),
					KEY(measurementType,INDEXED|HASHED),
					FIELD(unitMultiplier),
					FIELD(unitSymbol),

					FIELD(badReference),
					FIELD(estimatorReplaced),
					FIELD(failure),
					FIELD(oldData),
					FIELD(operatorBlocked),
					FIELD(oscillatory),
					FIELD(outOfRange),
					FIELD(overFlow),
					FIELD(source),
					FIELD(suspect),
					FIELD(test),
					FIELD(validity),

					FIELD(valueSource),

					FIELD(timeStamp),
					FIELD(sensorAccuracy),

					KEY(saveSection,INDEXED|HASHED),

					FIELD(lockFlag),
					FIELD(holdFlag),

					FIELD(psr_type),
					//FIELD(psr_rid)
					KEY(psr_rid,INDEXED|HASHED)

					//RELATION(terminal, measurements)
			));

};

class AnalogType
{
public:
	enum
	{
		Ia = 0, Ib, Ic, Ua, Ub, Uc, Uab, Uca, Ubc, P, Q, Cos
	//�й����޹�����������
	};
};

//ң��Խ��״̬
//0-Խ�����ޣ�1-Խ���ޣ�2-Խ�޻ع飻3-Խ���ޣ�4-Խ������

#define UP_HH_LIMIT			0 //Խ������
#define UP_H_LIMIT			1 //Խ����
#define NORMAL_LIMIT		2 //Խ�޻ع�
#define LOW_L_LIMIT			3 //Խ����
#define LOW_LL_LIMIT		4 //Խ������
#define UP_HH_LIMIT_RET		5 //Խ�����޻ع�
#define UP_H_LIMIT_RET		6 //Խ���޻ع�
#define LOW_LL_LIMIT_RET	7 //Խ�����޻ع�
#define LOW_L_LIMIT_RET		8 //Խ���޻ع�
// Analog represents an analog Measurement.
//##ModelId=40E50BEE0226
class Analog: public Measurement
{
public:
	//�Ƿ񱣴����߱���(�������߱���ľ�Ҫͳ�����ֵ����Сֵ)
	bool saveReport;

	// Normal value range maximum for any of the MeasurementValue.values. Used
	// for scaling, e.g. in bar graphs or of telemetered raw values.
	//##ModelId=447315DB03D3
	real8 maxValue;

	// Normal value range minimum for any of the MeasurementValue.values. Used
	// for scaling, e.g. in bar graphs or of telemetered raw values
	//##ModelId=447315E20026
	real8 minValue;

	// Normal measurement value, e.g., used for percentage calculations.
	//##ModelId=4473166C00D9
	real8 normalValue;

	// If true then this measurement is an active power, reactive power or
	// current with the convention that a positive value measured at the
	// Terminal means power is flowing into the related PowerSystemResource.
	//##ModelId=447317F0019F
	bool positiveFlowIn;

	//ң����
	real8 ratioFactor;

	// The value to supervise.
	//##ModelId=4CF4A6A60285
	real8 value;

	//�Ƿ���Խ��ֵ
	bool checkLimit;

	// ������ֵ
	//##ModelId=4CF4A7EB0343
	real8 hhLimitValue;

	// ����ֵ
	//##ModelId=4CF4A746020D
	real8 hLimitValue;

	// ����ֵ
	//##ModelId=4CF4A80D023F
	real8 lLimitValue;

	// ������ֵ
	//##ModelId=4CF4A82B0230
	real8 llLimitValue;

	// ��������
	real8 hlimitDead;

	// ��������
	real8 llimitDead;

	// Tells if the limit values are in percentage of normalValue or the
	// specified Unit for Measurements and Controls.
	//##ModelId=4CF4A6E802BC
	bool isPercentageLimits;

	//Խ��״̬
	int limitStatus;

	//�ɼ��豸��Ԫ��
	int4 ftuUnitId;

	//�ɼ��豸���
	int4 ftuPointId;

	//61850��Լֵ����
	std::string ftuVlDesc;

	//��λ���
	int4 dw_order;
	
	//��������������
	dbReference<AnalogCurveData> analog_curve;

	//����Ķ�������
	dbReference<AnalogSectionData> analog_sec;

	//�����ļ��㹫ʽ
	dbReference<FormulaDefinition> analog_formula;

	//���Խ��״̬�Ƿ�ı�
	bool checkLimitStatus(double& limit_vl)
	{
		double actual_vl = this->value;

		//�ж��Ƿ���Ҫ���Խ��
		if (!checkLimit)
			return false;

		int new_stauts = NORMAL_LIMIT;
		//��ȡ��״̬,˵��:ң��ֵ�ﵽ�趨�߽缴ΪԽ��
		if (actual_vl >= hhLimitValue)
		{
			limit_vl = hhLimitValue;
			new_stauts = UP_HH_LIMIT;
		}
		else if ((actual_vl < hhLimitValue) && (actual_vl >= hLimitValue))
		{
			limit_vl = hLimitValue;
			new_stauts = UP_H_LIMIT;
		}
		else if ((actual_vl < hLimitValue) && (actual_vl > lLimitValue))
		{
			limit_vl = 0;
			new_stauts = NORMAL_LIMIT;
		}
		else if ((actual_vl <= lLimitValue) && (actual_vl > llLimitValue))
		{
			limit_vl = lLimitValue;
			new_stauts = LOW_L_LIMIT;
		}
		else if (actual_vl <= llLimitValue)
		{
			limit_vl = llLimitValue;
			new_stauts = LOW_LL_LIMIT;
		}

		//�ж�״̬�Ƿ�ı�
		if (new_stauts != limitStatus)
		{
			limitStatus = new_stauts;
			return true;
		}
		else
			return false;
	}

	//����ң��ֵ�����Խ��״̬�仯�򷵻�ֵΪture,����Ϊfalse
	bool update_data(std::string tm, double org_vl, double& limit_vl)
	{
		//����ֵ
		if (lockFlag)
			return false;

		double actual_vl = org_vl * this->ratioFactor;
		
		if(actual_vl <0.000001 && actual_vl> -0.000001)
			actual_vl=0.00;
		
		this->timeStamp = tm;
		this->value = actual_vl;
		limit_vl = 0;

		//�ж��Ƿ���Ҫ���Խ��
		if (!checkLimit)
			return false;

		int new_stauts = NORMAL_LIMIT;
		//��ȡ��״̬,˵��:ң��ֵ�ﵽ�趨�߽缴ΪԽ��
		if (actual_vl >= hhLimitValue)
		{
			limit_vl = hhLimitValue;
			new_stauts = UP_HH_LIMIT;
		}
		else if ((actual_vl < hhLimitValue) && (actual_vl >= hLimitValue))
		{
			limit_vl = hLimitValue;
			new_stauts = UP_H_LIMIT;
		}
		else if ((actual_vl < hLimitValue) && (actual_vl > lLimitValue))
		{
			limit_vl = 0;
			new_stauts = NORMAL_LIMIT;
		}
		else if ((actual_vl <= lLimitValue) && (actual_vl > llLimitValue))
		{
			limit_vl = lLimitValue;
			new_stauts = LOW_L_LIMIT;
		}
		else if (actual_vl <= llLimitValue)
		{
			limit_vl = llLimitValue;
			new_stauts = LOW_LL_LIMIT;
		}

		//�ж�״̬�Ƿ�ı�
		if (new_stauts != limitStatus)
		{
			limitStatus = new_stauts;
			return true;
		}
		else
			return false;

	}

	TYPE_DESCRIPTOR((SUPERCLASS(Measurement),

					KEY(saveReport,INDEXED|HASHED),

					FIELD(maxValue),
					FIELD(minValue),
					FIELD(normalValue),

					FIELD(positiveFlowIn),
					FIELD(ratioFactor),
					FIELD(value),

					KEY(checkLimit,INDEXED|HASHED),
					FIELD(hhLimitValue),
					FIELD(hLimitValue),
					FIELD(lLimitValue),
					FIELD(llLimitValue),

					FIELD(hlimitDead),
					FIELD(llimitDead),

					FIELD(isPercentageLimits),
					FIELD(limitStatus),

					KEY(ftuUnitId,INDEXED|HASHED),
					KEY(ftuPointId,INDEXED|HASHED),
					KEY(ftuVlDesc,INDEXED|HASHED),

					FIELD(dw_order),

					OWNER(analog_curve, analog),
					OWNER(analog_sec, analog),
					OWNER(analog_formula, analog)
			));

};

//���ߵ�ֵ
struct CurvePointValue
{
	bool isValid;//�Ƿ�Ϊ��Чֵ
	real8 value;//ֵ

	TYPE_DESCRIPTOR((FIELD(isValid),
					FIELD(value)));
};

//��ֵ
struct Extremum
{
	std::string tm;//��ֵʱ��
	real8 value;//��ֵ

	TYPE_DESCRIPTOR((FIELD(tm),
					FIELD(value)));
};

//�������ݱ�
class AnalogCurveData
{
public:
	dbDateTime date;//ʱ��(������)

	dbReference<Analog> analog;//������ң����ID

	dbArray<CurvePointValue> pointValues;//���ݵ�����

	bool updateLimit;//�Ƿ�����˼�ֵ
	Extremum maxValue;//���ֵ
	Extremum minValue;//��Сֵ

	//���¼�ֵ
	bool UpdateExtreumValue(std::string tm, double vl)
	{
		if (!updateLimit)
		{
			maxValue.tm = minValue.tm = tm;
			maxValue.value = minValue.value = vl;

			updateLimit = true;
			return true;
		}

		bool is_update = false;

		if (maxValue.value < vl)
		{
			maxValue.tm = tm;
			maxValue.value = vl;

			is_update = true;
		}

		if (minValue.value > vl)
		{
			minValue.tm = tm;
			minValue.value = vl;

			is_update = true;
		}

		return is_update;
	}

	//��õ�ǰ��Ч�ĵ���
	int getValidPointCount()
	{
		dbDateTime tm = dbDateTime::current();
		int count = tm.hour() * 12 + tm.minute() / 5 + 1;

		return count;
	}

	//����ͳ��ֵ
	bool getStatisticsValue(double& ave_vl, std::string& max_tm, double& max_vl, std::string& min_tm, double& min_vl)
	{
		double vl_total = 0;
		int vl_count = 0;

		int is_update = false;

		ave_vl = 0;
		int max_id = 0;
		int min_id = 0;
		max_vl = 0;
		min_vl = 0;

		for (int i = 0; i < pointValues.length(); i++)
		{
			if (pointValues.getat(i).isValid)
			{
				vl_total += pointValues.getat(i).value;
				vl_count++;

				if (!is_update)
				{
					max_id = min_id = i;
					max_vl = min_vl = pointValues.getat(i).value;

					is_update = true;
				}
				else
				{
					if (pointValues.getat(i).value > max_vl)
					{
						max_id = i;
						max_vl = pointValues.getat(i).value;
					}

					if (pointValues.getat(i).value < min_vl)
					{
						min_id = i;
						min_vl = pointValues.getat(i).value;
					}
				}
			}
		}

		dbDateTime max_date(date.asTime_t() + max_id * 5 * 60);
		char temp[128];
		_snprintf(temp, 128, "%04d-%02d-%02d %02d:%02d:%02d", max_date.year(), max_date.month(), max_date.day(),
			max_date.hour(), max_date.minute(), max_date.second());
		max_tm = temp;

		dbDateTime min_date(date.asTime_t() + min_id * 5 * 60);
		_snprintf(temp, 128, "%04d-%02d-%02d %02d:%02d:%02d", min_date.year(), min_date.month(), min_date.day(),
			min_date.hour(), min_date.minute(), min_date.second());
		min_tm = temp;

		if (vl_count > 0)
			ave_vl = vl_total / vl_count;
		return true;
	}

	//��õ�ֵ��ɵ��ַ���
	std::string getPointValues(bool only_valid = false)
	{
		std::string strData;
		char chtmp[128];

		int count = pointValues.length();
		if (only_valid)
		{
			int valid_count = getValidPointCount();
			if (valid_count < count)
				count = valid_count;
		}

		for (int i = 0; i < count; i++)
		{
			if (pointValues.getat(i).isValid)
			{
				_snprintf(chtmp, 128, "%.2f;", pointValues.getat(i).value);
				strData += chtmp;
			}
			else
				strData += ";";
		}

		return strData;
	}

	bool updatePointValues(std::string str_values)
	{
		dbArray<double> actual_values;
		double value;

		int begin_pos = 0;
		int pos = -1;

		while ((pos = str_values.find(';', begin_pos)) != -1)
		{
			value = atof(std::string(str_values.begin() + begin_pos, str_values.begin() + pos).c_str());
			begin_pos = pos + 1;

			actual_values.append(value);
		}

		int valid_count = actual_values.length();
		if (valid_count > pointValues.length())
			valid_count = pointValues.length();

		CurvePointValue vl;
		for (int i = 0; i < pointValues.length(); i++)
		{
			if (i < valid_count)
			{
				vl.isValid = true;
				vl.value = actual_values.getat(i);
				pointValues.putat(i, vl);
			}
			else
			{
				vl.isValid = false;
				vl.value = 0;
				pointValues.putat(i, vl);
			}
		}

		return true;
	}

	//��λ����
	bool resetValue(dbDateTime& new_date, bool isBeginDay = false)
	{
		//ȡʱ���е������ղ���
		dbDateTime rec_date(new_date.year(), new_date.month(), new_date.day());

		//printf("���߼�¼��ʱ��:%04d-%02d-%02d\n", new_date.year(), new_date.month(), new_date.day());

		CurvePointValue vl;
		vl.isValid = false;
		vl.value = 0;

		//���ô�С
		if (pointValues.length() != 289)
		{
			pointValues.resize(289);//289
			if (0 < pointValues.length())
				pointValues.putat(0, vl);
		}
		else
		{
			//�µĿ�ʼ��һ�����������
			if (isBeginDay)
			{
				if (0 < pointValues.length())
					pointValues.putat(0, pointValues.getat(288));
				//printf("������ʼʱ����ֵ!!!\n");
			}
		}

		//����ʱ��
		date = rec_date;

		//��λֵ(ע�⣺��1��ʼ)
		for (int i = 1; i < pointValues.length(); i++)
			pointValues.putat(i, vl);

		updateLimit = false;
		maxValue.tm = "";
		maxValue.value = 0;
		minValue.tm = "";
		minValue.value = 0;

		return true;
	}

	//����ֵ
	bool setValue(int seq_id, double value, dbDateTime& update_tm)
	{
		if ((seq_id < 0) || (seq_id >= pointValues.length()))
			return false;

		if (seq_id < pointValues.length())
		{
			CurvePointValue vl;
			vl.isValid = true;
			vl.value = value;
			pointValues.putat(seq_id, vl);
		}

		CompleteData(seq_id, value);//��ȫ��ǰ����


		return true;
	}

	//��ȫ��ǰ����
	void CompleteData(int seq_id, double value)
	{
		//printf("come here 1 CompleteData:%d - %g\r\n",seq_id,value);

		if ((seq_id < 0) || (seq_id >= pointValues.length()))
			return;

		//printf("come here 2 CompleteData:%d - %g\r\n",seq_id,value);

		for (int i = seq_id - 1; i >= 0; i--)
		{
			if (!pointValues.getat(i).isValid)//��ȫ
			{
				if (i < pointValues.length())
				{
					CurvePointValue vl;
					vl.isValid = true;
					vl.value = value;
					pointValues.putat(i, vl);
				}

				//printf("come here 3 CompleteData:%d - %g\r\n",i,value);
			}
			else
				value = pointValues.getat(i).value;
		}
	}

	TYPE_DESCRIPTOR((FIELD(date),

		RELATION(analog, analog_curve),

		FIELD(pointValues),

		FIELD(updateLimit),
		FIELD(maxValue),
		FIELD(minValue)));
};

/**
 * An AnalogLimitSet specifies a set of Limits that are associated with an Analog
 * measurement.
 */
/*
 class AnalogLimitSet
 {

 public:
 dbReference<Analog> analog;//������ң����ID

 bool isPercentageLimits;

 //Խ��״̬
 int limitStatus;

 //���Խ��״̬
 bool CheckOutLimitStatus(double vl, double hhLimitValue, double hLimitValue, double lLimitValue,
 double llLimitValue, int& new_stauts, double& limit_vl)
 {
 new_stauts = 2;

 if (vl >= hhLimitValue)
 {
 new_stauts = UP_HH_LIMIT;
 limit_vl = hhLimitValue;
 }
 else if ((vl < hhLimitValue) && (vl >= hLimitValue))
 {
 new_stauts = UP_H_LIMIT;
 limit_vl = hLimitValue;
 }
 else if ((vl < hLimitValue) && (vl > lLimitValue))
 {
 new_stauts = NORMAL_LIMIT;
 limit_vl = 0;
 }
 else if ((vl <= lLimitValue) && (vl > llLimitValue))
 {
 new_stauts = LOW_L_LIMIT;
 limit_vl = lLimitValue;
 }
 else if (vl <= llLimitValue)
 {
 new_stauts = LOW_LL_LIMIT;
 limit_vl = llLimitValue;
 }

 //�ж�״̬�Ƿ�ı�
 if (new_stauts != limitStatus)
 {
 limitStatus = new_stauts;
 return true;
 }
 else
 return false;
 }

 TYPE_DESCRIPTOR((
 RELATION(analog, analog_limitset),

 FIELD (isPercentageLimits),
 FIELD(limitStatus)));
 };
 */

//������������
class SecDataType
{
public:
	enum
	{
		YC_SEC = 1, YX_SEC, DD_SEC
	//ң��������ݣ�ң�Ŷ������ݣ���ȶ�������
	};
};

//�������ݵĸ���
#define SEC_DATA_LEN 16

//��������
class SectionData
{
public:
	//���
	int pos;

	//�����ָ
	dbArray<real8> secData;

	void init()
	{
		pos = 0;
		secData.resize(SEC_DATA_LEN);

		for (int i = 0; i < secData.length(); i++)
			secData.putat(i, 0);
	}

	void update_data(double new_vl)
	{
		if (pos < secData.length())
			secData.putat(pos, new_vl);

		pos++;

		if (pos >= SEC_DATA_LEN)
			pos = 0;
	}

	void get_data(double* vl)
	{
		//������������ݵ�λ��
		int data_pos = pos - 1;

		for (int i = 0; i < SEC_DATA_LEN; i++)
		{
			if (data_pos < 0)
				data_pos = SEC_DATA_LEN - 1;

			vl[i] = secData[data_pos];
			data_pos--;
		}
	}

	TYPE_DESCRIPTOR((FIELD (pos),
					FIELD (secData)
			));
};

//ң���������
class AnalogSectionData: public SectionData
{
public:

	//������ģ����
	dbReference<Analog> analog;

	TYPE_DESCRIPTOR((
					SUPERCLASS(SectionData),

					RELATION(analog, analog_sec)
			));
};

//ң�Ŷ�������
class DiscreteSectionData: public SectionData
{
public:

	//������ģ����
	dbReference<Discrete> discrete;

	TYPE_DESCRIPTOR((
					SUPERCLASS(SectionData),

					RELATION(discrete, discrete_sec)
			));
};

//��ȶ�������
class AccumulatorSectionData: public SectionData
{
public:

	//������ģ����
	dbReference<Accumulator> accumulator;

	TYPE_DESCRIPTOR((
					SUPERCLASS(SectionData),

					RELATION(accumulator, accumulator_sec)
			));
};

/*********************************************************************************************************
 * ��ǰ�汾��0.0.1
 * ���ߣ�yening
 * ������ڣ�2011-5-26
 * ��ɢ�����Ͷ���
 *******************************************************************************************************/
class DiscreteType
{
public:
	enum
	{
		_Break_State = 0,//����״̬
		_Remote_Local,//�͵�Զ��
		_Protect
	//����

	};
};
class Discrete: public Measurement
{
public:
	// Normal value range maximum for any of the MeasurementValue.values. Used
	// for scaling, e.g. in bar graphs or of telemetered raw values.
	//##ModelId=447316E0011C
	int4 maxValue;

	// Normal value range minimum for any of the MeasurementValue.values. Used
	// for scaling, e.g. in bar graphs or of telemetered raw values
	//##ModelId=447316E50137
	int4 minValue;

	// Normal measurement value, e.g., used for percentage calculations.
	//##ModelId=447316EA0102
	int4 normalValue;

	// ң��ȡ����
	//##ModelId=4CF4A9A7009C
	bool reverse;

	// The value to supervise.
	//##ModelId=4CF4A9480150
	int4 value;

	// The ValueAliasSet used for translation of a MeasurementValue.value to a
	// name
	//##ModelId=44731B9101E3
	//ValueAliasSet *ValueAliasSet;

	//�ɼ��豸��Ԫ��
	int4 ftuUnitId;

	//�ɼ��豸���
	int4 ftuPointId;

	//##ModelId=447325F900F1
	//Command *Command;
	//dbReference<Command> command;RELATION(command,discrete)

	//61850��Լֵ����
	std::string ftuVlDesc;

	//��λ���
	int4 dw;

	//��λ��ʼ��
	int4 dw_order;

	// ������ң�ŵ�ң������
	// �Ƿ�ң��
	bool isControl;

	// ң�ص��
	int4 ykFtuPointId;

	// The last time a control output was sent
	std::string timeStamp;

	// Indicates that a client is currently sending control commands that has
	// not completed
	bool operationInProgress;

	int bilaFlag;//˫��ң�ر�־

	bool	directControl;	// ֱ�ر�־
	
	// ���ң��
	std::string	relatedAnalog;

	//�����Ķ�������
	dbReference<DiscreteSectionData> discrete_sec;

	//�����ļ��㹫ʽ
	dbReference<FormulaDefinition> discrete_formula;

	//�жϸ��������Ƿ�Ϊ���ؿ��ر�λ
	bool IsBreakChangeValue(unsigned char old_vl, unsigned char vl)
	{
		bool breakChangeFlag = ((old_vl != vl) && (this->measurementType == DiscreteType::_Break_State));

		return breakChangeFlag;
	}

	//����ֵ��ʾ�Ƿ���ֿ��ر�λ
	bool update_data(std::string tm, unsigned char vl)
	{
		//����ֵ
		if (lockFlag)
			return false;

		unsigned char actual_value = vl;
		if (reverse)
			actual_value = !vl;

		bool breakChangeFlag = ((this->value != actual_value) && (this->measurementType == DiscreteType::_Break_State));

		//����
		this->timeStamp = tm;
		this->value = actual_value;

		return breakChangeFlag;
	}

	TYPE_DESCRIPTOR((SUPERCLASS(Measurement),
					FIELD(maxValue),
					FIELD(minValue),
					FIELD(normalValue),
					FIELD(reverse),
					FIELD(value),
					KEY(ftuUnitId,INDEXED|HASHED),
					KEY(ftuPointId,INDEXED|HASHED),
					KEY(ftuVlDesc,INDEXED|HASHED),
					FIELD(dw),
					FIELD(dw_order),
					FIELD(isControl),
					FIELD(ykFtuPointId),
					FIELD(timeStamp),
					FIELD(operationInProgress),
					FIELD(bilaFlag),
					FIELD(directControl),
					FIELD(relatedAnalog),
					OWNER(discrete_sec, discrete),
					OWNER(discrete_formula, discrete)
			));

};

// �������
enum AccumulatorType
{
	HARD_KWH_TYPE = 0,		// ������
	SOFT_KWH_TYPE			// ���ֵ��
};

// ��ȼ��㷽ʽ
enum AccumulatorTag
{
	KWH_IN_MIN_OUT_TYPE = 0,	// ������ּ���
	KWH_IN_ADD_OUT_TYPE,		// ������Ӽ���
	KWH_IN_TYPE,				// ֻ���������
	KWH_OUT_TYPE				// ֻ���㸺���
};

// Accumulator represents a accumulated (counted) Measurement, e.g. an energy
// value.
//##ModelId=40E50BAC0293
class Accumulator: public Measurement
{
public:
	// Normal value range maximum for any of the MeasurementValue.values. Used
	// for scaling, e.g. in bar graphs or of telemetered raw values.
	//##ModelId=447316F803BF
	real8 maxValue;

	// The value to supervise.
	//##ModelId=4CF4A9480150
	real8 value;

	//�ɼ��豸��Ԫ��
	int4 ftuUnitId;

	//�ɼ��豸���
	int4 ftuPointId;

	//61850��Լֵ����
	std::string ftuVlDesc;

	bool saveReport;		// �Ƿ񱣴汨��
	double modulus;			// ϵ��
	int type;				// ������ͣ�AccumulatorType����
	int	tag;				// ���㷽ʽ, AccumulatorTag����
	double preValue;		// ǰһֵ֡
	double high1Kwh;		// �߷�һ�ε��
	double high2Kwh;		// �߷���ε��
	double low1Kwh;			// �͹�һ�ε��
	double low2Kwh;			// �͹ȶ��ε��
	double hourKwh;			// ʱ���
	double dayLowKwh;		// �յ͹ȵ��
	double dayHighKwh;		// �ո߷���
	double dayNormalKwh;	// ��ƽ�ȵ��
	double dayKwh;			// �յ��
	double monthLowKwh;		// �µ͹ȵ��
	double monthHighKwh;	// �¸߷���
	double monthNormalKwh;	// ��ƽ�ȵ��
	double monthKwh;		// �µ��
	double yearLowKwh;		// ��͹ȵ��
	double yearHighKwh;		// ��߷���
	double yearNormalKwh;	// ��ƽ�ȵ��
	double yearKwh;			// ����

	//����ң��ֵ�����Խ��״̬�仯�򷵻�ֵΪture,����Ϊfalse
	bool update_data(std::string tm, double org_vl)
	{
		//����ֵ
		if (lockFlag)
			return false;

		double actual_vl = org_vl * this->modulus;

		if(actual_vl < 0.000001 && actual_vl > -0.000001)
			actual_vl = 0.00;

		this->timeStamp = tm;
		this->value = actual_vl;
		
		return true;
	}
	
	//�����Ķ�������
	dbReference<AccumulatorSectionData> accumulator_sec;
	TYPE_DESCRIPTOR((SUPERCLASS(Measurement),
					FIELD(maxValue),
					FIELD(value),
					KEY(ftuUnitId,INDEXED|HASHED),
					KEY(ftuPointId,INDEXED|HASHED),
					KEY(ftuVlDesc,INDEXED|HASHED),
					FIELD(saveReport),
					FIELD(modulus),
					FIELD(type),
					FIELD(tag),
					FIELD(preValue),
					FIELD(high1Kwh),
					FIELD(high2Kwh),
					FIELD(low1Kwh),
					FIELD(low2Kwh),
					FIELD(hourKwh),
					FIELD(dayLowKwh),
					FIELD(dayHighKwh),
					FIELD(dayNormalKwh),
					FIELD(dayKwh),
					FIELD(monthLowKwh),
					FIELD(monthHighKwh),
					FIELD(monthNormalKwh),
					FIELD(monthKwh),
					FIELD(yearLowKwh),
					FIELD(yearHighKwh),
					FIELD(yearNormalKwh),
					FIELD(yearKwh),
					OWNER(accumulator_sec, accumulator)
			));

};

// A component part of a system extending between adjacent substations or from
// a substation to an adjacent interconnection point.
//##ModelId=35158B650032
class Line: public EquipmentContainer
{
public:
	//##ModelId=4472C1340167
	//dbReference<SubGeographicalRegion> sub_region;

	std::string voltageLevel;

	std::string	ec_type;
	std::string	ec_rid;

	real8	ctRatio;	// CT���
	real8	ptRatio;	// PT���

	int4	lineType;	// ��·����
	int4	lineNo;		// ��·��

	real8	capacity;	// ��ѹ������

	TYPE_DESCRIPTOR((SUPERCLASS(EquipmentContainer),
		FIELD(voltageLevel),
		FIELD(ec_type),
		FIELD(ec_rid),
		FIELD(ctRatio),
		FIELD(ptRatio),
		FIELD(lineType),
		FIELD(lineNo),
		FIELD(capacity)
		));
};

/*// An electrically connected subset of the network. Topological islands can
 // change as the current network state changes (i.e., disconnect switches,
 // breakers, etc. change state).
 //##ModelId=35158A68037A
 class TopologicalIsland: public IdentifiedObject
 {
 public:
 // A topological node belongs to a topological island
 //##ModelId=351690090169
 dbArray<dbReference<TopologicalNode> > topological_nodes;

 TYPE_DESCRIPTOR((SUPERCLASS(IdentifiedObject),
 RELATION(topological_nodes,topological_island )));

 };

 // A set of connectivity nodes that, in the current network state, are
 // connected together through any type of closed switches, including  jumpers.
 // Topological nodes can change as the current network state changes (i.e.,
 // switches, breakers, etc. change state).
 //##ModelId=35158A7B037A
 class TopologicalNode: public IdentifiedObject
 {
 public:
 // True if node energized
 //##ModelId=3527C65D00EC
 bool energized;

 // True if node is load carrying
 //##ModelId=3527C6710177
 bool loadCarrying;

 // Net injection reactive power
 //##ModelId=3527C6860019
 ReactivePower netInjectionQ;

 // Net injection active power
 //##ModelId=3527C69A013A
 ActivePower netInjectionP;

 // The observability status of the node.
 //##ModelId=3527C6B501C5
 bool observabilityFlag;

 // Phase angle of node
 //##ModelId=3527C6C80078
 AngleRadians phaseAngle;

 // Voltage of node
 //##ModelId=3527C7160387
 Voltage voltage;

 // Several ConnectivityNode(s) may combine together to form a single
 // TopologicalNode, depending on the current state of the network.
 //##ModelId=35168F7A0155
 dbArray<dbReference<ConnectivityNode> > connectivity_nodes;

 // A topological node belongs to a topological island
 //##ModelId=351690090168
 dbReference<TopologicalIsland> topological_island;

 TYPE_DESCRIPTOR((SUPERCLASS(IdentifiedObject),
 FIELD(energized),
 FIELD(loadCarrying),
 FIELD(netInjectionQ),
 FIELD(netInjectionP),
 FIELD(observabilityFlag),
 FIELD(phaseAngle),
 FIELD(voltage),
 RELATION(connectivity_nodes,topological_node ),
 RELATION(topological_island,topological_nodes )));
 };
 */

// Connectivity nodes are points where terminals of conducting equipment are
// connected together with zero impedance.
//##ModelId=351578890140
class ConnectivityNode: public IdentifiedObject
{
public:
	// ��Դ���ʶ
	//##ModelId=4D0090EB00CD
	//bool powerPoint;

	std::string fixed_terminal;//�̶��˵�RID

	////##ModelId=463FD0020138
	//ConnectivityNodeContainer *EquipmentContainer;
	std::string ec_type;//���ӵ������豸������psrType
	std::string ec_rid;//���ӵ������豸������RID

	// Several ConnectivityNode(s) may combine together to form a single
	// TopologicalNode, depending on the current state of the network.
	//##ModelId=35168F7A0154
	//dbReference<TopologicalNode> topological_node;

	// Terminals interconnect with zero impedance at a node.  Measurements on a
	// node apply to all of its terminals.
	//##ModelId=3516909E021D
	dbArray<dbReference<Terminal> > terminals;

	//���˵�Ĵ���״̬
	bool power_status;

	TYPE_DESCRIPTOR((SUPERCLASS(IdentifiedObject),
					//FIELD(powerPoint),
					FIELD(fixed_terminal),
					FIELD(ec_type),
					FIELD(ec_rid),
					RELATION(terminals,connectivity_node ),
					FIELD(power_status)

					//RELATION(topological_node,connectivity_nodes)
			));
};

// A generic device  designed to close, or open, or both, one or more electric
// circuits. The typeName attribute may be used to indicate that the database
// switch does not represent a corresponding real device but has been
// introduced for modeling purposes only.
//##ModelId=350375000070
class Switch: public ConductingEquipment
{
public:
	// The attribute is used in cases when no Measurement for the status value
	// is present. If the Switch has a status measurment the
	// Measurement.normalValue is expected to match with the Switch.normalOpen.
	//##ModelId=3526935003BF
	bool normalOpen;

	// The switch on count since the switch was last reset or initialized.
	//##ModelId=35269367010F
	int switchOnCount;

	// The date and time when the switch was last switched on.
	//##ModelId=3526937B038F
	std::string switchOnDate;

	std::string switchTranMode;//���زɼ�ģʽ
	std::string switchCommandType;//����ң������

	std::string brandFlag;//�豸�Ƿ���Ƽ�������Ϣ,

	int	actionCount;	// ���ض�������
	std::string groupNo;		// �����
	std::string manufacturer;	// �豸����
	std::string deviceType;		// �豸����
	std::string deviceModel;	// �豸�ͺ�
	std::string installTime;	// ��װ����
	std::string runTime;		// Ͷ������
	double load;				// ����
	double voltage;				// ���ѹ
	double current;				// �����
	
	TYPE_DESCRIPTOR((SUPERCLASS(ConductingEquipment),
					FIELD(normalOpen),
					FIELD(switchOnCount),
					FIELD(switchOnDate),
					FIELD(switchTranMode),
					FIELD(switchCommandType),
					FIELD(brandFlag),
					FIELD(actionCount),
					FIELD(groupNo),
					FIELD(manufacturer),
					FIELD(deviceType),
					FIELD(deviceModel),
					FIELD(installTime),
					FIELD(runTime),
					FIELD(load),
					FIELD(voltage),
					FIELD(current)
			));

};

// A manually operated or motor operated mechanical switching device used for
// changing the connections in a circuit, or for isolating a circuit or
// equipment from a source of power. It is required to open or close circuits
// when negligible current is broken or made. 
//##ModelId=35157AEB010E
class Disconnector: public Switch
{
public:

	TYPE_DESCRIPTOR(( SUPERCLASS(Switch)));
};

// A ProtectedSwitch is a switching device that can be operated by
// ProtectionEquipment.
//##ModelId=4472D7340005
class ProtectedSwitch: public Switch
{
public:

	TYPE_DESCRIPTOR(( SUPERCLASS(Switch)));
};

// Current flow in Amps (positive flow is out of the ConductingEquipment into
// the ConnectivityNode)
//##ModelId=350375CC0100
struct CurrentFlow
{
public:
	//##ModelId=350375D402E2
	real8 value;

	//##ModelId=45C32D9E0357
	//static UnitSymbol unit;

	//##ModelId=45C218AE0250
	int multiplier;

	TYPE_DESCRIPTOR((FIELD(value),
					FIELD(multiplier)));

};

// A mechanical switching device capable of making, carrying, and breaking
// currents under normal circuit conditions and also making, carrying for a
// specified time, and breaking currents under specified abnormal circuit
// conditions e.g.  those of short circuit. The typeName is the type of
// breaker, e.g., oil, air blast, vacuum, SF6.
//##ModelId=35037565038C
class Breaker: public ProtectedSwitch
{
public:
	// Fault interrupting rating in amperes
	//##ModelId=350375830014
	//CurrentFlow ratedCurrent;
	real8 ratedCurrent;
	//int ratedCurrent_multiplier;

	// The transition time from open to close, in seconds
	//##ModelId=3503769B00C1
	real8 inTransitTime;

	bool faFlag;//�Ƿ�ΪFA����
	bool PowerPointFlag;//��Դ���ʶ
	real8 PPThreshold;//��Դ������

	int4 FTUNo;//վ��ţ����վ��źͿ�������վ���һ�£�����Ҫ���ã�
	int4 EventID;//FTU���͵���·��

	bool WaveDirFlag;//�Ƿ�ο���������

	real8 factorDL_I;//������������ϵ��
	real8 factorJD_I;//�ӵص�������ϵ��

    bool breakerImportant;//���ɼ���0-��ͨ��1-��Ҫ zhoucw20130715
	
	TYPE_DESCRIPTOR((SUPERCLASS(ProtectedSwitch),
					//FIELD(ratedCurrent),
					FIELD(ratedCurrent),
					//FIELD(ratedCurrent_multiplier),
					FIELD(inTransitTime),

					FIELD(faFlag),
					FIELD(PowerPointFlag),
					FIELD(PPThreshold),

					FIELD(FTUNo),
					FIELD(EventID),

					FIELD (WaveDirFlag),
					FIELD (factorDL_I),
                    FIELD (factorJD_I),
                    FIELD (breakerImportant)
					));//zhoucw20130715
};

// An electrical device consisting of  two or more coupled windings, with or
// without a magnetic core, for introducing mutual coupling between electric
// circuits. Transformers can be used to control voltage and phase shift
// (active power flow). The typeName attribute indicates type of transformer.
//##ModelId=3503706E0276
class PowerTransformer: public Equipment
{
public:
	// Core shunt magnetizing susceptance in the saturation region, in per
	// cent.
	//##ModelId=350371EE0229
	real8 bmagSat;

	// The reference voltage at which the magnetizing saturation measurements
	// were made
	//##ModelId=350373E802B2
	//Voltage magBaseU;
	real8 magBaseU;
	//int4 magBaseU_multiplier;

	// Core magnetizing saturation curve knee flux level.
	//##ModelId=350374070086
	real8 magSatFlux;

	// Describes the phases carried by a power transformer. Possible values {
	// ABCN , ABC, ABN, ACN, BCN, AB, AC, BC, AN, BN, CN, A, B, C, N }.
	//##ModelId=3503743F0036
	int phases;

	// Type of transformer cooling
	//##ModelId=350374750297
	int transfCoolingType;

	//##ModelId=3A8A8F6C00F5
	int transformerType;

	//��λ
	int stall;

	//��λ���㷽��
	int stallCalcu;

	//����
	int4 FTUNo;

	//��ʼң�ź�
	int4 startDiscrete;

	//��Ŀ
	int4 discreteNum;

	//ң����
	int4 controlNo;

	// A transformer has windings
	//##ModelId=3530DBBF0121
	//TransformerWinding TransformerWindings;
	dbArray<dbReference<TransformerWinding> > transformer_windings;

	std::string groupNo;		// �����
	std::string manufacturer;	// �豸����
	std::string deviceType;		// �豸����
	std::string deviceModel;	// �豸�ͺ�
	std::string installTime;	// ��װ����
	std::string runTime;		// Ͷ������

	int controlMode;	// ң����ʽ

	TYPE_DESCRIPTOR((SUPERCLASS(Equipment),
					FIELD(bmagSat),
					//FIELD(magBaseU),
					FIELD(magBaseU),
					//FIELD(magBaseU_multiplier),
					FIELD(magSatFlux),
					FIELD(phases),
					FIELD(transfCoolingType),
					FIELD(transformerType),
					FIELD(stall),
					FIELD(stallCalcu),
					FIELD(FTUNo),
					FIELD(startDiscrete),
					FIELD(discreteNum),
					FIELD(controlNo),
					RELATION(transformer_windings,power_tranformer ),
					FIELD(groupNo),
					FIELD(manufacturer),
					FIELD(deviceType),
					FIELD(deviceModel),
					FIELD(installTime),
					FIELD(runTime),
					FIELD(controlMode)
					));
};

// Product of the RMS value of the voltage and the RMS value of the current
//##ModelId=350892520192
class ApparentPower
{
public:
	//##ModelId=3508925D0165
	real8 value;

	//##ModelId=45C32D890039
	//static UnitSymbol unit;

	//##ModelId=45C21651003C
	int multiplier;

	TYPE_DESCRIPTOR((FIELD(value),
					FIELD(multiplier)));

};

// The winding type, i.e., Primary, Secondary, Tertiary, Quaternary.
//##ModelId=350C71E700CC
enum WindingType
{
	//##ModelId=3B58636603DF
	primary,

	//##ModelId=3B58637002F3
	secondary,

	//##ModelId=3B58638300E7
	tertiary,

	//##ModelId=3B58638E02CE
	quaternary

};

// A winding is associated with each defined terminal of a transformer (or
// phase shifter).
//##ModelId=35158AF90190
class TransformerWinding: public ConductingEquipment
{
public:
	// Magnetizing branch susceptance (B mag).
	//##ModelId=3527C7AC0397
	//Susceptance b;
	real8 b;
	//int4 b_multiplier;

	// Zero sequence magnetizing branch susceptance.
	//##ModelId=4CF3471A00CD
	real8 b0;

	// The type of connection of the winding (e.g. Delta, Wye, zigzag)
	//##ModelId=3527C7D30307
	int connectionType;

	// The MVA that the winding can carry  under emergency conditions.
	//##ModelId=3527C7E702BF
	//ApparentPower emergencyS;
	real8 emergencyS;
	//int4 emergencyS_multiplier;

	// Magnetizing branch conductance (G mag).
	//##ModelId=3527C7F90329
	//Conductance g;
	real8 g;
	//int4 g_multiplier;

	// Zero sequence magnetizing branch conductance.
	//##ModelId=4CF347990097
	real8 g0;

	// Set if the winding is grounded.
	//##ModelId=3527C80D013D
	bool grounded;

	// Basic insulation level voltage rating
	//##ModelId=3527C7C1033D
	//Voltage insulationU;
	real8 insulationU;
	//int4 insulationU_multiplier;

	// Positive sequence series resistance of the winding.
	//##ModelId=3527C8200253
	//Resistance r;
	real8 r;
	//int4 r_multiplier;

	// Zero sequence series resistance of the winding.
	//##ModelId=3527C8320155
	//Resistance r0;
	real8 r0;
	//int4 r0_multiplier;

	// The rated voltage (phase-to-phase) of the winding, usually the same as
	// the neutral voltage.
	//##ModelId=3527C84301BD
	//Voltage ratedU;
	real8 ratedU;
	//int4 ratedU_multiplier;

	// The normal apparent power rating for the winding
	//##ModelId=3527C85702CA
	//ApparentPower ratedS;
	real8 ratedS;
	//int4 ratedS_multiplier;

	// Ground resistance path through connected grounding transformer.
	//##ModelId=3527C86A03B8
	//Resistance rground;
	real8 rground;
	//int4 rground_multiplier;

	// Apparent power that the winding can carry for a short period of time.
	//##ModelId=3527C87E029E
	//ApparentPower shortTermS;
	real8 shortTermS;
	//int4 shortTermS_multiplier;

	// The type of winding, i.e., Primary, Secondary, Tertiary, Quaternary.
	//##ModelId=3527C8A90174
	int windingType;

	// Positive sequence series reactance of the winding.
	//##ModelId=3527C8D100D1
	//Reactance x;
	real8 x;
	//int4 x_multiplier;

	// Zero sequence series reactance of the winding.
	//##ModelId=3527C8E50030
	//Reactance x0;
	real8 x0;
	//int4 x0_multiplier;

	// Ground reactance path through connected grounding transformer.
	//##ModelId=3527C8FE0202
	//Reactance xground;
	real8 xground;
	//int4 xground_multiplier;

	// A transformer has windings
	//##ModelId=3530DBBF0117
	//PowerTransformer *PowerTransformer;
	dbReference<PowerTransformer> power_tranformer;

	TYPE_DESCRIPTOR((SUPERCLASS(ConductingEquipment),
					FIELD (b),
					//FIELD (b_multiplier),
					FIELD (b0),

					FIELD(connectionType),
					FIELD(emergencyS),
					//FIELD(emergencyS_multiplier),

					FIELD(g),
					//FIELD(g_multiplier),
					FIELD(g0),
					FIELD(grounded),
					FIELD(insulationU),
					//FIELD(insulationU_multiplier),


					FIELD(r),
					//FIELD(r_multiplier),
					FIELD(r0),
					//FIELD(r0_multiplier),

					FIELD(ratedU),
					//FIELD(ratedU_multiplier),
					FIELD(ratedS),
					//FIELD(ratedS_multiplier),
					FIELD(rground),
					//FIELD(rground_multiplier),
					FIELD(shortTermS),
					//FIELD(shortTermS_multiplier),
					FIELD(windingType),

					FIELD(x),
					//FIELD(x_multiplier),
					FIELD(x0),
					//FIELD(x0_multiplier),
					FIELD(xground),
					//FIELD(xground_multiplier),

					RELATION(power_tranformer,transformer_windings)));
};

//��ʽ����
class FormulaDefinition
{
public:
	std::string mRID;
	std::string name;
	std::string formula;//��ʽ����

	std::string type;//��ʽ���ͣ�Analog��ʾң�⣬Discrete��ʾң��

	std::string ce_type;//�����豸����
	std::string ce_rid;//�����豸RID

	std::string descr;//��ʽ����

	dbReference<Analog> analog;//����Analog
	dbReference<Discrete> discrete;//����Analog

	TYPE_DESCRIPTOR((KEY(mRID,INDEXED|HASHED),
					FIELD (name),
					FIELD (formula),

					FIELD (type),

					FIELD (ce_type),
					KEY (ce_rid, INDEXED|HASHED),

					FIELD (descr),

					OWNER(analog, analog_formula),
					OWNER(discrete, discrete_formula)
			));
};

//��������
class VariableDefinition
{
public:
	std::string mRID;
	std::string name;
	std::string variable;//��ʽ����

	int4 measure_type;//��������
	std::string measure_rid;//����rid

	TYPE_DESCRIPTOR((KEY(mRID,INDEXED|HASHED),
					FIELD (name),
					FIELD (variable),
					FIELD (measure_type),
					FIELD (measure_rid)
			));
};

// ��λ��
class Step
{
public:
	std::string	mRID;			// ��λid
	std::string	name;			// ��λ����
	std::string	psr_type;		// ������������
	std::string psr_rid;		// ��������id
	int			compute_type;	// ���㷽��
	int			step;			// ��ǰ��λֵ
	int			highStep;		// ��λ����
	int			lowStep;		// ��λ����

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(name),
		FIELD(psr_type),
		FIELD(psr_rid),
		FIELD(compute_type),
		FIELD(step),
		FIELD(highStep),
		FIELD(lowStep)
		));
};

//ң�ر�����ʽ����
class ControlLockingFormula
{
public:
	std::string mRID;
	std::string name;
	std::string formula;//��ʽ����
	bool value;			// ��ʽֵ
	std::string discrete;//����Discrete

	TYPE_DESCRIPTOR((KEY(mRID,INDEXED|HASHED),
		FIELD (name),
		FIELD (formula),
		FIELD (value),
		FIELD (discrete)
		));
};

// �澯������
class ConfigFaultDesc
{
public:
	std::string	mRID;					// �澯����id
	std::string	manufactId;				// �豸����id
	int			lineType;				// ��·����
	int			protectTypeNo;			// �������ͺ�
	bool		protectHasValue;		// ��������ֵ
	std::string	name;					// ����
	std::string	units;					// ��λ
	real8		modulus;				// ϵ��

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(manufactId),
		FIELD(lineType),
		FIELD(protectTypeNo),
		FIELD(protectHasValue),
		FIELD(name),
		FIELD(units),
		FIELD(modulus)
		));
};

// ң��������
class ConfigYxDesc
{
public:
	std::string	mRID;		// ң������id
	int			yxType;		// ң������
	int			yxValue;	// ң��ֵ
	std::string	name;		// ����

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(yxType),
		FIELD(yxValue),
		FIELD(name)
		));
};

// ���ʱ�α�
class AccumulatorTimeSegment
{
public:
	std::string	mRID;		// ң������id
	int			up1Start;	// ��һ�߷�ʱ�����
	int			up1End;		// ��һ�߷�ʱ���յ�
	int			low1Start;	// ��һ�͹�ʱ�����
	int			low1End;	// ��һ�͹�ʱ���յ�
	int			up2Start;	// �ڶ��߷�ʱ�����
	int			up2End;		// �ڶ��߷�ʱ���յ�
	int			low2Start;	// �ڶ��͹�ʱ�����
	int			low2End;	// �ڶ��͹�ʱ���յ�

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(up1Start),
		FIELD(up1End),
		FIELD(low1Start),
		FIELD(low1End),
		FIELD(up2Start),
		FIELD(up2End),
		FIELD(low2Start),
		FIELD(low2End)
		));
};

// ���ϵ�����
class ProtectValue
{
public:
	std::string mRID;	// id
	int	unitNo;			// ��Ԫ��
	int lineNo;			// ��·��
	int no;				// ����
	std::string name;	// ����
	std::string unit;	// ��λ
	double factor;		// ϵ��
	int index;			// ���	KH8000Tϵͳ�и��ֶ�û��ʹ�ã���ʱ�����Ա��Ժ�ʹ��

	dbArray< dbReference<ProtectValueDesc> > valueDesces;

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(unitNo),
		FIELD(lineNo),
		FIELD(no),
		FIELD(name),
		FIELD(unit),
		FIELD(factor),
		FIELD(index),
		RELATION(valueDesces, protectValue)
		));
};

// ���ϵ���������
class ProtectValueDesc
{
public:
	std::string mRID;	// id
	int value;			// ֵ
	std::string valueDesc;	// ֵ��������Ϣ

	dbReference<ProtectValue> protectValue;	// �������ϵ���

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(value),
		FIELD(valueDesc),
		RELATION(protectValue, valueDesces)
		));
};

// �豸���ұ�
class DevManufacturer
{
public:
	std::string	mRID;		// ����id
	std::string	name;		// ��������
	std::string type;		// ����
	dbArray< dbReference<DevDeviceType> >	deviceTypes;	// �豸�ͺ�
	dbArray< dbReference<RemoteUnit> >	remoteUnits;		// ��Ԫ
	dbArray< dbReference<DevSettingLine> >	settingLines;	// ������·
	dbArray< dbReference<DevSettingType> >	settingTypes;	// ��������

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(name),
		FIELD(type),
		RELATION(deviceTypes, manufacturer),
		RELATION(remoteUnits, manufacturer),
		RELATION(settingLines, manufacturer),
		RELATION(settingTypes, manufacturer)
		));
};

// �豸�ͺű�
class DevDeviceType
{
public:
	std::string	mRID;		// �豸�ͺ�id
	std::string	name;		// �豸�ͺ�����
	dbReference<DevManufacturer>	manufacturer;	// ��������
	dbArray< dbReference<RemoteUnit> > remoteUnits;	// ��Ԫ
	dbArray< dbReference<DevSettingLine> >	settingLines;	// ������·
	dbArray< dbReference<DevSettingType> >	settingTypes;	// ��������

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(name),
		RELATION(manufacturer, deviceTypes),
		RELATION(remoteUnits, deviceType),
		RELATION(settingLines, deviceType),
		RELATION(settingTypes, deviceType)
		));
};

// ������·���ͱ�
class DevSettingLine
{
public:
	std::string	mRID;			// �豸�ͺ�id
	int			no;				// ���
	int			lineType;		// ��·����
	int			settingWay;		// ������ʽ
	int			startProNo;		// ��ʼ������
	int			endProNo;		// ��ֹ������
	int			protectNum;		// ��������
	int			fc;				// ������
	int			proTypeVal;		// �������ʹ�С
	int			funType;		// ��������

	dbReference<DevManufacturer>	manufacturer;	// �豸����
	dbReference<DevDeviceType>		deviceType;		// �豸����

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(no),
		FIELD(lineType),
		FIELD(settingWay),
		FIELD(startProNo),
		FIELD(endProNo),
		FIELD(protectNum),
		FIELD(fc),
		FIELD(proTypeVal),
		FIELD(funType),
		RELATION(manufacturer, settingLines),
		RELATION(deviceType, settingLines)
		));
};

// �������ͱ�
class DevSettingType
{
public:
	std::string	mRID;			// �豸�ͺ�id
	int			no;				// ���
	int			lineType;		// ��·����
	int			settingNo;		// �������ͺ�
	std::string	settingName;	// ������������
	int			proTypeVal;		// �������ͺ�
	int			settingType;	// ��ֵ����
	int			saveType;		// �洢����
	int			startSingle;	// ��ʼ(��һ)
	int			endSingle;		// ��ֹ(��һ)
	int			startLine;		// ��ʼ(��·)
	int			endLine;		// ��ֹ(��·)
	int			infoAddr;		// ��Ϣ��ַ
	real8		modulus;		// ϵ��
	std::string	units;			// ��λ
	int			settingLevel;	// ��������
	int			funType;		// ��������
	int			qpm;			// QPM

	dbReference<DevManufacturer>	manufacturer;	// �豸����
	dbReference<DevDeviceType>		deviceType;		// �豸����

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(no),
		FIELD(lineType),
		FIELD(settingNo),
		FIELD(settingName),
		FIELD(proTypeVal),
		FIELD(settingType),
		FIELD(saveType),
		FIELD(startSingle),
		FIELD(endSingle),
		FIELD(startLine),
		FIELD(endLine),
		FIELD(infoAddr),
		FIELD(modulus),
		FIELD(units),
		FIELD(settingLevel),
		FIELD(funType),
		FIELD(qpm),
		RELATION(manufacturer, settingTypes),
		RELATION(deviceType, settingTypes)
		));
};

// ������
class FepPartition
{
public:
	std::string	mRID;								// ����id
	std::string	name;								// ��������
	dbArray< dbReference<FepSection> > sections;	// �ֶ�
	dbArray< dbReference<FepProtocol> > protocols;	// ��Լ

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(name),
		RELATION(sections, partition),
		RELATION(protocols, partition)
		));
};

// �ֶα�
class FepSection
{
public:
	std::string	mRID;						// �ֶ�id
	std::string	name;						// �ֶ�����
	dbReference<FepPartition> partition;	// ����id
	dbArray< dbReference<FepProtocol> > protocols;	// ��Լ

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(name),
		RELATION(partition, sections),
		RELATION(protocols, section)
		));
};

// ��Լ��
class FepProtocol
{
public:
	std::string	mRID;						// ��Լid
	int			protocolNo;					// ��Լ����
	std::string	name;						// ��Լ����
	int			type;						// ��Լ����
	bool		isUse;						// �Ƿ�ʹ��
	std::string	paramLine;					// ����
	int			commCount;					// ͨ������
	int			unitCount;					// ��Ԫ����
	dbReference<FepPartition>	partition;	// ��������
	dbReference<FepSection>		section;	// �����ֶ�
	dbArray< dbReference<FepChannel> > channels;	// ͨ��

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(protocolNo),
		FIELD(name),
		FIELD(type),
		FIELD(isUse),
		FIELD(paramLine),
		FIELD(commCount),
		FIELD(unitCount),
		RELATION(partition, protocols),
		RELATION(section, protocols),
		RELATION(channels, protocol)
		));
};

// ͨ����
class FepChannel
{
public:
	std::string	mRID;			// ͨ��id
	int			channelId;		// ͨ����
	std::string	param;			// ����
	dbReference<FepProtocol>	protocol;		// ��Լid

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(channelId),
		FIELD(param),
		RELATION(protocol, channels)
		));
};

// ��Լ��Ԫ������
class FepProtocolUnit
{
public:
	std::string	mRID;			// id
	std::string	protocolId;		// ������Լ
	int			deviceId;		// ������Ԫ

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		KEY(protocolId, INDEXED | HASHED),
		KEY(deviceId, INDEXED | HASHED)
		));
};

// ��ɫ��
class SystemRole
{
public:
	std::string	mRID;			// ��ɫid
	std::string	roleName;		// ����
	std::string	permission;		// Ȩ��״̬
	std::string roleDesc;		// ����
	std::string operDesc;		// ��������

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(roleName),
		FIELD(permission),
		FIELD(roleDesc),
		FIELD(operDesc)
		));
};

// �û���
class SystemUser
{
public:
	std::string	mRID;			// �û�id
	std::string	loginId;		// ��¼id
	std::string	loginName;		// ��¼����
	std::string userPwd;		// ����
	std::string roleId;			// ��ɫ
	std::string userName;		// ����

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(loginId),
		FIELD(loginName),
		FIELD(userPwd),
		FIELD(roleId),
		FIELD(userName)
		));
};

// �绰�����
class SystemPhone
{
public:
	std::string	mRID;		// id
	std::string	name;		// ����
	std::string	phone;		// �绰����

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(name),
		FIELD(phone)
		));
};

// �������ñ�
class SystemMsgCfg
{
public:
	std::string	mRID;		// id
	int			type;		// ����
	int			state;		// ״̬

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(type),
		FIELD(state)
		));
};

// ͼ���ļ���
class GraphFile
{
public:
	std::string	mRID;		// id
	std::string	name;		// ����
	int			type;		// ����

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(name),
		FIELD(type)
		));
};

// ¼��������
class WavWaveConfig
{
public:
	std::string	mRID;			// id
	int			deviceId;		// ��Ԫ��
	int			configNo;		// ���
	std::string dataName;		// ��������
	int			maxVal;			// ���ֵ
	int			minVal;			// ��Сֵ
	std::string unit;			// ��λ
	real8		modulus;		// ϵ��
	std::string color;			// ������ɫ
	int			belongBmp;		// ��������
	int			protectLineNo;	// ������·��
	int			channelNo;		// ͨ����
	int			zhouBoNum;		// ����ǰ�ܲ���

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(deviceId),
		FIELD(configNo),
		FIELD(dataName),
		FIELD(maxVal),
		FIELD(minVal),
		FIELD(unit),
		FIELD(modulus),
		FIELD(color),
		FIELD(belongBmp),
		FIELD(protectLineNo),
		FIELD(channelNo),
		FIELD(zhouBoNum)
		));
};

// �������߲�����
class WavTrendCurve
{
public:
	std::string	mRID;			// id
	int			deviceId;		// ��Ԫ��
	std::string	ycDesc;			// ����
	int			no;				// ���
	int			ycIndex;		// ң����
	real8		modulus;		// ϵ��
	int			analogType;		// ң������
	std::string curveColor;		// ������ɫ
	int			coordinateNo;	// ����ϵ��
	std::string reserved;		// Ԥ��

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(deviceId),
		FIELD(ycDesc),
		FIELD(no),
		FIELD(ycIndex),
		FIELD(modulus),
		FIELD(analogType),
		FIELD(curveColor),
		FIELD(coordinateNo),
		FIELD(reserved)
		));
};

// ��ȫ���
class SecurityGroups
{
public:
	std::string	mRID;		// id
	int			no;			// ��ȫ���
	std::string	name;		// ��ȫ����
	std::string	state1;		// ״̬1
	std::string state2;		// ״̬2

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(no),
		FIELD(name),
		FIELD(state1),
		FIELD(state2)
		));
};

// ��ȫ�����û���
class SecurityGroupsUsers
{
public:
	std::string	mRID;		// id
	std::string	groupMrid;	// ��ȫ��id
	std::string	userMrid;	// �û�id

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		KEY(groupMrid, INDEXED | HASHED),
		FIELD(userMrid)
		));
};

// ��ȫ����վ���
class SecurityGroupsStations
{
public:
	std::string	mRID;			// id
	std::string	groupMrid;		// ��ȫ��id
	std::string	stationMrid;	// �����/��վid

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(groupMrid),
		FIELD(stationMrid)
		));
};

// ������Ϣ��
class EquipGroup
{
public:
	std::string	mRID;	// id
	std::string	no;		// �����
	std::string	name;	// ��������

	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(no),
		FIELD(name)
		));
};

// �豸������
class EquipParam
{
public:
	std::string	mRID;	// id
	std::string	no;		// �豸��
	std::string	name;	// �豸����
	std::string groupNo; // ���������
	std::string manufacturer; // �豸����
	std::string deviceType; // �豸����
	std::string deviceModel; // �豸�ͺ�
	std::string installTime; // ��װ����
	std::string runTime;	// Ͷ������


	TYPE_DESCRIPTOR((
		KEY(mRID, INDEXED | HASHED),
		FIELD(no),
		FIELD(name),
		FIELD(groupNo),
		FIELD(manufacturer),
		FIELD(deviceType),
		FIELD(deviceModel),
		FIELD(installTime),
		FIELD(runTime)
		));
};

#endif

