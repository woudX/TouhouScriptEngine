#ifndef _H_Parser
#define _H_Parser

#include "stdafx.h"
#include "Lexer.h"
#include "Node.h"
#include "THScriptMgr.h"

class Parser
{
public:
	FileMgr* fileManager;		// 文件管理器
	THScriptMgr* scriptMgr;		// 脚本管理器
	SymbolTable* symTop;		// 当前顶层符号表
	Lexer* lexer;				// 词法分析器
	Token* look;

	Parser();
	Parser(Lexer* lexer);

	void Move();				// 从单词流预读一个单词
	void Retrack(int num);		// 退回指定的单词数
	void Match(int t, int id);	// 匹配字符类型，不相同的话则报错
	void Error(string s);		// 显示报错信息

	void ScriptType();			// 脚本类型
	void ScriptAnalysis();		// 脚本分析入口
	void ScriptHeader();		// 脚本头部提取
	void Varible();				// 变量定义
	int FuncHeader();			// 函数头
	Stmt* Block();				// 程序块
	Stmt* Stmts();				// 语句列
	Stmt* StmtOne();			// 语句
	Stmt* Assign();				// 赋值语句

	Expr* _bool();				// 运算符分析
	Expr* _join();
	Expr* _equality();			
	Expr* _rel();	
	Expr* _exprOne();			
	Expr* _term();
	Expr* _unary();
	Expr* _factor();

};

#endif