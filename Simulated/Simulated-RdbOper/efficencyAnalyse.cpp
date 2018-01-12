
#include <QtWidgets/QtWidgets>

#include "efficencyAnalyse.h"
#include "logger.h"

EfficiencyAnalyseThread::EfficiencyAnalyseThread( const QString& fileName, QObject* parent )
	: QThread(parent), _fileName(fileName)
{

}

// ��ʼ�����ļ�
void EfficiencyAnalyseThread::startAnalyse()
{
	QFile file(_fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(0, QStringLiteral("���ļ�"), 
							QStringLiteral("���ļ�ʧ��: %1").arg(file.errorString()));
		return;
	}

	QTextStream textStream(&file);
	QString line;
	int lineNumber = 0;			// �ļ���������
	QDateTime prevDateTime;
	QDateTime nextDateTime;

	SecondData  secondData;
	MinuteData	minuteData;
	HourData	hourData;
	while(textStream.readLineInto(&line))
	{
		// ��һ��ʱ��ת��ʱ��ֵ
		if (lineNumber == 0)
		{
			// ��ȡ��һ�е�ʱ��
			if (!transferStringToDateTime(line, prevDateTime))
			{
				continue;
			}
			secondData.second = prevDateTime.time().second();
			secondData.count++;

			minuteData.minute = prevDateTime.time().minute();
			hourData.hour = prevDateTime.time().hour();

			_startDateTime = prevDateTime;
			++lineNumber;
		}
		else
		{
			// ��ȡ��ǰ�е�ʱ��
			if (!transferStringToDateTime(line, nextDateTime))
			{
				continue;
			}

			if (prevDateTime.time().second() == nextDateTime.time().second())
			{
			}
			else if (prevDateTime.time().minute() == nextDateTime.time().minute())
			{
				minuteData.secondDatas.push_back(secondData);
				secondData.clear();
			}
			else if (prevDateTime.time().hour() == nextDateTime.time().hour())
			{
				minuteData.secondDatas.push_back(secondData);
				secondData.clear();
			
				hourData.minuteDatas.push_back(minuteData);
				minuteData.clear();
				minuteData.minute = nextDateTime.time().minute();
			}
			else
			{
				minuteData.secondDatas.push_back(secondData);
				secondData.clear();

				hourData.minuteDatas.push_back(minuteData);
				minuteData.clear();

				_hourDatas.push_back(hourData);
				hourData.clear();

				minuteData.minute = nextDateTime.time().minute();
				hourData.hour = nextDateTime.time().hour();
			}

			secondData.second = nextDateTime.time().second();
			secondData.count++;

			prevDateTime = nextDateTime;
			++lineNumber;
		}
	}

	minuteData.secondDatas.push_back(secondData);
	hourData.minuteDatas.push_back(minuteData);
	_hourDatas.push_back(hourData);

	_endDateTime = nextDateTime;

	QString analyseInfo;
	generateAnalyseInfo(analyseInfo);
	outputAnalyseInfo(analyseInfo);

	file.close();
}

void EfficiencyAnalyseThread::run()
{
	startAnalyse();
}

// ת���ַ���ΪQDateTime
bool EfficiencyAnalyseThread::transferStringToDateTime( const QString& text, QDateTime& dateTime )
{
	QStringList textes = text.split(" ");
	if (textes.size() < 2)
	{
		return false;
	}

	QString date = textes[0];
	QStringList dateList = date.split('-');
	if (dateList.size() != 3)
	{
		return false;
	}
	int year = dateList[0].toInt();
	int month = dateList[1].toInt();
	int day = dateList[2].toInt();
	QDate qDate(year, month, day);

	QString time = textes[1];
	QStringList timeList = time.split(':');
	if (timeList.size() != 3)
	{
		return false;
	}
	int hour = timeList[0].toInt();
	int minute = timeList[1].toInt();
	int second = timeList[2].toInt();
	QTime qTime(hour, minute, second);

	dateTime = QDateTime(qDate, qTime);
	return true;
}

// ����������Ϣ
void EfficiencyAnalyseThread::generateAnalyseInfo(QString& analyseInfo)
{
	int executeSecond;
	QString executeTime;
	computeExecuteTime(executeSecond, executeTime);

	QString executeEfficiency;
	computeExecuteEfficiency(executeEfficiency);

	analyseInfo += QStringLiteral("������: %1, ����ʱ��: %2, ƽ��Ч��: %3")
			.arg(computeDataCount())
			.arg(executeTime)
			.arg(executeEfficiency);

	foreach(const HourData& data, _hourDatas)
	{
		analyseInfo += "\n";
		analyseInfo += QStringLiteral("Сʱ: %1, ִ�д���: %2, ƽ��ִ�д���: %3��/��")
			.arg(data.hour).arg(data.count()).arg(data.average());

		foreach(const MinuteData& minuteData, data.minuteDatas)
		{
			analyseInfo += "\n\t";
			analyseInfo += QStringLiteral("����: %1, ִ�д���: %2, ƽ��ִ�д���: %3��/��")
				.arg(minuteData.minute).arg(minuteData.count()).arg(minuteData.average());

			foreach(const SecondData& secondData, minuteData.secondDatas)
			{
				analyseInfo += "\n\t\t";
				analyseInfo += QStringLiteral("��: %1, ִ�д���: %2, ƽ��ִ�д���: %3��/��")
					.arg(secondData.second).arg(secondData.sum()).arg(secondData.average());
			}
		}
	}

}

void EfficiencyAnalyseThread::outputAnalyseInfo(const QString& analyseInfo)
{
	QFile file("./log/efficencyLog.log");
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		return;
	}

	QTextStream textStream(&file);
	textStream << analyseInfo;

	file.close();
}

// �����¼����
long EfficiencyAnalyseThread::computeDataCount()
{
	long sum = 0;
	foreach(const HourData& hourData, _hourDatas)
	{
		sum += hourData.count();
	}
	return sum;
}

// ��������ʱ��
void EfficiencyAnalyseThread::computeExecuteTime(int& executeSec,  QString& executeTime )
{
	executeSec = _startDateTime.secsTo(_endDateTime);
	int executeHour = executeSec / 3600;
	int executeMinute = (executeSec % 3600) / 60;
	int executeSecond = (executeSec % 3600) % 60;
	executeTime = QStringLiteral("%1Сʱ %2�� %3��").arg(executeHour).arg(executeMinute).arg(executeSecond);
}

// ����ƽ��Ч��
void EfficiencyAnalyseThread::computeExecuteEfficiency( QString& executeEfficiency )
{
	int executeSecond;
	QString executeTime;
	computeExecuteTime(executeSecond, executeTime);

	if (executeSecond > 0)
	{
		executeEfficiency = QStringLiteral("%1 ��/��").arg(computeDataCount() / executeSecond);
	}
	else
	{
		executeEfficiency = QStringLiteral("&&& ��/��");
	}
}
