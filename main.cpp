#include "stdafx.h"
#include "Lexer.h"

int main()
{
	FileManager* fileManager = 0;
	fileManager = fileManager->Instance();

	Lexer* lexer = new Lexer();

	fileManager->ReadCodeFile("test.txt");
	lexer->MakeWordStream();

	return 0;
}