#ifndef OPERATIONINFO_H
#define OPERATIONINFO_H

#include "AmlConst.h"
#include "TableHeader.h"

#include <QtCore/QString>
#include <QtCore/QDateTime>

#pragma execution_character_set("utf-8")

class OperationInfo
{
public:
	OperationInfo(int type = TYPE_AMS, const QString& oper = "", bool res = true, const QString& reas = "")
		: serviceType(type), operation(oper), result(res), reason(reas)
	{}

	QString getContent(int column) const
	{
		switch(column)
		{
		case Header_Operation:
			return getOperation();
		case Header_OperTime:
			return getOperTime();
		case Header_Result:
			return getResult();
		case Header_Reason:
			return getReason();
		default:
			return "";
		}
	}

	void setServiceType(int type)
	{
		serviceType = type;
	}

	QString getServiceType() const
	{
		switch(serviceType)
		{
		case TYPE_AMS:
			return "AMS";
		case TYPE_DATASRV:
			return "���ݷ�����";
		default:
			return "δ֪";
		}
	}

	void setOperation(const QString& oper)
	{
		operation = oper;
	}

	QString getOperation() const
	{
		return operation;
	}

	void setOperTime(const QDateTime& time = QDateTime())
	{
		if (time.isValid())
		{
			operTime = time;
		}
		else
		{
			operTime = QDateTime::currentDateTime();
		}
	}

	QString getOperTime() const
	{
		if (!operTime.isValid())
		{
			return QDateTime::currentDateTime().toString(Qt::SystemLocaleLongDate);
		}
		return operTime.toString(Qt::SystemLocaleLongDate);
	}

	void setResult(bool res)
	{
		result = res;
	}

	QString getResult() const
	{
		return result ? "�ɹ�" : "ʧ��";
	}

	void setReason(const QString& reas)
	{
		reason = reas;
	}

	QString getReason() const
	{
		return reason;
	}

private:
	int			serviceType;	// ����������
	QString		operation;		// ������Ϣ
	QDateTime	operTime;		// ����ʱ��
	bool		result;			// �������
	QString		reason;			// ʧ��ԭ��
};
Q_DECLARE_METATYPE(OperationInfo)

#endif