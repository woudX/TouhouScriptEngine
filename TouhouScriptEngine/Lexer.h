#ifndef _H_LEXER
#define _H_LEXER

#include "stdafx.h"
#include "Tag.h"
#include "FileMgr.h"

class Token
{
public:
	int tag;			// 保存该词对应的编号
	Token();
	Token(int t);
	virtual string ToString();
	virtual string ToSign();
};

class Num : public Token
{
public:
	int value;			// 该单词的值
	Num();
	Num(int v);
	string ToString();
};

class Double : public Token
{
public:
	double value;
	Double();
	Double(double v);
	string ToString();
};

class Word : public Token
{
public:
	string lexeme;		// 该字符串的内容
	Word();
	Word(string s, int tag);
	string ToString();

	static Word *eql, *neq, *leq, *geq, *lss, *gre, *and, *or, *not;
	static Word *plus, *minus, *plusplus, *minusminus, *mult, *div, *assign, *semicn, *comma, *dot;
	static Word *assign_plus, *assign_minus, *assign_mult, *assign_div;
	static Word *lparent, *rparent, *lbrace, *rbrace;
	static Word *True, *False, *temp;
	static Word *note, *note_a, *note_b;
	static Word *null;
};

class Type : public Word {
public:
	int width;			// 用于分配存储空间
	static Type *Double, *Int, *Func, *String;

	Type();
	Type(string s, int tag, int w);
	
	static bool numeric(Type* p);
	static Type* max(Type* l_type, Type* r_type);

};



class Lexer
{
public:
	int lineID;			// 当前行数
	char peek;			// 下一个要读取的字符
	int line;			// 当前读取单词的行数
	int nowWord;		// 当前读取的单词

	FileMgr* fileManager;	// 文件管理器
	vector<Token*> wordStream;	// 单词流
	map<string, Word*> words;	// 存储表
	vector<int>	wordLine;		// 单词流对应的行数

	Lexer();			
	Token* Scan();		// 读取一个单词
	void ReadCh();		// 读取一个字符
	bool ReadCh(char ch);		// 读取判断字符是不是ch
	void Reserve(Word* w);		// 保存保留字
	void MakeWordStream();		// 构造单词流

	Token* ScanWord();			// 获取单词流的一个单词
	Token* RetrackWord(int num);	// 倒读指定数量的单词

	string getString();			// 读取一个字符串

};
#endif