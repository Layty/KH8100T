#ifndef TRANSFERFILE_COMMON_H
#define TRANSFERFILE_COMMON_H

#include <QtCore/QString>

// �ļ����䷽ʽ
enum TransferMode
{
	Transfer_Ice,
	Transfer_IceStorm
};

// �ļ���д��ʽ
enum FileOperMode
{
	FileOper_Text,
	FileOper_Binary
};

// �ļ������ӿ�
enum FileOperInterface
{
	FileInter_C,
	FileInter_CPlusPlus
};

// ���������������������
extern const QString serverAdapterIdentify;

// �������ͻ�������������
extern const QString clientAdapterIdentify;

// �������ͻ��˴���ӿ�����
extern const QString clientProxyIdentify;

// ÿ�δ���Ļ����С
#define TransferBufferSize	4096

#endif