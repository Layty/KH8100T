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
	connect(m_fepServerThreadPtr, &FepServerThread::publishFepData, this, &FepFrame::updateTextEdit);
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

	textEdit = new QTextEdit;
	textEdit->setReadOnly(false);

	QSplitter* splitter = new QSplitter(Qt::Vertical);
	splitter->addWidget(tableWidget);
	splitter->addWidget(textEdit);
	splitter->setStretchFactor(0, 1);
	splitter->setStretchFactor(1, 3);

	setCentralWidget(splitter);

	resize(1200, 800);
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
	processDataAction->setStatusTip(QStringLiteral("ǰ�û���������"));
	connect(processDataAction, SIGNAL(triggered()), m_fepServerThreadPtr, SLOT(processData()));

	processDLFaultAction = new QAction(QIcon(":/images/dlfault.png"), QStringLiteral("������·��������"), this);
	processDLFaultAction->setStatusTip(QStringLiteral("ǰ�û�������·��������"));
	connect(processDLFaultAction, SIGNAL(triggered()), m_fepServerThreadPtr, SLOT(processDLFault()));

	processJDFaultAction = new QAction(QIcon(":/images/jdfault.png"), QStringLiteral("�����ӵع�������"), this);
	processJDFaultAction->setStatusTip(QStringLiteral("ǰ�û������ӵع�������"));
	connect(processJDFaultAction, SIGNAL(triggered()), m_fepServerThreadPtr, SLOT(processJDFault()));

	processYxTypeEventAction = new QAction(QIcon(":/images/yxtype.png"), QStringLiteral("����ң�ű�λ����"), this);
	processYxTypeEventAction->setStatusTip(QStringLiteral("����ǰ�û�ң�ű�λ����"));
	connect(processYxTypeEventAction, SIGNAL(triggered()), m_fepServerThreadPtr, SLOT(processYxTypeEvent()));

	processSoeTypeEventAction = new QAction(QIcon(":/images/soetype.png"), QStringLiteral("����SOE����"), this);
	processSoeTypeEventAction->setStatusTip(QStringLiteral("����ǰ�û�SOE����"));
	connect(processSoeTypeEventAction, SIGNAL(triggered()), m_fepServerThreadPtr, SLOT(processSoeTypeEvent()));

	processUnitTypeEventAction = new QAction(QIcon(":/images/unittype.png"), QStringLiteral("������Ԫ����"), this);
	processUnitTypeEventAction->setStatusTip(QStringLiteral("����ǰ�û���Ԫ����"));
	connect(processUnitTypeEventAction, SIGNAL(triggered()), m_fepServerThreadPtr, SLOT(processUnitTypeEvent()));

	processProTypeEventAction = new QAction(QIcon(":/images/protype.png"), QStringLiteral("������������"), this);
	processProTypeEventAction->setStatusTip(QStringLiteral("����ǰ�û���������"));
	connect(processProTypeEventAction, SIGNAL(triggered()), m_fepServerThreadPtr, SLOT(processProTypeEvent()));
	
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
	operMenu->addSeparator();
	operMenu->addAction(processDLFaultAction);
	operMenu->addAction(processJDFaultAction);
	operMenu->addSeparator();
	operMenu->addAction(processYxTypeEventAction);
	operMenu->addAction(processSoeTypeEventAction);
	operMenu->addAction(processUnitTypeEventAction);
	operMenu->addAction(processProTypeEventAction);
	operMenu->addSeparator();
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
	operToolBar->addSeparator();
	operToolBar->addAction(processDLFaultAction);
	operToolBar->addAction(processJDFaultAction);
	operToolBar->addSeparator();
	operToolBar->addAction(processYxTypeEventAction);
	operToolBar->addAction(processSoeTypeEventAction);
	operToolBar->addAction(processUnitTypeEventAction);
	operToolBar->addAction(processProTypeEventAction);
	operToolBar->addSeparator();
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

void FepFrame::updateTextEdit( const QString& text )
{
	textEdit->insertPlainText(text);
	textEdit->insertPlainText("\n");
}
