#include "workstationframe.h"
#include "TableHeader.h"
#include "workstationserver.h"
#include "workstationserverthread.h"
#include "OperationInfo.h"
#include "RequestDataDialog.h"
#include "GlobalVariable.h"
#include "BatchRequestDialog.h"

#include <QtWidgets/QtWidgets>

#define MAX_TABLE_ROWS 999

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
	startServerAction = createActionImpl(QIcon(":/images/startServer.png"), QStringLiteral("��������"), 
		QStringLiteral("����Ice����"),	this, SLOT(startServer()));
	stopServerAction = createActionImpl(QIcon(":/images/stopServer.png"), QStringLiteral("ֹͣ����"), 
		QStringLiteral("ֹͣIce����"),	this, SLOT(stopServer()));
	exitAction = createActionImpl(QIcon(":/images/exit.png"), QStringLiteral("�˳�"), 
		QStringLiteral("�˳�ģ�������"),	this, SLOT(close()));
		
	requestStormRdbDataAction = createActionImpl(QIcon(":/images/requestStormRdb.png"), 
		QStringLiteral("����ʵʱ����(IceStorm)"), QStringLiteral("ͨ��IceStorm����ʵʱ����"),	
		this, SLOT(requestStormRdbData()), false);
	requestStormTopoDataAction = createActionImpl(QIcon(":/images/requestStormTopo.png"), 
		QStringLiteral("������������(IceStorm)"), QStringLiteral("ͨ��IceStorm������������"),	
		this, SLOT(requestStormTopoData()), false);
	batchRequestStormDataAction = createActionImpl(QIcon(":/images/requestStormRdb.png"), 
		QStringLiteral("��������ʵʱ����(IceStorm)"), QStringLiteral("ͨ��IceStorm��������ʵʱ����"),	
		this, SLOT(batchRequestStormData()), false);

	requestRdbDataAction = createActionImpl(QIcon(":/images/requestRdb.png"), 
		QStringLiteral("����ʵʱ����(Ice)"), QStringLiteral("ͨ��Ice����ʵʱ����"),	
		this, SLOT(requestRdbData()), false);
	requestTopoDataAction = createActionImpl(QIcon(":/images/requestTopo.png"), 
		QStringLiteral("������������(Ice)"), QStringLiteral("ͨ��Ice������������"),	
		this, SLOT(requestTopoData()), false);
	requestWarningMsgAction = createActionImpl(QIcon(":/images/requestTopo.png"), 
		QStringLiteral("����澯�ļ�(Ice)"), QStringLiteral("ͨ��Ice����澯�ļ�"),	
		this, SLOT(requestWarningMsg()), false);

	subscriberRdbRequestAction = createActionImpl(QIcon(":/images/subscribeRdbRequest.png"), 
		QStringLiteral("����ʵʱ��������"), "",	this, SLOT(subscriberRdbRequest()), false);
	subscriberRdbRespondAction = createActionImpl(QIcon(":/images/subscribeRdbRespond.png"), 
		QStringLiteral("����ʵʱ������Ӧ"), "",	this, SLOT(subscriberRdbRespond()), false);
	subscriberAlarmDataAction = createActionImpl(QIcon(":/images/subscribeAlarmData.png"), 
		QStringLiteral("���ı�������"), "",	this, SLOT(subscriberAlarmData()), false);
	subscriberFepDataAction = createActionImpl(QIcon(":/images/subscribeFepData.png"), 
		QStringLiteral("����ǰ�û�����"), "",	this, SLOT(subscriberFepData()), false);
	subscriberYkFepAction = createActionImpl(QIcon(":/images/subscribeFepData.png"), 
		QStringLiteral("����ң������"), "",	this, SLOT(subscriberYkFep()), false);
	subscriberYkAppAction = createActionImpl(QIcon(":/images/subscribeFepData.png"), 
		QStringLiteral("����ң����Ӧ"), "",	this, SLOT(subscriberYkApp()), false);
	subscriberWarningMsgAction = createActionImpl(QIcon(":/images/subscribeFepData.png"), 
		QStringLiteral("���ĸ澯�ļ�"), "",	this, SLOT(subscribeWarningMsg()), false);
	ykSelectAction = createActionImpl(QIcon(":/images/subscribeFepData.png"), QStringLiteral("ң��ѡ��"), 
		"",	this, SLOT(ykSelect()), false);

	transferCurveFileAction = createActionImpl(QIcon(":/images/icemenu.png"), QStringLiteral("������ʷ�����ļ�"), 
		"",	this, SLOT(transferCurveFile()), false);
	transferWarningFileAction = createActionImpl(QIcon(":/images/icemenu.png"), QStringLiteral("����澯�ļ�"), 
		"",	this, SLOT(transferWarningFile()), false);

	getSubscribersAction = createActionImpl(QIcon(":/images/icemenu.png"), QStringLiteral("��ȡ������"), 
		"",	this, SLOT(getSubscribers()), false);
	getPublishersAction = createActionImpl(QIcon(":/images/icemenu.png"), QStringLiteral("��ȡ������"), 
		"",	this, SLOT(getPublishers()), false);

	clearAction = createActionImpl(QIcon(":/images/clear.png"), QStringLiteral("����ı�"), 
		"",	this, SLOT(clearTextEdit()));
	helpAction = createActionImpl(QIcon(":/images/about.png"), QStringLiteral("����"), 
		QStringLiteral("����ģ�������"),	this, SLOT(about()));
}

QAction* WorkStationFrame::createActionImpl(const QIcon &icon, const QString &text, const QString& statusTip, 
	const QObject* receiver, const char* member, bool enabled)
{
	QAction* action = new QAction(icon, text, this);
	action->setEnabled(enabled);
	action->setStatusTip(statusTip.isEmpty() ? text : statusTip);
	connect(action, SIGNAL(triggered()), receiver, member);
	return action;
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
	iceStormMenu->addAction(batchRequestStormDataAction);

	QMenu* iceMenu = operMenu->addMenu(QIcon(":/images/icemenu.png"), QStringLiteral("Ice"));
	iceMenu->addAction(requestRdbDataAction);
	iceMenu->addAction(requestTopoDataAction);
	iceMenu->addAction(requestWarningMsgAction);
	QMenu* subscriberMenu = operMenu->addMenu(QIcon(":/images/icemenu.png"), QStringLiteral("IceStorm Subscriber"));
	subscriberMenu->addAction(subscriberRdbRequestAction);
	subscriberMenu->addAction(subscriberRdbRespondAction);
	subscriberMenu->addAction(subscriberAlarmDataAction);
	subscriberMenu->addAction(subscriberFepDataAction);
	subscriberMenu->addAction(subscriberYkFepAction);
	subscriberMenu->addAction(subscriberYkAppAction);
	subscriberMenu->addAction(subscriberWarningMsgAction);
	subscriberMenu->addSeparator();
	subscriberMenu->addAction(ykSelectAction);
	operMenu->addSeparator();
	operMenu->addAction(getSubscribersAction);
	operMenu->addAction(getPublishersAction);
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
	operToolBar->addAction(batchRequestStormDataAction);

	operToolBar->addSeparator();
	operToolBar->addAction(requestRdbDataAction);
	operToolBar->addAction(requestTopoDataAction);
	operToolBar->addAction(requestWarningMsgAction);
	operToolBar->addSeparator();
	operToolBar->addAction(subscriberRdbRequestAction);
	operToolBar->addAction(subscriberRdbRespondAction);
	operToolBar->addAction(subscriberAlarmDataAction);
	operToolBar->addAction(subscriberFepDataAction);
	operToolBar->addAction(subscriberYkFepAction);
	operToolBar->addAction(subscriberYkAppAction);
	operToolBar->addAction(subscriberWarningMsgAction);
	operToolBar->addSeparator();
	operToolBar->addAction(ykSelectAction);
	operToolBar->addSeparator();
	operToolBar->addAction(transferCurveFileAction);
	operToolBar->addAction(transferWarningFileAction);
	operToolBar->addSeparator();
	operToolBar->addAction(getSubscribersAction);
	operToolBar->addAction(getPublishersAction);
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
	connect(this, SIGNAL(requestCompleteDataSingal()), m_workStationServerThreadPtr, SLOT(requestCompleteData()));
	connect(this, SIGNAL(requestStormTopoDataSingal()), m_workStationServerThreadPtr, SLOT(requestStormTopoData()));
	connect(this, SIGNAL(batchRequestStormDataSingal()), m_workStationServerThreadPtr, SLOT(batchRequestStormData()));

	connect(this, SIGNAL(selectCompleteDataSingal()), m_workStationServerThreadPtr, SLOT(selectCompleteData()));
	connect(this, SIGNAL(requestWarningMsgSingal()), m_workStationServerThreadPtr, SLOT(requestWarningMsg()));
	connect(this, SIGNAL(subscriberRdbRequestSignal(bool)), m_workStationServerThreadPtr, SLOT(subscriberRdbRequest(bool)));
	connect(this, SIGNAL(subscriberRdbRespondSignal(bool)), m_workStationServerThreadPtr, SLOT(subscriberRdbRespond(bool)));
	connect(this, SIGNAL(subscriberAlarmDataSignal(bool)), m_workStationServerThreadPtr, SLOT(subscriberAlarmData(bool)));
	connect(this, SIGNAL(subscriberFepDataSignal(bool)), m_workStationServerThreadPtr, SLOT(subscriberFepData(bool)));
	connect(this, SIGNAL(subscriberYkFepSignal(bool)), m_workStationServerThreadPtr, SLOT(subscriberYkFep(bool)));
	connect(this, SIGNAL(subscriberYkAppSignal(bool)), m_workStationServerThreadPtr, SLOT(subscriberYkApp(bool)));
	connect(this, SIGNAL(subscriberWarningMsgSignal(bool)), m_workStationServerThreadPtr, SLOT(subscriberWarningMsg(bool)));
	connect(this, SIGNAL(ykSelectSignal(bool)), m_workStationServerThreadPtr, SLOT(ykSelect(bool)));
	connect(this, SIGNAL(transferCurveFileSignal(QString, QString)), m_workStationServerThreadPtr, SLOT(transferCurveFile(QString, QString)));
	connect(this, SIGNAL(transferWarningFileSignal(QString)), m_workStationServerThreadPtr, SLOT(transferWarningFile(QString)));
	connect(this, SIGNAL(getSubscribersSignal(QString)), m_workStationServerThreadPtr, SLOT(getSubscribers(QString)));
	connect(this, SIGNAL(getPublishersSignal(QString)), m_workStationServerThreadPtr, SLOT(getPublishers(QString)));
	connect(m_workStationServerThreadPtr, &WorkStationServerThread::executeOperation, 
		this, &WorkStationFrame::updateTableWidget);
	connect(m_workStationServerThreadPtr, &WorkStationServerThread::outputReceiveData, 
		this, &WorkStationFrame::updateTextEdit);
}

void WorkStationFrame::updateActionText(QAction* action, bool& isStop)
{
	QString text = action->text();
	QString str = QStringLiteral("ȡ��");
	if (text.contains(str))
	{
		QString newText = text.right(text.length() - text.indexOf(str) - 2);
		action->setText(newText);
		action->setStatusTip(newText);

		isStop = true;
	}
	else
	{
		QString newText = str + text;
		action->setText(newText);
		action->setStatusTip(newText);

		isStop = false;
	}
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
		if (tableWidget->rowCount() > MAX_TABLE_ROWS)
		{
			tableWidget->removeRow(0);
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
	batchRequestStormDataAction->setEnabled(serverStarted);
	requestRdbDataAction->setEnabled(serverStarted);
	requestTopoDataAction->setEnabled(serverStarted);
	requestWarningMsgAction->setEnabled(serverStarted);
	subscriberRdbRequestAction->setEnabled(serverStarted);
	subscriberRdbRespondAction->setEnabled(serverStarted);
	subscriberAlarmDataAction->setEnabled(serverStarted);
	subscriberFepDataAction->setEnabled(serverStarted);
	subscriberYkFepAction->setEnabled(serverStarted);
	subscriberYkAppAction->setEnabled(serverStarted);
	subscriberWarningMsgAction->setEnabled(serverStarted);
	ykSelectAction->setEnabled(serverStarted);
	transferCurveFileAction->setEnabled(serverStarted);
	transferWarningFileAction->setEnabled(serverStarted);
	getSubscribersAction->setEnabled(serverStarted);
	getPublishersAction->setEnabled(serverStarted);
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
	QString topic = getInputText(CGlobalVariable::instance().getRdbRequestTopic());
	if (!topic.isEmpty())
	{
		CGlobalVariable::instance().setRdbRequestTopic(topic);
	}

	CRequestDataDialog dialog(CompleteData, this);
	if (dialog.exec() == QDialog::Accepted)
	{
	}
	emit requestCompleteDataSingal();
}

void WorkStationFrame::requestStormTopoData()
{
	QString topic = getInputText(CGlobalVariable::instance().getRdbRequestTopic());
	if (!topic.isEmpty())
	{
		CGlobalVariable::instance().setRdbRequestTopic(topic);
	}

	emit requestStormTopoDataSingal();
}

void WorkStationFrame::batchRequestStormData()
{
	CRequestManager::stopBatchCompleteDataSeq();

	BatchRequestDialog dialog(this);
	if (dialog.exec() == QDialog::Accepted)
	{
		emit batchRequestStormDataSingal();
	}
}

void WorkStationFrame::requestRdbData()
{
	emit selectCompleteDataSingal();
}

void WorkStationFrame::requestTopoData()
{

}

void WorkStationFrame::requestWarningMsg()
{
	emit requestWarningMsgSingal();
}

void WorkStationFrame::subscriberRdbRequest()
{
	bool isStop = false;
	updateActionText(subscriberRdbRequestAction, isStop);
	emit subscriberRdbRequestSignal(isStop);
}


void WorkStationFrame::subscriberRdbRespond()
{
	bool isStop = false;
	updateActionText(subscriberRdbRespondAction, isStop);
	if (!isStop)
	{
		QString text =getInputText(CGlobalVariable::instance().getRdbRespondTopic());
		if (!text.isEmpty())
		{
			CGlobalVariable::instance().setRdbRespondTopic(text);
		}
	}
	emit subscriberRdbRespondSignal(isStop);
}

void WorkStationFrame::subscriberAlarmData()
{
	bool isStop = false;
	updateActionText(subscriberAlarmDataAction, isStop);
	emit subscriberAlarmDataSignal(isStop);
}

void WorkStationFrame::subscriberFepData()
{
	bool isStop = false;
	updateActionText(subscriberFepDataAction, isStop);
	emit subscriberFepDataSignal(isStop);
}


void WorkStationFrame::subscriberYkFep()
{
	bool isStop = false;
	updateActionText(subscriberYkFepAction, isStop);
	emit subscriberYkFepSignal(isStop);
}

void WorkStationFrame::subscriberYkApp()
{
	bool isStop = false;
	updateActionText(subscriberYkAppAction, isStop);
	emit subscriberYkAppSignal(isStop);
}

void WorkStationFrame::subscribeWarningMsg()
{
	bool isStop = false;
	updateActionText(subscriberWarningMsgAction, isStop);
	emit subscriberWarningMsgSignal(isStop);
}

void WorkStationFrame::ykSelect()
{
	bool isStop = false;
	updateActionText(ykSelectAction, isStop);
	emit ykSelectSignal(isStop);
}

void WorkStationFrame::transferCurveFile()
{
	QString text = QInputDialog::getText(this, QStringLiteral("������ʷ�����ļ�"), QStringLiteral("��,�ָ�·�����ļ���): "));
	if (text.isEmpty())
	{
		return;
	}
	QStringList strValues = text.split(",");
	emit transferCurveFileSignal(strValues[0], strValues[1]);
}

void WorkStationFrame::transferWarningFile()
{
	QString text = QInputDialog::getText(this, QStringLiteral("����澯�ļ�"), QStringLiteral("�ļ���: "));
	if (text.isEmpty())
	{
		return;
	}
	emit transferWarningFileSignal(text);
}

void WorkStationFrame::getSubscribers()
{
	QString text = QInputDialog::getText(this, QStringLiteral("��ȡ������"), QStringLiteral("��������: "));
	if (text.isEmpty())
	{
		return;
	}
	emit getSubscribersSignal(text);
}

void WorkStationFrame::getPublishers()
{
	QString text = QInputDialog::getText(this, QStringLiteral("��ȡ������"), QStringLiteral("��������: "));
	if (text.isEmpty())
	{
		return;
	}
	emit getPublishersSignal(text);
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

QString WorkStationFrame::getInputText(const QString& defaultText)
{
	bool ok = false;
	QString text = QInputDialog::getText(this, QStringLiteral("��������"), QStringLiteral("������:"), QLineEdit::Normal, 
		defaultText, &ok);
	return ok ? text : "";
}
