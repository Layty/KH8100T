#include "publishfileframe.h"
#include "FileHandler.h"

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

	readFileAction = new QAction(QIcon(":/images/read.png"), QStringLiteral("��ȡ�ļ�"), this);
	readFileAction->setStatusTip(QStringLiteral("��ȡ�ļ�"));
	connect(readFileAction, SIGNAL(triggered()), this, SLOT(readFile()));

	writeFileAction = new QAction(QIcon(":/images/write.png"), QStringLiteral("д���ļ�"), this);
	writeFileAction->setStatusTip(QStringLiteral("д���ļ�"));
	connect(writeFileAction, SIGNAL(triggered()), this, SLOT(writeFile()));

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
	operMenu->addAction(readFileAction);
	operMenu->addAction(writeFileAction);
	operMenu->addAction(clearAction);
}

void PublishFileFrame::createToolBars()
{
	fileToolBar = addToolBar(QStringLiteral("�ļ�"));
	fileToolBar->addAction(closeAction);

	operToolBar = addToolBar(QStringLiteral("����"));
	operToolBar->addAction(publishAction);
	operToolBar->addAction(readFileAction);
	operToolBar->addAction(writeFileAction);
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

void PublishFileFrame::readFile()
{
	CFileHandler fileHandler;
	string content;
	bool ok;
	int value = QInputDialog::getInt(this, QStringLiteral("ѡ���ȡ�ļ��ķ�ʽ"), 
		QStringLiteral("1: default	2: fstream	3: QFile	4: QTextStream	5: QDataStream"), 
		1, 1, 5, 1, &ok);
	if (ok)
	{
		bool (CFileHandler::*pfun)(const string&, string&);
		QString mode;
		switch(value)
		{
		case 1:
			pfun = &CFileHandler::readFile;
			mode = "readFile";
			break;
		case 2:
			pfun = &CFileHandler::readFileWithFStream;
			mode = "readFileWithFStream";
			break;
		case 3:
			pfun = &CFileHandler::readFileWithQFile;
			mode = "readFileWithQFile";
			break;
		case 4:
			pfun = &CFileHandler::readFileWithQTextStream;
			mode = "readFileWithQTextStream";
			break;
		case 5:
			pfun = &CFileHandler::readFileWithQDataStream;
			mode = "readFileWithQDataStream";
			break;
		default:
			pfun = 0;
			break;
		}

		updateTextEdit(QStringLiteral("�� %1 ��ʽ��ȡ�ļ�").arg(mode));
		if ((fileHandler.*pfun)("input.log", content))
		{
			m_fileContent = content;
			updateTextEdit(QString().fromStdString(content));
		}
		else
		{
			updateTextEdit(QStringLiteral("��ȡ�ļ�ʧ��"));
		}
	}
}

void PublishFileFrame::writeFile()
{
	CFileHandler fileHandler;
	string content = m_fileContent;
	if (fileHandler.writeFile("output.log", content))
	{
		updateTextEdit(QStringLiteral("д���ļ��ɹ�"));
	}
	else
	{
		updateTextEdit(QStringLiteral("д���ļ�ʧ��"));
	}
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
