
#include "ReadFastdbRunnable.h"
#include "logger.h"
#include "FastdbManager.h"

void ReadFastdbRunnable::run() {
	try {
		dbDatabase* db = m_dbManager->getDbDatabase();
		while(!Thread::interrupted()) {
			// ����fastdb����
			if (!db->isAttached())
			{
				db->attach();
			}

			// ��ѯ����
			m_fastdbHelper.selectFastdbData();

			// �ر�fastdb����
			db->detach();
			Thread::sleep(200);
		}
	} catch(Interrupted_Exception&) {
		RdbLog(CLogger::Log_INFO, "Exit read thread %d by Interrupted_Exception", id);
	}
}

