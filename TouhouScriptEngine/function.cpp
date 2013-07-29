#include "function.h"
#include "Tag.h"

string IntToString(int v_int)
{
	char ptr[20];
	_itoa(v_int, ptr, 10);
	string r_value(ptr);
	
	return r_value;
}

string DoubleToString(double v_double)
{
	char _ptr[20];
	_gcvt(v_double, 5, _ptr);

	int len = strlen(_ptr);

	if (_ptr[len - 1] == '.')
	{
		_ptr[len - 1] = '\0';
	}

	string r_value(_ptr);

	return r_value;
}

string AscToSign(int tag)
{
	string str="";

	if (tag < 256)
		str = (char)tag;
	else
	{
		switch (tag)
		{
		case IDEN:	str = "IDEN"; break;
		case STRCON: str = "STRCON"; break;
		case INTCON: str = "INTCON"; break;
		case DOUBLECON: str = "DOUBLECON"; break;
		case INTTK: str = "INTTK"; break;
		case VARTK: str = "VARTK"; break;
		case IFTK: str = "IFTK"; break;
		case ELSETK: str = "ELSETK"; break;
		case WHILETK: str = "WHILETK"; break;
		case LOOPTK: str = "LOOPTK";	break;
		case PLUS: str = "PLUS"; break;
		case PLUSPLUS: str = "PLUSPLUS"; break;
		case MINUS: str = "MINUS"; break;
		case MINUSMINUS: str = "MINUSMINUS"; break;
		case MULT: str = "MULT"; break;
		case DIV: str = "DIV"; break;
		case LSS: str = "LSS"; break;
		case LEQ: str = "LEQ"; break;
		case GRE: str = "GRE"; break;
		case GEQ: str = "GEQ"; break;
		case EQL: str = "EQL"; break;
		case NEQ: str = "NEQ"; break;
		case ASSIGN: str = "ASSIGN"; break;
		case SEMICN: str = "SEMICN"; break;
		case COMMA: str = "COMMA"; break;
		case DQMARK: str = "DQMARK"; break;
		case LPARENT: str = "LPARENT"; break;
		case RPARENT: str = "RPARENT"; break;
		case LBRACE: str = "LBRACE"; break;
		case RBRACE: str = "RBRACE"; break;
		case STAGEMAIN: str = "STGAEMAIN"; break;
		case ENEMYMAIN: str = "ENEMYMAIN"; break;
		case MAINLOOPTK: str = "MAINLOOPTK"; break;
		case INITTK: str = "INITTK"; break;
		case FINALTK: str = "FINALTK"; break;
		case BACKGROUNDTK: str = "BACKGROUNDTK"; break;
		case TOUHOUSCRIPT: str = "TOUHOUSCRIPT"; break;
		case TITLE: str = "TITLE"; break;
		case TEXT: str = "TEXT"; break;
		case MUSIC: str = "MUSIC"; break;
		case IMAGE: str = "IMAGE"; break;
		case BACKGROUND: str = "BACKGROUND"; break;
		case PLAYER: str = "PLAYER"; break;
		case SCRIPTVERSION: str = "SCRIPTVERSION"; break;
		case OR: str = "OR"; break;
		case AND: str = "AND"; break;
		case NOT: str = "NOT"; break;
		case NOTE: str = "NOTE"; break;
		case NOTE_A: str = "NOTE_A"; break;
		case NOTE_B: str = "NOTE_B"; break;
		case NULL_A: str = "NULL_A"; break;
		case FUNCTK: str = "FUNCTK"; break;
		case FORTK:	str = "FORTK"; break;
		case ASSIGN_PLUS: str = "ASSIGN_PLUS"; break;
		case ASSIGN_MINUS: str = "ASSIGN_MINUS"; break;
		case ASSIGN_MULT: str = "ASSIGN_MULT"; break;
		case ASSIGN_DIV: str = "ASSIGN_DIV"; break;
		default: str = "ERROR"; break;
		}
	}

	return str;
}

vector<string> split(string str, char ch) 
{
	vector<string> result;
	string lstr = str + ch;
	int size = lstr.size();

	int i = 0;
	while (size != 0)
	{
		
		while (lstr[i] == ch && i < size) { ++i; }
		int start = i;

		while (lstr[i] != ch && i < size) { ++i; }
		int end = i;

		string ans = lstr.substr(start, end - start);

		if (start != end)
			result.push_back(ans);

		lstr = lstr.substr(end, size - end);

		size = lstr.size();
		i = 0;

	}

	return result;
}