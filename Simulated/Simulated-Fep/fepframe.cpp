#include "fepframe.h"
#include "fepserver.h"
#include "fepserverthread.h"
#include "OperationInfo.h"
#include "TableHeader.h"

#include <QtWidgets/QtWidgets>
#include <QtCore/QThread>

FepFrame::FepFrame(int argc, char* argv[], QWidget *parent)
	: QMainWindow(parent)
{
	m_fepServerPtr = new FepServer(argc, argv);
	m_fepServerThreadPtr = new FepServerThread;

	createWidgets();

	createActions();
	createMenus();
	createToolBars();
	createStatusBar();
}

FepFrame::~FepFrame()
{

}

void FepFrame::startServer()
{
	qRegisterMetaType<OperationInfo>("OperationInfo");

	QThread* threadPtr = new QThread;
	m_fepServerPtr->setThreadPtr(m_fepServerThreadPtr);
	m_fepServerPtr->moveToThread(threadPtr);
	connect(threadPtr, SIGNAL(started()), m_fepServerPtr, SLOT(startServer()));
	connect(m_fepServerPtr, &FepServer::executeOperation, this, &FepFrame::updateTableWidget);
	connect(m_fepServerThreadPtr, &FepServerThread::executeOperation, this, &FepFrame::updateTableWidget);
	threadPtr->start();
}

void FepFrame::createWidgets()
{
	tableWidget = new QTableWidget;
	QStringList headLabels = TableHeader::getTableHeaderLabels();
	tableWidget->setColumnCount(headLabels.count());
	tableWidget->setHorizontalHeaderLabels(headLabels);
	tableWidget->setShowGrid(true);
	tableWidget->setAlternatingRowColors(true);
	setCentralWidget(tableWidget);

	resize(800, 600);
	setWindowTitle(QStringLiteral("ǰ�û�ģ���"));
	setWindowIcon(QIcon(":/images/fep.png"));
}

void FepFrame::createActions()
{
	exitAction = new QAction(QIcon(":/images/exit.png"), QStringLiteral("�˳�"), this);
	exitAction->setShortcut(QKeySequence::Quit);
	exitAction->setStatusTip(QStringLiteral("�˳�ģ�������"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	processDataAction = new QAction(QIcon(":/images/data.png"), QStringLiteral("��������"), this);
	processDataAction->setStatusTip(QStringLiteral("����ǰ�û�����"));
	connect(processDataAction, SIGNAL(triggered()), m_fepServerThreadPtr, SLOT(processData()));

	processFaultAction = new QAction(QIcon(":/images/fault.png"), QStringLiteral("������������"), this);
	processFaultAction->setStatusTip(QStringLiteral("����ǰ�û���������"));
	connect(processFaultAction, SIGNAL(triggered()), m_fepServerThreadPtr, SLOT(processFault()));

	processEventAction = new QAction(QIcon(":/images/data.png"), QStringLiteral("����ͨ������"), this);
	processEventAction->setStatusTip(QStringLiteral("����ǰ�û�ͨ������"));
	connect(processEventAction, SIGNAL(triggered()), m_fepServerThreadPtr, SLOT(processEvent()));

	processWaveAction = new QAction(QIcon(":/images/wave.png"), QStringLiteral("����¼������"), this);
	processWaveAction->setStatusTip(QStringLiteral("����ǰ�û�¼������"));
	connect(processWaveAction, SIGNAL(triggered()), m_fepServerThreadPtr, SLOT(processWave()));
	
	helpAction = new QAction(QIcon(":/images/about.png"), QStringLiteral("����"), this);
	helpAction->setStatusTip(QStringLiteral("����ģ�������"));
	connect(helpAction, SIGNAL(triggered()), this, SLOT(about()));
}

void FepFrame::createMenus()
{
	fileMenu = menuBar()->addMenu(QStringLiteral("�ļ�"));
	fileMenu->addAction(exitAction);

	operMenu = menuBar()->addMenu(QStringLiteral("����"));
	operMenu->addAction(processDataAction);
	operMenu->addAction(processFaultAction);
	operMenu->addAction(processEventAction);
	operMenu->addAction(processWaveAction);

	helpMenu = menuBar()->addMenu(QStringLiteral("����"));
	helpMenu->addAction(helpAction);
}

void FepFrame::createToolBars()
{
	fileToolBar = addToolBar(QStringLiteral("�ļ�"));
	fileToolBar->addAction(exitAction);

	operToolBar = addToolBar(QStringLiteral("����"));
	operToolBar->addAction(processDataAction);
	operToolBar->addAction(processFaultAction);
	operToolBar->addAction(processEventAction);
	operToolBar->addAction(processWaveAction);
}

void FepFrame::createStatusBar()
{
	statusBar()->showMessage(QStringLiteral("׼������"));
}

void FepFrame::about()
{
	QMessageBox::information(this, QStringLiteral("ǰ�û�ģ���"), 
			QStringLiteral("�ṩģ��ǰ�û��������ݵĹ���"));
}

void FepFrame::updateTableWidget( const OperationInfo& info )
{
	if (tableWidget)
	{
		int nCount = tableWidget->rowCount();
		tableWidget->insertRow(nCount);
		for (int i = 0; i < Header_Count; ++i)
		{
			tableWidget->setItem(nCount, i, new QTableWidgetItem(info.getContent(i)));
		}

		tableWidget->resizeColumnToContents(Header_OperTime);
	}
}
