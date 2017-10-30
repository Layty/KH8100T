#include "publishfileframe.h"

#include <QtWidgets/QtWidgets>

const QString	TITLE = QStringLiteral("ģ�ⷢ���ļ�");

PublishFileFrame::PublishFileFrame(QWidget *parent)
	: QMainWindow(parent)
{
	createWidgets();
	createActions();
	createConnectes();
	createMenus();
	createToolBars();
	createStatusBar();
}

PublishFileFrame::~PublishFileFrame()
{

}

void PublishFileFrame::setTransFileServer( const QSharedPointer<TransferFileServer>& server )
{
	m_transFileServer = server;
}

void PublishFileFrame::createWidgets()
{
	textEdit = new QTextEdit();
	setCentralWidget(textEdit);

	setWindowTitle(QStringLiteral("%1").arg(TITLE));
	setWindowIcon(QIcon(":/images/app.png"));
	resize(800, 600);
}

void PublishFileFrame::createActions()
{
	closeAction = new QAction(QIcon(":/images/close.png"), QStringLiteral("�رճ���"), this);
	closeAction->setStatusTip(QStringLiteral("�رճ���"));
	connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

	publishAction = new QAction(QIcon(":/images/publish.png"), QStringLiteral("�����ļ�"), this);
	publishAction->setStatusTip(QStringLiteral("�����ļ�"));
	connect(publishAction, SIGNAL(triggered()), this, SLOT(publishFile()));

	clearAction = new QAction(QIcon(":/images/clear.png"), QStringLiteral("����ı�"), this);
	clearAction->setStatusTip(QStringLiteral("����ı�"));
	connect(clearAction, SIGNAL(triggered()), this, SLOT(clearTextEdit()));
}

void PublishFileFrame::createConnectes()
{

}

void PublishFileFrame::createMenus()
{
	fileMenu = menuBar()->addMenu(QStringLiteral("�ļ�"));
	fileMenu->addAction(closeAction);

	operMenu = menuBar()->addMenu(QStringLiteral("����"));
	operMenu->addAction(publishAction);
	operMenu->addAction(clearAction);
}

void PublishFileFrame::createToolBars()
{
	fileToolBar = addToolBar(QStringLiteral("�ļ�"));
	fileToolBar->addAction(closeAction);

	operToolBar = addToolBar(QStringLiteral("����"));
	operToolBar->addAction(publishAction);
	operToolBar->addAction(clearAction);
}

void PublishFileFrame::createStatusBar()
{
	statusBar()->showMessage(QStringLiteral("׼������"));
}

void PublishFileFrame::updateActions()
{

}

void PublishFileFrame::publishFile()
{
	m_publishing = !m_publishing;

	// ��ʼ�����ļ�
	setWindowTitle(QStringLiteral("%1: %2").arg(TITLE).arg(QStringLiteral("���ڷ����ļ�...")));
	publishAction->setText(QStringLiteral("ȡ�������ļ�"));

	m_transFileServer->publishFile(true);
	setWindowTitle(QStringLiteral("%1").arg(TITLE));
}

void PublishFileFrame::clearTextEdit()
{
	if (textEdit)
	{
		textEdit->clear();
	}
}

void PublishFileFrame::updateTextEdit( QString text )
{
	if (textEdit)
	{
		textEdit->moveCursor(QTextCursor::End);
		textEdit->insertPlainText(text);
		textEdit->insertPlainText("\n");
		textEdit->moveCursor(QTextCursor::End);
	}
}
