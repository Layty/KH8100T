#include "sqlframe.h"

#include <QtWidgets/QtWidgets>

#define THREAD_COUNT	10

SqlFrame::SqlFrame(QWidget *parent)
	: QMainWindow(parent)
{
	createWidgets();
	createActions();
	createConnectes();
	createMenus();
	createToolBars();
	createStatusBar();
}

SqlFrame::~SqlFrame()
{

}

void SqlFrame::createWidgets()
{
	textEdit = new QTextEdit();
	setCentralWidget(textEdit);

	setWindowTitle(QStringLiteral("MySql����ģ�����"));
	setWindowIcon(QIcon(":/images/app.png"));
	resize(800, 600);
}

void SqlFrame::createActions()
{
	startAction = new QAction(QIcon(":/images/start.png"), QStringLiteral("��ʼִ��"), this);
	startAction->setStatusTip(QStringLiteral("��ʼִ��MySql����"));
	connect(startAction, SIGNAL(triggered()), this, SLOT(startExecSql()));

	stopAction = new QAction(QIcon(":/images/stop.png"), QStringLiteral("ִֹͣ��"), this);
	stopAction->setStatusTip(QStringLiteral("ִֹͣ��MySql����"));
	stopAction->setEnabled(false);
	connect(stopAction, SIGNAL(triggered()), this, SLOT(stopExecSql()));

	closeAction = new QAction(QIcon(":/images/close.png"), QStringLiteral("�˳�����"), this);
	closeAction->setStatusTip(QStringLiteral("�˳�����"));
	connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

	clearAction = new QAction(QIcon(":/images/clear.png"), QStringLiteral("����ı�"), this);
	clearAction->setStatusTip(QStringLiteral("����ı�"));
	connect(clearAction, SIGNAL(triggered()), this, SLOT(clearTextEdit()));
}

void SqlFrame::createConnectes()
{

}

void SqlFrame::createMenus()
{
	fileMenu = menuBar()->addMenu(QStringLiteral("�ļ�"));
	fileMenu->addAction(startAction);
	fileMenu->addAction(stopAction);
	fileMenu->addSeparator();
	fileMenu->addAction(closeAction);

	operMenu = menuBar()->addMenu(QStringLiteral("����"));
	operMenu->addAction(clearAction);
}

void SqlFrame::createToolBars()
{
	fileToolbar = addToolBar(QStringLiteral("�ļ�"));
	fileToolbar->addAction(startAction);
	fileToolbar->addAction(stopAction);
	fileToolbar->addSeparator();
	fileToolbar->addAction(closeAction);

	operToolbar = addToolBar(QStringLiteral("����"));
	operToolbar->addAction(clearAction);
}

void SqlFrame::createStatusBar()
{
	statusBar()->showMessage(QStringLiteral("׼������"));
}

void SqlFrame::updateExecAction( bool isStart )
{
	startAction->setEnabled(!isStart);
	stopAction->setEnabled(isStart);
}

void SqlFrame::startExecSql()
{
	updateExecAction(true);

	for (int i = 0; i < THREAD_COUNT; ++i)
	{
		QSharedPointer<CExecThread> execThreadPtr(new CExecThread);
		execThreadPtr->start();
		connect(execThreadPtr.data(), SIGNAL(outputOperInfo(QString)), this, SLOT(updateTextEdit(QString)));
		m_execThreads.push_back(execThreadPtr);
	}

}

void SqlFrame::stopExecSql()
{
	updateExecAction(false);

	for (int i = 0; i < m_execThreads.size(); ++i)
	{
		m_execThreads.at(i)->setStop(true);
	}

	for (int i = 0; i < m_execThreads.size(); )
	{
		if (m_execThreads.at(i)->isRunning())
		{
			continue;
		}
		++i;
	}
	m_execThreads.clear();
}

void SqlFrame::clearTextEdit()
{
	if (textEdit)
	{
		textEdit->clear();
	}
}

void SqlFrame::updateTextEdit( QString text )
{
	if (textEdit)
	{
		textEdit->moveCursor(QTextCursor::End);
		textEdit->insertPlainText(text);
		textEdit->moveCursor(QTextCursor::End);
	}
}
