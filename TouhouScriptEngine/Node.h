#ifndef _H_NODE
#define _H_NODE

#include "stdafx.h"
#include "Lexer.h"

/// 万物之源
//////////////////////////////////////////////////////////////////////////

class Node {
public:
	int lexline;
	static int labels;
	
	Node();
	Node(int l);
	void error(string s);
	int newlabel();

	void emitlabel(int i);
	void emit(string s);

	~Node();
};

/// 表达式代码
//////////////////////////////////////////////////////////////////////////

class Expr : public Node {
public:
	Token* op;
	Type* type;

	Expr();
	Expr(Token* token, Type* v_type);

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

	~Id();
};

/// 操作符
//////////////////////////////////////////////////////////////////////////

class Op : public Expr {
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
	Arith(Token* token, Expr* v_l_expr, Expr* v_r_expr);

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
	Unary(Token* token, Expr* v_expr);

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
	Logical(Token* token, Expr* v_l_expr, Expr* v_r_expr);

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

	~Not();
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

/// 函数调用
//////////////////////////////////////////////////////////////////////////

class CallFunc : public Op {
public:
	Id* funcName;
	vector<Expr*> params;

	CallFunc();
	CallFunc(Id* id);
	Expr* gen();

	void AddToParams(Expr* paramExpr);
	string ToString();

	~CallFunc();
};

/// 语句的中间代码
//////////////////////////////////////////////////////////////////////////

class Stmt : public Node {
public:
	static Stmt* Null;
	int after;			// 保存语句下一条指令的标号

	Stmt();
	virtual void gen(int b, int a);

	~Stmt();
};

/// IF语句
//////////////////////////////////////////////////////////////////////////

class If : public Stmt {
public:
	Expr* expr;
	Stmt* stmt;

	If();
	If(Expr* v_expr, Stmt* v_stmt);
	void gen(int b, int a);

	~If();
};

/// Else语句
//////////////////////////////////////////////////////////////////////////

class Else : public Stmt {
public:
	Expr* expr;
	Stmt *t_stmt, *f_stmt;

	Else();
	Else(Expr* v_expr, Stmt* v_t_stmt, Stmt* v_f_stmt);
	void gen(int b, int a);

	~Else();
};

/// For语句
//////////////////////////////////////////////////////////////////////////

class For : public Stmt
{
public:
	Stmt *start, *repeat, *body;
	Expr* expr;

	For();

	void init(Stmt* start, Expr* expr, Stmt* repeat, Stmt* body);
	void gen(int b, int a);

	~For();
};

/// While语句
//////////////////////////////////////////////////////////////////////////

class While : public Stmt
{
public:
	Expr* expr;
	Stmt* stmt;

	While();
	While(Expr* v_expr, Stmt* v_stmt);
	void gen(int b, int a);

	~While();

};


/// Loop语句
//////////////////////////////////////////////////////////////////////////

class Loop : public Stmt {
public:
	Expr* expr;
	Stmt* stmt;

	Loop();
	Loop(Expr* expr, Stmt* stmt);
	void gen(int b, int a);
};

/// 调用语句
//////////////////////////////////////////////////////////////////////////

class Call : public Stmt {
public:
	Expr* expr;
	
	Call();
	void init(Expr* expr);
	void gen(int b, int a);

	~Call();
};

/// 赋值语句
//////////////////////////////////////////////////////////////////////////

class Set : public Stmt {
public:
	Id* id;
	Expr* expr;
	
	Set();
	Set(Id* v_id, Expr* v_epxr);
	Type* check(Type* p1, Type p2);
	void gen(int b, int a);

	~Set();
};

/// 语句序列
//////////////////////////////////////////////////////////////////////////

class Seq : public Stmt {
public:
	Stmt *first_stmt, *second_stmt;

	Seq();
	Seq(Stmt* v_first_stmt, Stmt* v_second_stmt);
	void gen(int b, int a);

	~Seq();
};

/// 返回语句
//////////////////////////////////////////////////////////////////////////

class Return : public Stmt {
public:
	Expr* expr;

	Return();
	Return(Expr* expr);
	void gen(int b, int a);

	~Return();
};
#endif