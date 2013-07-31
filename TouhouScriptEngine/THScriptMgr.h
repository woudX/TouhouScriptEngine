#ifndef _H_THSCRIPTMGR
#define _H_THSCRIPTMGR

#include "stdafx.h"
#include "THScriptFull.h"

class THScriptMgr
{
public:
	map<string, THScriptFull*> scriptMap;
	THScriptFull* lastScript;					// 保存最后添加的脚本

	THScriptMgr* Instance();
	
	void AddTHScript(THScriptFull* script);					// 添加TH脚本包
	THScriptFull* GetTHScriptByFileName(string fileName);	// 根据脚本文件名获取指定脚本
	THScriptFull* GetTHScriptByTitle(string title);			// 根据脚本题目获取指定脚本

protected:
	THScriptMgr();

private:
	static THScriptMgr* _instance;
};

#endif // !_H_THSCRIPTMGR
