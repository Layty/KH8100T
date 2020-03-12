
#include "FastdbManager.h"
#include "logger.h"
#include "ReadFastdbRunnable.h"
#include "ReadWriteFastdbRunnable.h"
#include "WriteFastdbRunnable.h"
#include "zthread/Thread.h"
#include "zthread/ThreadedExecutor.h"

#include <iostream>
using namespace ZThread;
using namespace std;

// ��ʼ��log4cplus��־
log4cplus::Logger CLogger::my_logger = CLogger::init("./fastdbConcurrency.log4");

int main() {
	srand(time(NULL));

	RdbLog(CLogger::Log_INFO, "����������...");
	FastdbManager* dbManager = FastdbManagerInstance::getFastdbManagerInstance();
	
	// ��ʵʱ��
	if (!dbManager || !dbManager->openDatabase("simulated"))
	{
		RdbLog(CLogger::Log_INFO, "��ʵʱ��ʧ��...");
		return -1;
	}

	cout << "Press <Enter> to quit" << endl;

	CountedPtr<FastdbCollection> collection(new FastdbCollection);
	ThreadedExecutor executor;
	// ����5����ȡ�߳�
	for (int i = 0; i < 5; ++i)
	{
		executor.execute(new ReadFastdbRunnable(i, dbManager));
	}
	// ����10���޸��߳�
	for (int i = 0; i < 0; ++i)
	{
		executor.execute(new WriteFastdbRunnable(i, collection, dbManager));
	}

	// ����10����ȡ�޸��߳�
	for (int i = 0; i < 0; ++i)
	{
		executor.execute(new ReadWriteFastdbRunnable(i, collection, dbManager));
	}

	cin.get();
	executor.interrupt();
	Thread::sleep(10000);

	// �ر�ʵʱ��
	if (dbManager && dbManager->closeDatabase())
	{
		RdbLog(CLogger::Log_INFO, "�ѹر�ʵʱ��...");
	}

	RdbLog(CLogger::Log_INFO, "�������˳�...");
	return 0;
}