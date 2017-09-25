#include "amsframe.h"
#include "AmsServer.h"
#include "AmsServerThread.h"
#include "OperationInfo.h"
#include "TableHeader.h"

#include <QtWidgets/QtWidgets>

AmsFrame::AmsFrame(QWidget *parent)
	: QMainWindow(parent)
{
	createWidgets();

	createActions();

	createMenus();
	createToolbar();
	createStatusBar();
}

AmsFrame::~AmsFrame()
{

}

void AmsFrame::createWidgets()
{
	tableWidget = new QTableWidget();
	QStringList labels = TableHeader::getTableHeaderLabels();
	tableWidget->setColumnCount(labels.count());
	tableWidget->setHorizontalHeaderLabels(labels);
	tableWidget->setShowGrid(true);
	tableWidget->setWordWrap(true);
	tableWidget->setAlternatingRowColors(true);
	setCentralWidget(tableWidget);

	resize(800, 600);
	setWindowTitle(QStringLiteral("AMSģ���"));
	setWindowIcon(QIcon(":/images/ams.png"));
}

void AmsFrame::createActions()
{
	exitAction = new QAction(QIcon(":/images/exit.png"), QStringLiteral("�˳�"), this);
	exitAction->setShortcuts(QKeySequence::Quit);
	exitAction->setStatusTip(QStringLiteral("�˳�����"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	helpAction = new QAction(QIcon(":/images/about.png"), QStringLiteral("����"), this);
	helpAction->setStatusTip(QStringLiteral("���ڳ���Ľ���"));
	connect(helpAction, SIGNAL(triggered()), this, SLOT(about()));
}

void AmsFrame::createMenus()
{
	fileMenu = menuBar()->addMenu(QStringLiteral("�ļ�"));
	fileMenu->addAction(exitAction);
}

void AmsFrame::createToolbar()
{
	fileToolbar = addToolBar(QStringLiteral("�ļ�"));
	fileToolbar->addAction(exitAction);
}

void AmsFrame::createStatusBar()
{
	statusBar()->showMessage(QStringLiteral("׼������"));
}

void AmsFrame::about()
{
	QMessageBox::about(this, QStringLiteral("AMSģ���"), 
			QStringLiteral("ģ��AMS�������ݷ������Ĺ���"));
}

void AmsFrame::setParam( int argc, char* argv[] )
{
	m_argc = argc;
	m_argv = argv;
}

// ��ʼִ�з���
void AmsFrame::startServer()
{
	qRegisterMetaType<OperationInfo>("OperationInfo");

	AmsServerThread* thread = new AmsServerThread();
	thread->setParam(m_argc, m_argv);
	connect(thread, &AmsServerThread::executeOperation, this, &AmsFrame::updateTableWidget);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
}

void AmsFrame::updateTableWidget( const OperationInfo& info )
{
	if (tableWidget)
	{
		int count = tableWidget->rowCount();
		tableWidget->insertRow(count);
		for (int i = 0; i < Header_Count; ++i)
		{
			tableWidget->setItem(count, i, new QTableWidgetItem(info.getContent(i)));
		}
	}
}
