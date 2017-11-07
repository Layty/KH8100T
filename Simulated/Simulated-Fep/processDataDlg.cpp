#include "processDataDlg.h"

#include <QtWidgets/QtWidgets>

const int COUNT = 10;

ProcessDataDialog::ProcessDataDialog(DataType type, AllDataTypeType alltype, QWidget* parent /*= 0*/ )
	: QDialog(parent), dataType(type), allDataTypeType(alltype), m_processCount(0)
{
	m_timer = QSharedPointer<QTimer>::create();
	
	createWidgets();
	createConnections();
}

void ProcessDataDialog::createWidgets()
{
	idLable = new QLabel(QStringLiteral("���ݰ�id"));
	idEdit = new QLineEdit(QStringLiteral("1"));
	idLable->setBuddy(idEdit);
	
	fepNodeLable = new QLabel(QStringLiteral("ǰ�û�"));
	fepNodeEdit = new QLineEdit(QStringLiteral("fep-36"));
	fepNodeLable->setBuddy(fepNodeEdit);

	typeLable = new QLabel(QStringLiteral("��������"));
	typeEdit = new QLineEdit;
	typeEdit->setText(getAllDataTypeTitle());
	typeEdit->setReadOnly(true);

	unitNoLable = new QLabel(QStringLiteral("��Ԫ���"));
	unitNoEdit = new QLineEdit(QStringLiteral("1"));
	unitNoLable->setBuddy(unitNoEdit);

	valueModeLable = new QLabel(QStringLiteral("����ֵ�ķ�ʽ"));
	specificRadio = new QRadioButton(QStringLiteral("ָ��"));
	randomRadio = new QRadioButton(QStringLiteral("���"));

	connect(specificRadio, SIGNAL(clicked()), this, SLOT(generateValue()));
	connect(randomRadio, SIGNAL(clicked()), this, SLOT(generateValue()));
	specificRadio->setChecked(true);

	QButtonGroup* btnGroup = new QButtonGroup;
	btnGroup->addButton(specificRadio);
	btnGroup->addButton(randomRadio);
	QHBoxLayout* radioLayout = new QHBoxLayout;
	radioLayout->addWidget(specificRadio);
	radioLayout->addWidget(randomRadio);
	
	sendCountLable = new QLabel(QStringLiteral("���ʹ���(0��ʾѭ������)"));
	sendCountEdit = new QLineEdit(QStringLiteral("5"));
	sendCountLable->setBuddy(sendCountEdit);

	// ���񲼾�
	QGridLayout* gridLayout = new QGridLayout();
	gridLayout->addWidget(idLable, 0, 0);
	gridLayout->addWidget(idEdit, 0, 1);
	gridLayout->addWidget(fepNodeLable, 0, 2);
	gridLayout->addWidget(fepNodeEdit, 0, 3);
	gridLayout->addWidget(typeLable, 1, 0);
	gridLayout->addWidget(typeEdit, 1, 1);
	gridLayout->addWidget(unitNoLable, 1, 2);
	gridLayout->addWidget(unitNoEdit, 1, 3);
	gridLayout->addWidget(valueModeLable, 2, 0);
	gridLayout->addLayout(radioLayout, 2, 1);
	gridLayout->addWidget(sendCountLable, 2, 2);
	gridLayout->addWidget(sendCountEdit, 2, 3);

	// ���ݱ��
	QStringList labels;
	for (int i = 0; i < COUNT; ++i)
	{
		labels << QString("%1").arg(i+1);
	}
	dataTable = new QTableWidget;
	dataTable->setColumnCount(COUNT);
	dataTable->setRowCount(COUNT);
	dataTable->setHorizontalHeaderLabels(labels);
	dataTable->setVerticalHeaderLabels(labels);

	// ������ť����
	startBtn = new QPushButton(QStringLiteral("����"));
	cancelBtn = new QPushButton(QStringLiteral("ȡ��"));
	cancelBtn->setEnabled(false);
	closeBtn = new QPushButton(QStringLiteral("�ر�"));

	connect(startBtn, SIGNAL(clicked()), this, SLOT(startProcessData()));
	connect(cancelBtn, SIGNAL(clicked()), this, SLOT(cancelProcessData()));
	connect(closeBtn, SIGNAL(clicked()), this, SLOT(close()));

	QHBoxLayout* btnLayout = new QHBoxLayout;
	btnLayout->addStretch(1);
	btnLayout->addWidget(startBtn);
	btnLayout->addWidget(cancelBtn);
	btnLayout->addWidget(closeBtn);
	btnLayout->addStretch(1);

	// ��ֱ����
	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(gridLayout);
	mainLayout->addWidget(dataTable);
	mainLayout->addLayout(btnLayout);

	setLayout(mainLayout);

	generateValue();
	resize(1100, 600);
	setWindowTitle(getWindowTitle());
}

void ProcessDataDialog::createConnections()
{
	connect(m_timer.data(), SIGNAL(timeout()), this, SLOT(processRandomData()));
}

QString ProcessDataDialog::getWindowTitle() const
{
	QString title = QStringLiteral("��������-");
	switch(dataType)
	{
	case AllDataType:
		title += QStringLiteral("ȫ����-") + getAllDataTypeTitle();
		break;
	case ChangedAnalogType:
		title += QStringLiteral("�仯ң��");
		break;
	case AccumulatorType:
		title += QStringLiteral("���");
		break;
	case UnitStateType:
		title += QStringLiteral("��Ԫ״̬");
		break;
	default:
		title += QStringLiteral("δ֪");
		break;
	}
	return title;
}

QString ProcessDataDialog::getAllDataTypeTitle() const
{
	QString title = QStringLiteral("");
	switch(allDataTypeType)
	{
	case Analog:
		title = QStringLiteral("ң��");
		break;
	case Discrete:
		title = QStringLiteral("ң��");
		break;
	case Accumulator:
		title = QStringLiteral("���");
		break;
	default:
		title = QStringLiteral("δ֪");
		break;
	}
	return title;
}

GenerateValueMode ProcessDataDialog::getValueMode() const
{
	if (specificRadio->isChecked())
	{
		return Specific;
	}
	else if (randomRadio->isChecked())
	{
		return Random;
	}
	
	return UnKnown;
}

void ProcessDataDialog::getDataPacket( SelfDataPacket& packet )
{
	packet.id = idEdit->text().toInt();
	packet.fepNode = fepNodeEdit->text();
	packet.type = dataType;
	packet.unitNo = unitNoEdit->text().toInt();
	packet.analogs.clear();
	packet.discretes.clear();
	packet.accmulators.clear();

	if (dataType == AllDataType)
	{
		if (allDataTypeType == Analog)
		{
			for (int i = 0; i < COUNT; ++i)
			{
				for (int j = 0; j < COUNT; ++j)
				{
					packet.analogs.push_back(i * 10 + j + 1);
					packet.analogs.push_back(dataTable->item(i, j)->text().toDouble());
				}
			}			
		}
		else if (allDataTypeType == Discrete)
		{
			for (int i = 0; i < COUNT; ++i)
			{
				for (int j = 0; j < COUNT; ++j)
				{
					packet.discretes.push_back(i * 10 + j + 1);
					packet.discretes.push_back(dataTable->item(i, j)->text().toInt());
				}
			}			
		}
		else if (allDataTypeType == Accumulator)
		{
			for (int i = 0; i < COUNT; ++i)
			{
				for (int j = 0; j < COUNT; ++j)
				{
					packet.accmulators.push_back(dataTable->item(i, j)->text().toDouble());
				}
			}			
		}
	}
	else
	{

	}
}

void ProcessDataDialog::generateYcValues()
{
	// �������200���ڵ�����
	QList<double> values;
	qsrand(QDateTime::currentDateTime().toTime_t());
	for (int i = 0; i < COUNT; ++i)
	{
		for (int j = 0; j < COUNT; ++j)
		{
			double value = qrand() % 200;
			dataTable->setItem(i, j, new QTableWidgetItem(QString("%1").arg(value)));
		}
	}
}

void ProcessDataDialog::generateYxValues()
{
	// �������0��1������
	QList<int> values;
	qsrand(QDateTime::currentDateTime().toTime_t());
	for (int i = 0; i < COUNT; ++i)
	{
		for (int j = 0; j < COUNT; ++j)
		{
			int value = qrand() % 2;
			dataTable->setItem(i, j, new QTableWidgetItem(QString("%1").arg(value)));
		}
	}
}

void ProcessDataDialog::generateDdValues()
{
	// �������200���ڵ�����
	QList<double> values;
	qsrand(QDateTime::currentDateTime().toTime_t());
	for (int i = 0; i < COUNT; ++i)
	{
		for (int j = 0; j < COUNT; ++j)
		{
			double value = qrand() % 200;
			dataTable->setItem(i, j, new QTableWidgetItem(QString("%1").arg(value)));
		}
	}
}

void ProcessDataDialog::generateValue()
{
	GenerateValueMode mode = getValueMode();

	switch(allDataTypeType)
	{
	case Analog:
		return generateYcValues();
	case Discrete:
		return generateYxValues();
	case Accumulator:
		return generateDdValues();
	default:
		return;
	}
}

void ProcessDataDialog::startProcessData()
{
	startBtn->setEnabled(false);
	cancelBtn->setEnabled(true);

	GenerateValueMode mode = getValueMode();
	if (mode == Specific)
	{
		SelfDataPacket dataPacket;
		getDataPacket(dataPacket);
		emit start(dataPacket);

		startBtn->setEnabled(true);
		cancelBtn->setEnabled(false);
	}
	else if (mode == Random)
	{
		int sendCount = sendCountEdit->text().toInt();
		
		m_processCount = sendCount;
		m_timer->start(2000);
		//if (sendCount == 0)
		//{
		//	while(true)
		//	{
		//		generateValue();
		//		SelfDataPacket dataPacket;
		//		getDataPacket(dataPacket);
		//		emit start(dataPacket);
		//	}
		//}
		//else if (sendCount > 0)
		//{
		//	for (int i = 0; i < sendCount; ++i)
		//	{
		//		generateValue();
		//		SelfDataPacket dataPacket;
		//		getDataPacket(dataPacket);
		//		emit start(dataPacket);

		//		QThread::sleep(1);
		//	}
		//}
	}
}

void ProcessDataDialog::cancelProcessData()
{
	startBtn->setEnabled(true);
	cancelBtn->setEnabled(false);

	if (!m_timer.isNull() && m_timer->isActive())
	{
		m_timer->stop();
	}
}

void ProcessDataDialog::processRandomData()
{
	generateValue();
	SelfDataPacket dataPacket;
	getDataPacket(dataPacket);
	emit start(dataPacket);

	if (m_processCount != 0)
	{
		if(--m_processCount == 0)
		{
			cancelProcessData();
		}
	}

}
