#ifndef _H_FILEMANAGER
#define _H_FILEMANAGER

#include "stdafx.h"

class FileManager {
public:
	FileManager* Instance();
	vector<string> codeFile;
	ifstream inFile;
	ofstream outFile;

	void ReadCodeFile(string fileName);		// 读取目标文件
	char ReadCh();							// 读取一个字符
	void Retrack(int t);					// 倒读t个字符
	int line,row;

	~FileManager();
protected:
	FileManager();

private:
	static FileManager* _instance;
};

#endif