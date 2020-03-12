
#include "AnalyseFileThread.h"

CAnalyseFileThread::CAnalyseFileThread(const QString& fileName, int timeSpan, QObject* parent)
	: QThread(parent), m_stop(false), m_fileName(fileName), m_timeSpan(timeSpan)
{

}

void CAnalyseFileThread::run()
{
	QFile file(m_fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		outputInfo(QStringLiteral("Դ�ļ���ʧ��"));
		return;
	}

	// ȷ������ļ�
	QFile outputFile(m_fileName + ".filter.log");
	if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
	{
		outputInfo(QStringLiteral("����ļ���ʧ��"));
		return;
	}

	QTextStream inputStream(&file);
	QTextStream outputStream(&outputFile);
	QString line, prevLine;
	QDateTime prevDateTime;
	int count = 0;
	try {
		while (inputStream.readLineInto(&line)) {
			if (m_stop)
			{
				break;
			}
			if (count % 100 == 0)
			{
				outputInfo(QStringLiteral("���ڶ�ȡ�� %1 ������").arg(++count));
			}

			QString strDateTime = line.left(23);
			QDateTime dateTime = QDateTime::fromString(strDateTime, "yyyy-MM-dd hh:mm:ss:zzz");

			if (!prevLine.isEmpty())
			{
				qint64 value = prevDateTime.msecsTo(dateTime);
				if (value > m_timeSpan)
				{
					outputStream << prevLine << "\n" << line << "\n" << value << "ms" << "\n\n";
				}
			}

			prevLine = line;
			prevDateTime = dateTime;
		}
	} catch(...) {

	}

	outputStream.flush();
	file.close();
	outputFile.close();
}
