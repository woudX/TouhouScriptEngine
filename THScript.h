#ifndef _H_THSCRIPT
#define _H_THSCRIPT

#include "stdafx.h"
#include "SymbolTable.h"

class THScript
{
public:
	string fileName;			// 脚本文件名
	string touhouScript;		// 脚本类型
	string title;				// 脚本标题
	string text;				// 脚本介绍
	string music;				// 脚本音乐
	string image;				// 脚本贴图
	string background;			// 脚本背景
	string player;				// 玩家数量
	string scriptVersion;		// 脚本版本号

	SymbolTable* top;			// 脚本变量表

	void SetValue(string varStr, string value);

	THScript();
};

#endif // !_H_THSCRIPT
