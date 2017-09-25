#include "fepframe.h"
#include "fepserver.h"
#include "fepserverthread.h"

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
	QThread* threadPtr = new QThread;
	m_fepServerPtr->setThreadPtr(m_fepServerThreadPtr);
	m_fepServerPtr->moveToThread(threadPtr);
	connect(threadPtr, SIGNAL(started()), m_fepServerPtr, SLOT(startServer()));
	connect(m_fepServerPtr, &FepServer::executeOperation, this, &FepFrame::updateListWidget);
	connect(m_fepServerThreadPtr, &FepServerThread::executeOperation, this, &FepFrame::updateListWidget);
	threadPtr->start();
}

void FepFrame::createWidgets()
{
	listWidget = new QListWidget;
	listWidget->setAlternatingRowColors(true);
	listWidget->setWordWrap(true);
	setCentralWidget(listWidget);

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

	helpMenu = menuBar()->addMenu(QStringLiteral("����"));
	helpMenu->addAction(helpAction);
}

void FepFrame::createToolBars()
{
	fileToolBar = addToolBar(QStringLiteral("�ļ�"));
	fileToolBar->addAction(exitAction);

	operToolBar = addToolBar(QStringLiteral("����"));
	operToolBar->addAction(processDataAction);
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

void FepFrame::updateListWidget( const QString& text )
{
	if (listWidget)
	{
		listWidget->addItem(text);
	}
}
