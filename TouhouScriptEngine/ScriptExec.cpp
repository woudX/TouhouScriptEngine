#include "THScript.h"
#include "ScriptExec.h"
#include "stdafx.h"

class ScriptExec_Impl
{
public:
	ScriptExec_Impl(THScript* script):_script(script)
	{
		_initialize();
	}

private:
	THScript* const	_script;		// 所引用的脚本——不可改变
	SymbolTable*	_symRoot;	// 执行器所需的变量表 

	// 初始化Exec
	void _initialize()
	{
		_symRoot = new SymbolTable(*_script->symRoot);	// 还没写复制构造= = 这个··· 我觉得如果是深度copy的话还是Clone()吧
	}
};

inline void Run()
{

}

ScriptExec::ScriptExec(THScript* script)
{
	_pImpl = new ScriptExec_Impl(script);
}

ScriptExec::~ScriptExec()
{
	delete _pImpl;
	_pImpl = NULL;
}