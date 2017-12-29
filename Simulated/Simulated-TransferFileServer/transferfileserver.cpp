
#include <QtWidgets/QtWidgets>
#include <string>

#include "BaseIceStorm.h"
#include "transferFileByCThread.h"
#include "transferfileserver.h"

using namespace std;

TransferFileServer::TransferFileServer(QWidget *parent)
	: QMainWindow(parent), transferMode(Transfer_Ice), fileOperMode(FileOper_Text), fileOperInterface(FileInter_C), 
	adapterIdentify(serverAdapterIdentify), 
	m_communicatorPtr(0), m_objectAdapterPtr(0), 
	m_transferFilePrx(0), m_transferFilePublisher(0)
{
	createWidgets();
	createActions();
	createMenus();
	createToolBars();
	createStatusBar();

	updateUi();
}

TransferFileServer::~TransferFileServer()
{

}

void TransferFileServer::createWidgets()
{
	textEdit = new QTextEdit;
	textEdit->setReadOnly(true);
	setCentralWidget(textEdit);

	setWindowIcon(QIcon(":/icon.png"));
	setWindowTitle(QStringLiteral("�����ļ�--�����"));
	resize(800, 600);
}

void TransferFileServer::createActions()
{
	iceAction = createActionImpl(QIcon(":/ice.png"), QStringLiteral("Ice"), 
		QStringLiteral("ͨ��Ice�����ļ�"), SLOT(useIce()));
	iceStormAction = createActionImpl(QIcon(":/iceStorm.png"), QStringLiteral("IceStorm"), 
		QStringLiteral("ͨ��IceStorm�����ļ�"), SLOT(useIceStorm()));

	textAction = createActionImpl(QIcon(":/text.png"), QStringLiteral("�ı��ļ�"), 
		QStringLiteral("�����ı��ļ�"), SLOT(useText()));
	binaryAction = createActionImpl(QIcon(":/binary.png"), QStringLiteral("�������ļ�"), 
		QStringLiteral("����������ļ�"), SLOT(useBinary()));

	useCAction = createActionImpl(QIcon(":/c.png"), QStringLiteral("��׼C�ӿ�"), 
		QStringLiteral("ʹ��C�ӿڲ����ļ�"), SLOT(useC()));
	useCPlusPlusAction = createActionImpl(QIcon(":/cPlusPlus.png"), QStringLiteral("��׼C++�ӿ�"), 
		QStringLiteral("ʹ��C++�ӿڲ����ļ�"), SLOT(useCPlusPlus()));

	selectFileAction = createActionImpl(QIcon(":/selectFile.png"), QStringLiteral("ѡ���ļ�"), 
		QStringLiteral("ѡ��Ҫ���͵��ļ�"), SLOT(selectFile()));
	clearTextEditAction = createActionImpl(QIcon(":/clear.png"), QStringLiteral("����ı���"), 
		QStringLiteral("����ı���"), SLOT(clearTextEdit()));
	closeAction = createActionImpl(QIcon(":/close.png"), QStringLiteral("�˳�����"), 
		QStringLiteral("�˳�����"), SLOT(close()));

	configIceAction = createActionImpl(QIcon(":/config.png"), QStringLiteral("����Ice����"), 
		QStringLiteral("����Ice����"), SLOT(configIceServer()));
	startIceAction = createActionImpl(QIcon(":/start.png"), QStringLiteral("����Ice����"), 
		QStringLiteral("����Ice����"), SLOT(startIceServer()));
	stopIceAction = createActionImpl(QIcon(":/stop.png"), QStringLiteral("ֹͣIce����"), 
		QStringLiteral("ֹͣIce����"), SLOT(stopIceServer()));
}

QAction* TransferFileServer::createActionImpl( const QIcon& icon, const QString& text, const QString& statusTip, 
	const char* slot)
{
	QAction* action = new QAction(icon, text, this);
	action->setStatusTip(statusTip);
	connect(action, SIGNAL(triggered()), this, slot);
	return action;
}

void TransferFileServer::createMenus()
{
	QMenu* transferModeMenu = menuBar()->addMenu(QStringLiteral("�ļ����䷽ʽ"));
	transferModeMenu->addAction(iceAction);
	transferModeMenu->addAction(iceStormAction);

	QMenu* fileModeMenu = menuBar()->addMenu(QStringLiteral("�ļ���д��ʽ"));
	fileModeMenu->addAction(textAction);
	fileModeMenu->addAction(binaryAction);

	QMenu* fileInterfaceMenu = menuBar()->addMenu(QStringLiteral("�ļ������ӿ�"));
	fileInterfaceMenu->addAction(useCAction);
	fileInterfaceMenu->addAction(useCPlusPlusAction);

	QMenu* operMenu = menuBar()->addMenu(QStringLiteral("����"));
	operMenu->addAction(selectFileAction);
	operMenu->addAction(clearTextEditAction);
	operMenu->addAction(closeAction);

	QMenu* iceMenu = menuBar()->addMenu(QStringLiteral("Ice����"));
	iceMenu->addAction(configIceAction);
	iceMenu->addAction(startIceAction);
	iceMenu->addAction(stopIceAction);
}

void TransferFileServer::createToolBars()
{
	QToolBar* transferModeBar = addToolBar(QStringLiteral("�ļ����䷽ʽ"));
	transferModeBar->addAction(iceAction);
	transferModeBar->addAction(iceStormAction);

	QToolBar* fileModeModeBar = addToolBar(QStringLiteral("�ļ���д��ʽ"));
	fileModeModeBar->addAction(textAction);
	fileModeModeBar->addAction(binaryAction);

	QToolBar* fileInterfaceBar = addToolBar(QStringLiteral("�ļ������ӿ�"));
	fileInterfaceBar->addAction(useCAction);
	fileInterfaceBar->addAction(useCPlusPlusAction);

	QToolBar* operBar = addToolBar(QStringLiteral("����"));
	operBar->addAction(selectFileAction);
	operBar->addAction(clearTextEditAction);
	operBar->addAction(closeAction);

	QToolBar* iceBar = addToolBar(QStringLiteral("Ice����"));
	iceBar->addAction(configIceAction);
	iceBar->addAction(startIceAction);
	iceBar->addAction(stopIceAction);
}

void TransferFileServer::createStatusBar()
{
	statusBar()->showMessage(QStringLiteral("׼������"));
}

void TransferFileServer::updateUi()
{
	iceAction->setEnabled(transferMode != Transfer_Ice);
	iceStormAction->setEnabled(transferMode != Transfer_IceStorm);

	textAction->setEnabled(fileOperMode != FileOper_Text);
	binaryAction->setEnabled(fileOperMode != FileOper_Binary);

	useCAction->setEnabled(fileOperInterface != FileInter_C);
	useCPlusPlusAction->setEnabled(fileOperInterface != FileInter_CPlusPlus);
}

void TransferFileServer::transferFile( const QString& filePath )
{
	if (getFileOperInterface() == FileInter_C)
	{
		transferFile_C(filePath);
	}
	else if (getFileOperInterface() == FileInter_CPlusPlus)
	{
		transferFile_CPlusPlus(filePath);
	}
}

void TransferFileServer::transferFile_C( const QString& filePath )
{
	TransferFileByCThread thread(this, filePath);
	connect(&thread, SIGNAL(finished()), &thread, SLOT(deleteLater()));
	thread.start();
}

void TransferFileServer::transferFile_CPlusPlus( const QString& filePath )
{

}

void TransferFileServer::useIce()
{
	transferMode = Transfer_Ice;
	updateUi();
}

void TransferFileServer::useIceStorm()
{
	transferMode = Transfer_IceStorm;
	updateUi();
}

void TransferFileServer::useText()
{
	fileOperMode = FileOper_Text;
	updateUi();
}

void TransferFileServer::useBinary()
{
	fileOperMode = FileOper_Binary;
	updateUi();
}

void TransferFileServer::useC()
{
	fileOperInterface = FileInter_C;
	updateUi();
}

void TransferFileServer::useCPlusPlus()
{
	fileOperInterface = FileInter_CPlusPlus;
	updateUi();
}

void TransferFileServer::selectFile()
{
	QString filePath = QFileDialog::getOpenFileName(this, QStringLiteral("ѡ���ļ�"));
	if (filePath.isEmpty())
	{
		return;
	}

	// �����ļ�
	filePath.replace("\\", "/");
	transferFile(filePath);
}

void TransferFileServer::clearTextEdit()
{
	if (textEdit)
	{
		textEdit->clear();
	}
}

void TransferFileServer::configIceServer()
{
	ConfigIceDialog dialog;
	if (dialog.exec() == QDialog::Accepted)
	{
		configIceInfo = dialog.getConfigIceInfo();
		BaseIceStorm::SetIceStormIpAndPort(configIceInfo.iceStormIp.toStdString(), configIceInfo.iceStormPort);
	}
}

void TransferFileServer::startIceServer()
{
	if (m_communicatorPtr)
	{
		return;
	}

	try
	{
		int argc = 0;
		Ice::InitializationData initData;
		initData.properties = Ice::createProperties();
		m_communicatorPtr = Ice::initialize(argc, 0, initData);
		QString endPoints = QString("tcp -h %1 -p %2").arg(configIceInfo.iceIp).arg(configIceInfo.icePort);
		m_objectAdapterPtr = m_communicatorPtr->createObjectAdapterWithEndpoints(adapterIdentify.toStdString(), 
			endPoints.toStdString());

		m_objectAdapterPtr->activate();

		updateTextEdit(QStringLiteral("����� -- Ice���������ɹ�"));
	}
	catch(const Ice::Exception& ex)
	{
		QMessageBox::warning(this, QStringLiteral("����Ice�����쳣"), ex.what());
	}
}

void TransferFileServer::stopIceServer()
{
	if (m_communicatorPtr)
	{
		try
		{
			m_communicatorPtr->destroy();
			
			m_communicatorPtr = 0;
			m_objectAdapterPtr = 0;

			updateTextEdit(QStringLiteral("����� -- Ice����ֹͣ�ɹ�"));
		}
		catch(const Ice::Exception& ex)
		{
			QMessageBox::warning(this, QStringLiteral("ֹͣIce�����쳣"), ex.what());
		}
	}
}

void TransferFileServer::updateTextEdit( const QString& text )
{
	if (textEdit)
	{
		textEdit->moveCursor(QTextCursor::End);
		textEdit->insertPlainText(text);
		textEdit->insertPlainText("\n");
		textEdit->moveCursor(QTextCursor::End);
	}
}

TransferMode TransferFileServer::getTransferMode() const
{
	return transferMode;
}

FileOperMode TransferFileServer::getFileOperMode() const
{
	return fileOperMode;
}

FileOperInterface TransferFileServer::getFileOperInterface() const
{
	return fileOperInterface;
}

TransferFileSpace::TransferFilePrx TransferFileServer::getTransferFilePrx()
{
	if (m_transferFilePrx == 0)
	{
		try
		{
			QString proxy = QString("%1: tcp -h %2 -p %3").arg(clientAdapterIdentify).
				arg(configIceInfo.iceOffsideIp).arg(configIceInfo.iceOffsidePort);
			m_transferFilePrx = TransferFileSpace::TransferFilePrx::checkedCast(
				m_communicatorPtr->stringToProxy(proxy.toStdString()));
			if (m_transferFilePrx != 0)
			{
				updateTextEdit(QStringLiteral("���������ļ���Ice����ɹ�"));
			}
			else
			{
				updateTextEdit(QStringLiteral("���������ļ���Ice����ʧ��"));
			}
		}
		catch(const Ice::Exception& ex)
		{
			updateTextEdit(QStringLiteral("���������ļ���Ice�����쳣: %1").arg(ex.what()));
			m_transferFilePrx = 0;
		}
	}
	
	return m_transferFilePrx;
}

TransferFileSpace::TransferFilePrx TransferFileServer::getTransferFilePublisher()
{
	if (m_transferFilePublisher == 0)
	{
		string topic = TransferFileSpace::TransferFileTopic;
		string deliverModel = "oneway";
		try
		{
			Ice::ObjectPrx objectPrx = BaseIceStorm::GetPublisher(m_communicatorPtr, topic, deliverModel);
			if (objectPrx != 0)
			{
				m_transferFilePublisher = TransferFileSpace::TransferFilePrx::uncheckedCast(objectPrx);
				updateTextEdit(QStringLiteral("���������ļ���IceStorm��������ɹ�"));
			}
			else
			{
				m_transferFilePublisher = 0;
				updateTextEdit(QStringLiteral("���������ļ���IceStorm��������ʧ��"));
			}
		}
		catch(const Ice::Exception& ex)
		{
			updateTextEdit(QStringLiteral("���������ļ���IceStorm���������쳣: %1").arg(ex.what()));
			m_transferFilePublisher = 0;
		}
	}
	
	return m_transferFilePublisher;
}
