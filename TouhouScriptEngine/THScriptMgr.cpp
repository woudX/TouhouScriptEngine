#include "THScriptMgr.h"

THScriptMgr* THScriptMgr::_instance = 0;

THScriptMgr* THScriptMgr::Instance()
{
	if (_instance == 0)
		_instance = new THScriptMgr;

	return _instance;
}

THScriptMgr::THScriptMgr():lastScript(0)
{

}

THScript* THScriptMgr::GetTHScriptByFileName(string fileName)
{
	map<string, THScript*>::iterator itor;

	if ((itor = _scriptMap.find(fileName)) == _scriptMap.end())
		return NULL;
	else
		return itor->second;
}

void THScriptMgr::AddTHScript(THScript* script)
{
	if (script != NULL)
	{
		_scriptMap.insert(make_pair(script->fileName, script));
		lastScript =  script;
	}
}