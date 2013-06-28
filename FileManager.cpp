#include "FileManager.h"

FileManager* FileManager::_instance = 0;

FileManager* FileManager::Instance()
{
	if (_instance == 0)
		_instance = new FileManager;

	return _instance;
}

FileManager::FileManager():line(0),row(0)
{

}

void FileManager::ReadCodeFile(string fileName)
{
	inFile.open(fileName);

	if (!inFile)
	{
		printf("open file error");
	}

	string tempCode;

	while (getline(inFile, tempCode))
	{
		codeFile.push_back(tempCode);
	}

	inFile.clear();
	inFile.close();
}

char FileManager::ReadCh()
{
	if (line >= codeFile.size())	// 模拟文件流结尾
	{
		return EOF;
	}

	if (row >= codeFile[line].length())		// 模拟读取到行尾
	{
		row = 0;
		++line;
		return '\n';
	}

	char ch = codeFile[line][row];
	row++;
	return ch;
}

void FileManager::Retrack(int t)
{
	int num = t;

	while (num != 0)
	{
		num--;
		row--;
		if (row < 0)
		{
			line--;
			row = codeFile[line].length();
		}
	}
}

FileManager::~FileManager()
{

}