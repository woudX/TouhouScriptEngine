#ifndef _H_FUNCTION
#define _H_FUNCTION

using namespace std;

// 常量表
extern const double MATH_PI;
extern const double MATH_PI_D;

// 数学函数
extern double reg(double _deg);
extern double deg(double _reg);

// 转换函数
extern string IntToString(int v_int);
extern string DoubleToString(double v_double);
extern int StringToInt(string str);
extern double StringToDouble(string str);
extern string AscToSign(int tag);
extern vector<string> split(string str, char ch);
extern int isContain(string str, string substr);
extern string removeSystemMark(string str, string substr);
#endif
