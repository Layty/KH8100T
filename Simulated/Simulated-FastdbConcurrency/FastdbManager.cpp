
#include "FastdbManager.h"

FastdbManager* FastdbManagerInstance::getFastdbManagerInstance()
{
	if (m_fastdbManager)
	{
		return m_fastdbManager;
	}

	m_fastdbManager = new FastdbManager();
	return m_fastdbManager;
}

void FastdbManagerInstance::releaseFastdbManagerInstance()
{
	if (m_fastdbManager)
	{
		delete m_fastdbManager;
		m_fastdbManager = NULL;
	}
}

FastdbManager*	FastdbManagerInstance::m_fastdbManager = NULL;

FastdbManager::FastdbManager()
	: m_bSetTransactionLogger(false)
{

}

FastdbManager::~FastdbManager()
{

}

bool FastdbManager::openDatabase(const string& dbName)
{
	if (m_db.isOpen())
	{
		return true;
	}

	if(!m_db.open(dbName.c_str()))
	{
		return false;
	}
	m_dbName = dbName;

	return true;
}

bool FastdbManager::reopenDatabase(const string& dbName)
{
	if (m_db.isOpen())
	{
		m_db.close();
	}

	if(!m_db.open(dbName.c_str()))
	{
		return false;
	}

	return true;
}

bool FastdbManager::closeDatabase()
{
	if (!m_db.isOpen())
	{
		return true;
	}

	m_db.close();

	return true;
}

void FastdbManager::setTransactionLogger( dbTransactionLogger* logger )
{
	m_db.setTransactionLogger(logger);

	m_bSetTransactionLogger = logger != NULL;
}

void FastdbManager::setTransactionLogger(const string& path, int flags, bool crc)
{
	openDatabase(m_dbName);

	closeTransactionLogger();

	if (!openTransactionLogger(path.c_str(), flags, crc))
	{
		setTransactionLogger(NULL);
		return;
	}

	setTransactionLogger(&m_tl);
}

bool FastdbManager::openTransactionLogger( const string& path, int flags /*= dbFile::no_sync*/, bool crc /*= true*/ )
{
	return m_tl.open(path.c_str(), flags, crc);
}

bool FastdbManager::closeTransactionLogger()
{
	if (hasSetTransactionLogger())
	{
		m_tl.close();
	}

	return true;
}

bool FastdbManager::restoreDatabase( const string& logger )
{
	// ͨ��������־�ָ�ʵʱ��ʱ������ر�ʵʱ�⣬�����´򿪣����ܽ��к����ָ�����
	if(!openDatabase(m_dbName))
	{
		return false;
	}

	if (!openTransactionLogger(logger, dbFile::read_only))
	{
		return false;
	}

	size_t n;
	dbFileTransactionLogger::RestoreStatus status = m_tl.restore(m_db, n);
	if (status == dbFileTransactionLogger::rsOK)
	{
		m_tl.close();
		return true;
	}
	else
	{
		m_tl.rollback();
		return false;
	}
}

void FastdbManager::commit()
{	
	try
	{
		m_db.commit();
	}
	catch (const dbException&)
	{
	}
}

bool FastdbManager::hasSetTransactionLogger()
{
	return m_bSetTransactionLogger;
}

dbDatabase* FastdbManager::getDbDatabase()
{
	if(!openDatabase(m_dbName))
	{
		return NULL;
	}

	return &m_db;
}

dbFileTransactionLogger* FastdbManager::getDbFileTransactionLogger()
{
	return &m_tl;
}

string FastdbManager::getRestoreStatus( dbFileTransactionLogger::RestoreStatus status )
{
	switch(status)
	{
	case dbFileTransactionLogger::rsOK:
		return "rsOK";
	case dbFileTransactionLogger::rsCRCMismatch:
		return "rsCRCMismatch";
	case dbFileTransactionLogger::rsReadFailed:
		return "rsReadFailed";
	case dbFileTransactionLogger::rsTableNotFound:
		return "rsTableNotFound";
	case  dbFileTransactionLogger::rsOIDMismatch:
		return "rsOIDMismatch";
	default:
		return "Unknown";
	}
}
