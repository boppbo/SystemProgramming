/*
 * TreeVisitorPrintTree.h
 *
 *  Created on: Jun 1, 2017
 *      Author: boris
 */

#ifndef PARSER_INCLUDES_TREEVISITORPRINTTREE_H_
#define PARSER_INCLUDES_TREEVISITORPRINTTREE_H_

#include "TreeVisitor.h"

class TreeVisitorPrintTree : public TreeVisitor {
public:
	TreeVisitorPrintTree();
	virtual ~TreeVisitorPrintTree();

	virtual void visit(Leaf* leaf) override;
	virtual void visit(Node* node) override;

private:
	void print(Tree* node);
	int indent = 0;
};

#endif /* PARSER_INCLUDES_TREEVISITORPRINTTREE_H_ */
