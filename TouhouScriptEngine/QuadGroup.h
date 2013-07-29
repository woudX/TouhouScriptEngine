#ifndef _H_QUADGROUP
#define _H_QUADGROUP

#include "Quad.h"

class QuadGroup
{
public:
	string type;				// 脚本组类型
	vector<Quad*> quadList;		// 四元式表单
	int nowQuad;				// 当前即将执行的脚本语句

	QuadGroup();
	QuadGroup(string v_type);
	void AddQuad(Quad* quad);	// 添加四元式
	
	~QuadGroup();
};

#endif // !_H_QUADGROUP
