#ifndef RANDOMOPERATEDB_H
#define RANDOMOPERATEDB_H

#include "fastdb.h"

#include <QtCore/QtCore>

class FastdbManager;

enum OperateMode
{
	InsertMode,
	UpdateMode,
	DeleteMode,
	SelectMode,
	ModeCount
};

class RandomOperateDb
{
public:
	RandomOperateDb();
	~RandomOperateDb();

public:
	void startOperate(OperateMode mode = ModeCount);
	void insertData();
	void updateData();
	void deleteData();
	void selectData();

	QString getOperateInfo() const;
	void	setThreadId(const QString& threadId);
	QString	getThreadId() const;

private:
	int getRandValue();

private:
	FastdbManager*	m_fastdbManager;
	QString m_operInfo;	// ������Ϣ
	QString	m_threadId;	// �߳�Id

	QMutex	m_mutex;
};

#endif