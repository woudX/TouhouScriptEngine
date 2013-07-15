#ifndef _H_FILEMANAGER
#define _H_FILEMANAGER

#include "stdafx.h"

class FileMgr {
public:
	vector<string> codeFile;
	string fileName;			// 脚本文件名
	ifstream inFile;
	ofstream outFile;

	FileMgr* Instance();
	void ReadCodeFile(string fileName);		// 读取目标文件
	char ReadCh();							// 读取一个字符
	void Retrack(int t);					// 倒读t个字符
	int line,row;

	~FileMgr();
protected:
	FileMgr();

private:
	static FileMgr* _instance;
};

#endif