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


Symbol::~Symbol()
{

}