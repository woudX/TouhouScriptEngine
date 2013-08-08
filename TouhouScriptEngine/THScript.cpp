#include "THScript.h"
#include "function.h"

THScript::THScript():symRoot(NULL)
{

}

THScript::THScript(const THScript& rhs)
	:fileName(rhs.fileName),
	touhouScript(rhs.touhouScript),
	title(rhs.title),
	text(rhs.text),
	music(rhs.music),
	image(rhs.image),
	background(rhs.background),
	player(rhs.player),
	scriptVersion(rhs.scriptVersion),
	symRoot(new SymbolTable(*(rhs.symRoot)))
{
	for (vector<QuadGroup*>::const_iterator itor = rhs.scriptGroup.begin(); 
		itor != rhs.scriptGroup.end(); ++itor)
	{
		QuadGroup* quadGroup = new QuadGroup(*(*itor));
		scriptGroup.push_back(quadGroup);
	}
}

THScript& THScript::operator= (const THScript& rhs)
{
	if (&rhs != this)
	{
		fileName = rhs.fileName;
		touhouScript = rhs.touhouScript;
		title = rhs.title;
		text = rhs.text;
		music = rhs.music;
		image = rhs.image;
		background = rhs.background;
		player = rhs.player;
		scriptVersion = rhs.scriptVersion;
		symRoot = new SymbolTable(*(rhs.symRoot));

		for (vector<QuadGroup*>::const_iterator itor = rhs.scriptGroup.begin();
			itor != rhs.scriptGroup.end(); ++itor)
		{
			QuadGroup* quadGroup = new QuadGroup(*(*itor));
			scriptGroup.push_back(quadGroup);
		}
	}

	return *this;
}

void THScript::SetValue(string varStr, string value)
{
	if (varStr == "#TouhouScript")
		touhouScript = value;
	else if (varStr == "#Title")
		title = value;
	else if (varStr == "#Text")
		text = value;
	else if (varStr == "#Music")
		music = value;
	else if (varStr == "#Image")
		image = value;
	else if (varStr == "#BackGround")
		background = value;
	else if (varStr == "#Player")
		player = value;
	else if (varStr == "#ScriptVersion")
		scriptVersion = value;
}

THScript::~THScript()
{
	for (vector<QuadGroup*>::iterator itor = scriptGroup.begin(); itor != scriptGroup.end(); )
		if (*itor == NULL)
		{
			delete *itor;
			*itor = NULL;
			itor = scriptGroup.erase(itor);
		}
		else
			++itor;
	scriptGroup.clear();

	if (symRoot != NULL)
	{
		delete symRoot;
		symRoot = NULL;
	}
}