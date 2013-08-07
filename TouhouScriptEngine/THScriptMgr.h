#ifndef _H_THSCRIPTMGR
#define _H_THSCRIPTMGR

#include "stdafx.h"
#include "THScript.h"
#include "ScriptTrans.h"

class THScriptMgr
{
public:
	THScript* lastScript;					// 保存最后添加的脚本
	Translator* lastTranslator;				// 保存最后添加的翻译器	
	THScriptMgr* Instance();
	
	void AddTHScript(THScript* script);					// 添加TH脚本文件
	THScript* GetTHScriptByFileName(string fileName);	// 根据脚本文件名获取指定脚本

protected:
	THScriptMgr();

private:
	map<string, THScript*> _scriptMap;
	static THScriptMgr* _instance;
};

#endif // !_H_THSCRIPTMGR
