#include "ReadWriteFastdbRunnable.h"
#include "FastdbTableDefine.h"
#include "logger.h"

void ReadWriteFastdbRunnable::run()
{
	try {
		dbDatabase* db = m_dbManager->getDbDatabase();
		while(!Thread::interrupted()) {
			// ����fastdb����
			if (!db->isAttached()) {
				db->attach();
			}

			// д������
			int value = rand() % 3;
			if (value == 0) {
				m_fastdbHelper.insertFastdbData();
			} else if(value == 1) {
				m_fastdbHelper.updateFastdbData();
			} else {
				m_fastdbHelper.selectFastdbData();
			}

			// �ر�fastdb����
			db->detach();
			Thread::sleep(200);
		}
	} catch (Interrupted_Exception&) {
		RdbLog(CLogger::Log_INFO, "Exit read-write thread %d by Interrupted_Exception", id);
	}
}
