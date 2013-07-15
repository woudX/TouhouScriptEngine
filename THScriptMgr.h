#ifndef _H_THSCRIPTMGR
#define _H_THSCRIPTMGR

#include "stdafx.h"
#include "THScript.h"

class THScriptMgr
{
public:
	map<string, THScript*> scriptMap;
	THScript* lastScript;					// 保存最后添加的脚本

	THScriptMgr* Instance();
	
	void AddTHScript(THScript* script);					// 添加TH脚本包
	THScript* GetTHScriptByFileName(string fileName);	// 根据脚本文件名获取指定脚本
	THScript* GetTHScriptByTitle(string title);			// 根据脚本题目获取指定脚本

protected:
	THScriptMgr();

private:
	static THScriptMgr* _instance;
};

#endif // !_H_THSCRIPTMGR
