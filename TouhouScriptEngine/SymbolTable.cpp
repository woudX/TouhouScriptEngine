#include "SymbolTable.h"

SymbolTable::SymbolTable():father(NULL),sonIndex(-1)
{

}

SymbolTable::SymbolTable(SymbolTable* father):father(father),sonIndex(-1)
{

}

SymbolTable::~SymbolTable()
{
	for (map<string, Symbol*>::iterator itor = symbolMap.begin(); itor != symbolMap.end(); )
		itor = symbolMap.erase(itor);

	symbolMap.clear();
}

SymbolTable* SymbolTable::MakeNewSymbolTable()
{
	SymbolTable* symTable = new SymbolTable(this);
	son.push_back(symTable);

	return symTable;
}

void SymbolTable::ResetSymbolTableStatus()
{
	sonIndex = -1;

	for (int index = 0; index < son.size(); ++index)
	{
		son[index]->ResetSymbolTableStatus();
	}
}

SymbolTable* SymbolTable::GetNextSymbolTable()
{
	++sonIndex;

	if (sonIndex < son.size())
	{
		return son[sonIndex];
	}
	else
	{
		return father;
	}
}

void SymbolTable::AddSymbol(Symbol* symbol)
{
	if (symbol != NULL)
		symbolMap.insert(make_pair(symbol->name, symbol));
}

Symbol* SymbolTable::GetSymbol(string name)
{
	SymbolTable* nowSym = this;
	Symbol* retSym = NULL;

	while (nowSym != NULL && (retSym = _FindSymbol(nowSym, name)) == NULL) {
		nowSym = nowSym->father;
	}

	return retSym;
}

Symbol* SymbolTable::_FindSymbol(SymbolTable* symTable, string name)
{
	map<string, Symbol*>::iterator itor = symTable->symbolMap.find(name);
	
	if (itor == symTable->symbolMap.end())
	{
		return NULL;
	}
	else
	{
		return itor->second;
	}
}