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
	char ptr[20];
	_gcvt(v_double, 5, ptr);
	string r_value(ptr);

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
		default: str = "ERROR"; break;
		}
	}

	return str;
}