#include "fepframe.h"
#include "fepserver.h"
#include "fepserverthread.h"
#include "faultEventDlg.h"
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

	processYcDataAction = new QAction(QIcon(":/images/ycdata.png"), QStringLiteral("����ң������"), this);
	processYcDataAction->setStatusTip(QStringLiteral("ǰ�û�����ң������"));
	connect(processYcDataAction, SIGNAL(triggered()), m_fepServerThreadPtr, SLOT(processYcData()));
	
	processYxDataAction = new QAction(QIcon(":/images/yxdata.png"), QStringLiteral("����ң������"), this);
	processYxDataAction->setStatusTip(QStringLiteral("ǰ�û�����ң������"));
	connect(processYxDataAction, SIGNAL(triggered()), m_fepServerThreadPtr, SLOT(processYxData()));

	processDdDataAction = new QAction(QIcon(":/images/dddata.png"), QStringLiteral("�����������"), this);
	processDdDataAction->setStatusTip(QStringLiteral("ǰ�û������������"));
	connect(processDdDataAction, SIGNAL(triggered()), m_fepServerThreadPtr, SLOT(processDdData()));

	processUnitStateDataAction = new QAction(QIcon(":/images/unitstatedata.png"), QStringLiteral("�����ն�״̬"), this);
	processUnitStateDataAction->setStatusTip(QStringLiteral("ǰ�û������ն�״̬"));
	connect(processUnitStateDataAction, SIGNAL(triggered()), this, SLOT(processUnitStateData()));

	processDLFaultAction = new QAction(QIcon(":/images/dlfault.png"), QStringLiteral("������·��������"), this);
	processDLFaultAction->setStatusTip(QStringLiteral("ǰ�û�������·��������"));
	connect(processDLFaultAction, SIGNAL(triggered()), m_fepServerThreadPtr, SLOT(processDLFault()));

	processJDFaultAction = new QAction(QIcon(":/images/jdfault.png"), QStringLiteral("�����ӵع�������"), this);
	processJDFaultAction->setStatusTip(QStringLiteral("ǰ�û������ӵع�������"));
	connect(processJDFaultAction, SIGNAL(triggered()), m_fepServerThreadPtr, SLOT(processJDFault()));

	processYxTypeEventAction = new QAction(QIcon(":/images/yxtype.png"), QStringLiteral("����ң�ű�λ����"), this);
	processYxTypeEventAction->setStatusTip(QStringLiteral("����ǰ�û�ң�ű�λ����"));
	connect(processYxTypeEventAction, SIGNAL(triggered()), this, SLOT(processYxTypeEvent()));

	processSoeTypeEventAction = new QAction(QIcon(":/images/soetype.png"), QStringLiteral("����SOE����"), this);
	processSoeTypeEventAction->setStatusTip(QStringLiteral("����ǰ�û�SOE����"));
	connect(processSoeTypeEventAction, SIGNAL(triggered()), this, SLOT(processSoeTypeEvent()));

	processUnitTypeEventAction = new QAction(QIcon(":/images/unittype.png"), QStringLiteral("������Ԫ����"), this);
	processUnitTypeEventAction->setStatusTip(QStringLiteral("����ǰ�û���Ԫ����"));
	connect(processUnitTypeEventAction, SIGNAL(triggered()), m_fepServerThreadPtr, SLOT(processUnitTypeEvent()));

	processUnitChannelEventAction = new QAction(QIcon(":/images/unittype.png"), QStringLiteral("����ͨ������"), this);
	processUnitChannelEventAction->setStatusTip(QStringLiteral("����ǰ�û�ͨ������"));
	connect(processUnitChannelEventAction, SIGNAL(triggered()), m_fepServerThreadPtr, SLOT(processUnitChannelEvent()));

	processProTypeEventAction = new QAction(QIcon(":/images/protype.png"), QStringLiteral("������������"), this);
	processProTypeEventAction->setStatusTip(QStringLiteral("����ǰ�û���������"));
	//connect(processProTypeEventAction, SIGNAL(triggered()), m_fepServerThreadPtr, SLOT(processProTypeEvent()));
	//connect(processProTypeEventAction, SIGNAL(triggered()), this, SLOT(configFaultEvent()));
	connect(processProTypeEventAction, SIGNAL(triggered()), this, SLOT(processProTypeEvent()));
	
	processWaveAction = new QAction(QIcon(":/images/wave.png"), QStringLiteral("����¼������"), this);
	processWaveAction->setStatusTip(QStringLiteral("����ǰ�û�¼������"));
	connect(processWaveAction, SIGNAL(triggered()), m_fepServerThreadPtr, SLOT(processWave()));

	clearAction = new QAction(QIcon(":/images/clear.png"), QStringLiteral("����ı�"), this);
	clearAction->setStatusTip(QStringLiteral("����ı��ؼ�"));
	connect(clearAction, SIGNAL(triggered()), this, SLOT(clearTextEdit()));
	
	helpAction = new QAction(QIcon(":/images/about.png"), QStringLiteral("����"), this);
	helpAction->setStatusTip(QStringLiteral("����ģ�������"));
	connect(helpAction, SIGNAL(triggered()), this, SLOT(about()));
}

void FepFrame::createMenus()
{
	fileMenu = menuBar()->addMenu(QStringLiteral("�ļ�"));
	fileMenu->addAction(exitAction);

	operMenu = menuBar()->addMenu(QStringLiteral("����"));
	operMenu->addAction(processYcDataAction);
	operMenu->addAction(processYxDataAction);
	operMenu->addAction(processDdDataAction);
	operMenu->addAction(processUnitStateDataAction);
	operMenu->addSeparator();
	operMenu->addAction(processDLFaultAction);
	operMenu->addAction(processJDFaultAction);
	operMenu->addSeparator();
	operMenu->addAction(processYxTypeEventAction);
	operMenu->addAction(processSoeTypeEventAction);
	operMenu->addAction(processUnitTypeEventAction);
	operMenu->addAction(processUnitChannelEventAction);
	operMenu->addAction(processProTypeEventAction);
	operMenu->addSeparator();
	operMenu->addAction(processWaveAction);
	operMenu->addSeparator();
	operMenu->addAction(clearAction);

	helpMenu = menuBar()->addMenu(QStringLiteral("����"));
	helpMenu->addAction(helpAction);
}

void FepFrame::createToolBars()
{
	fileToolBar = addToolBar(QStringLiteral("�ļ�"));
	fileToolBar->addAction(exitAction);

	operToolBar = addToolBar(QStringLiteral("����"));
	operToolBar->addAction(processYcDataAction);
	operToolBar->addAction(processYxDataAction);
	operToolBar->addAction(processDdDataAction);
	operToolBar->addAction(processUnitStateDataAction);
	operToolBar->addSeparator();
	operToolBar->addAction(processDLFaultAction);
	operToolBar->addAction(processJDFaultAction);
	operToolBar->addSeparator();
	operToolBar->addAction(processYxTypeEventAction);
	operToolBar->addAction(processSoeTypeEventAction);
	operToolBar->addAction(processUnitTypeEventAction);
	operToolBar->addAction(processUnitChannelEventAction);
	operToolBar->addAction(processProTypeEventAction);
	operToolBar->addSeparator();
	operToolBar->addAction(processWaveAction);
	operToolBar->addSeparator();
	operToolBar->addAction(clearAction);
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
	textEdit->moveCursor(QTextCursor::End);
	textEdit->insertPlainText(text);
	textEdit->insertPlainText("\n");
	textEdit->moveCursor(QTextCursor::End);
}

void FepFrame::clearTextEdit()
{
	if (textEdit)
	{
		textEdit->clear();
	}
}

void FepFrame::processUnitStateData()
{
	QString text = processUnitStateDataAction->text();
	if (text.contains(QStringLiteral("ȡ��")))
	{
		processUnitStateDataAction->setText(QStringLiteral("�����ն�״̬"));
		processUnitStateDataAction->setStatusTip(QStringLiteral("�����ն�״̬"));

		m_fepServerThreadPtr->processUnitStateData(false);
	}
	else
	{
		processUnitStateDataAction->setText(QStringLiteral("ȡ�������ն�״̬"));
		processUnitStateDataAction->setStatusTip(QStringLiteral("ȡ�������ն�״̬"));

		m_fepServerThreadPtr->processUnitStateData(true);
	}
}

void FepFrame::processYxTypeEvent()
{
	QString text = processYxTypeEventAction->text();
	if (text.contains(QStringLiteral("ȡ��")))
	{
		processYxTypeEventAction->setText(QStringLiteral("����ң�ű�λ����"));
		processYxTypeEventAction->setStatusTip(QStringLiteral("����ң�ű�λ����"));

		m_fepServerThreadPtr->processYxTypeEvent(false);
	}
	else
	{
		processYxTypeEventAction->setText(QStringLiteral("ȡ������ң�ű�λ����"));
		processYxTypeEventAction->setStatusTip(QStringLiteral("ȡ������ң�ű�λ����"));

		m_fepServerThreadPtr->processYxTypeEvent(true);
	}
}

void FepFrame::processSoeTypeEvent()
{
	QString text = processSoeTypeEventAction->text();
	if (text.contains(QStringLiteral("ȡ��")))
	{
		processSoeTypeEventAction->setText(QStringLiteral("����SOE����"));
		processSoeTypeEventAction->setStatusTip(QStringLiteral("����SOE����"));

		m_fepServerThreadPtr->processSoeTypeEvent(false);
	}
	else
	{
		processSoeTypeEventAction->setText(QStringLiteral("ȡ������SOE����"));
		processSoeTypeEventAction->setStatusTip(QStringLiteral("ȡ������SOE����"));

		m_fepServerThreadPtr->processSoeTypeEvent(true);
	}
}

void FepFrame::processProTypeEvent()
{
	QString text = processProTypeEventAction->text();
	if (text.contains(QStringLiteral("ȡ��")))
	{
		processProTypeEventAction->setText(QStringLiteral("������������"));
		processProTypeEventAction->setStatusTip(QStringLiteral("������������"));

		m_fepServerThreadPtr->processProTypeEvent(false);
	}
	else
	{
		processProTypeEventAction->setText(QStringLiteral("ȡ��������������"));
		processProTypeEventAction->setStatusTip(QStringLiteral("ȡ��������������"));

		m_fepServerThreadPtr->processProTypeEvent(true);
	}
}

void FepFrame::configFaultEvent()
{
	CFaultEventDlg dlg(m_fepServerThreadPtr, this);
	dlg.exec();
}
