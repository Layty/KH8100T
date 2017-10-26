#ifndef SQLEXEC_H
#define SQLEXEC_H

#include <QtSql/QtSql>
#include <QtCore/QtCore>

class CSqlExec;

class CSqlExecInstance
{
public:
	static QSharedPointer<CSqlExec>	getSqlExecInstance();

private:
	static QSharedPointer<CSqlExec>	sqlExecInstance;
};

class CSqlExec
{
friend class CSqlExecInstance;

private:
	CSqlExec();

public:
	// �����ݿ�
	bool openDb();

	// ִ�в�ѯ����
	bool exec(QSqlQuery& query, const QString& sql);

	// ��ȡ������Ϣ
	QString	getError();

private:
	QSqlDatabase	m_database;

	QMutex			m_mutex;
	QString			m_databaseName;
	QString			m_userName;
	QString			m_password;
	QString			m_hostname;
	int				m_port;
	QString			m_error;
};
#endif