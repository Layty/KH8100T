
#include <stdio.h>

#include "transferFileByCThread.h"
#include "transferFileCommon.h"
#include "transferFileNew.h"
#include "transferfileserver.h"

TransferFileByCThread::TransferFileByCThread(TransferFileServer* frame,  const QString& filePath, QObject* parent /*= 0*/ )
	: QThread(parent), _frame(frame), _filePath(filePath)
{

}

void TransferFileByCThread::run()
{
	// ��ȡ�����ļ���Ice����
	TransferFileSpace::TransferFilePrx transferFilePrx = 0;
	if (_frame->getTransferMode() == Transfer_Ice)
	{
		transferFilePrx = _frame->getTransferFilePrx();
	}
	else
	{
		transferFilePrx = _frame->getTransferFilePublisher();
	}
	if (transferFilePrx == 0)
	{
		emit emitExecuteInfo(QStringLiteral("��ȡ�����ļ��ӿ�ʧ��: ����ӿ�Ϊ��"));
		return;
	}

	// ���ļ�
	FILE* inFile = NULL;
	if ((inFile = fopen(_filePath.toLatin1(), "r+b")) == NULL)
	{
		emit emitExecuteInfo(QStringLiteral("���ļ� %1 ʧ��").arg(_filePath));
		return;
	}

	try
	{
		// ��ȡ�ļ����ݲ�����
		char buffer[TransferBufferSize] = { 0 };
		int count = 0;
		QString fileName = _filePath.right(_filePath.length() - _filePath.lastIndexOf('/') - 1);
		while((count = fread(buffer, sizeof(char), TransferBufferSize, inFile)) > 0)
		{
			TransferFileSpace::Bytes fileDatas;
			fileDatas.resize(count);
			for (int i = 0; i < count; ++i)
			{
				fileDatas[i] = buffer[i];
			}
			transferFilePrx->sendFile(fileName.toStdString(), fileDatas);
		}

		if (count < 0)
		{
			emit emitExecuteInfo(QStringLiteral("�ļ� %1 ����ʧ��: ��ȡ�ļ�ʱ���ʹ���").arg(_filePath));
		}
		else
		{
			emit emitExecuteInfo(QStringLiteral("�ļ� %1 ���ͳɹ�").arg(_filePath));
		}
	}
	catch(const Ice::Exception& ex)
	{
		emit emitExecuteInfo(QStringLiteral("�ļ� %1 ����ʧ��: %2").arg(_filePath).arg(ex.what()));
	}	

	// �ر��ļ�
	fclose(inFile);
}
