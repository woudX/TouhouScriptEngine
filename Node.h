#ifndef _H_NODE
#define _H_NODE

#include "stdafx.h"
#include "Lexer.h"

/// 万物之源——根节点
//////////////////////////////////////////////////////////////////////////

class Node {
public:
	int lexline;
	static int labels;
	
	Node();
	Node(int l);
	void error(string s);
	int newlabel();

	~Node();
};

/// 表达式代码
//////////////////////////////////////////////////////////////////////////

class Expr : public Node {
public:
	Token* op;
	Type* type;

	Expr();
	Expr(Token* token, Type* type);

	virtual Expr* gen();
	virtual Expr* reduce();
	virtual void jumping(int t, int f);
	void emitjumps(string test, int t, int f);
	virtual string ToString();

	~Expr();
};

/// 地址
//////////////////////////////////////////////////////////////////////////

class Id : public Expr {
public:
	int offset;
	Id();
	Id(Word* id, Type* type, int l_offset);
};

/// 操作符
//////////////////////////////////////////////////////////////////////////

class Op : public Id {
public:
	Op();
	Op(Token* token, Type* type);

	Expr* reduce();

	~Op();
};

/// 双目运算符
//////////////////////////////////////////////////////////////////////////

class Arith : public Op {
public:
	Expr *l_expr, *r_expr;
	Arith();
	Arith(Token* token, Expr* l_expr, Expr* r_expr);

	Expr* gen();
	string ToString();

	~Arith();
};

/// 单目运算符
//////////////////////////////////////////////////////////////////////////

class Unary : public Op {
public:
	Expr *expr;
	Unary();
	Unary(Token* token, Expr* expr);

	Expr* gen();
	string ToString();

	~Unary();
};

/// 临时变量
//////////////////////////////////////////////////////////////////////////

class Temp : public Expr {
public:
	static int count;
	int number;

	Temp();
	Temp(Type* type);
	string ToString();

	~Temp();
};

/// 常量
//////////////////////////////////////////////////////////////////////////

class Constant : public Expr {
public:
	Constant();
	Constant(double value);
	Constant(int value);
	Constant(Token* token, Type* type);

	void jumping(int t, int f);

	~Constant();
};

/// 逻辑运算符
//////////////////////////////////////////////////////////////////////////

class Logical : public Expr {
public:
	Expr *l_expr, *r_expr;
	Logical();
	Logical(Token* token, Expr* l_expr, Expr* r_expr);

	virtual Type* check(Type* l_type, Type* r_type);
	Expr* gen();
	string ToString();

	~Logical();
};

/// 或运算
//////////////////////////////////////////////////////////////////////////

class Or : public Logical {
public:
	Or();
	Or(Token* token, Expr* l_expr, Expr* r_expr);
	
	
	void jumping(int t, int f);

	~Or();
};

/// 与运算
//////////////////////////////////////////////////////////////////////////

class And : public Logical {
public:
	And();
	And(Token* token, Expr* l_expr, Expr* r_expr);

	void jumping(int t, int f);

	~And();
};

/// 非运算
//////////////////////////////////////////////////////////////////////////

class Not : public Logical {
public:
	Not();
	Not(Token* token, Expr* r_expr);

	void jumping(int t, int f);
	string ToString();
};

/// 关系运算符
//////////////////////////////////////////////////////////////////////////

class Rel : public Logical {
public:
	Rel();
	Rel(Token* token, Expr* l_expr, Expr* r_expr);

	Type* check(Type* l_type, Type* r_type);
	void jumping(int t, int f);

	~Rel();
};

#endif