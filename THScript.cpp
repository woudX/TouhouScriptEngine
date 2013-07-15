#include "THScript.h"

THScript::THScript():top(NULL)
{

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