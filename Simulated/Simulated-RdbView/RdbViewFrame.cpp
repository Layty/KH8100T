#include "rdbviewframe.h"
#include "FdbTableDefine.h"
#include "tableoperation.h"
#include "hidecolumndialog.h"

#include <QtWidgets/QtWidgets>

RdbViewFrame::RdbViewFrame(QWidget *parent)
	: QMainWindow(parent)
{
	m_dbPtr = new dbDatabase(dbDatabase::dbAllAccess);
	m_tableOperPtr = new TableOperation(m_dbPtr);

	createWidgets();
	createActions();
	createMenus();
	createToolbars();
	createStatusBar();
	createConnects();
}

RdbViewFrame::~RdbViewFrame()
{

}

void RdbViewFrame::createWidgets()
{
	m_rdbTreeWidget = new QTreeWidget();
	m_rdbTreeWidget->setColumnCount(1);
	m_rdbTreeWidget->setHeaderLabels(QStringList(QStringLiteral("ʵʱ���б�")));
	m_rdbTreeWidget->setRootIsDecorated(false);
	m_rdbTreeWidget->setSelectionMode(QAbstractItemView::SingleSelection);

	m_rdbTableWidget = new QTableWidget;
	m_rdbTableWidget->setWindowTitle(QStringLiteral("ʵʱ������"));
	m_rdbTableWidget->setShowGrid(true);
	m_rdbTableWidget->setSortingEnabled(true);
	m_rdbTableWidget->setAlternatingRowColors(true);

	QSplitter* splitter = new QSplitter;
	splitter->addWidget(m_rdbTreeWidget);
	splitter->addWidget(m_rdbTableWidget);
	splitter->setStretchFactor(0, 1);
	splitter->setStretchFactor(1, 6);

	setCentralWidget(splitter);
	setWindowTitle(QStringLiteral("ʵʱ�����"));
	setWindowIcon(QIcon(":/images/rdbview.png"));
	resize(1400, 800);
}

void RdbViewFrame::createActions()
{
	openAction = new QAction(QIcon(":/images/open.png"), QStringLiteral("��ʵʱ��"), this);
	openAction->setShortcut(QKeySequence::Open);
	openAction->setStatusTip(QStringLiteral("�򿪱���ʵʱ���ݿ�"));
	connect(openAction, SIGNAL(triggered()), this, SLOT(openRdbDatabase()));

	closeAction = new QAction(QIcon(":/images/close.png"), QStringLiteral("�ر�ʵʱ��"), this);
	closeAction->setShortcut(QKeySequence::Close);
	closeAction->setStatusTip(QStringLiteral("�رձ���ʵʱ���ݿ�"));
	closeAction->setEnabled(false);
	connect(closeAction, SIGNAL(triggered()), this, SLOT(closeRdbDatabase()));

	exitAction = new QAction(QIcon(":/images/exit.png"), QStringLiteral("�˳�"), this);
	exitAction->setShortcut(QKeySequence::Quit);
	exitAction->setStatusTip(QStringLiteral("�˳�ϵͳ"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	addAction = new QAction(QIcon(":/images/add.png"), QStringLiteral("����"), this);
	addAction->setStatusTip(QStringLiteral("��������"));
	addAction->setEnabled(false);
	connect(addAction, SIGNAL(triggered()), this, SLOT(addData()));

	deleteAction = new QAction(QIcon(":/images/delete.png"), QStringLiteral("ɾ��"), this);
	deleteAction->setStatusTip(QStringLiteral("ɾ������"));
	deleteAction->setEnabled(false);
	connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteData()));

	saveAction = new QAction(QIcon(":/images/save.png"), QStringLiteral("����"), this);
	saveAction->setStatusTip(QStringLiteral("��������"));
	saveAction->setEnabled(false);
	connect(saveAction, SIGNAL(triggered()), this, SLOT(saveData()));

	refreshAction = new QAction(QIcon(":/images/refresh.png"), QStringLiteral("ˢ��"), this);
	refreshAction->setStatusTip(QStringLiteral("ˢ������"));
	refreshAction->setEnabled(false);
	connect(refreshAction, SIGNAL(triggered()), this, SLOT(refreshData()));

	deleteAllAction = new QAction(QIcon(":/images/deleteAll.png"), QStringLiteral("ȫ��ɾ��"), this);
	deleteAllAction->setStatusTip(QStringLiteral("ɾ��ȫ������"));
	deleteAllAction->setEnabled(false);
	connect(deleteAllAction, SIGNAL(triggered()), this, SLOT(deleteAllData()));

	hideTableColumnAction = new QAction(QIcon(":/images/hideColumn.png"), QStringLiteral("������"), this);
	hideTableColumnAction->setStatusTip(QStringLiteral("���ر���е�ָ����"));
	hideTableColumnAction->setEnabled(true);
	connect(hideTableColumnAction, SIGNAL(triggered()), this, SLOT(hideTableColumn()));

	aboutAction = new QAction(QIcon(":/images/about.png"), QStringLiteral("����"), this);
	aboutAction->setStatusTip(QStringLiteral("���ڳ���"));
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

void RdbViewFrame::createMenus()
{
	fileMenu = menuBar()->addMenu(QStringLiteral("�ļ�"));
	fileMenu->addAction(openAction);
	fileMenu->addAction(closeAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	editMenu = menuBar()->addMenu(QStringLiteral("�༭"));
	editMenu->addAction(addAction);
	editMenu->addAction(deleteAction);
	editMenu->addAction(saveAction);
	editMenu->addAction(refreshAction);
	editMenu->addSeparator();
	editMenu->addAction(deleteAllAction);
	editMenu->addAction(hideTableColumnAction);

	helpMenu = menuBar()->addMenu(QStringLiteral("����"));
	helpMenu->addAction(aboutAction);
}

void RdbViewFrame::createToolbars()
{
	fileToolBar = addToolBar(QStringLiteral("�ļ�"));
	fileToolBar->addAction(openAction);
	fileToolBar->addAction(closeAction);
	fileToolBar->addSeparator();
	fileToolBar->addAction(exitAction);

	editToolBar = addToolBar(QStringLiteral("�༭"));
	editToolBar->addAction(addAction);
	editToolBar->addAction(deleteAction);
	editToolBar->addAction(saveAction);
	editToolBar->addAction(refreshAction);
	editToolBar->addSeparator();
	editToolBar->addAction(deleteAllAction);
	editToolBar->addAction(hideTableColumnAction);
}

void RdbViewFrame::createStatusBar()
{
	statusBar()->showMessage(QStringLiteral("׼������"));
}

void RdbViewFrame::createConnects()
{
	connect(this, SIGNAL(databaseOpenState(bool)), this, SLOT(updateDatabaseActions(bool)));
	connect(this, SIGNAL(databaseOpenState(bool)), this, SLOT(updateTreeWidget()));
	connect(m_rdbTreeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, 
		SLOT(updateTableWidget(QTreeWidgetItem*, QTreeWidgetItem*)));
	connect(m_rdbTreeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, 
		SLOT(treeItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
	connect(m_rdbTableWidget,SIGNAL(currentItemChanged(QTableWidgetItem*,QTableWidgetItem*)), this, 
		SLOT(tableItemChanged(QTableWidgetItem*,QTableWidgetItem*)));
}

void RdbViewFrame::refreshDatas( QTreeWidgetItem* item )
{
	// ������ݱ�
	QStringList tableHeaders;
	m_rdbTableWidget->clearContents();
	m_rdbTableWidget->setRowCount(0);
	m_rdbTableWidget->setHorizontalHeaderLabels(tableHeaders);
	m_rdbTableWidget->setColumnCount(0);

	if (item)
	{
		QString tableName = item->text(0);
		// ��д��ͷ
		tableHeaders = m_tableOperPtr->getTableFieldNames(tableName);
		m_rdbTableWidget->setColumnCount(tableHeaders.count());
		m_rdbTableWidget->setHorizontalHeaderLabels(tableHeaders);

		// ��д������
		QList<QStringList> datas = m_tableOperPtr->selectDatas(tableName);
		deleteAllAction->setEnabled(!datas.isEmpty());
		for (int i = 0; i < datas.count(); ++i)
		{
			int count = m_rdbTableWidget->rowCount();
			m_rdbTableWidget->insertRow(count);
			for (int j = 0; j < datas.at(i).count(); ++j)
			{
				m_rdbTableWidget->setItem(count, j, new QTableWidgetItem(datas.at(i).at(j)));
			}
		}

		// �Զ����ز���Ҫ���ֶ�
		QList<int> hideColumns;
		m_tableOperPtr->getHidedColumns(tableName, hideColumns);
		foreach(int i, hideColumns)
		{
			m_rdbTableWidget->hideColumn(i);
		}
	}
}

bool RdbViewFrame::getCurrentTableName( QString& tableName )
{
	QTreeWidgetItem* item = m_rdbTreeWidget->currentItem();
	if (!item)
	{
		QMessageBox::critical(this, QStringLiteral("ʵʱ�����"), QStringLiteral("��δѡ���κ�ʵʱ��"));
		return false;
	}

	tableName = item->text(0);
	return true;
}

bool RdbViewFrame::getCurrentMRID( QString& mRID )
{
	int row = m_rdbTableWidget->currentRow();
	if (row < 0)
	{
		QMessageBox::critical(this, QStringLiteral("ʵʱ�����"), QStringLiteral("��ǰ����С��0"));
		return false;
	}

	QTableWidgetItem* item = m_rdbTableWidget->item(row, 0);
	if (!item)
	{
		QMessageBox::critical(this, QStringLiteral("ʵʱ�����"), QStringLiteral("��ǰѡ������Ч"));
		return false;
	}

	mRID = item->text();
	return true;
}

bool RdbViewFrame::getCurrentTableItemValue( QString& value )
{
	QTableWidgetItem* item = m_rdbTableWidget->currentItem();
	if (item)
	{
		value = item->text();
		return true;
	}
	else
	{
		QMessageBox::critical(this, QStringLiteral("ʵʱ�����"), QStringLiteral("��ǰѡ������Ч"));
		return false;
	}
}

bool RdbViewFrame::getCurrentTableHeaderLabel( QString& value )
{
	QTableWidgetItem* item = m_rdbTableWidget->currentItem();
	if (item)
	{
		int column = item->column();
		QTableWidgetItem* headerItem = m_rdbTableWidget->horizontalHeaderItem(column);
		if (headerItem)
		{
			value = headerItem->text();
		}
		else
		{
			QMessageBox::critical(this, QStringLiteral("ʵʱ�����"), QStringLiteral("��ǰѡ������Ч"));
			return false;
		}
	}
	else
	{
		QMessageBox::critical(this, QStringLiteral("ʵʱ�����"), QStringLiteral("��ǰѡ������Ч"));
		return false;
	}
	return true;
}

void RdbViewFrame::updateDatabaseActions( bool opened )
{
	openAction->setEnabled(!opened);
	closeAction->setEnabled(opened);
}

void RdbViewFrame::updateTreeWidget()
{
	m_rdbTreeWidget->clear();

	if (m_dbPtr->isOpen())
	{
		QStringList tableNames;
		dbTableDescriptor* tableDesc = m_dbPtr->getTables();
		do 
		{
			if (tableDesc)
			{
				tableNames.push_back(tableDesc->getName());
			}
			else
			{
				break;
			}
		} while (tableDesc = tableDesc->getNextTable());


		for (int i = 0; i < tableNames.count(); ++i) {
			QTreeWidgetItem *item = new QTreeWidgetItem(m_rdbTreeWidget);
			item->setText(0, tableNames[i]);
		}

		if (tableNames.count() > 0)
			m_rdbTreeWidget->setCurrentItem(m_rdbTreeWidget->topLevelItem(0));
	}
}

void RdbViewFrame::updateTableWidget( QTreeWidgetItem* current, QTreeWidgetItem* previous )
{
	if (current == previous)
	{
		return;
	}

	refreshDatas(current);
}

void RdbViewFrame::treeItemChanged( QTreeWidgetItem* current, QTreeWidgetItem* previous )
{
	if (current)
	{
		addAction->setEnabled(true);
		refreshAction->setEnabled(true);
	}
	else
	{
		addAction->setEnabled(false);
		refreshAction->setEnabled(false);
	}
}

void RdbViewFrame::tableItemChanged( QTableWidgetItem* current, QTableWidgetItem* previous )
{
	if (current)
	{
		deleteAction->setEnabled(true);
		saveAction->setEnabled(true);
	}
	else
	{
		deleteAction->setEnabled(false);
		saveAction->setEnabled(false);
	}
}

bool RdbViewFrame::openRdbDatabase()
{
	if (!m_dbPtr->open("serverdb1"))
	{
		emit databaseOpenState(false);
		QMessageBox::critical(this, QStringLiteral("ʵʱ�����"), QStringLiteral("���ݿ��ʧ��"));
		return false;
	}

	emit databaseOpenState(true);
	return true;
}

bool RdbViewFrame::closeRdbDatabase()
{
	m_dbPtr->close();
	emit databaseOpenState(false);
	return true;
}

bool RdbViewFrame::addData()
{
	if (m_tableOperPtr)
	{
		QString tableName;
		if (!getCurrentTableName(tableName))
		{
			return false;
		}
		if (m_tableOperPtr->insertData(tableName))
		{
			refreshData();
		}
		else
		{
			QMessageBox::critical(this, QStringLiteral("ʵʱ�����"), QStringLiteral("��������ʧ��"));
		}
	}
	else
	{
		QMessageBox::critical(this, QStringLiteral("ʵʱ�����"), QStringLiteral("ʵʱ�����ָ��Ϊ��"));
		return false;
	}
	return true;
}

bool RdbViewFrame::deleteData()
{
	if (m_tableOperPtr)
	{
		// ��ȡ���ݱ���
		QString tableName;
		if (!getCurrentTableName(tableName))
		{
			return false;
		}

		// ��ȡ��ǰ���ݵ�mRID
		QString mRID;
		if (!getCurrentMRID(mRID))
		{
			return false;
		}
		
		if (m_tableOperPtr->deleteData(tableName, mRID))
		{
			refreshData();
		}
		else
		{
			QMessageBox::critical(this, QStringLiteral("ʵʱ�����"), QStringLiteral("ɾ������ʧ��"));
		}
	}
	else
	{
		QMessageBox::critical(this, QStringLiteral("ʵʱ�����"), QStringLiteral("ʵʱ�����ָ��Ϊ��"));
		return false;
	}
	return true;
}

bool RdbViewFrame::saveData()
{
	if (m_tableOperPtr)
	{
		// ��ȡ���ݱ���
		QString tableName;
		if (!getCurrentTableName(tableName))
		{
			return false;
		}

		// ��ȡ��ǰ���ݵ�mRID
		QString mRID;
		if (!getCurrentMRID(mRID))
		{
			return false;
		}

		// ��ȡ��ǰ�е����м�¼
		QTableWidgetItem* item = m_rdbTableWidget->currentItem();
		if (item)
		{
			QMap<QString, QString> values;
			int columnCount = m_rdbTableWidget->columnCount();
			for (int i = 0; i < columnCount; ++i)
			{
				QString fieldName = m_rdbTableWidget->horizontalHeaderItem(i)->text();
				QString value = m_rdbTableWidget->item(item->row(), i)->text();
				values.insert(fieldName, value);
			}
			if (!m_tableOperPtr->saveData(tableName, mRID, values))
			{
				QMessageBox::critical(this, QStringLiteral("ʵʱ�����"), QStringLiteral("ɾ������ʧ��"));
				refreshData();
			}
		}
	}
	else
	{
		QMessageBox::critical(this, QStringLiteral("ʵʱ�����"), QStringLiteral("ʵʱ�����ָ��Ϊ��"));
		return false;
	}
	return true;
}

bool RdbViewFrame::refreshData()
{
	QTreeWidgetItem* item = m_rdbTreeWidget->currentItem();
	refreshDatas(item);
	return true;
}

bool RdbViewFrame::deleteAllData()
{
	if (m_tableOperPtr)
	{
		// ��ȡ���ݱ���
		QString tableName;
		if (!getCurrentTableName(tableName))
		{
			return false;
		}

		if (m_tableOperPtr->deleteAllData(tableName))
		{
			refreshData();
		}
		else
		{
			QMessageBox::critical(this, QStringLiteral("ʵʱ�����"), QStringLiteral("ɾ������ʧ��"));
		}
	}
	else
	{
		QMessageBox::critical(this, QStringLiteral("ʵʱ�����"), QStringLiteral("ʵʱ�����ָ��Ϊ��"));
		return false;
	}
	return true;
}

void RdbViewFrame::hideTableColumn()
{
	if (!m_rdbTableWidget)
	{
		return;
	}

	HideColumnDialog hideDlg(m_rdbTableWidget, this);
	if(hideDlg.exec() == QDialog::Accepted)
	{
		QList<int> hideColumns = hideDlg.getHideColumns();
		foreach(int i, hideColumns)
		{
			m_rdbTableWidget->hideColumn(i);
		}
	}
}

void RdbViewFrame::about()
{
	QMessageBox::information(this, QStringLiteral("ʵʱ�����"), QStringLiteral("ʵʱ���������Ӧ�ó���"));
}


