#include "Parser.h"

Parser::Parser():lexer(NULL)
{

}

Parser::Parser(Lexer* lexer):lexer(lexer)
{
	fileManager = 0;
	fileManager = fileManager->Instance();
}

void Parser::Move()
{
	look = lexer->ScanWord();
}

void Parser::Retrack(int num)
{
	look = lexer->RetrackWord(num);
}

void Parser::Match(int t, int id)
{
	if (look == NULL)
		return ;

	if (look->tag == t)
	{
		Move();
	}
	else
	{
		Error("匹配错误");
	}
}

void Parser::Error(string s)
{
	cout << "Error: " + s << endl;
}

void Parser::ScriptAnalysis()
{
	ScriptHeader();		// 分析脚本头部声明，鉴定脚本类型
	Varible();			// 分析变量声明

	while (FuncHeader() != -1)		// 函数头分析
	{
		Block();			// 分析程序块
	}
}

void Parser::ScriptHeader()
{
	Move();
	string str = look->ToString();


	while (((Word*)look)->lexeme[0] == '#')
	{
		Move();
		// TO-DO: 保存对应的数据

		cout << look->ToString() << endl;
		Move();
	}

	if (look->tag == STAGEMAIN)		// 关卡脚本
	{
		
	}

	cout << look->ToString() << endl;
}

void Parser::Varible()
{
	Move();

	while (look->tag == VARTK)
	{
		
	}
}

int Parser::FuncHeader()
{
	return 1;
}

Stmt* Parser::Block()
{
	return NULL;
}