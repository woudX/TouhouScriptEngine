#include "THScriptFull.h"
#include "function.h"

THScriptFull::THScriptFull():_streamIdx(-1)
{

}

THScriptFull::THScriptFull(const THScriptFull& rhs):
	scriptStream(rhs.scriptStream),
	_lastGroup(new QuadGroup(*(rhs._lastGroup)))
{
	_streamIdx = rhs._streamIdx;
}

THScriptFull& THScriptFull::operator= (const THScriptFull& rhs)
{
	if ((&rhs) != this)
	{
		scriptStream = rhs.scriptStream;
		_lastGroup = new QuadGroup(*(rhs._lastGroup));
		_streamIdx = rhs._streamIdx;
	}

	return *this;
}

void THScriptFull::AddToStream(string str) 
{
	vector<string> result = split(str, ' ');

	for (int i = 0; i < result.size(); ++i)
	{
		scriptStream.push_back(result[i]);
	}
}

string THScriptFull::_NextWord()
{
	++_streamIdx;

	if (_streamIdx < scriptStream.size())
		return scriptStream[_streamIdx];
	else
		return "NULL";
}

string THScriptFull::_RetrackWord(int num)
{
	_streamIdx -= num;

	if (_streamIdx < 0)
		cout << "脚本翻译过程中单词流越界" << endl;
	else
		return scriptStream[_streamIdx];
}

void THScriptFull::_MakeNewQuad(string op, string arg_1, string arg_2, string obj, string lineID)
{
	Quad* quad;

	if (op == "")
		quad = new Quad("SYS_V_END", arg_1, arg_2, obj);
	else
		quad = new Quad(op, arg_1, arg_2, obj);

	if (lineID != "")
		quad->lineID = lineID;

	_lastGroup->AddQuad(quad);
}

void THScriptFull::TranslateScript()
{
	string st, op, arg_1, arg_2, obj;
	string l_str,r_str, cmp_str;

	while ((st = _NextWord()) != "NULL")
	{
		string lineID = "";
		op = "", arg_1 = "", arg_2 = "", obj = "";

		if (st[0] == '@')									// 脚本组
		{
			QuadGroup* quadGroup = new QuadGroup(st);
			scriptGroup.push_back(quadGroup);

			_lastGroup = quadGroup;

			continue;
		}

		while (st[st.length()- 1] == ':')					// 行号 
		{
			lineID += st;
			st = _NextWord();
		}

		if (st == "iffalse" || st == "if")					// if、iffalse语句
		{
			op = st;

			// 获取判断条件
			l_str = _NextWord();
			cmp_str = _NextWord();
			
			if (cmp_str == "goto")
			{
				obj = _NextWord();
			}
			else
			{
				r_str = _NextWord();
				arg_1 = l_str + " " + cmp_str + " " + r_str;

				// 读取跳转行号
				_NextWord();
				obj = _NextWord();
			}
		}
		else if (st == "push" || st == "call" || st == "pop")
		{
			op = st;
			arg_1 = _NextWord();
		}
		else if (st == "goto")
		{
			op = st;
			obj = _NextWord();
		}
		else if (st[0] == '@')	// 进入下一区域
		{
			_MakeNewQuad("SYS_V_END", arg_1, arg_2, obj, lineID);	// 直接创建结尾语句
			_RetrackWord(1);

			continue;
		}
		else	// 存在赋值情况
		{
			obj = st;

			st = _NextWord();
			if (st == "+=" || st == "-=" || st == "*=" || st == "/=")	// 简化运算符
			{
				op = st;
				arg_1 = _NextWord();
			}
			else if (st == "=")
			{
				st = _NextWord();

				if (st == "+" || st == "++" || st == "-" || st == "--" || st == "!" || st == "call") // 一元运算符
				{
					op = st;
					arg_1 = _NextWord();
				}
				else 
				{
					arg_1 = st;

					st = _NextWord();
					if (st == "+" || st == "-" || st == "*" || st == "/" || st == ">" || st == ">=" || st == "<" 
						|| st == "<=" || st == "==" || st == "!=")	// 二元运算符
					{
						op = st;
						arg_2 = _NextWord();
					}
					else
					{
						op = "=";
						_RetrackWord(1);
					}
				}
			}
		}

		_MakeNewQuad(op, arg_1, arg_2, obj, lineID);
	}
}

THScriptFull::~THScriptFull()
{

}