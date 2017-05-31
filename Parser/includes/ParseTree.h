/*
* ParseTree.h
*/

#ifndef PARSETREE_H_
#define PARSETREE_H_

#include "Node.h"

class ParseTree {

public:
	ParseTree();
	ParseTree(Node* prog);
	Node* prog;
	Node* getProg() {
		return prog;
	};
};

#endif /* PARSETREE_H_ */