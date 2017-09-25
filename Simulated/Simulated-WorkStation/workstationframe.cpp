#include "workstationframe.h"
#include "TableHeader.h"
#include "workstationserver.h"
#include "workstationserverthread.h"

#include <QtWidgets/QtWidgets>

WorkStationFrame::WorkStationFrame(int argc, char* argv[], QWidget *parent)
	: QMainWindow(parent), m_argc(argc), m_argv(argv)
{
	createWidgets();

	createActions();
	createMenus();
	createToolBars();
	createStatusBar();
	createConnects();

	m_workStationServerPtr = new WorkStationServer(m_argc, m_argv);
	m_workStationServerThreadPtr = new WorkStationServerThread;
}

WorkStationFrame::~WorkStationFrame()
{

}

void WorkStationFrame::createWidgets()
{
	QWidget* widget = new QWidget;
	tableWidget = new QTableWidget;
	QStringList tableHeaders = TableHeader::getTableHeaderLabels();
	tableWidget->setColumnCount(tableHeaders.count());
	tableWidget->setShowGrid(true);
	tableWidget->setHorizontalHeaderLabels(tableHeaders);

	textEdit = new QTextEdit;
	textEdit->setTextBackgroundColor(QColor(255, 0, 0));

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(tableWidget, 1);
	layout->addStretch();
	layout->addWidget(textEdit, 2);

	widget->setLayout(layout);
	setCentralWidget(widget);

	OperationInfo info(TYPE_CLIENT, "������Ϣ����");
	updateTableWidget(info);

	resize(800, 600);
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
	
	requestStormRdbDataAction = new QAction(QIcon(":/images/requestStormRdb.png"), QStringLiteral("����ʵʱ����"), this);
	requestStormRdbDataAction->setStatusTip(QStringLiteral("ͨ��IceStorm����ʵʱ����"));
	requestStormRdbDataAction->setEnabled(false);
	connect(requestStormRdbDataAction, SIGNAL(triggered()), this, SLOT(requestStormRdbData()));
	
	requestStormTopoDataAction = new QAction(QIcon(":/images/requestStormTopo.png"), QStringLiteral("������������"), this);
	requestStormTopoDataAction->setStatusTip(QStringLiteral("ͨ��IceStorm������������"));
	requestStormTopoDataAction->setEnabled(false);
	connect(requestStormTopoDataAction, SIGNAL(triggered()), this, SLOT(requestStormTopoData()));

	requestRdbDataAction = new QAction(QIcon(":/images/requestRdb.png"), QStringLiteral("����ʵʱ����"), this);
	requestRdbDataAction->setStatusTip(QStringLiteral("ͨ��Ice����ʵʱ����"));
	requestRdbDataAction->setEnabled(false);
	connect(requestRdbDataAction, SIGNAL(triggered()), this, SLOT(requestRdbData()));

	requestTopoDataAction = new QAction(QIcon(":/images/requestTopo.png"), QStringLiteral("������������"), this);
	requestTopoDataAction->setStatusTip(QStringLiteral("ͨ��Ice������������"));
	requestTopoDataAction->setEnabled(false);
	connect(requestTopoDataAction, SIGNAL(triggered()), this, SLOT(requestTopoData()));

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
}

void WorkStationFrame::createStatusBar()
{
	statusBar()->showMessage(QStringLiteral("׼������"));
}

void WorkStationFrame::createConnects()
{
	connect(this, SIGNAL(serverStarted(bool)), this, SLOT(updateActions(bool)));
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

void WorkStationFrame::updateActions( bool serverStarted )
{
	startServerAction->setEnabled(!serverStarted);
	stopServerAction->setEnabled(serverStarted);
	requestStormRdbDataAction->setEnabled(serverStarted);
	requestStormTopoDataAction->setEnabled(serverStarted);
	requestRdbDataAction->setEnabled(serverStarted);
	requestTopoDataAction->setEnabled(serverStarted);
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

}

void WorkStationFrame::requestStormTopoData()
{

}

void WorkStationFrame::requestRdbData()
{

}

void WorkStationFrame::requestTopoData()
{

}

void WorkStationFrame::about()
{
	QMessageBox::information(this, QStringLiteral("����վģ���"), 
		QStringLiteral("�ṩģ�⹤��վ�������ݵĹ���"));
}
