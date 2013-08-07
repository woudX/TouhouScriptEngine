#ifndef _SCRIPT_TRANS
#define _SCRIPT_TRANS

class Translator
{
public:
	Translator();

	THScript*	Translate(THScript *script);	// 翻译脚本
	void		Add(string word);				// 添加到中间代码流

	~Translator();
private:
	class Impl;
	Impl *_pImpl;
};

#endif // !_SCRIPT_TRANS
