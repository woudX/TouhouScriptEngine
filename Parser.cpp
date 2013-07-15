#include "Parser.h"

Parser::Parser():lexer(NULL)
{

}

Parser::Parser(Lexer* lexer):lexer(lexer),fileManager(0),scriptMgr(0)
{
	fileManager = fileManager->Instance();
	scriptMgr = scriptMgr->Instance();
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
	// 创建新的脚本数据
	THScript* scriptData = new THScript();
	scriptData->fileName = fileManager->fileName;
	scriptMgr->AddTHScript(scriptData);

	ScriptHeader();					// 分析脚本头部声明，鉴定脚本类型
	Varible();						// 分析头部变量声明

	while (FuncHeader() != -1)		// 函数头分析
	{
		Block();					// 分析程序块
	}
}

void Parser::ScriptHeader()
{
	Move();
	string str = look->ToString();
	string varStr = ((Word*)look)->lexeme;
	
	while (varStr[0] == '#')		// 读取脚本头部声明
	{
		Move();
		scriptMgr->lastScript->SetValue(varStr, look->ToString());
		Move();
		varStr = ((Word*)look)->lexeme;
	}


	if (scriptMgr->lastScript->touhouScript == "Stage")		// 验证主函数与脚本类型一致性
		Match(STAGEMAIN, -1);
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