#ifndef ICESERVER_H
#define ICESERVER_H

#include "transferfile.h"
#include "TransferFileItem.h"

#include <Ice/Ice.h>
#include <QObject>
#include <string>

using namespace std;
using namespace TransferFileModule;

class IceServer : public QObject, public Ice::Application
{
	Q_OBJECT

public:
	IceServer(QObject* parent = 0);

	virtual int run(int argc, char* argv[]);

	void shutdown();

	void setParam(int argc, char* argv[]);

	// ���ñ���������Ϣ
	void setLocalHost(const QString& host, int port);

	// ����Զ��������Ϣ
	void setRemoteHostPort(const QString& host, int port);

	// �ϴ��ļ�
	void uploadFile(const QString& fileName);

	// �����ļ�
	void downloadFile(const QString& fileName);

private:
	QString getTransferFileProxy();

signals:
	void serverStarted(bool status, const QString& msg = "");
	void emitMessage(const QString& msg);
	void emitTransferFileItem(const TransferFileItem& item);
	void emitProgress(int value);

public slots:
	void start();

private:
	Ice::CommunicatorPtr m_communicatorPtr;
	Ice::ObjectAdapterPtr m_objectAdapterPtr;
	Ice::ObjectPrx	m_transferFileManagerPrx;

	int m_argc;
	char** m_argv;

	QString m_localIp;
	int		m_localPort;

	QString m_remoteIp;
	int		m_remotePort;

	string	m_transferFileIdentity;
};
#endif