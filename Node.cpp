#include "Node.h"

/// 根节点
//////////////////////////////////////////////////////////////////////////

int Node::labels = 0;

Node::Node():lexline(0) {}

Node::Node(int l):lexline(l) {}

void Node::error(string s)
{
	cout << "Error:" << "near line" << lexline << ": " << s << endl;
}

int Node::newlabel()
{
	++labels;
}

Node::~Node()
{

}

/// 表达式
//////////////////////////////////////////////////////////////////////////

