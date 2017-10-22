#ifndef WORKSTATIONSERVERTHREAD_H
#define WORKSTATIONSERVERTHREAD_H

#include "rdbdata.h"

#include <QThread>
#include <Ice/ice.h>
#include <IceUtil/IceUtil.h>
#include <IceStorm/IceStorm.h>

class OperationInfo;

#pragma execution_character_set("utf-8")

class WorkStationServerThread : public QThread
{
	Q_OBJECT

public:
	void setCommunicatorPtr(Ice::CommunicatorPtr ptr);
	void setObjectAdapterPtr(Ice::ObjectAdapterPtr ptr);

	// ���������Ϣ
	void outputOperationData(const QString& text);

protected:
	virtual void run();

private:
	bool getRdbRealDataRequestPublisher();
	bool subscribeData();

signals:
	void executeOperation(const OperationInfo& text);
	void outputReceiveData(const QString& text);

private slots:
	void requestCompleteData();
	void subscriberRdbRequest(bool isStop);
	void subscriberRdbRespond(bool isStop);
	void subscriberAlarmData(bool isStop);
	void subscriberFepData(bool isStop);

private:
	Ice::CommunicatorPtr m_communicatorPtr;
	Ice::ObjectAdapterPtr	m_objectAdapterPtr;

	Ice::ObjectPrx	m_rdbDataPrx;			// ʵʱ���������Ľӿ�
	Ice::ObjectPrx  m_rdbRespondDataPrx;	// ʵʱ������Ӧ���Ľӿ�
	Ice::ObjectPrx	m_alarmDataPrx;			// �澯���ݶ��Ľӿ�
	Ice::ObjectPrx  m_fepDataPrx;			// ǰ�û�������Ӧ���Ľӿ�

	RdbRealData::RdbRealDataRequestPrx	m_rdbRealDataRequestPrx;
};

#endif