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

	vector<string> scriptStream;	// 脚本文件流，被翻译成四元式保存后会被歼灭
	vector<QuadGroup*> scriptGroup;	// 脚本代码库
	SymbolTable* symRoot;		// 脚本变量表

	QuadGroup* _lastGroup;		// 最近一次操作的脚本组
	int _streamIdx;				// 脚本文件留位置

	
	void AddToStream(string str);	// 添加字符串到单词流中
	void SetValue(string varStr, string value);		// 设定脚本参数值
	void TranslateScript();			// 翻译脚本中间码

	string	_NextWord();				// 获得脚本文件流的下一个词
	string	_RetrackWord(int num);		// 退回脚本文件流之前的指定单词数目
	void	_MakeNewQuad(string op, string arg_1, string arg_2, string obj, string lineID);		// 新建一句脚本				
	THScript();
	~THScript();
};

#endif // !_H_THSCRIPT
