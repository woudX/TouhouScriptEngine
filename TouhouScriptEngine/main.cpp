#include "stdafx.h"
#include "Lexer.h"
#include "Parser.h"
#include "SymbolTable.h"
#include "THScriptMgr.h"
#include "Object.h"
int main()
{


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

	Object* object = new Object(scriptMgr->GetTHScriptByFileName("test.ths"));

	object->script->Run();

	return 0;
}