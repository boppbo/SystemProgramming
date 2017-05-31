#include "..\includes\ParseTree.h"

ParseTree::ParseTree() {
	_prog = NULL;
}
ParseTree::ParseTree(Node* prog)
{
	this->_prog = prog;
}