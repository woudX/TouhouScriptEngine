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

void THScript::_clearNotGlobalSymTable(SymbolTable* symTable)
{
	// 重置所有子符号表的值
	for (vector<SymbolTable*>::iterator itor = symTable->son.begin(); 
		itor != symTable->son.end(); ++itor)
	{
		(*itor)->ResetSymbolTableValue();
	}
}

double THScript::_getVal(string arg)
{
	if (isdigit(arg[0]))
		return StringToInt(arg);
	else
	{
		return _top->GetSymbol(arg)->value;
	}
}

int THScript::_goto(int scriptGroupId, string lineId)
{
	int count = scriptGroup[scriptGroupId]->quadList.size();
	for (int c_idx = 0; c_idx < count; ++c_idx)
	{
		if (isContain(scriptGroup[scriptGroupId]->quadList[c_idx]->lineID, lineId))
		{
			return c_idx;
		}
	}

	return -1;
}

int THScript::_iffalse(string l_str, string cmp_str, string r_str)
{
	int _flag = 1;

	if (cmp_str == ">")
	{
		if (_getVal(l_str) > _getVal(r_str))
			_flag = 0;
	}
	else if (cmp_str == ">=")
	{
		if (_getVal(l_str) >= _getVal(r_str))
			_flag = 0;
	}
	else if (cmp_str == "<")
	{
		if (_getVal(l_str) < _getVal(r_str))
			_flag = 0;
	}
	else if (cmp_str == "<=")
	{
		if (_getVal(l_str) <= _getVal(r_str))
			_flag = 0;
	}
	else if (cmp_str == "==")
	{
		if (_getVal(l_str) == _getVal(r_str))
			_flag = 0;
	}
	else if (cmp_str == "!=")
	{
		if (_getVal(l_str) != _getVal(r_str))
			_flag = 0;
	}

	return _flag;
}

void THScript::Run()
{
	for (int s_idx = 0; s_idx < scriptGroup.size(); ++s_idx)
	{
		// 重置变量值
		//_ClearNotGlobalSymTable(symRoot);

		// 设定当前变量层
		_top = symRoot;

		// 脚本运行栈空间
		vector<string> stack;
		int stack_top = -1;

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
				++stack_top;
			}
			else if (op == "pop")
			{
				for (int idx = 0; idx < StringToInt(arg_1); ++idx)
				{
					stack.pop_back();
					--stack_top;
				}
			}
			else if (op == "call")	
			{
				if (arg_1 == "SYS_F_ChangeTableArea")	// 变量作用域调整
				{
					int symTabId = StringToInt(stack.back());

					_top = symRoot->_FindSymbolTable(symTabId);

					if (_top == NULL)
					{
						cout << "符号表崩坏！" << endl;
						exit(1);
					}
				}
				else if (arg_1 == "sys_print")	// 输出语句
				{
					int sum = StringToInt(scriptGroup[s_idx]->quadList[c_idx + 1]->arg1);

					cout << "print: " ;
					for (int idx = 0; idx < sum; ++idx)
					{
						if (isContain(stack[stack_top - idx], "SYS_STR_"))
							cout << removeSystemMark(stack[stack_top - idx], "SYS_STR_");
						else
							cout << _getVal(stack[stack_top - idx]);
					}
					cout << endl;
				}	
			}
			else if (op == "goto")
			{
				c_idx = _goto(s_idx, obj) - 1;
			}
			else if (op == "iffalse")
			{
				vector<string> equality = split(arg_1, ' ');
				
				if (equality.size() == 1)	// 条件只有一个时
				{
					if (!_getVal(equality[0]))
						c_idx = _goto(s_idx, obj) - 1;
				}
				else
				{
					if (_iffalse(equality[0], equality[1], equality[2]))
						c_idx = _goto(s_idx, obj) - 1;
				}
			}
			else if (op == "if")
			{
				vector<string> equality = split(arg_1, ' ');

				if (equality.size() == 1)	// 条件只有一个时
				{
					if (_getVal(equality[0]))
						c_idx = _goto(s_idx, obj) - 1;
				}
				else
				{
					if (!_iffalse(equality[0], equality[1], equality[2]))
						c_idx = _goto(s_idx, obj) - 1;
				}
			}
			else if (op == "=")
			{
				double val = _getVal(arg_1);

				_top->GetSymbol(obj)->value = val;
			}
			else if (op == "+=")
			{
				double val = _getVal(arg_1);
				
				_top->GetSymbol(obj)->value += val;
			}
			else if (op == "-=")
			{
				double val = _getVal(arg_1);

				_top->GetSymbol(obj)->value -= val;
			}
			else if (op == "*=")
			{
				double val = _getVal(arg_1);

				_top->GetSymbol(obj)->value *= val;
			}
			else if (op == "/=")
			{
				double val = _getVal(arg_1);

				_top->GetSymbol(obj)->value /= val;
			}
			else if (op == "+" && arg_1 != "")	// 二元+
			{
				double val_1 = _getVal(arg_1);
				double val_2 = _getVal(arg_2);

				_top->GetSymbol(obj)->value = val_1 + val_2;
			}
			else if (op == "+" && arg_1 == "")	// 一元+
			{
				double val_2 = _getVal(arg_2);

				_top->GetSymbol(obj)->value = val_2;
			}
			else if (op == "-" && arg_1 != "")	// 二元-
			{
				double val_1 = _getVal(arg_1);
				double val_2 = _getVal(arg_2);

				_top->GetSymbol(obj)->value = val_1 - val_2;
			}
			else if (op == "-" && arg_1 == "")	// 一元-
			{
				double val_2 = _getVal(arg_2);

				_top->GetSymbol(obj)->value = -val_2;
			}
			else if (op == "*")
			{
				double val_1 = _getVal(arg_1);
				double val_2 = _getVal(arg_2);

				_top->GetSymbol(obj)->value = val_1 * val_2;
			}
			else if (op == "/")
			{
				double val_1 = _getVal(arg_1);
				double val_2 = _getVal(arg_2);

				_top->GetSymbol(obj)->value = val_1 / val_2;
			}
			else if (op == ">")
			{
				double val_1 = _getVal(arg_1);
				double val_2 = _getVal(arg_2);

				_top->GetSymbol(obj)->value = val_1 > val_2;
			}
			else if (op == ">=")
			{
				double val_1 = _getVal(arg_1);
				double val_2 = _getVal(arg_2);

				_top->GetSymbol(obj)->value = val_1 >= val_2;
			}
			else if (op == "<")
			{
				double val_1 = _getVal(arg_1);
				double val_2 = _getVal(arg_2);

				_top->GetSymbol(obj)->value = val_1 < val_2;
			}
			else if (op == "<=")
			{
				double val_1 = _getVal(arg_1);
				double val_2 = _getVal(arg_2);

				_top->GetSymbol(obj)->value = val_1 <= val_2;
			}
			else if (op == "==")
			{
				double val_1 = _getVal(arg_1);
				double val_2 = _getVal(arg_2);

				_top->GetSymbol(obj)->value = val_1 == val_2;
			}
			else if (op == "!=")
			{
				double val_1 = _getVal(arg_1);
				double val_2 = _getVal(arg_2);

				_top->GetSymbol(obj)->value = val_1 != val_2;
			}
			else if (op == "!")
			{
				double val_2 = _getVal(arg_2);

				_top->GetSymbol(obj)->value = !val_2;
			}
			else if (op == "++" && arg_1 == "")	// 后置++
			{
				Symbol* sym = _top->GetSymbol(arg_2);

				sym->value++;
				_top->GetSymbol(obj)->value = sym->value;
			}
			else if (op == "++" && arg_2 == "")	// 前置++
			{
				Symbol* sym = _top->GetSymbol(arg_1);
				
				_top->GetSymbol(obj)->value = sym->value;
				sym->value++;
			}
			else if (op == "--" && arg_1 == "")	// 后置--
			{
				Symbol* sym = _top->GetSymbol(arg_2);

				sym->value--;
				_top->GetSymbol(obj)->value = sym->value;
			}
			else if (op == "--" && arg_2 == "")	// 前置--
			{
				Symbol* sym = _top->GetSymbol(arg_1);

				_top->GetSymbol(obj)->value = sym->value;
				sym->value--;
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