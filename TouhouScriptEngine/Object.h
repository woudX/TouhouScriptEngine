#ifndef _H_OBJECT
#define _H_OBJECT

#include "THScript.h"

class Object
{
public:
	THScript* script;	// Object执行对应的脚本程序

	Object();
	Object(THScript* v_script);

};

#endif // !_H_OBJECT
