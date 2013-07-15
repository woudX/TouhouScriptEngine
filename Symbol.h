#ifndef _H_SYMBOL
#define _H_SYMBOL

#include "stdafx.h"

// Symbol的类型type取值
	
#define TYPE_DOUBLE	0		// 浮点数类型
#define TYPE_INT	1		// 整数类型
#define TYPE_STRING	2		// 字符串类型
#define TYPE_BOOL	3		// 布尔类型
#define TYPE_VOID	4		// 无类型

// Symbol的种类kind取值
#define KIND_CONST	20		//常量
#define KIND_VAR	21		//变量
#define KIND_TVAR	22		//临时变量
#define	KIND_PROC	23		//过程头部
#define KIND_FUNC	24		//函数头部

class Symbol
{
public:
	string name;		// 变量名
	int type;			// 变量类型
	int kind;			// 变量种类
	double value;		// 变量值

	Symbol();
	Symbol(string name, int type, int kind);
	Symbol(string name, int type, int kind, double value);
	~Symbol();
};

#endif // !_H_SYMBOL
