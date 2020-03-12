#include "restoredb.h"
#include "FastdbManager.h"

#include <QtWidgets/QtWidgets>

RestoreDb::RestoreDb(QWidget *parent)
	: QMainWindow(parent)
{
	m_fastdbManager = FastdbManagerInstance::getFastdbManagerInstance();

	createWidgets();
	createActions();
	createConnects();
	createMenus();
	createToolBars();
	createStatusBar();
}

RestoreDb::~RestoreDb()
{
	FastdbManagerInstance::releaseFastdbManagerInstance();
}

void RestoreDb::createWidgets()
{
	textEdit = new QTextEdit();
	setCentralWidget(textEdit);

	setWindowTitle(QStringLiteral("�ָ�ʵʱ��"));
	setWindowIcon(QIcon(":/images/app.png"));
	resize(800, 600);
}

void RestoreDb::createActions()
{
	openAction = new QAction(QIcon(":/images/open.png"), QStringLiteral("��ʵʱ��"), this);
	openAction->setShortcut(QKeySequence::Open);
	openAction->setStatusTip(QStringLiteral("��ʵʱ��"));
	connect(openAction, SIGNAL(triggered()), this, SLOT(openDb()));

	closeAction = new QAction(QIcon(":/images/close.png"), QStringLiteral("�ر�ʵʱ��"), this);
	closeAction->setStatusTip(QStringLiteral("�ر�ʵʱ��"));
	connect(closeAction, SIGNAL(triggered()), this, SLOT(closeDb()));

	exitAction = new QAction(QIcon(":/images/close.png"), QStringLiteral("�˳�����"), this);
	exitAction->setShortcut(QKeySequence::Close);
	exitAction->setStatusTip(QStringLiteral("�˳�����"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	restoreAction = new QAction(QIcon(":/images/restore.png"), QStringLiteral("�ָ�ʵʱ��"), this);
	restoreAction->setStatusTip(QStringLiteral("�ָ�ʵʱ��"));
	connect(restoreAction, SIGNAL(triggered()), this, SLOT(restoreDb()));

	backupAction = new QAction(QIcon(":/images/restore.png"), QStringLiteral("����ʵʱ��"), this);
	backupAction->setStatusTip(QStringLiteral("����ʵʱ��"));
	connect(backupAction, SIGNAL(triggered()), this, SLOT(backupDb()));

	checkAction = new QAction(QIcon(":/images/restore.png"), QStringLiteral("���ʵʱ��"), this);
	checkAction->setStatusTip(QStringLiteral("���ʵʱ��"));
	connect(checkAction, SIGNAL(triggered()), this, SLOT(checkDb()));

	clearAction = new QAction(QIcon(":/images/clear.png"), QStringLiteral("����ı�"), this);
	clearAction->setStatusTip(QStringLiteral("����ı�"));
	connect(clearAction, SIGNAL(triggered()), this, SLOT(clearTextEdit()));
}

void RestoreDb::createConnects()
{
	connect(m_fastdbManager, SIGNAL(outputOperationInfo(QString)), this, SLOT(outputOperationInfo(QString)));
}

void RestoreDb::createMenus()
{
	fileMenu = menuBar()->addMenu(QStringLiteral("�ļ�"));
	fileMenu->addAction(openAction);
	fileMenu->addAction(closeAction);
	fileMenu->addAction(exitAction);

	operMenu = menuBar()->addMenu(QStringLiteral("����"));
	operMenu->addAction(restoreAction);
	operMenu->addAction(backupAction);
	operMenu->addAction(checkAction);
	operMenu->addAction(clearAction);
}

void RestoreDb::createToolBars()
{
	fileToolbar = addToolBar(QStringLiteral("�ļ�"));
	fileToolbar->addAction(openAction);
	fileToolbar->addAction(closeAction);
	fileToolbar->addAction(exitAction);

	operToolbar = addToolBar(QStringLiteral("����"));
	operToolbar->addAction(restoreAction);
	operToolbar->addAction(backupAction);
	operToolbar->addAction(checkAction);
	operToolbar->addAction(clearAction);
}

void RestoreDb::createStatusBar()
{
	statusBar()->showMessage(QStringLiteral("׼������"));
}

void RestoreDb::openDb()
{
	QString dbName = QFileDialog::getOpenFileName(this, QStringLiteral("ѡ��ʵʱ��"));
	if (dbName.isEmpty())
	{
		return;
	}

	if (!m_fastdbManager)
	{
		return;
	}

	dbName = dbName.left(dbName.indexOf("."));
	try {
		m_fastdbManager->openDatabase(dbName.toStdString());
	} catch (dbException& ex) {
		outputOperationInfo(QString("fastdb exception: %1").arg(ex.what()));
	} catch (std::exception& ex) {
		outputOperationInfo(QString("std exception: %1").arg(ex.what()));
	} catch (...) {
		outputOperationInfo("unknown exception");
	}
}

void RestoreDb::closeDb()
{
	try {
		m_fastdbManager->closeDatabase();
	} catch (dbException& ex) {
		outputOperationInfo(QString("fastdb exception: %1").arg(ex.what()));
	} catch (std::exception& ex) {
		outputOperationInfo(QString("std exception: %1").arg(ex.what()));
	} catch (...) {
		outputOperationInfo("unknown exception");
	}
}

void RestoreDb::restoreDb()
{
	QString fileName = QFileDialog::getOpenFileName(this, QStringLiteral("ѡ��ָ��ļ�"));
	if (fileName.isEmpty())
	{
		return;
	}

	if (!m_fastdbManager)
	{
		return;
	}

	try {
		m_fastdbManager->restoreDatabase(fileName.toStdString());
	} catch (dbException& ex) {
		outputOperationInfo(QString("fastdb exception: %1").arg(ex.what()));
	} catch (std::exception& ex) {
		outputOperationInfo(QString("std exception: %1").arg(ex.what()));
	} catch (...) {
		outputOperationInfo("unknown exception");
	}
}

void RestoreDb::backupDb()
{
	if (!m_fastdbManager)
	{
		return;
	}

	try {
		m_fastdbManager->backupDatabase();
	} catch (dbException& ex) {
		outputOperationInfo(QString("fastdb exception: %1").arg(ex.what()));
	} catch (std::exception& ex) {
		outputOperationInfo(QString("std exception: %1").arg(ex.what()));
	} catch (...) {
		outputOperationInfo("unknown exception");
	}
}

void RestoreDb::checkDb()
{
	if (!m_fastdbManager)
	{
		return;
	}

	try {
		m_fastdbManager->checkDatabase();
	} catch (dbException& ex) {
		outputOperationInfo(QString("fastdb exception: %1").arg(ex.what()));
	} catch (std::exception& ex) {
		outputOperationInfo(QString("std exception: %1").arg(ex.what()));
	} catch (...) {
		outputOperationInfo("unknown exception");
	}
}

void RestoreDb::clearTextEdit()
{
	if (textEdit)
	{
		textEdit->clear();
	}
}

void RestoreDb::outputOperationInfo( QString text )
{
	if (textEdit)
	{
		textEdit->moveCursor(QTextCursor::End);
		textEdit->insertPlainText(text);
		textEdit->insertPlainText("\n");
		textEdit->moveCursor(QTextCursor::End);
	}
}
