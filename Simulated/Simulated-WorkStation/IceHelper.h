#ifndef ICEHELPER_H
#define ICEHELPER_H

#include "rdbdata.h"

#include <Ice/Ice.h>
#include <string>
#include <vector>
using namespace std;

#define SUBSTATION 		"Substation"
#define BREAKER			"Breaker"
#define DISCONNECTOR	"Disconnector"
#define ANALOG 			"Analog"
#define DISCRETE 		"Discrete"
#define REMOTEUNIT 		"RemoteUnit"

#define MRID	"mRID"
#define NAME	"name"
#define ECTYPE	"ec_type"
#define ECRID	"ec_rid"
#define FTUUNITID	"ftuUnitId"

typedef vector<string> StringVct;
typedef vector< StringVct > StringsVct;

struct RdbDataItem
{
	string mrid;
	string name;
};
typedef vector<RdbDataItem> RdbDataItemVct;

struct RemoteUnitItem
{
	string mrid;
	string iedId;
	string iedName;
	string ecRid;
};
typedef vector<RemoteUnitItem> RemoteUnitItemVct;

class CIceHelper
{
private:
	CIceHelper();

public:
	static CIceHelper* instance()
	{
		static CIceHelper iceHelper;
		return &iceHelper;
	}

public:
	void setCommunicatorPtr(Ice::CommunicatorPtr ptr);
	void setProxyPoints(const string& points);

	bool selectCompleteData(const string& tableName, 
		const string& fieldName, const string& fieldValue, StringsVct& dataValues);

	bool selectCompleteData(const string& tableName, 
		const string& fieldName, const string& fieldValue, RdbDataItemVct& items);

	// ��ѯ���еĵ�Ԫ
	void selectRemoteUnits(const string& fieldName, const string& fieldValue, RemoteUnitItemVct& items);

	// ��ѯ���е������/��վ
	void selectSubstations(const string& fieldName, const string& fieldValue, RdbDataItemVct& items);

	// ��ѯ��������
	void selectBreakers(const string& fieldName, const string& fieldValue, RdbDataItemVct& items);

	// ��ѯ��բ����
	void selectDisconnectors(const string& fieldName, const string& fieldValue, RdbDataItemVct& items);

	// ��ѯң������
	void selectAnalogs(const string& fieldName, const string& fieldValue, RdbDataItemVct& items);

	// ��ѯң������
	void selectDiscretes(const string& fieldName, const string& fieldValue, RdbDataItemVct& items);

private:
	RdbRealData::RdbDataOptPrx getRdbDataOptPrx();

private:
	Ice::CommunicatorPtr m_communicatorPtr;
	RdbRealData::RdbDataOptPrx m_rdbOptPrx;

	string m_proxyPoints;
};
#endif