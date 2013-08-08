#ifndef _H_SCRIPTEXEC
#define _H_SCRIPTEXEC

class ScriptExec_Impl;

class ScriptExec
{
public:
	ScriptExec(THScript* script);
	~ScriptExec();

	void Run();
private:	
	ScriptExec_Impl *_pImpl;
};

#endif // !_H_SCRIPTEXEC
