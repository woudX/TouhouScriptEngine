#include "THScript.h"
#include "function.h"

THScript::THScript():symRoot(NULL)
{

}

THScript::THScript(const THScript& rhs)
	:fileName(rhs.fileName),
	touhouScript(rhs.touhouScript),
	title(rhs.title),
	text(rhs.text),
	music(rhs.music),
	image(rhs.image),
	background(rhs.background),
	player(rhs.player),
	scriptVersion(rhs.scriptVersion),
	symRoot(new SymbolTable(*(rhs.symRoot)))
{
	for (vector<QuadGroup*>::const_iterator itor = rhs.scriptGroup.begin(); 
		itor != rhs.scriptGroup.end(); ++itor)
	{
		QuadGroup* quadGroup = new QuadGroup(*(*itor));
		scriptGroup.push_back(quadGroup);
	}
}

THScript& THScript::operator= (const THScript& rhs)
{
	if (&rhs != this)
	{
		fileName = rhs.fileName;
		touhouScript = rhs.touhouScript;
		title = rhs.title;
		text = rhs.text;
		music = rhs.music;
		image = rhs.image;
		background = rhs.background;
		player = rhs.player;
		scriptVersion = rhs.scriptVersion;
		symRoot = new SymbolTable(*(rhs.symRoot));

		for (vector<QuadGroup*>::const_iterator itor = rhs.scriptGroup.begin();
			itor != rhs.scriptGroup.end(); ++itor)
		{
			QuadGroup* quadGroup = new QuadGroup(*(*itor));
			scriptGroup.push_back(quadGroup);
		}
	}

	return *this;
}

void THScript::SetValue(string varStr, string value)
{
	if (varStr == "#TouhouScript")
		touhouScript = value;
	else if (varStr == "#Title")
		title = value;
	else if (varStr == "#Text")
		text = value;
	else if (varStr == "#Music")
		music = value;
	else if (varStr == "#Image")
		image = value;
	else if (varStr == "#BackGround")
		background = value;
	else if (varStr == "#Player")
		player = value;
	else if (varStr == "#ScriptVersion")
		scriptVersion = value;
}

void THScript::_ClearNotGlobalSymTable(SymbolTable* symTable)
{
	// 重置所有子符号表的值
	for (vector<SymbolTable*>::iterator itor = symTable->son.begin(); 
		itor != symTable->son.end(); ++itor)
	{
		(*itor)->ResetSymbolTableValue();
	}
}

SymbolTable* THScript::_FindSymbolTableById(int id)
{

}

void THScript::Run()
{
	// 重置变量值
	_ClearNotGlobalSymTable(symRoot);

	// 设定当前变量层
	SymbolTable* top = symRoot;

	// 脚本运行栈空间
	vector<string> stack;

	for (int s_idx = 0; s_idx < scriptGroup.size(); ++s_idx)
	{

		int count = scriptGroup[s_idx]->quadList.size();

		// 遍历每一句话并执行
		for (int c_idx = 0; c_idx < count; ++c_idx)
		{
			Quad* quad = scriptGroup[s_idx]->quadList[c_idx];
			string op = quad->op, 
				arg_1 = quad->arg1,
				arg_2 = quad->arg2,
				obj   = quad->obj;

			if (op == "push")
			{
				stack.push_back(arg_1);
			}
			else if (op == "pop")
			{
				for (int idx = 0; idx < StringToInt(arg_1); ++idx)
				{
					stack.pop_back();
				}
			}
			else if (op == "SYS_F_ChangeTableArea")	// 变量作用域调整
			{
				// TO-DO: 更新符号表层
			}
			else if (op == "=")
			{
				double val = StringToDouble(arg_1);

			}

		}
	}
}



THScript::~THScript()
{
	for (vector<QuadGroup*>::iterator itor = scriptGroup.begin(); itor != scriptGroup.end(); )
		if (*itor == NULL)
		{
			delete *itor;
			*itor = NULL;
			itor = scriptGroup.erase(itor);
		}
		else
			++itor;
	scriptGroup.clear();

	if (symRoot != NULL)
	{
		delete symRoot;
		symRoot = NULL;
	}
}