#ifndef _H_SYMBOLTABLE
#define _H_SYMBOLTABLE


#include "Symbol.h"

class SymbolTable
{
public:
	SymbolTable* father;				// 父表
	map<string, Symbol*> symbolMap;		// 符号Map
	vector<SymbolTable*> son;			// 下属符号表
	int sonIndex;						// 下一个要获取的符号表

	SymbolTable();
	SymbolTable(SymbolTable* father);

	void AddSymbol(Symbol* symbol);		// 添加一个新符号
	void DeleteSymbol(Symbol* symbol);	// 删除一个符号
	void MakeNewSymbolTable();			// 生成一个新的符号表
	SymbolTable* GetNextSymbolTable();	// 获得下一个符号表
	Symbol* GetSymbol(string name);		// 获得一个符号
	

	~SymbolTable();
	
};

#endif // !_H_SYMBOLTABLE
