#include "transactionframe.h"
#include "RandomOperateDb.h"
#include "fastdb.h"

#include <QtWidgets/QtWidgets>

#define Thread_Count	10

TransactionFrame::TransactionFrame(QWidget *parent)
	: QMainWindow(parent)
{
	createWidgets();
	createServices();
	createActions();
	createConnects();
	createMenus();
	createToolBars();
	createStatusBar();
	
}

TransactionFrame::~TransactionFrame()
{
	Q_FOREACH(MasterServiceThread* thread, vctMasterServices)
	{
		if (thread)
		{
			delete thread;
			thread = NULL;
		}
	}

	if (slaveService)
	{
		delete slaveService;
		slaveService = NULL;
	}
}

void TransactionFrame::createServices()
{
	openDatabase();

	vctMasterServices.reserve(Thread_Count);
	for (int i = 0; i < Thread_Count; ++i)
	{
		vctMasterServices.push_back(new MasterServiceThread(&m_db));
	}
	slaveService = new SlaveServiceThread();
}

void TransactionFrame::createWidgets()
{
	textEdit = new QTextEdit();
	setCentralWidget(textEdit);

	resize(800, 600);
	setWindowTitle(QStringLiteral("Fastdb���ݻָ�"));
	setWindowIcon(QIcon(":/images/logger.png"));
}

void TransactionFrame::createMenus()
{
	fileMenu = menuBar()->addMenu(QIcon(":/images/file.png"), QStringLiteral("�ļ�"));
	fileMenu->addAction(closeAction);

	operMenu = menuBar()->addMenu(QIcon(":/images/oper.png"), QStringLiteral("����"));
	operMenu->addAction(startMasterAction);
	operMenu->addAction(startSlaveAction);
	operMenu->addAction(stopAction);
	operMenu->addSeparator();
	operMenu->addAction(selectAction);
	operMenu->addAction(clearAction);
	operMenu->addSeparator();
	operMenu->addAction(restoreAction);
}

void TransactionFrame::createToolBars()
{
	fileToolbar = addToolBar(QStringLiteral("�ļ�"));
	fileToolbar->addAction(closeAction);

	operToolbar = addToolBar(QStringLiteral("����"));
	operToolbar->addAction(startMasterAction);
	operToolbar->addAction(startSlaveAction);
	operToolbar->addAction(stopAction);
	operToolbar->addSeparator();
	operToolbar->addAction(selectAction);
	operToolbar->addAction(clearAction);
	operToolbar->addSeparator();
	operToolbar->addAction(restoreAction);
}

void TransactionFrame::createStatusBar()
{
	statusBar()->showMessage(QStringLiteral("׼������"));
}

void TransactionFrame::createActions()
{
	closeAction = new QAction(QIcon(":/images/close.png"), QStringLiteral("�ر�"), this);
	closeAction->setStatusTip(QStringLiteral("�˳�����"));
	connect(closeAction, SIGNAL(triggered()), this, SLOT(closeApp()));

	startMasterAction = new QAction(QIcon(":/images/startMaster.png"), QStringLiteral("����������"), this);
	startMasterAction->setStatusTip(QStringLiteral("����������"));
	connect(startMasterAction, SIGNAL(triggered()), this, SLOT(startMasterService()));

	startSlaveAction = new QAction(QIcon(":/images/startSlave.png"), QStringLiteral("����������"), this);
	startSlaveAction->setStatusTip(QStringLiteral("����������"));
	connect(startSlaveAction, SIGNAL(triggered()), this, SLOT(startSlaveService()));

	stopAction = new QAction(QIcon(":/images/stop.png"), QStringLiteral("ֹͣ����"), this);
	stopAction->setStatusTip(QStringLiteral("ֹͣ����"));
	stopAction->setEnabled(false);
	connect(stopAction, SIGNAL(triggered()), this, SLOT(stopService()));

	selectAction = new QAction(QIcon(":/images/select.png"), QStringLiteral("��ѯ����"), this);
	selectAction->setStatusTip(QStringLiteral("��ѯ����"));
	connect(selectAction, SIGNAL(triggered()), this, SLOT(selectData()));

	clearAction = new QAction(QIcon(":/images/clear.png"), QStringLiteral("����ı�"), this);
	clearAction->setStatusTip(QStringLiteral("����ı�"));
	connect(clearAction, SIGNAL(triggered()), this, SLOT(clearTextEdit()));

	restoreAction = new QAction(QIcon(":/images/restore.png"), QStringLiteral("�ָ�ʵʱ��"), this);
	restoreAction->setStatusTip(QStringLiteral("�ָ�ʵʱ��"));
	connect(restoreAction, SIGNAL(triggered()), this, SLOT(restoreDb()));
}

void TransactionFrame::createConnects()
{
	//connect(this, SIGNAL(startMasterServiceSignal()), &masterService, SLOT(start()));
	Q_FOREACH(MasterServiceThread* thread, vctMasterServices)
	{
		connect(this, SIGNAL(startMasterServiceSignal()), thread, SLOT(start()));
	}
	connect(this, SIGNAL(startSlaveServiceSignal()), slaveService, SLOT(start()));

	//connect(&masterService, SIGNAL(outputOperationInfo(QString)), this, SLOT(outputOperationInfo(QString)));
	Q_FOREACH(MasterServiceThread* thread, vctMasterServices)
	{
		connect(thread, SIGNAL(outputOperationInfo(QString)), this, SLOT(outputOperationInfo(QString)));
	}
	connect(slaveService, SIGNAL(outputOperationInfo(QString)), this, SLOT(outputOperationInfo(QString)));
}

void TransactionFrame::openDatabase()
{
	if (m_db.isOpen())
	{
		outputOperationInfo(LoggerInfo::getLoggerInfo(QStringLiteral("ʵʱ���Ѵ�"), FrameService));
		return;
	}

	if(!m_db.open(DatabaseName))
	{
		outputOperationInfo(LoggerInfo::getLoggerInfo(QStringLiteral("ʵʱ���ʧ��"), FrameService));
		return;
	}
	outputOperationInfo(LoggerInfo::getLoggerInfo(QStringLiteral("ʵʱ��򿪳ɹ�"), FrameService));
}

void TransactionFrame::reopenDatabase()
{
	if (m_db.isOpen())
	{
		m_db.close();
	}

	if(!m_db.open(DatabaseName))
	{
		outputOperationInfo(LoggerInfo::getLoggerInfo(QStringLiteral("ʵʱ���ʧ��"), FrameService));
		return;
	}
	outputOperationInfo(LoggerInfo::getLoggerInfo(QStringLiteral("ʵʱ��򿪳ɹ�"), FrameService));
}

void TransactionFrame::closeDatabase()
{
	if (!m_db.isOpen())
	{
		outputOperationInfo(LoggerInfo::getLoggerInfo(QStringLiteral("ʵʱ���ѹر�"), FrameService));
		return;
	}

	m_db.close();
	outputOperationInfo(LoggerInfo::getLoggerInfo(QStringLiteral("ʵʱ��رճɹ�"), FrameService));
}

void TransactionFrame::updateStartStopAction( bool isStart )
{
	startMasterAction->setEnabled(!isStart);
	startSlaveAction->setEnabled(!isStart);
	stopAction->setEnabled(isStart);
	selectAction->setEnabled(!isStart);
}

void TransactionFrame::setCurrentServiceType( ServiceType type )
{
	m_currServiceType = type;
}

ServiceType TransactionFrame::getCurrentServiceType() const
{
	return m_currServiceType;
}

QString TransactionFrame::getRestoreStatus( dbFileTransactionLogger::RestoreStatus status )
{
	switch(status)
	{
	case dbFileTransactionLogger::rsOK:
		return QStringLiteral("rsOK");
	case dbFileTransactionLogger::rsCRCMismatch:
		return QStringLiteral("rsCRCMismatch");
	case dbFileTransactionLogger::rsReadFailed:
		return QStringLiteral("rsReadFailed");
	case dbFileTransactionLogger::rsTableNotFound:
		return QStringLiteral("rsTableNotFound");
	case  dbFileTransactionLogger::rsOIDMismatch:
		return QStringLiteral("rsOIDMismatch");
	default:
		return QStringLiteral("Unknown");
	}
}

void TransactionFrame::closeApp()
{
	if(QMessageBox::information(this, QStringLiteral("�˳�"), QStringLiteral("�Ƿ��˳���ǰӦ�ó���"), 
		QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok)
	{
		stopService();
		close();
	}
	return;
}

void TransactionFrame::startMasterService()
{
	updateStartStopAction(true);
	openDatabase();

	tl.open(_T("testtl.log"), dbFile::truncate|dbFile::no_sync);
	m_db.setTransactionLogger(&tl);

	outputOperationInfo(LoggerInfo::getLoggerInfo(QStringLiteral("��ʵʱ���������־�ļ��ɹ�"), FrameService));

	setCurrentServiceType(MasterService);

	emit startMasterServiceSignal();
}

void TransactionFrame::startSlaveService()
{
	updateStartStopAction(true);
	closeDatabase();

	setCurrentServiceType(SlaveService);

	emit startSlaveServiceSignal();
}

void TransactionFrame::stopService()
{
	updateStartStopAction(false);

	ServiceType currServiceType = getCurrentServiceType();
	if (currServiceType == MasterService)
	{
		Q_FOREACH(MasterServiceThread* thread, vctMasterServices)
		{
			if (thread->isRunning())
			{
				thread->setStop(true);
			}
		}
	}
	else if (currServiceType == SlaveService)
	{
		if (slaveService->isRunning())
		{
			slaveService->setStop(true);
		}
	}

	bool allThreadFinished = false;
	while(!allThreadFinished)
	{
		allThreadFinished = true;
		if (currServiceType == MasterService)
		{
			Q_FOREACH(MasterServiceThread* thread, vctMasterServices)
			{
				if (!thread->isFinished())
				{
					allThreadFinished = false;
				}
			}
		}
		else if (currServiceType == SlaveService)
		{
			if (!slaveService->isFinished())
			{
				allThreadFinished = false;
			}
		}
	}
	outputOperationInfo(LoggerInfo::getLoggerInfo(QStringLiteral("�ر�ʵʱ���������־�ļ��ɹ�"), FrameService));

	if (currServiceType == MasterService)
	{
		m_db.close();
		tl.close();
	}
}

void TransactionFrame::selectData()
{
	openDatabase();

	RandomOperateDb operDb(&m_db);
	QString threadId = QString("%1").arg((DWORD)(QThread::currentThreadId()));
	operDb.setThreadId(threadId);
	operDb.startOperate(SelectMode);

	outputOperationInfo(LoggerInfo::getLoggerInfo(operDb.getOperateInfo(), FrameService));

}

void TransactionFrame::clearTextEdit()
{
	if (textEdit)
	{
		textEdit->clear();
	}
}

void TransactionFrame::restoreDb()
{
	// ͨ��������־�ָ�ʵʱ��ʱ������ر�ʵʱ�⣬�����´򿪣����ܽ��к����ָ�����
	reopenDatabase();
	if(!tl.open(_T("testtl.log"), dbFile::read_only))
	{
		outputOperationInfo(LoggerInfo::getLoggerInfo(QStringLiteral("��������־�ļ�ʧ��"), FrameService));

		return;
	}

	outputOperationInfo(LoggerInfo::getLoggerInfo(QStringLiteral("��������־�ļ��ɹ�"), FrameService));
	
	try 
	{
		size_t n;
		dbFileTransactionLogger::RestoreStatus status = tl.restore(m_db, n);
		if (status == dbFileTransactionLogger::rsOK)
		{
			tl.close();
			outputOperationInfo(LoggerInfo::getLoggerInfo(QStringLiteral("�ָ�ʵʱ��ɹ�"), FrameService));
		}
		else
		{
			tl.rollback();
			QString text = QStringLiteral("�ָ�ʵʱ��ʧ��\t����ԭ��: %1").arg(getRestoreStatus(status));
			outputOperationInfo(LoggerInfo::getLoggerInfo(text, FrameService));
		}
	}
	catch(const dbException& ex)
	{
		QString text = QStringLiteral("�ָ�ʵʱ���쳣\t�쳣ԭ��: %1").arg(QString().fromStdString(ex.what()));
		outputOperationInfo(LoggerInfo::getLoggerInfo(text, FrameService));
	}
}

void TransactionFrame::outputOperationInfo( QString text )
{
	if (textEdit)
	{
		textEdit->moveCursor(QTextCursor::End);
		textEdit->insertPlainText(text);
		textEdit->moveCursor(QTextCursor::End);
	}
}

