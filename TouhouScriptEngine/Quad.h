#ifndef _H_QUAD
#define _H_QUAD

#include "stdafx.h"

class Quad 
{
public:
	string op, arg1, arg2, obj;		// 四元式的四个部分
	string lineID;					// 四元式对应的跳转行号

	Quad();
	Quad(string v_op, string v_arg1, string v_arg2, string v_obj);
};

#endif // !_H_QUAD
