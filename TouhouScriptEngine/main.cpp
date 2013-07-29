#include "stdafx.h"
#include "Lexer.h"
#include "Parser.h"
#include "SymbolTable.h"
#include "THScriptMgr.h"
int main()
{
	int a,b;
	a = 2, b = 3;

	FileMgr* fileManager = 0;
	fileManager = fileManager->Instance();

	Lexer* lexer = new Lexer();

	// 读取并进行词法分析
	fileManager->ReadCodeFile("test.ths");
	lexer->MakeWordStream();

	cout << "---------------------" << endl;

	Parser* parser = new Parser(lexer);
	parser->ScriptAnalysis();
	
	THScriptMgr* scriptMgr = 0;
	scriptMgr = scriptMgr->Instance();


	return 0;
}