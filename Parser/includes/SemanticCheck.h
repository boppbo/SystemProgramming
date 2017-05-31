#ifndef SEMANTIC_CHECK_H
#define SEMANTIC_CHECK_H

#include "ParseTree.h"
#include "Node.h"
#include "Leaf.h"
#include "Visitor.h"

class SemanticCheck : public Visitor {
public:
	SemanticCheck();
	virtual ~SemanticCheck();
	void check(ParseTree* tree);

	virtual void visit(Node* node);
	virtual void visit(Leaf* leaf);
};

#endif /* SEMANTIC_CHECK_H */
