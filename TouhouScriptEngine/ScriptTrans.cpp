#include "THScript.h"
#include "function.h"
#include "ScriptTrans.h"
#include "stdafx.h"

using namespace std;

/// Impl
//////////////////////////////////////////////////////////////////////////


class Translator::Impl {
public:
	Impl():_streamIdx(-1),_tableId(-1) {}

	// 翻译脚本
	THScript* Translate(THScript *script)
	{

		string st, op, arg_1, arg_2, obj;
		string l_str,r_str, cmp_str;

		while ((st = _Next()) != "NULL")
		{
			string lineID = "";
			op = "", arg_1 = "", arg_2 = "", obj = "";

			if (st[0] == '@')									// 脚本组
			{
				QuadGroup* quadGroup = new QuadGroup(st);
				script->scriptGroup.push_back(quadGroup);

				_lastGroup = quadGroup;

				continue;
			}

			while (st[st.length()- 1] == ':')					// 行号 
			{
				lineID += st;
				st = _Next();
			}

			if (st == "iffalse" || st == "if")					// if、iffalse语句
			{
				op = st;

				// 获取判断条件
				l_str = _Next();
				cmp_str = _Next();

				if (cmp_str == "goto")
				{
					arg_1 = l_str;
					obj = _Next();
				}
				else
				{
					r_str = _Next();
					arg_1 = l_str + " " + cmp_str + " " + r_str;

					// 读取跳转行号
					_Next();
					obj = _Next();
				}
			}
			else if (st == "push" || st == "call" || st == "pop")
			{
				op = st;
				arg_1 = _Next();

				if (arg_1 == "SYS_F_ChangeTableArea") // 作用域调整
				{
					_tableId = StringToInt(_lastGroup->quadList.back()->arg1);
				}
			}
			else if (st == "goto")
			{
				op = st;
				obj = _Next();
			}
			else if (st[0] == '@')	// 进入下一区域
			{
				_lastGroup->AddQuad(_NewQuad("SYS_V_END", arg_1, arg_2, obj, lineID));	// 直接创建结尾语句
				_Retract(1);

				continue;
			}
			else	// 存在赋值情况
			{
				obj = st;

				st = _Next();
				if (st == "+=" || st == "-=" || st == "*=" || st == "/=")	// 简化运算符
				{
					op = st;
					arg_1 = _Next();
				}
				else if (st == "=")
				{
					st = _Next();

					if (st == "+" || st == "++" || st == "-" || st == "--" || st == "!" || st == "call") // 一元运算符
					{
						op = st;
						arg_2 = _Next();
					}
					else 
					{
						arg_1 = st;

						st = _Next();
						if (st == "+" || st == "-" || st == "*" || st == "/" || st == ">" || st == ">=" || st == "<" 
							|| st == "<=" || st == "==" || st == "!=")	// 二元运算符
						{
							op = st;
							arg_2 = _Next();
						}
						else if ( st == "++" || st == "--")	//后置++ --
						{
							op = st;
						}
						else
						{
							op = "=";
							_Retract(1);
						}
					}
				}
			}

			_lastGroup->AddQuad(_NewQuad(op, arg_1, arg_2, obj, lineID));
			_AddTempVar(obj, script);
		}

		return script;
	}

	// 添加到中间代码流
	void Add(string word)
	{
		vector<string> _vecStr = split(word, ' ');
		
		int _count = _vecStr.size();

		for (int idx = 0; idx < _count; ++idx)
			_scriptStream.push_back(_vecStr[idx]);
	}

private:
	vector<string> _scriptStream;		// 中间代码流
	QuadGroup* _lastGroup;				// 最近一次操作的脚本组（不必释放）
	int _streamIdx;						// 当前脚本文件流位置
	int _tableId;						// 当前符号表位置

	Impl(const Impl& rhs);					// 禁止复制构造
	Impl& operator= (const Impl& rhs);		// 禁止赋值复制

	// 读取下一个单词
	string _Next()
	{
		++_streamIdx;

		if (_streamIdx < (int)_scriptStream.size())
			return _scriptStream[_streamIdx];
		else
			return "NULL";
	}

	// 退回指定数目的词
	string _Retract(int num)
	{
		_streamIdx -= num;

		assert(_streamIdx >= 0 && "Script Interpreter's _streamIdx is invalid(must >= 0)");
		return _scriptStream[_streamIdx];
	}

	// 添加临时变量到符号表
	void _AddTempVar(string name, THScript* script)
	{
		if (isContain(name, "SYS_T_"))
		{
			Symbol* sym = new Symbol(name, TYPE_DOUBLE, KIND_TVAR);
			script->symRoot->AddSymbol(sym);
		}	
		
	}

	// 新建一句脚本
	Quad* _NewQuad(string op, string arg_1, string arg_2, string obj, string lineId)
	{
		op = (op == "") ? "SYS_V_END" : op;

		Quad* quad = new Quad(op, arg_1, arg_2, obj);

		quad->lineID = lineId;

		

		return quad;	// quad最好提供赋值构造来触发NRV优化
	}
	
};



/// Translator
//////////////////////////////////////////////////////////////////////////

Translator::Translator():_pImpl(new Impl)
{
	
}

THScript* Translator::Translate(THScript *script)
{
	return _pImpl->Translate(script);
}

void Translator::Add(string word)
{
	_pImpl->Add(word);
}


Translator::~Translator()
{
	delete _pImpl;
	_pImpl = NULL;
}