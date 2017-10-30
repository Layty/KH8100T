#include "subscriberfileframe.h"

#include <QtWidgets/QtWidgets>

const QString	TITLE = QStringLiteral("ģ�ⶩ���ļ�");

SubscriberFileFrame::SubscriberFileFrame(QWidget *parent)
	: QMainWindow(parent)
{
	m_subscribering = false;

	createWidgets();
	createActions();
	createConnectes();
	createMenus();
	createToolBars();
	createStatusBar();
}

SubscriberFileFrame::~SubscriberFileFrame()
{

}

void SubscriberFileFrame::setTransFileServer( const QSharedPointer<TransferFileServer>& server )
{
	m_transFileServer = server;
}

void SubscriberFileFrame::createWidgets()
{
	textEdit = new QTextEdit();
	setCentralWidget(textEdit);

	setWindowTitle(QStringLiteral("%1").arg(TITLE));
	setWindowIcon(QIcon(":/images/app.png"));
	resize(800, 600);
}

void SubscriberFileFrame::createActions()
{
	closeAction = new QAction(QIcon(":/images/close.png"), QStringLiteral("�رճ���"), this);
	closeAction->setStatusTip(QStringLiteral("�رճ���"));
	connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

	subscriberAction = new QAction(QIcon(":/images/subscriber.png"), QStringLiteral("�����ļ�"), this);
	subscriberAction->setStatusTip(QStringLiteral("�����ļ�"));
	connect(subscriberAction, SIGNAL(triggered()), this, SLOT(subscriberFile()));

	clearAction = new QAction(QIcon(":/images/clear.png"), QStringLiteral("����ı�"), this);
	clearAction->setStatusTip(QStringLiteral("����ı�"));
	connect(clearAction, SIGNAL(triggered()), this, SLOT(clearTextEdit()));
}

void SubscriberFileFrame::createConnectes()
{

}

void SubscriberFileFrame::createMenus()
{
	fileMenu = menuBar()->addMenu(QStringLiteral("�ļ�"));
	fileMenu->addAction(closeAction);

	operMenu = menuBar()->addMenu(QStringLiteral("����"));
	operMenu->addAction(subscriberAction);
	operMenu->addAction(clearAction);
}

void SubscriberFileFrame::createToolBars()
{
	fileToolBar = addToolBar(QStringLiteral("�ļ�"));
	fileToolBar->addAction(closeAction);

	operToolBar = addToolBar(QStringLiteral("����"));
	operToolBar->addAction(subscriberAction);
	operToolBar->addAction(clearAction);
}

void SubscriberFileFrame::createStatusBar()
{
	statusBar()->showMessage(QStringLiteral("׼������"));
}

void SubscriberFileFrame::updateActions()
{

}

void SubscriberFileFrame::subscriberFile()
{
	m_subscribering = !m_subscribering;
	if (m_subscribering)
	{
		// ��ʼ�����ļ�

		setWindowTitle(QStringLiteral("%1: %2").arg(TITLE).arg(QStringLiteral("���ڶ����ļ�...")));
		subscriberAction->setText(QStringLiteral("ȡ�������ļ�"));

		m_transFileServer->subscriberFile(true);
	}
	else
	{
		// ֹͣ�����ļ�

		setWindowTitle(QStringLiteral("%1").arg(TITLE));
		subscriberAction->setText(QStringLiteral("�����ļ�"));

		m_transFileServer->subscriberFile(false);
	}
}

void SubscriberFileFrame::clearTextEdit()
{
	if (textEdit)
	{
		textEdit->clear();
	}
}

void SubscriberFileFrame::updateTextEdit( QString text )
{
	if (textEdit)
	{
		textEdit->moveCursor(QTextCursor::End);
		textEdit->insertPlainText(text);
		textEdit->insertPlainText("\n");
		textEdit->moveCursor(QTextCursor::End);
	}
}
