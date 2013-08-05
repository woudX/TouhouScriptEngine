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

	SymbolTable* _top;			// 当前分析时的变量层

	THScript();
	THScript(const THScript& rhs);
	THScript& operator= (const THScript& rhs);
	~THScript();

	void	SetValue(string varStr, string value);		// 设定脚本参数值
	void	Run();										// 脚本执行一次
	void	_clearNotGlobalSymTable(SymbolTable* symTable);					// 清空所有非全局变量的值
	double	_getVal(string arg);						// 获取一个参数实际的值(这意味着他可能是一个变量，或者就是一个常数)
	int		_goto(int scriptGroupId, string lineId);						// 跳转到指定行数继续执行
	int		_iffalse(string l_str, string cmp_str, string r_str);			// 返回iffalse的判断条件
};
#endif // !_H_THSCRIPT
