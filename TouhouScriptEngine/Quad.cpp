#include "Quad.h"

Quad::Quad():op(""), arg1(""), arg2(""), obj(""),lineID("")
{

}

Quad::Quad(string v_op, string v_arg1, string v_arg2, string v_obj)
	:op(v_op),arg1(v_arg1),arg2(v_arg2),obj(v_obj)
{

}