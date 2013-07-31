#ifndef _H_THSCRIPTFULL
#define _H_THSCRIPTFULL

#include "THScript.h"

class THScriptFull : public THScript
{
public:
	vector<string> scriptStream;	// 脚本文件流，脚本四元式形成后便没有意义
	int _streamIdx;				// 脚本文件流位置
	QuadGroup* _lastGroup;		// 最近一次操作的脚本组，请勿释放
	
	THScriptFull();
	THScriptFull(const THScriptFull& rhs);
	THScriptFull& operator=(const THScriptFull& rhs);
	~THScriptFull();

	string	_NextWord();				// 获得脚本文件流的下一个词
	string	_RetrackWord(int num);		// 退回脚本文件流之前的指定单词数目
	void	TranslateScript();			// 翻译脚本中间码
	void	AddToStream(string str);	// 添加字符串到单词流中
	void	_MakeNewQuad(string op, string arg_1, string arg_2, string obj, string lineID);		// 新建一句脚本				
};

#endif // !_H_THSCRIPTFULL
