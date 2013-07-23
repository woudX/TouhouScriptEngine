#include "Symbol.h"

Symbol::Symbol():name("")
{

}

Symbol::Symbol(string name, int type, int kind):name(name),type(type),kind(kind)
{
	
}

Symbol::Symbol(string name, int type, int kind, double value):name(name),type(type),kind(kind),value(value)
{

}

Id* Symbol::ToID()
{
	// 目前只支持Double类型
	Id* idTemp = new Id(new Word(name, IDEN), Type::Double, Type::Double->width);

	return idTemp;
}


Symbol::~Symbol()
{

}