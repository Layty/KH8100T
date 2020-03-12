
#include "WriteFastdbRunnable.h"
#include "FastdbTableDefine.h"
#include "logger.h"

void WriteFastdbRunnable::run()
{
	try {
		dbDatabase* db = m_dbManager->getDbDatabase();
		while(!Thread::interrupted()) {
			// ����fastdb����
			if (!db->isAttached()) {
				db->attach();
			}

			// д������
			if (rand() % 2 == 0) {
				m_fastdbHelper.insertFastdbData();
			} else {
				m_fastdbHelper.updateFastdbData();
			}

			// �ر�fastdb����
			db->detach();
			Thread::sleep(200);
		}
	} catch (Interrupted_Exception&) {
		RdbLog(CLogger::Log_INFO, "Exit write thread %d by Interrupted_Exception", id);
	}
}


