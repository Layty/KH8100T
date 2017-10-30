#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <QtCore/QtCore>

using namespace std;

class CFileHandler
{
public:
	CFileHandler();

public:
	// ���ļ�
	bool openFile(const string& fileName);

	// �ر��ļ�
	void closeFile();

	// ��ȡ�ļ�
	bool readFile(const string& fileName, string& content);


	bool readFileWithFStream(const string& fileName, string& content);
	bool readFileWithQFile(const string& fileName, string& content);
	bool readFileWithQTextStream(const string& fileName, string& content);
	bool readFileWithQDataStream(const string& fileName, string& content);

	// д���ļ�
	bool writeFile(const string& fileName, const string& content);

private:
	QString	getReadFilePath(const string& fileName);
	QString getWriteFilePath(const string& fileName);

};
#endif