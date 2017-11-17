#ifndef WORKSTATIONSERVERTHREAD_H
#define WORKSTATIONSERVERTHREAD_H

#include "rdbdata.h"
#include "ykdata.h"

#include <string>
#include <QtCore/QtCore>
#include <Ice/ice.h>
#include <IceUtil/IceUtil.h>
#include <IceStorm/IceStorm.h>

using namespace std;
using namespace Yk;

class OperationInfo;

#pragma execution_character_set("utf-8")

class WorkStationServerThread : public QThread
{
	Q_OBJECT

public:
	WorkStationServerThread(QObject* parent = 0);

public:
	void setCommunicatorPtr(Ice::CommunicatorPtr ptr);
	void setObjectAdapterPtr(Ice::ObjectAdapterPtr ptr);

	// ���������Ϣ
	void outputOperationData(const QString& text);
	
protected:
	virtual void run();

private:
	bool getRdbRealDataRequestPublisher();
	// ��ȡң�ط�������
	bool getYkFepPublisher();
	// ��ȡң�ط��ط�������
	bool getYkAppPublisher();

	// ����IceStorm����
	bool subscribeTopic(Ice::ObjectPrx &objectPrx, const std::string &topic, const QString& type);
	// ȡ������IceStorm����
	bool unSubscribeTopic(Ice::ObjectPrx &objectPrx, const std::string &topic, const QString& type);
	// ��ȡ��������
	bool getPublisher(const std::string& topic, const QString& type, Ice::ObjectPrx& objectPrx);
signals:
	void executeOperation(const OperationInfo& text);
	void outputReceiveData(const QString& text);

public slots:
	// ң��ѡ��
	void select();

	// ѡ��ȷ��
	void selectEcho(YkCommand cmd, bool flag, string tip);

	// ѡ��У
	void selectReturn(YkCommand cmd, bool flag, string tip);

private slots:
	void requestCompleteData();
	void selectCompleteData();
	void subscriberRdbRequest(bool isStop);
	void subscriberRdbRespond(bool isStop);
	void subscriberAlarmData(bool isStop);
	void subscriberFepData(bool isStop);
	void subscriberYkFep(bool isStop);
	void subscriberYkApp(bool isStop);
	void ykSelect(bool isStop);

private:
	Ice::CommunicatorPtr m_communicatorPtr;
	Ice::ObjectAdapterPtr	m_objectAdapterPtr;

	Ice::ObjectPrx	m_rdbDataPrx;			// ʵʱ���������Ľӿ�
	Ice::ObjectPrx  m_rdbRespondDataPrx;	// ʵʱ������Ӧ���Ľӿ�
	Ice::ObjectPrx	m_alarmDataPrx;			// �澯���ݶ��Ľӿ�
	Ice::ObjectPrx  m_fepDataPrx;			// ǰ�û�������Ӧ���Ľӿ�
	Ice::ObjectPrx  m_ykFepPrx;				// ң�����������Ľӿ�
	Ice::ObjectPrx  m_ykAppPrx;				// ң��������Ӧ���Ľӿ�

	RdbRealData::RdbRealDataRequestPrx	m_rdbRealDataRequestPrx;
	Yk::YkFepManagerPrx					m_ykFepManagerPrx;
	Yk::YkAppManagerPrx					m_ykAppManagerPrx;

	QTimer			m_ykSelectTimer;	// ң��ѡ��ʱ��

	string		m_rdbRequestSubIdentity;
	string		m_rdbRespondSubIdentity;
	string		m_alarmSubIdentity;
	string		m_fepDataSubIdentity;
	string		m_ykFepSubIdentity;
	string		m_ykAppSubIdentity;
};

#endif