#include "SymbolTable.h"

SymbolTable::SymbolTable()
{

}

SymbolTable::SymbolTable(SymbolTable* father):father(father)
{

}

SymbolTable::~SymbolTable()
{
	for (map<string, Symbol*>::iterator itor = symbolMap.begin(); itor != symbolMap.end(); )
		itor = symbolMap.erase(itor);

	symbolMap.clear();
}

void SymbolTable::MakeNewSymbolTable()
{
	SymbolTable* symTable = new SymbolTable(this);
	son.push_back(symTable);
}

void SymbolTable::AddSymbol(Symbol* symbol)
{
	if (symbol != NULL)
		symbolMap.insert(make_pair(symbol->name, symbol));
}