#include "..\includes\ParseTree.h"

ParseTree::ParseTree() {
}
ParseTree::ParseTree(Node* prog)
{
	this->_prog = prog;
}