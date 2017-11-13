#include "RdbAlarmDataI.h"
#include "textelement.h"
#include "workstationserverthread.h"

#include <QtCore/QtCore>

string	getRdbWarningLevel(RdbWarningData::RdbWarningLevel value)
{
	switch(value)
	{
	case RdbWarningData::Critical:
		return "����";
	case RdbWarningData::Major:
		return "��Ҫ";
	case RdbWarningData::Minor:
		return "�е�";
	case RdbWarningData::Info:
		return "һ��";
	default:
		return "δ֪";
	}
}

string	getRdbWarningType(RdbWarningData::RdbWarningType value)
{
	switch(value)
	{
	case RdbWarningData::LimitEvent:
		return "ң��Խ��";
	case RdbWarningData::SoeEvent:
		return "SOE����";
	case RdbWarningData::YxEvent:
		return "ң�ű�λ";
	case RdbWarningData::UnitEvent:
		return "�ն�״̬";
	case RdbWarningData::SysEvent:
		return "ϵͳ����";
	case RdbWarningData::OperEvent:
		return "��������";
	case RdbWarningData::RelayEvent:
		return "��������";
	case RdbWarningData::FaultEvent:
		return "��������";
	case RdbWarningData::FaEvent:
		return "FA�澯";
	case RdbWarningData::WaveEvent:
		return "¼������";
	case RdbWarningData::GraphEvent:
		return "��������";
	default:
		return "δ֪";
	}
}

RdbAlarmDataI::RdbAlarmDataI( WorkStationServerThread* threadPtr )
	: m_threadPtr(threadPtr)
{

}

void RdbAlarmDataI::SendAlarmData( const ::RdbWarningData::WarningInfoSeq& seq, const ::Ice::Current& /* = ::Ice::Current */ )
{
	if (!m_threadPtr)
	{
		return;
	}
	if (!seq.empty())
	{
		for (size_t i = 0; i < seq.size(); ++i)
		{
			RdbWarningData::WarningInfo info = seq.at(i);
			TextElement parent("�յ� �澯����", ConvertTypeToString<size_t>().convertToString(seq.size()));
			parent.insertChild(new TextElement("��ʶ��", info.id));
			parent.insertChild(new TextElement("�澯����", getRdbWarningType(info.warnType)));
			IceUtil::Time time = IceUtil::Time::milliSeconds(info.timeStamp);
			parent.insertChild(new TextElement("�澯ʱ��", time.toString("%Y-%m-%d %H:%M:%S")));
			parent.insertChild(new TextElement("�澯�ȼ�", getRdbWarningLevel(info.warningLevel)));
			parent.insertChild(new TextElement("�澯�ȼ�", getRdbWarningLevel(info.warningLevel)));
			parent.insertChild(new TextElement("�澯Դ", info.warnSource));
			parent.insertChild(new TextElement("�澯��������", ConvertTypeToString<int>().convertToString(info.columnNum)));

			string content;
			for (size_t j = 0; j < info.contents.size(); ++j)
			{
				content += info.contents.at(j) + "\t";
			}
			parent.insertChild(new TextElement("�澯����", content));

			QString text = QString().fromStdString(parent.toString());
			m_threadPtr->outputOperationData(text);
		}
	}
}
