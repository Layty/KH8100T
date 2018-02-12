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

void AmsFrame::setParam( int argc, char* argv[] )
{
	m_argc = argc;
	m_argv = argv;
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
	setWindowTitle(QStringLiteral("AMSģ���(��������ɫ)"));
	setWindowIcon(QIcon(":/images/ams.png"));
}

void AmsFrame::createActions()
{
	exitAction = new QAction(QIcon(":/images/exit.png"), QStringLiteral("�˳�"), this);
	exitAction->setShortcuts(QKeySequence::Quit);
	exitAction->setStatusTip(QStringLiteral("�˳�����"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	setMasterAction = new QAction(QIcon(":/images/master.png"), QStringLiteral("��������ɫ"), this);
	setMasterAction->setStatusTip(QStringLiteral("��������ɫ"));
	setMasterAction->setEnabled(false);
	connect(setMasterAction, SIGNAL(triggered()), this, SLOT(setMasterRole()));

	setSlaveAction = new QAction(QIcon(":/images/slave.png"), QStringLiteral("���ر���ɫ"), this);
	setSlaveAction->setStatusTip(QStringLiteral("���ر���ɫ"));
	connect(setSlaveAction, SIGNAL(triggered()), this, SLOT(setSlaveRole()));

	changeRoleAction = new QAction(QIcon(":/images/slave.png"), QStringLiteral("�л���ɫ"), this);
	changeRoleAction->setStatusTip(QStringLiteral("�л����ݷ�������ɫ"));
	connect(changeRoleAction, SIGNAL(triggered()), this, SLOT(changeRole()));

	configAction = new QAction(QIcon(":/images/config.png"), QStringLiteral("���������˿�"), this);
	configAction->setStatusTip(QStringLiteral("���������˿�"));
	connect(configAction, SIGNAL(triggered()), this, SLOT(configHostPort()));

	helpAction = new QAction(QIcon(":/images/about.png"), QStringLiteral("����"), this);
	helpAction->setStatusTip(QStringLiteral("���ڳ���Ľ���"));
	connect(helpAction, SIGNAL(triggered()), this, SLOT(about()));
}

void AmsFrame::createMenus()
{
	fileMenu = menuBar()->addMenu(QStringLiteral("�ļ�"));
	fileMenu->addAction(exitAction);

	operMenu = menuBar()->addMenu(QStringLiteral("����"));
	operMenu->addAction(setMasterAction);
	operMenu->addAction(setSlaveAction);
	operMenu->addAction(changeRoleAction);
	operMenu->addAction(configAction);
}

void AmsFrame::createToolbar()
{
	fileToolbar = addToolBar(QStringLiteral("�ļ�"));
	fileToolbar->addAction(exitAction);

	operToolbar = addToolBar(QStringLiteral("����"));
	operToolbar->addAction(setMasterAction);
	operToolbar->addAction(setSlaveAction);
	operToolbar->addAction(changeRoleAction);
	operToolbar->addAction(configAction);
}

void AmsFrame::createStatusBar()
{
	statusBar()->showMessage(QStringLiteral("׼������"));
}

void AmsFrame::hasSetRole(bool isMaster)
{
	setMasterAction->setEnabled(!isMaster);
	setSlaveAction->setEnabled(isMaster);
	if (isMaster)
	{
		setWindowTitle(QStringLiteral("AMSģ���(��������ɫ)"));
	}
	else
	{
		setWindowTitle(QStringLiteral("AMSģ���(���ر���ɫ)"));
	}
}

// ��ʼִ�з���
void AmsFrame::startServer()
{
	qRegisterMetaType<OperationInfo>("OperationInfo");

	AmsServerThread* thread = new AmsServerThread();
	thread->setParam(m_argc, m_argv);
	connect(thread, &AmsServerThread::executeOperation, this, &AmsFrame::updateTableWidget);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	connect(this, SIGNAL(setRole(QString)), thread, SLOT(setRole(QString)));
	connect(this, SIGNAL(changeRole(QString)), thread, SLOT(changeRole(QString)));
	connect(this, SIGNAL(configHostPort(QString, int)), thread, SLOT(configHostPort(QString, int)));
	thread->start();
}

void AmsFrame::about()
{
	QMessageBox::about(this, QStringLiteral("AMSģ���"), 
		QStringLiteral("ģ��AMS�������ݷ������Ĺ���"));
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
		tableWidget->resizeColumnToContents(Header_OperTime);
	}
}

void AmsFrame::setMasterRole()
{
	hasSetRole(true);
	emit setRole(ROLE_MASTER);
}

void AmsFrame::setSlaveRole()
{
	hasSetRole(false);
	emit setRole(ROLE_SLAVE);
}

void AmsFrame::changeRole()
{
	QString role = QInputDialog::getText(this, "�л����ݷ�������ɫ", "��ɫ:", QLineEdit::Normal, "slave");
	if (!role.isEmpty())
	{
		emit changeRole(role);
	}
}

void AmsFrame::configHostPort()
{
	QInputDialog inputDlg;
	QString title = QStringLiteral("��������");
	QString label = QStringLiteral("����Ip: ");
	QString host = QInputDialog::getText(this, title, label, QLineEdit::Normal, "192.168.3.25");
	if (!host.isEmpty())
	{
		label = QStringLiteral("�����˿�: ");
		int port = QInputDialog::getInt(this, title, label, 10003);

		emit configHostPort(host, port);
	}
}
