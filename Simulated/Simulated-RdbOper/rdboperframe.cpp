
#include <QtWidgets/QtWidgets>

#include "addRecordDialog.h"
#include "rdboperframe.h"
#include "rdbTableDefine.h"
#include "selectCompleteDataDialog.h"
#include "selectDefaultDataDialog.h"
#include "selectSpecficDataDialog.h"

RdbOperFrame::RdbOperFrame(QWidget *parent)
	: QMainWindow(parent), m_adapterIdentify("SimulatedRdbOpt")
{
	createWidget();
	createActions();
	createMenus();
	createToolBars();
	createStatusBar();

	initIcePtr();
}

RdbOperFrame::~RdbOperFrame()
{

}

void RdbOperFrame::createWidget()
{
	listView = new QListView;
	QStringList tableNames = RdbTableFactory::getTableNames();
	QStringListModel* listModel = new QStringListModel(tableNames);
	listView->setModel(listModel);

	tableView = new QTableView;

	QHBoxLayout* layout = new QHBoxLayout;
	layout->addWidget(listView, 1);
	layout->addWidget(tableView, 4);
	
	QWidget* widget = new QWidget;
	widget->setLayout(layout);
	setCentralWidget(widget);

	setWindowTitle(QStringLiteral("ʵʱ�����"));
	setWindowIcon(QIcon(":/icon.png"));
	resize(1000, 800);
}

void RdbOperFrame::createActions()
{
	quitAppAction = createActionImpl(QIcon(":/quit.png"), QStringLiteral("�˳�����"), 
		QStringLiteral("�˳�����"), SLOT(close()));

	configServerAction = createActionImpl(QIcon(":/configServer.png"), QStringLiteral("����Ice����"), 
			QStringLiteral("����Ice����"), SLOT(configServer()));
	startServerAction = createActionImpl(QIcon(":/startServer.png"), QStringLiteral("����Ice����"), 
		QStringLiteral("����Ice����"), SLOT(startServer()));
	stopServerAction = createActionImpl(QIcon(":/stopServer.png"), QStringLiteral("ֹͣIce����"), 
		QStringLiteral("ֹͣIce����"), SLOT(stopServer()));

	selectDefaultDataAction = createActionImpl(QIcon(":/select.png"), QStringLiteral("��ѯĬ������"), 
		QStringLiteral("��ѯĬ������"), SLOT(selectDefaultData())); 
	selectSpecficDataAction = createActionImpl(QIcon(":/select.png"), QStringLiteral("��ѯָ������"), 
		QStringLiteral("��ѯָ������"), SLOT(selectSpecficData())); 
	selectCompleteDataAction = createActionImpl(QIcon(":/select.png"), QStringLiteral("��ѯȫ������"), 
		QStringLiteral("��ѯȫ������"), SLOT(selectCompleteData())); 
	
	addRecordAction = createActionImpl(QIcon(":/addRecord.png"), QStringLiteral("�����¼"), 
		QStringLiteral("�����¼"), SLOT(addRecord()));
}

QAction* RdbOperFrame::createActionImpl(const QIcon& icon, const QString& text, const QString& statusTip, const char* slot)
{
	QAction* action = new QAction(icon, text, this);
	action->setStatusTip(statusTip);
	connect(action, SIGNAL(triggered()), this, slot);

	return action;
}

void RdbOperFrame::createMenus()
{
	QMenu* fileMenu = menuBar()->addMenu(QStringLiteral("�ļ�"));
	fileMenu->addAction(quitAppAction);

	QMenu* serverMenu = menuBar()->addMenu(QStringLiteral("Ice����"));
	serverMenu->addAction(configServerAction);
	serverMenu->addAction(startServerAction);
	serverMenu->addAction(stopServerAction);

	QMenu* operMenu = menuBar()->addMenu(QStringLiteral("����"));
	operMenu->addAction(selectDefaultDataAction);
	operMenu->addAction(selectSpecficDataAction);
	operMenu->addAction(selectCompleteDataAction);
	operMenu->addSeparator();
	operMenu->addAction(addRecordAction);
}

void RdbOperFrame::createToolBars()
{
	QToolBar* fileToolBar = addToolBar(QStringLiteral("�ļ�"));
	fileToolBar->addAction(quitAppAction);

	QToolBar* serverToolBar = addToolBar(QStringLiteral("Ice����"));
	serverToolBar->addAction(configServerAction);
	serverToolBar->addAction(startServerAction);
	serverToolBar->addAction(stopServerAction);

	QToolBar* operToolBar = addToolBar(QStringLiteral("����"));
	operToolBar->addAction(selectDefaultDataAction);
	operToolBar->addAction(selectSpecficDataAction);
	operToolBar->addAction(selectCompleteDataAction);
	operToolBar->addSeparator();
	operToolBar->addAction(addRecordAction);
}

void RdbOperFrame::createStatusBar()
{
	statusBar()->showMessage(QStringLiteral("׼������"));
}

void RdbOperFrame::initIcePtr()
{
	m_communicatorPtr = 0;
	m_objectAdapterPtr = 0;
	m_rdbDataOptPrx = 0;
}

bool RdbOperFrame::getRdbDataOptPrx()
{
	if (m_rdbDataOptPrx)
	{
		return true;
	}

	try
	{
		QString proxy = QString("rdb-opt: tcp -h %1 -p %2").arg(m_configIceInfo.iceOffsideIp).
				arg(m_configIceInfo.iceOffsidePort);
		m_rdbDataOptPrx = RdbDataOptPrx::checkedCast(m_communicatorPtr->stringToProxy(proxy.toStdString()));
		
		return true;
	}
	catch(const Ice::Exception& ex)
	{
		QMessageBox::warning(this, QStringLiteral("��ȡʵʱ�����ݴ���"), 
			QStringLiteral("��ȡ����ʧ��: %1").arg(ex.what()));
		m_rdbDataOptPrx = 0;
		return false;
	}
}

void RdbOperFrame::configServer()
{
	ConfigIceDialog configDialog(QIcon(":/configServer.png"));
	if (configDialog.exec() == QDialog::Accepted)
	{
		m_configIceInfo = configDialog.getConfigIceInfo();
	}
}

void RdbOperFrame::startServer()
{
	if (m_communicatorPtr)
	{
		return;
	}

	try
	{
		int argc = 0;
		Ice::InitializationData initData;
		initData.properties = Ice::createProperties();
		m_communicatorPtr = Ice::initialize(argc, 0, initData);
		QString endPoints = QString("tcp -h %1 -p %2").arg(m_configIceInfo.iceIp).arg(m_configIceInfo.icePort);
		m_objectAdapterPtr = m_communicatorPtr->createObjectAdapterWithEndpoints(m_adapterIdentify.toStdString(), 
			endPoints.toStdString());

		m_objectAdapterPtr->activate();

		updateStatusBar(QStringLiteral("Ice���������ɹ�"));
	}
	catch(const Ice::Exception& ex)
	{
		initIcePtr();
		QMessageBox::warning(this, QStringLiteral("����Ice����"), 
			QStringLiteral("��������ʧ��: %1").arg(ex.what()));
	}
}

void RdbOperFrame::stopServer()
{
	if (m_communicatorPtr)
	{
		try
		{
			m_communicatorPtr->destroy();

			initIcePtr();
			updateStatusBar(QStringLiteral("Ice����ֹͣ�ɹ�"));
		}
		catch(const Ice::Exception& ex)
		{
			initIcePtr();
			QMessageBox::warning(this, QStringLiteral("ֹͣIce����"), 
				QStringLiteral("ֹͣ����ʧ��: %1").arg(ex.what()));
		}
	}
}

void RdbOperFrame::selectDefaultData()
{
	if (!getRdbDataOptPrx())
	{
		return;
	}

	SelectDefaultDataDialog	selectDialog(m_rdbDataOptPrx);
	selectDialog.exec();
}

void RdbOperFrame::selectSpecficData()
{
	if (!getRdbDataOptPrx())
	{
		return;
	}

	SelectSpecficDataDialog	selectDialog(m_rdbDataOptPrx);
	selectDialog.exec();
}

void RdbOperFrame::selectCompleteData()
{
	if (!getRdbDataOptPrx())
	{
		return;
	}

	SelectCompleteDataDialog	selectDialog(m_rdbDataOptPrx);
	selectDialog.exec();
}

void RdbOperFrame::addRecord()
{
	if (!getRdbDataOptPrx())
	{
		return;
	}

	AddRecordDialog	addDialog(m_rdbDataOptPrx);
	addDialog.exec();
}

void RdbOperFrame::updateTableView()
{

}

void RdbOperFrame::updateStatusBar( const QString& text, int timeout )
{
	statusBar()->showMessage(text, timeout);
}