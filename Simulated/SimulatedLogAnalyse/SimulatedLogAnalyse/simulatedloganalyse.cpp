#include "simulatedloganalyse.h"
#include "AnalyseFileThread.h"

#include <QtWidgets/QtWidgets>

const QString START_ANALYSE = QStringLiteral("��ʼ����");
const QString STOP_ANALYSE = QStringLiteral("ֹͣ����");

SimulatedLogAnalyse::SimulatedLogAnalyse(QWidget *parent)
	: QMainWindow(parent)
{
	m_isAnalysing = false;
	m_timeSpan = 10;	// Ĭ��10ms

	initWidget();
}

SimulatedLogAnalyse::~SimulatedLogAnalyse()
{

}

void SimulatedLogAnalyse::initWidget()
{
	createActions();

	QToolBar* toolBar = addToolBar(QString("ToolBar"));
	toolBar->addAction(m_openFileAction);
	toolBar->addAction(m_analyseAction);
	toolBar->addAction(m_clearAction);
	toolBar->addAction(m_quitAction);

	m_textEdit = new QTextEdit();
	setCentralWidget(m_textEdit);

	statusBar()->showMessage(QStringLiteral("׼������"));

	this->resize(1000, 750);
}

void SimulatedLogAnalyse::createActions()
{
	m_openFileAction = new QAction(QStringLiteral("ѡ���ļ�"), this);
	connect(m_openFileAction, SIGNAL(triggered()), this, SLOT(doOpenFile()));

	m_analyseAction = new QAction(START_ANALYSE, this);
	connect(m_analyseAction, SIGNAL(triggered()), this, SLOT(doAnalyse()));

	m_settingAction = new QAction(QStringLiteral("����"), this);
	connect(m_settingAction, SIGNAL(triggered()), this, SLOT(doSetting()));

	m_clearAction = new QAction(QStringLiteral("��������Ϣ"), this);
	connect(m_clearAction, SIGNAL(triggered()), this, SLOT(doClear()));

	m_quitAction = new QAction(QStringLiteral("�˳�"), this);
	connect(m_quitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void SimulatedLogAnalyse::startAnalyseFile()
{
	if (m_fileName.isEmpty())
	{
		QMessageBox::warning(this, QStringLiteral("��־����"), QStringLiteral("�ļ���Ϊ��"));
		return;
	}

	stopAnalyseFile();
	m_analyseThread = QSharedPointer<CAnalyseFileThread>(new CAnalyseFileThread(m_fileName, m_timeSpan));
	connect(m_analyseThread.data(), SIGNAL(finished()), this, SLOT(doAnalyseFinished()));
	connect(m_analyseThread.data(), SIGNAL(outputInfo(const QString&)), 
		this, SLOT(doThreadOutput(const QString&)));
	m_analyseThread->start();
	m_isAnalysing = true;
}

void SimulatedLogAnalyse::stopAnalyseFile()
{
	if (m_isAnalysing && m_analyseThread != NULL && m_analyseThread->isRunning())
	{
		m_analyseThread->setStop(true);
		m_analyseThread->wait();
	}
	m_isAnalysing = false;
}

void SimulatedLogAnalyse::outputInfo(const QString& info)
{
	if(m_textEdit->document()->lineCount() > 1000) {
		m_textEdit->clear();
	}
	m_textEdit->append(info);
}

void SimulatedLogAnalyse::doOpenFile()
{
	if (m_isAnalysing)
	{
		return;
	}

	m_fileName = QFileDialog::getOpenFileName(this, QStringLiteral("���ļ�"), QString("./log/"));
	outputInfo(QStringLiteral("���ļ�: ") + m_fileName);
}

void SimulatedLogAnalyse::doAnalyse()
{
	QString text = m_analyseAction->text();
	if (text == START_ANALYSE)
	{
		startAnalyseFile();
		m_analyseAction->setText(STOP_ANALYSE);
	}
	else 
	{
		stopAnalyseFile();
		m_analyseAction->setText(START_ANALYSE);
	}
}

void SimulatedLogAnalyse::doSetting()
{
	m_timeSpan = QInputDialog::getInt(this, QStringLiteral("��־��������"), QStringLiteral("ʱ����(ms)"));
}

void SimulatedLogAnalyse::doClear()
{
	if (m_textEdit)
	{
		m_textEdit->clear();
	}
}

void SimulatedLogAnalyse::doAnalyseFinished()
{
	outputInfo(QStringLiteral("��־�ļ��������"));

	m_isAnalysing = false;
	m_analyseAction->setText(START_ANALYSE);
}

void SimulatedLogAnalyse::doThreadOutput(const QString& info)
{
	outputInfo(info);
}
