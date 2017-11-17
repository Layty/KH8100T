#ifndef PROCESSDATADLG_H
#define PROCESSDATADLG_H

#include "fepdata.h"

#include <QtWidgets/QDialog>
#include <QtCore/QtCore>
#include <vector>
using namespace std;

class QLabel;
class QLineEdit;
class QRadioButton;
class QTableWidget;
class QPushButton;

enum DataType {
	AllDataType,        // 0-ȫ����
	ChangedAnalogType,  // 1-�仯ң��
	AccumulatorType,    // 2-���
	UnitStateType       // 3-�ն�״̬
};

enum AllDataTypeType
{
	Analog,
	Discrete,
	Accumulator
};

enum GenerateValueMode
{
	Random,
	Specific,
	Timed,
	UnKnown
};

class SelfDataPacket : public QObject
{
	Q_OBJECT

public:
	SelfDataPacket(QObject* parent = 0)
		: QObject(parent)
	{}

	SelfDataPacket(const SelfDataPacket& packet)
	{
		this->id = packet.id;
		this->fepNode = packet.fepNode;
		this->type = packet.type;
		this->unitNo = packet.unitNo;
		this->units.assign(packet.units.begin(), packet.units.end());
		this->analogs.assign(packet.analogs.begin(), packet.analogs.end());
		this->discretes.assign(packet.discretes.begin(), packet.discretes.end());
		this->accmulators.assign(packet.accmulators.begin(), packet.accmulators.end());
	}

public:
	int			id;       // ���ݰ�ID
	QString     fepNode;  // ����ǰ�û�    
	DataType    type;     // ��������
	short       unitNo;   // ��Ԫ��
	::FepData::UnitSeq             units;           // �ն�״̬
	vector<double>	analogs;         // ң��
	vector<int>		discretes;       // ң��
	vector<double>	accmulators;     // ���
};

class ProcessDataDialog : public QDialog
{
	Q_OBJECT

public:
	ProcessDataDialog(DataType type, AllDataTypeType alltype, QWidget* parent = 0);

private:
	void createWidgets();
	void createConnections();
	QString getWindowTitle() const;
	QString getAllDataTypeTitle() const;
	GenerateValueMode	getValueMode() const;
	void	getDataPacket(SelfDataPacket& packet);
	void generateYcValues();
	void generateYxValues();
	void generateDdValues();

signals:
	void start(SelfDataPacket);

private slots:
	void generateValue();
	void startProcessData();
	void cancelProcessData();
	void processRandomData();

private:
	DataType	dataType;
	AllDataTypeType	allDataTypeType;
	
	QLabel*		idLable;		// ���ݰ�id
	QLineEdit*	idEdit;
	QLabel*		fepNodeLable;	// ǰ�û�
	QLineEdit*	fepNodeEdit;
	QLabel*		typeLable;		// ��������
	QLineEdit*	typeEdit;
	QLabel*		unitNoLable;	// ��Ԫ���
	QLineEdit*	unitNoEdit;

	QLabel*		valueModeLable;	// ����ֵ�ķ�ʽ
	QRadioButton*	specificRadio;
	QRadioButton*	randomRadio;
	QRadioButton*	timerRadio;

	QLabel*		sendCountLable;	// ���ʹ���
	QLineEdit*	sendCountEdit;

	QTableWidget*	dataTable;	// ���ݱ��

	QPushButton*	startBtn;
	QPushButton*	cancelBtn;
	QPushButton*	closeBtn;

	QSharedPointer<QTimer>	m_timer;
	int				m_processCount;
};

#endif