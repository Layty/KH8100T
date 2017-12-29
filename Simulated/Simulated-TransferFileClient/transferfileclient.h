/********************************************************************
	created:	2017/12/27
	created:	27:12:2017   15:41
	filename: 	F:\code\GitProject\KH8100T\Simulated\Simulated-TransferFileClient\transferfileclient.h
	file path:	F:\code\GitProject\KH8100T\Simulated\Simulated-TransferFileClient
	file base:	transferfileclient
	file ext:	h
	author:		Masf
	
	purpose:	�ļ�����Ŀͻ��� -- ���ڱ��������ļ������������ļ�
*********************************************************************/
#ifndef TRANSFERFILECLIENT_H
#define TRANSFERFILECLIENT_H

#include <Ice/Ice.h>
#include <IceUtil/IceUtil.h>
#include <IceStorm/IceStorm.h>
#include <QtWidgets/QMainWindow>

#include "configIceDialog.h"
#include "transferFileCommon.h"
#include "transferFileNew.h"

class QAction;
class QTextEdit;

class TransferFileClient : public QMainWindow
{
	Q_OBJECT

public:
	TransferFileClient(QWidget *parent = 0);
	~TransferFileClient();

private:
	void createWidgets();
	void createActions();
	QAction* createActionImpl(const QIcon& icon, const QString& text, const QString& statusTip, 
		const char* slot);
	void createMenus();
	void createToolBars();
	void createStatusBar();
	void updateUi();
	void transferFile(const QString& filePath);
	void transferFile_C(const QString& filePath);
	void transferFile_CPlusPlus(const QString& filePath);

private slots:
	void useIce();
	void useIceStorm();
	void useText();
	void useBinary();
	void useC();
	void useCPlusPlus();
	void selectFile();
	void clearTextEdit();
	void configIceServer();
	void startIceServer();
	void stopIceServer();

public slots:
	void updateTextEdit(const QString& text);

public:
	TransferMode getTransferMode() const;
	FileOperMode getFileOperMode() const;
	FileOperInterface getFileOperInterface() const;
	TransferFileSpace::TransferFilePrx getTransferFilePrx();
	TransferFileSpace::TransferFilePrx getTransferFilePublisher();

private:
	QAction*	iceAction;			// ͨ��Ice���д����ļ�
	QAction*	iceStormAction;		// ͨ��IceStorm���д����ļ�

	QAction*	textAction;			// �����ı��ļ�
	QAction*	binaryAction;		// ����������ļ�

	QAction*	useCAction;			// ʹ��C��׼�ӿڲ����ļ�
	QAction*	useCPlusPlusAction;	// ʹ��C++��׼�ӿڲ����ļ�

	QAction*	selectFileAction;		// ѡ��������ļ�
	QAction*	clearTextEditAction;	// ����ı���
	QAction*	closeAction;			// �رճ���

	QAction*	configIceAction;	// ����Ice����
	QAction*	startIceAction;		// ����Ice����
	QAction*	stopIceAction;		// ֹͣIce����

	QTextEdit*	textEdit;		// ������Ϣ�ı���

	TransferMode		transferMode;		// �ļ����䷽ʽ
	FileOperMode		fileOperMode;		// �ļ���д��ʽ
	FileOperInterface	fileOperInterface;	// �ļ������ӿ�

	Ice::CommunicatorPtr	m_communicatorPtr;	// ice������
	Ice::ObjectAdapterPtr	m_objectAdapterPtr;	// ice�����

	QString	adapterIdentify;	// ��������ʶ
	ConfigIceInfo	configIceInfo;	// Ice����������Ϣ

	TransferFileSpace::TransferFilePrx	m_transferFilePrx;			// �����ļ���Ice����
	TransferFileSpace::TransferFilePrx	m_transferFilePublisher;	// �����ļ���IceStorm��������
};

#endif // TRANSFERFILESERVER_H
