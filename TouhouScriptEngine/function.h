#ifndef _H_FUNCTION
#define _H_FUNCTION

#include "stdafx.h"

using namespace std;

// ×ª»»º¯Êý
extern string IntToString(int v_int);
extern string DoubleToString(double v_double);
extern int StringToInt(string str);
extern double StringToDouble(string str);
extern string AscToSign(int tag);
extern vector<string> split(string str, char ch);
extern int isContain(string str, string substr);
extern string removeSystemMark(string str, string substr);
#endif
