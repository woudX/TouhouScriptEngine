#include "THScript.h"
#include "function.h"
#include "ScriptExec.h"
#include "stdafx.h"

class ScriptExec_Impl
{
public:
	ScriptExec_Impl(THScript* script):_script(script),_symRoot(new SymbolTable(*_script->symRoot))	
	{
		
	}

	// 执行脚本
	void Run()
	{
		int count = static_cast<int>(_script->scriptGroup.size());

		for (int s_idx = 0; s_idx < count; ++s_idx)
		{
			// 设定当前变量层
			_top = _symRoot;

			// 脚本运行栈空间
			vector<string> stack;
			int stack_top = -1;

			int count = _script->scriptGroup[s_idx]->quadList.size();

			// 遍历每一句话并执行
			for (int c_idx = 0; c_idx < count; ++c_idx)
			{
				Quad* quad = _script->scriptGroup[s_idx]->quadList[c_idx];
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

						_top = _symRoot->_FindSymbolTable(symTabId);

						assert(_top != NULL  && "Script run symbolTable error(Invalid access : NULL)");
					}
					else if (arg_1 == "sys_print")	// 输出语句
					{
						// 这种猜测函数入栈的方法太sb了，需要改，考虑用push计数来解决问题，pop后清零
						int sum = StringToInt(_script->scriptGroup[s_idx]->quadList[c_idx + 1]->arg1);

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

	~ScriptExec_Impl()
	{
		delete _symRoot;
		_symRoot = NULL;
	}

private:
	THScript* const	_script;	// 所引用的脚本——不可改变
	SymbolTable*	_symRoot;	// 执行器所需的变量表 
	SymbolTable*	_top;		// 当前变量表顶层

	// 清空所有非全局变量的值
	void _clearNotGlobalSymTable(SymbolTable* symTable)
	{
		for (vector<SymbolTable*>::iterator itor = symTable->son.begin(); 
			itor != symTable->son.end(); ++itor)
		{
			(*itor)->ResetSymbolTableValue();
		}
	}

	// 获取一个参数实际的值(这意味着他可能是一个变量，或者就是一个常数)
	double	_getVal(string arg)
	{
		if (isdigit(arg[0]))
			return StringToInt(arg);
		else
		{
			return _top->GetSymbol(arg)->value;
		}
	}

	// 跳转到指定行数继续执行
	int _goto(int scriptGroupId, string lineId)
	{
		int count = _script->scriptGroup[scriptGroupId]->quadList.size();
		for (int c_idx = 0; c_idx < count; ++c_idx)
		{
			if (isContain(_script->scriptGroup[scriptGroupId]->quadList[c_idx]->lineID, lineId))
			{
				return c_idx;
			}
		}

		return -1;
	}

	// 返回iffalse的判断条件
	int	_iffalse(string l_str, string cmp_str, string r_str)
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
};

ScriptExec::ScriptExec(THScript* script):_pImpl(new ScriptExec_Impl(script))
{

}

void ScriptExec::Run()
{
	_pImpl->Run();
}

ScriptExec::~ScriptExec()
{
	delete _pImpl;
	_pImpl = NULL;
}