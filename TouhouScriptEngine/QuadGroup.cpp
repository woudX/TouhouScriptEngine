#include "QuadGroup.h"

QuadGroup::QuadGroup():nowQuad(0)
{

}

QuadGroup::QuadGroup(string v_type):nowQuad(0),type(v_type)
{

}

void QuadGroup::AddQuad(Quad* quad)
{
	if (quad != NULL)
		quadList.push_back(quad);
}

QuadGroup::~QuadGroup()
{
	for (vector<Quad*>::iterator itor = quadList.begin(); itor != quadList.end(); )
	{
		if (*itor != NULL)
		{
			delete *itor;
			*itor = NULL;
			itor = quadList.erase(itor);
		}
		else
			itor++;
	}

	quadList.clear();
}