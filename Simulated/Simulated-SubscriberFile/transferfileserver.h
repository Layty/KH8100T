#ifndef TRANSFERFILESERVER_H
#define TRANSFERFILESERVER_H

#include "translogger.h"

#include <Ice/Application.h>
#include <QObject>

using namespace TransferRdbLogger;

class TransferFileServer : public QObject, public Ice::Application
{
	Q_OBJECT

public:
	TransferFileServer(int argc, char* argv[]);
	~TransferFileServer();

	virtual int run(int argc, char* argv[]);

private:
	// ��ȡ�����ӿ�
	bool getPublisherPtr();

	// �Ƴ������ӿ�
	bool removePublisherPtr();

signals:
	void outputOperationInfo(QString text);

public slots:
	void start();

	void publishFile(bool isStart);
	void subscriberFile(bool isStart);

private:
	int m_argc;
	char**	m_argv;

	Ice::CommunicatorPtr m_communicatorPtr;
	Ice::ObjectAdapterPtr m_objectAdapterPtr;

	TransferRdbLoggerInfoPrx	m_publishFilePrx;				// �ļ������ӿ�
	::Ice::ObjectPrx			m_subscriberFilePrx;			// �ļ����Ľӿ�
};
#endif