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
