#ifndef _H_OBJECT
#define _H_OBJECT

#include "THScriptFull.h"

class Object
{
public:
	THScript* script;	// Object执行对应的脚本程序

	Object();
	Object(THScriptFull* v_script);

};

#endif // !_H_OBJECT
