#ifndef _H_SYMBOL
#define _H_SYMBOL

#include "stdafx.h"

// Symbol的类型type取值
	
#define DOUBLE	0		// 浮点数类型
#define INT		1		// 整数类型
#define STRING	2		// 字符串类型
#define BOOL	3		// 布尔类型
#define VOID	4		// 无类型

class Symbol
{
public:
	string name;		// 变量名
	int type;			// 变量类型
	int kind;			// 变量种类
	double value;		// 变量值

	Symbol();
	Symbol(string name, int type, int kind);

	~Symbol();
};

#endif // !_H_SYMBOL
