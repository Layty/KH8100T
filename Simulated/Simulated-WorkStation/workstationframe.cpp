#include "workstationframe.h"
#include "TableHeader.h"
#include "workstationserver.h"
#include "workstationserverthread.h"
#include "OperationInfo.h"

#include <QtWidgets/QtWidgets>

WorkStationFrame::WorkStationFrame(int argc, char* argv[], QWidget *parent)
	: QMainWindow(parent), m_argc(argc), m_argv(argv)
{
	m_workStationServerPtr = new WorkStationServer(m_argc, m_argv);
	m_workStationServerThreadPtr = new WorkStationServerThread;

	createWidgets();

	createActions();
	createMenus();
	createToolBars();
	createStatusBar();
	createConnects();

}

WorkStationFrame::~WorkStationFrame()
{

}

void WorkStationFrame::createWidgets()
{
	tableWidget = new QTableWidget;
	QStringList tableHeaders = TableHeader::getTableHeaderLabels();
	tableWidget->setColumnCount(tableHeaders.count());
	tableWidget->setShowGrid(true);
	tableWidget->setHorizontalHeaderLabels(tableHeaders);

	textEdit = new QTextEdit;
	textEdit->setTextBackgroundColor(QColor(255, 0, 0));
	textEdit->setReadOnly(true);

	QSplitter* splitter = new QSplitter(Qt::Vertical);
	splitter->addWidget(tableWidget);
	splitter->addWidget(textEdit);
	splitter->setStretchFactor(0, 1);
	splitter->setStretchFactor(1, 4);
	setCentralWidget(splitter);

	OperationInfo info(TYPE_CLIENT, "������Ϣ����");
	updateTableWidget(info);

	resize(1200, 800);
	setWindowTitle(QStringLiteral("����վģ���"));
	setWindowIcon(QIcon(":/images/workstation.png"));
}

void WorkStationFrame::createActions()
{
	startServerAction = new QAction(QIcon(":/images/startServer.png"), QStringLiteral("��������"), this);
	startServerAction->setStatusTip(QStringLiteral("����Ice����"));
	connect(startServerAction, SIGNAL(triggered()), this, SLOT(startServer()));

	stopServerAction = new QAction(QIcon(":/images/stopServer.png"), QStringLiteral("ֹͣ����"), this);
	stopServerAction->setStatusTip(QStringLiteral("ֹͣIce����"));
	stopServerAction->setEnabled(false);
	connect(stopServerAction, SIGNAL(triggered()), this, SLOT(stopServer()));

	exitAction = new QAction(QIcon(":/images/exit.png"), QStringLiteral("�˳�"), this);
	exitAction->setShortcut(QKeySequence::Quit);
	exitAction->setStatusTip(QStringLiteral("�˳�ģ�������"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
	
	requestStormRdbDataAction = new QAction(QIcon(":/images/requestStormRdb.png"), QStringLiteral("����ʵʱ����(IceStorm)"), this);
	requestStormRdbDataAction->setStatusTip(QStringLiteral("ͨ��IceStorm����ʵʱ����"));
	requestStormRdbDataAction->setEnabled(false);
	connect(requestStormRdbDataAction, SIGNAL(triggered()), this, SLOT(requestStormRdbData()));
	
	requestStormTopoDataAction = new QAction(QIcon(":/images/requestStormTopo.png"), QStringLiteral("������������(IceStorm)"), this);
	requestStormTopoDataAction->setStatusTip(QStringLiteral("ͨ��IceStorm������������"));
	requestStormTopoDataAction->setEnabled(false);
	connect(requestStormTopoDataAction, SIGNAL(triggered()), this, SLOT(requestStormTopoData()));

	requestRdbDataAction = new QAction(QIcon(":/images/requestRdb.png"), QStringLiteral("����ʵʱ����(Ice)"), this);
	requestRdbDataAction->setStatusTip(QStringLiteral("ͨ��Ice����ʵʱ����"));
	requestRdbDataAction->setEnabled(false);
	connect(requestRdbDataAction, SIGNAL(triggered()), this, SLOT(requestRdbData()));

	requestTopoDataAction = new QAction(QIcon(":/images/requestTopo.png"), QStringLiteral("������������(Ice)"), this);
	requestTopoDataAction->setStatusTip(QStringLiteral("ͨ��Ice������������"));
	requestTopoDataAction->setEnabled(false);
	connect(requestTopoDataAction, SIGNAL(triggered()), this, SLOT(requestTopoData()));

	subscriberRdbRequestAction = new QAction(QIcon(":/images/subscribeRdbRequest.png"), QStringLiteral("����ʵʱ��������"), this);
	subscriberRdbRequestAction->setStatusTip(QStringLiteral("����ʵʱ��������"));
	subscriberRdbRequestAction->setEnabled(false);
	connect(subscriberRdbRequestAction, SIGNAL(triggered()), this, SLOT(subscriberRdbRequest()));

	subscriberRdbRespondAction = new QAction(QIcon(":/images/subscribeRdbRespond.png"), QStringLiteral("����ʵʱ������Ӧ"), this);
	subscriberRdbRespondAction->setStatusTip(QStringLiteral("����ʵʱ������Ӧ"));
	subscriberRdbRespondAction->setEnabled(false);
	connect(subscriberRdbRespondAction, SIGNAL(triggered()), this, SLOT(subscriberRdbRespond()));

	subscriberAlarmDataAction = new QAction(QIcon(":/images/subscribeAlarmData.png"), QStringLiteral("���ı�������"), this);
	subscriberAlarmDataAction->setStatusTip(QStringLiteral("���ı�������"));
	subscriberAlarmDataAction->setEnabled(false);
	connect(subscriberAlarmDataAction, SIGNAL(triggered()), this, SLOT(subscriberAlarmData()));

	subscriberFepDataAction = new QAction(QIcon(":/images/subscribeFepData.png"), QStringLiteral("����ǰ�û���������"), this);
	subscriberFepDataAction->setStatusTip(QStringLiteral("����ǰ�û���������"));
	subscriberFepDataAction->setEnabled(false);
	connect(subscriberFepDataAction, SIGNAL(triggered()), this, SLOT(subscriberFepData()));

	subscriberYkFepAction = new QAction(QIcon(":/images/subscribeFepData.png"), QStringLiteral("����ң������"), this);
	subscriberYkFepAction->setStatusTip(QStringLiteral("����ң������"));
	subscriberYkFepAction->setEnabled(false);
	connect(subscriberYkFepAction, SIGNAL(triggered()), this, SLOT(subscriberYkFep()));

	subscriberYkAppAction = new QAction(QIcon(":/images/subscribeFepData.png"), QStringLiteral("����ң����Ӧ"), this);
	subscriberYkAppAction->setStatusTip(QStringLiteral("����ң����Ӧ"));
	subscriberYkAppAction->setEnabled(false);
	connect(subscriberYkAppAction, SIGNAL(triggered()), this, SLOT(subscriberYkApp()));

	ykSelectAction = new QAction(QIcon(":/images/subscribeFepData.png"), QStringLiteral("ң��ѡ��"), this);
	ykSelectAction->setStatusTip(QStringLiteral("ң��ѡ��"));
	ykSelectAction->setEnabled(false);
	connect(ykSelectAction, SIGNAL(triggered()), this, SLOT(ykSelect()));
	
	clearAction = new QAction(QIcon(":/images/clear.png"), QStringLiteral("����ı�"), this);
	clearAction->setStatusTip(QStringLiteral("����ı�"));
	connect(clearAction, SIGNAL(triggered()), this, SLOT(clearTextEdit()));

	helpAction = new QAction(QIcon(":/images/about.png"), QStringLiteral("����"), this);
	helpAction->setStatusTip(QStringLiteral("����ģ�������"));
	connect(helpAction, SIGNAL(triggered()), this, SLOT(about()));
}

void WorkStationFrame::createMenus()
{
	fileMenu = menuBar()->addMenu(QStringLiteral("�ļ�"));
	fileMenu->addAction(startServerAction);
	fileMenu->addAction(stopServerAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	operMenu = menuBar()->addMenu(QStringLiteral("����"));
	QMenu* iceStormMenu = operMenu->addMenu(QIcon(":/images/icestormmenu.png"), QStringLiteral("IceStorm"));
	iceStormMenu->addAction(requestStormRdbDataAction);
	iceStormMenu->addAction(requestStormTopoDataAction);
	QMenu* iceMenu = operMenu->addMenu(QIcon(":/images/icemenu.png"), QStringLiteral("Ice"));
	iceMenu->addAction(requestRdbDataAction);
	iceMenu->addAction(requestTopoDataAction);
	QMenu* subscriberMenu = operMenu->addMenu(QIcon(":/images/icemenu.png"), QStringLiteral("IceStorm Subscriber"));
	subscriberMenu->addAction(subscriberRdbRequestAction);
	subscriberMenu->addAction(subscriberRdbRespondAction);
	subscriberMenu->addAction(subscriberAlarmDataAction);
	subscriberMenu->addAction(subscriberFepDataAction);
	subscriberMenu->addAction(subscriberYkFepAction);
	subscriberMenu->addAction(subscriberYkAppAction);
	subscriberMenu->addSeparator();
	subscriberMenu->addAction(ykSelectAction);
	operMenu->addSeparator();
	operMenu->addAction(clearAction);

	helpMenu = menuBar()->addMenu(QStringLiteral("����"));
	helpMenu->addAction(helpAction);
}

void WorkStationFrame::createToolBars()
{
	fileToolBar = addToolBar(QStringLiteral("�ļ�"));
	fileToolBar->addAction(startServerAction);
	fileToolBar->addAction(stopServerAction);
	fileToolBar->addSeparator();
	fileToolBar->addAction(exitAction);

	operToolBar = addToolBar(QStringLiteral("����"));
	operToolBar->addAction(requestStormRdbDataAction);
	operToolBar->addAction(requestStormTopoDataAction);
	operToolBar->addSeparator();
	operToolBar->addAction(requestRdbDataAction);
	operToolBar->addAction(requestTopoDataAction);
	operToolBar->addSeparator();
	operToolBar->addAction(subscriberRdbRequestAction);
	operToolBar->addAction(subscriberRdbRespondAction);
	operToolBar->addAction(subscriberAlarmDataAction);
	operToolBar->addAction(subscriberFepDataAction);
	operToolBar->addAction(subscriberYkFepAction);
	operToolBar->addAction(subscriberYkAppAction);
	operToolBar->addSeparator();
	operToolBar->addAction(ykSelectAction);
	operToolBar->addSeparator();
	operToolBar->addAction(clearAction);
}

void WorkStationFrame::createStatusBar()
{
	statusBar()->showMessage(QStringLiteral("׼������"));
}

void WorkStationFrame::createConnects()
{
	qRegisterMetaType<OperationInfo>("OperationInfo");
	connect(this, SIGNAL(serverStarted(bool)), this, SLOT(updateActions(bool)));
	connect(this, SIGNAL(requestCompleteData()), m_workStationServerThreadPtr, SLOT(requestCompleteData()));
	connect(this, SIGNAL(selectCompleteData()), m_workStationServerThreadPtr, SLOT(selectCompleteData()));
	connect(this, SIGNAL(subscriberRdbRequestSignal(bool)), m_workStationServerThreadPtr, SLOT(subscriberRdbRequest(bool)));
	connect(this, SIGNAL(subscriberRdbRespondSignal(bool)), m_workStationServerThreadPtr, SLOT(subscriberRdbRespond(bool)));
	connect(this, SIGNAL(subscriberAlarmDataSignal(bool)), m_workStationServerThreadPtr, SLOT(subscriberAlarmData(bool)));
	connect(this, SIGNAL(subscriberFepDataSignal(bool)), m_workStationServerThreadPtr, SLOT(subscriberFepData(bool)));
	connect(this, SIGNAL(subscriberYkFepSignal(bool)), m_workStationServerThreadPtr, SLOT(subscriberYkFep(bool)));
	connect(this, SIGNAL(subscriberYkAppSignal(bool)), m_workStationServerThreadPtr, SLOT(subscriberYkApp(bool)));
	connect(this, SIGNAL(ykSelectSignal(bool)), m_workStationServerThreadPtr, SLOT(ykSelect(bool)));
	connect(m_workStationServerThreadPtr, &WorkStationServerThread::executeOperation, 
		this, &WorkStationFrame::updateTableWidget);
	connect(m_workStationServerThreadPtr, &WorkStationServerThread::outputReceiveData, 
		this, &WorkStationFrame::updateTextEdit);
}

void WorkStationFrame::updateTableWidget( const OperationInfo& info )
{
	if (tableWidget)
	{
		int count = tableWidget->rowCount();
		tableWidget->insertRow(count);
		for (int i = 0; i < Header_Count; ++i)
		{
			tableWidget->setItem(count, i, new QTableWidgetItem(info.getContent(i)));
		}

		tableWidget->resizeColumnsToContents();
	}
}

void WorkStationFrame::updateTextEdit( const QString& text )
{
	textEdit->moveCursor(QTextCursor::End);
	textEdit->insertPlainText(text);
	textEdit->insertPlainText("\n");
	textEdit->moveCursor(QTextCursor::End);
}

void WorkStationFrame::updateActions( bool serverStarted )
{
	startServerAction->setEnabled(!serverStarted);
	stopServerAction->setEnabled(serverStarted);
	requestStormRdbDataAction->setEnabled(serverStarted);
	requestStormTopoDataAction->setEnabled(serverStarted);
	requestRdbDataAction->setEnabled(serverStarted);
	requestTopoDataAction->setEnabled(serverStarted);
	subscriberRdbRequestAction->setEnabled(serverStarted);
	subscriberRdbRespondAction->setEnabled(serverStarted);
	subscriberAlarmDataAction->setEnabled(serverStarted);
	subscriberFepDataAction->setEnabled(serverStarted);
	subscriberYkFepAction->setEnabled(serverStarted);
	subscriberYkAppAction->setEnabled(serverStarted);
	ykSelectAction->setEnabled(serverStarted);
}

void WorkStationFrame::startServer()
{
	QThread* threadPtr = new QThread;
	m_workStationServerPtr->setThreadPtr(m_workStationServerThreadPtr);
	m_workStationServerPtr->moveToThread(threadPtr);
	connect(threadPtr, SIGNAL(started()), m_workStationServerPtr, SLOT(startServer()));
	connect(m_workStationServerPtr, &WorkStationServer::executeOperation, this, &WorkStationFrame::updateTableWidget);
	connect(m_workStationServerThreadPtr, &WorkStationServerThread::executeOperation, this, &WorkStationFrame::updateTableWidget);
	threadPtr->start();

	emit serverStarted(true);
}

void WorkStationFrame::stopServer()
{
	emit serverStarted(false);
}

void WorkStationFrame::requestStormRdbData()
{
	emit requestCompleteData();
}

void WorkStationFrame::requestStormTopoData()
{

}

void WorkStationFrame::requestRdbData()
{
	emit selectCompleteData();
}

void WorkStationFrame::requestTopoData()
{

}

void WorkStationFrame::subscriberRdbRequest()
{
	QString text = subscriberRdbRequestAction->text();
	if (text.contains(QStringLiteral("ȡ��")))
	{
		subscriberRdbRequestAction->setText(QStringLiteral("����ʵʱ��������"));
		subscriberRdbRequestAction->setStatusTip(QStringLiteral("����ʵʱ��������"));

		emit subscriberRdbRequestSignal(true);
	}
	else
	{
		subscriberRdbRequestAction->setText(QStringLiteral("ȡ������ʵʱ��������"));
		subscriberRdbRequestAction->setStatusTip(QStringLiteral("ȡ������ʵʱ��������"));

		emit subscriberRdbRequestSignal(false);
	}
}


void WorkStationFrame::subscriberRdbRespond()
{
	QString text = subscriberRdbRespondAction->text();
	if (text.contains(QStringLiteral("ȡ��")))
	{
		subscriberRdbRespondAction->setText(QStringLiteral("����ʵʱ������Ӧ"));
		subscriberRdbRespondAction->setStatusTip(QStringLiteral("����ʵʱ������Ӧ"));

		emit subscriberRdbRespondSignal(true);
	}
	else
	{
		subscriberRdbRespondAction->setText(QStringLiteral("ȡ������ʵʱ������Ӧ"));
		subscriberRdbRespondAction->setStatusTip(QStringLiteral("ȡ������ʵʱ������Ӧ"));

		emit subscriberRdbRespondSignal(false);
	}
}

void WorkStationFrame::subscriberAlarmData()
{
	QString text = subscriberAlarmDataAction->text();
	if (text.contains(QStringLiteral("ȡ��")))
	{
		subscriberAlarmDataAction->setText(QStringLiteral("���ı�������"));
		subscriberAlarmDataAction->setStatusTip(QStringLiteral("���ı�������"));

		emit subscriberAlarmDataSignal(true);
	}
	else
	{
		subscriberAlarmDataAction->setText(QStringLiteral("ȡ�����ı�������"));
		subscriberAlarmDataAction->setStatusTip(QStringLiteral("ȡ�����ı�������"));

		emit subscriberAlarmDataSignal(false);
	}
}

void WorkStationFrame::subscriberFepData()
{
	QString text = subscriberFepDataAction->text();
	if (text.contains(QStringLiteral("ȡ��")))
	{
		subscriberFepDataAction->setText(QStringLiteral("����ǰ�û�����"));
		subscriberFepDataAction->setStatusTip(QStringLiteral("����ǰ�û�����"));

		emit subscriberFepDataSignal(true);
	}
	else
	{
		subscriberFepDataAction->setText(QStringLiteral("ȡ������ǰ�û�����"));
		subscriberFepDataAction->setStatusTip(QStringLiteral("ȡ������ǰ�û�����"));

		emit subscriberFepDataSignal(false);
	}
}


void WorkStationFrame::subscriberYkFep()
{
	QString text = subscriberYkFepAction->text();
	if (text.contains(QStringLiteral("ȡ��")))
	{
		subscriberYkFepAction->setText(QStringLiteral("����ң������"));
		subscriberYkFepAction->setStatusTip(QStringLiteral("����ң������"));

		emit subscriberYkFepSignal(true);
	}
	else
	{
		subscriberYkFepAction->setText(QStringLiteral("ȡ������ң������"));
		subscriberYkFepAction->setStatusTip(QStringLiteral("ȡ������ң������"));

		emit subscriberYkFepSignal(false);
	}
}

void WorkStationFrame::subscriberYkApp()
{
	QString text = subscriberYkAppAction->text();
	if (text.contains(QStringLiteral("ȡ��")))
	{
		subscriberYkAppAction->setText(QStringLiteral("����ң����Ӧ"));
		subscriberYkAppAction->setStatusTip(QStringLiteral("����ң����Ӧ"));

		emit subscriberYkAppSignal(true);
	}
	else
	{
		subscriberYkAppAction->setText(QStringLiteral("ȡ������ң����Ӧ"));
		subscriberYkAppAction->setStatusTip(QStringLiteral("ȡ������ң����Ӧ"));

		emit subscriberYkAppSignal(false);
	}
}

void WorkStationFrame::ykSelect()
{
	QString text = ykSelectAction->text();
	if (text.contains(QStringLiteral("ȡ��")))
	{
		ykSelectAction->setText(QStringLiteral("ң��ѡ��"));
		ykSelectAction->setStatusTip(QStringLiteral("ң��ѡ��"));

		emit ykSelectSignal(true);
	}
	else
	{
		ykSelectAction->setText(QStringLiteral("ȡ��ң��ѡ��"));
		ykSelectAction->setStatusTip(QStringLiteral("ȡ��ң��ѡ��"));

		emit ykSelectSignal(false);
	}
}

void WorkStationFrame::clearTextEdit()
{
	if (textEdit)
	{
		textEdit->clear();
	}
}

void WorkStationFrame::about()
{
	QMessageBox::information(this, QStringLiteral("����վģ���"), 
		QStringLiteral("�ṩģ�⹤��վ�������ݵĹ���"));
}