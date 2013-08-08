#ifndef _H_THSCRIPT
#define _H_THSCRIPT

#include "stdafx.h"
#include "SymbolTable.h"
#include "QuadGroup.h"

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

	vector<QuadGroup*>	scriptGroup;	// 脚本代码库
	SymbolTable*		symRoot;		// 脚本变量表

	THScript();
	THScript(const THScript& rhs);
	THScript& operator= (const THScript& rhs);
	~THScript();

	void SetValue(string varStr, string value);		// 设定脚本参数值
	
};
#endif // !_H_THSCRIPT
