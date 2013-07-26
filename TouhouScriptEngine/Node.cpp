#include "Node.h"
#include "function.h"

/// 根节点
//////////////////////////////////////////////////////////////////////////

int Node::labels = 0;

Node::Node():lexline(0) {}

Node::Node(int l):lexline(l) {}

void Node::error(string s)
{
	cout << "Error:" << "near line" << lexline << ": " << s << endl;
}

int Node::newlabel()
{
	return ++labels;
}

void Node::emitlabel(int i) 
{
	cout << "L" << i << ":";
}

void Node::emit(string s) 
{
	cout << "\t" << s << endl;
}

Node::~Node()
{

}

/// 表达式
//////////////////////////////////////////////////////////////////////////

Expr::Expr():op(NULL),type(NULL) 
{

}

Expr::Expr(Token* token, Type* v_type):op(token),type(v_type) 
{

}

Expr* Expr::gen() 
{
	return this;
}

Expr* Expr::reduce()
{
	return this;
}

void Expr::jumping(int t, int f)
{
	emitjumps(ToString(), t, f);
}

void Expr::emitjumps(string test, int t, int f)
{
	if (t != 0 && f != 0)
	{
		emit("if " + test + " goto L" + IntToString(t));
		emit("goto L" + f);
	} 
	else if (t != 0) 
	{
		emit("if " + test + " goto L" + IntToString(t));
	} 
	else if (f != 0) {
		emit("iffalse " + test + " goto L" + IntToString(f));
	}
}

string Expr::ToString()
{
	return op->ToString();
}

Expr::~Expr()
{

}

/// 地址
//////////////////////////////////////////////////////////////////////////

Id::Id():offset(0)
{

}

Id::Id(Word* id, Type* type, int l_offset):Expr(id, type),offset(l_offset)
{

}

Id::~Id() 
{

}

/// 操作符
//////////////////////////////////////////////////////////////////////////

Op::Op()
{

}

Op::Op(Token* token, Type* type):Expr(token, type)
{

}

Expr* Op::reduce()
{
	Expr* x = gen();
	Temp* t = new Temp(type);
	emit(t->ToString() + " = " + x->ToString());
	return t;
}

Op::~Op()
{

}

/// 双目运算符
//////////////////////////////////////////////////////////////////////////

Arith::Arith():l_expr(NULL),r_expr(NULL)
{

}

Arith::Arith(Token* token, Expr* v_l_expr, Expr* v_r_expr):Op(token, NULL),l_expr(v_l_expr),r_expr(v_r_expr)
{
	if (l_expr != NULL && r_expr != NULL)
	{
		type = Type::max(l_expr->type, r_expr->type);
	}
}

Expr* Arith::gen()
{
	return new Arith(op, l_expr->reduce(), r_expr->reduce());
}

string Arith::ToString()
{
	string l_str = l_expr->reduce()->ToString();
	string r_str = r_expr->reduce()->ToString();

	return l_str + " " + op->ToString() + " " + r_str;
}

Arith::~Arith()
{

}

/// 单目运算符
//////////////////////////////////////////////////////////////////////////

Unary::Unary():expr(NULL)
{

}

Unary::Unary(Token* token, Expr* v_expr):Op(token, NULL),expr(v_expr)
{
	if (expr != NULL)
	{
		type = expr->type;
	}
}

Expr* Unary::gen()
{
	return new Unary(op, expr->reduce());
}

string Unary::ToString()
{
	return op->ToString() + " " + expr->ToString();
}

Unary::~Unary()
{

}

/// 单目后置运算符
//////////////////////////////////////////////////////////////////////////

UnaryAfter::UnaryAfter():Unary()
{

}

UnaryAfter::UnaryAfter(Token* token, Expr* v_expr):Unary(token, v_expr)
{

}

Expr* UnaryAfter::gen()
{
	return new UnaryAfter(op, expr->reduce());
}

string UnaryAfter::ToString()
{
	return expr->ToString() + " " + op->ToString();
}



/// 临时变量
//////////////////////////////////////////////////////////////////////////

int Temp::count = 0;

Temp::Temp()
{

}

Temp::Temp(Type* type):Expr(Word::temp, type)
{
	number = ++count;
}

string Temp::ToString()
{
	return "SYS_T_" + IntToString(number); // + "_" + type->ToString();
}

Temp::~Temp()
{

}

/// 常量
//////////////////////////////////////////////////////////////////////////


Constant::Constant()
{

}

Constant::Constant(int value):Expr(new Num(value), Type::Int)
{

}

Constant::Constant(double value):Expr(new Double(value), Type::Double)
{

}

Constant::Constant(Token* token, Type* type):Expr(token, type)
{

}

void Constant::jumping(int t, int f)
{
	emit("goto L" + IntToString(t));
}

/// 逻辑运算符
//////////////////////////////////////////////////////////////////////////

Logical::Logical():l_expr(NULL),r_expr(NULL)
{

}

Logical::Logical(Token* token, Expr* v_l_expr, Expr* v_r_expr):Expr(token, NULL),l_expr(v_l_expr),r_expr(v_r_expr)
{
	type = check(l_expr->type, r_expr->type);
}

Type* Logical::check(Type* l_type, Type* r_type)
{
	if (l_type == Type::Double || r_type == Type::Double)	
		return Type::Double;
	else 
		return Type::Int;
}

Expr* Logical::gen()
{
	int f = newlabel();
	int a = newlabel();
	Temp* temp = new Temp(type);
	this->jumping(0, f);
	emit(temp->ToString() + " = true");
	emit("goto L" + IntToString(a));
	emitlabel(f);
	emit(temp->ToString() + " = false");
	emitlabel(a);

	return temp;
}

string Logical::ToString()
{
	string l_str = l_expr->gen()->reduce()->ToString();
	string r_str = r_expr->gen()->reduce()->ToString();

	return l_str + " " + op->ToString() + " " + r_str;
}

Logical::~Logical()
{

}

/// 或运算
//////////////////////////////////////////////////////////////////////////

Or::Or()
{

}

Or::Or(Token* token, Expr* l_expr, Expr* r_expr):Logical(token, l_expr, r_expr)
{

}

void Or::jumping(int t, int f)
{
	int label = (t != 0) ? t : newlabel();
	l_expr->jumping(label, 0);
	r_expr->jumping(t, f);

	if (t == 0) emitlabel(label);
}

Or::~Or()
{

}

/// 与运算
//////////////////////////////////////////////////////////////////////////

And::And()
{

}

And::And(Token* token, Expr* l_expr, Expr* r_expr):Logical(token, l_expr, r_expr)
{

}

void And::jumping(int t, int f)
{
	int label = (f != 0) ? f : newlabel();
	l_expr->jumping(0, label);
	r_expr->jumping(t ,f);

	if (f == 0) emitlabel(label);
}

And::~And()
{

}

/// 非运算
//////////////////////////////////////////////////////////////////////////

Not::Not()
{

}

Not::Not(Token* token, Expr* r_expr):Logical(token, r_expr, r_expr)
{

}

void Not::jumping(int t, int f)
{
	r_expr->jumping(f, t);
}

string Not::ToString()
{
	return op->ToString() + " " + r_expr->ToString();
}

Not::~Not()
{

}

/// 关系运算符
//////////////////////////////////////////////////////////////////////////

Rel::Rel()
{

}

Rel::Rel(Token* token, Expr* l_expr, Expr* r_expr):Logical(token, l_expr, r_expr)
{

}

Type* Rel::check(Type* l_type, Type* r_type)
{
	// To-do:关于判断条件是否需要引入true false的问题暂时没有想好
	return l_type;
}

void Rel::jumping(int t, int f)
{
	Expr* l_e = l_expr->reduce();
	Expr* r_e = r_expr->reduce();

	string rel = l_e->ToString() + " " + op->ToString() + " " + r_e->ToString();
	emitjumps(rel, t, f);
}

Rel::~Rel()
{

}

/// 函数调用
//////////////////////////////////////////////////////////////////////////

CallFunc::CallFunc():funcName(NULL)
{

}

CallFunc::CallFunc(Id* id):Op(new Word("", 0), id->type),funcName(id)
{

}

Expr* CallFunc::gen()
{
	for (int i = params.size() - 1; i >= 0; i--)
		emit("push " + params[i]->reduce()->ToString());

	int label = newlabel();
	emitlabel(label);

	return this;
}

void CallFunc::AddToParams(Expr* paramExpr)
{
	params.push_back(paramExpr);
}

string CallFunc::ToString()
{
	return "call " + ((Expr*)funcName)->op->ToString();
}

CallFunc::~CallFunc()
{
	if (funcName != NULL)
	{
		delete funcName;
		funcName = NULL;
	}

	for (vector<Expr*>::iterator itor = params.begin(); itor != params.end(); )
		if (*itor != NULL)
		{
			delete *itor;
			*itor = NULL;
			itor = params.erase(itor);
		}
		else
			itor++;

	params.clear();
}

/// 语句的中间代码
//////////////////////////////////////////////////////////////////////////

Stmt* Stmt::Null = new Stmt;

Stmt::Stmt():after(0)
{

}

void Stmt::gen(int b, int a)
{

}

Stmt::~Stmt()
{
	
}

/// IF语句
//////////////////////////////////////////////////////////////////////////

If::If():expr(NULL),stmt(NULL)
{

}

If::If(Expr* v_expr, Stmt* v_stmt):expr(v_expr),stmt(v_stmt)
{

}

void If::gen(int b, int a)
{
	int label = newlabel();
	expr->jumping(0, a);
	emitlabel(label);
	stmt->gen(label, a);
}

If::~If()
{

}

/// ELSE语句
//////////////////////////////////////////////////////////////////////////

Else::Else():expr(NULL),t_stmt(NULL),f_stmt(NULL)
{

}

Else::Else(Expr* v_expr, Stmt* v_t_stmt, Stmt* v_f_stmt):expr(v_expr),t_stmt(v_t_stmt),f_stmt(v_f_stmt)
{

}

void Else::gen(int b, int a)
{
	int label1 = newlabel();
	int label2 = newlabel();

	expr->jumping(0, label2);

	emitlabel(label1);
	t_stmt->gen(label1, a);
	emit("goto L" + IntToString(a));

	emitlabel(label2);
	f_stmt->gen(label2, a);
}

Else::~Else()
{

}

/// For语句
//////////////////////////////////////////////////////////////////////////

For::For():start(NULL),repeat(NULL),expr(NULL),body(NULL)
{

}

void For::init(Stmt* start, Expr* expr, Stmt* repeat, Stmt* body)
{
	this->start = start;
	this->expr = expr;
	this->repeat = repeat;
	this->body = body;

}

void For::gen(int b, int a)
{
	int label1 = newlabel();	// 初始化语句
	int label2 = newlabel();	// 条件更新位置

	if (start != NULL)
		start->gen(b, label1);

	emitlabel(label1);			// 初始化后标记

	if (expr != NULL)
		expr->gen()->jumping(0, a);

	if (body != NULL)
		body->gen(label1, label2);

	emitlabel(label2);			// 循环体累加前

	if (repeat != NULL)
		repeat->gen(label2, 0);

	emit("goto L" + IntToString(label1));
}

For::~For()
{

}

/// While语句
//////////////////////////////////////////////////////////////////////////

While::While():expr(NULL),stmt(NULL)
{

}

While::While(Expr* v_expr, Stmt* v_stmt):expr(v_expr),stmt(v_stmt)
{

}

void While::gen(int b, int a)
{
	int label = newlabel();		// 条件判断
	
	emitlabel(label);

	expr->emitjumps(expr->gen()->reduce()->ToString(), 0, a);
	stmt->gen(label, 0);

	emit("goto L" + IntToString(label));
}

While::~While()
{

}

/// Loop语句
//////////////////////////////////////////////////////////////////////////

// To-do: 暂时不实现

/// 调用语句
//////////////////////////////////////////////////////////////////////////

Call::Call():expr(NULL)
{

}

void Call::init(Expr* expr)
{
	this->expr = expr;
}

void Call::gen(int b, int a)
{
	emit(expr->gen()->ToString());
}

Call::~Call()
{

}

/// 赋值语句
//////////////////////////////////////////////////////////////////////////

Set::Set():id(NULL),expr(NULL)
{

}

Set::Set(Id* v_id, Expr* v_expr):id(v_id),expr(v_expr)
{

}

Type* Set::check(Type* p1, Type p2)
{
	return p1;
}

void Set::gen(int b, int a)
{
	emit( id->ToString() + " = " + expr->gen()->ToString());
}

Set::~Set()
{

}


/// 运算赋值语句
//////////////////////////////////////////////////////////////////////////

AssignSet::AssignSet():id(NULL),expr(NULL),op(NULL)
{

}

AssignSet::AssignSet(Id* v_id, Token* v_op, Expr* v_expr):id(v_id),expr(v_expr),op(v_op)
{

}

Type* AssignSet::check(Type* p1, Type p2)
{
	return p1;
}

void AssignSet::gen(int b, int a)
{
	string val = expr->reduce()->gen()->ToString();
	emit(id->ToString() + " " + op->ToString() + " " + val);
}


/// 语句序列
//////////////////////////////////////////////////////////////////////////

Seq::Seq():first_stmt(NULL),second_stmt(NULL)
{

}

Seq::Seq(Stmt* v_first_stmt, Stmt* v_second_stmt):first_stmt(v_first_stmt),second_stmt(v_second_stmt)
{

}

void Seq::gen(int b, int a)
{
	int label = newlabel();

	first_stmt->gen(b, label);
	emitlabel(label);
	second_stmt->gen(label, a);
}

Seq::~Seq()
{

}

/// 返回语句
//////////////////////////////////////////////////////////////////////////

// TO-DO:暂时不实现