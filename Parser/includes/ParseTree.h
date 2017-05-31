#ifndef ParseTree_H__
#define ParseTree_H__

#include "Node.h"

class ParseTree {
	
public:
	ParseTree();
	ParseTree(Node* prog);
	Node* _prog;
};

#endif