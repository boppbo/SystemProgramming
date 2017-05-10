/*
 * TreeVisitor.h
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#ifndef PARSER_INCLUDES_TREEVISITOR_H_
#define PARSER_INCLUDES_TREEVISITOR_H_

#include "Leaf.h"
#include "Node.h"

class TreeVisitor {
public:
	virtual ~TreeVisitor() { }
	virtual void visit(Leaf *leaf) = 0;
	virtual void visit(Node *node) = 0;
};

#endif /* PARSER_INCLUDES_TREEVISITOR_H_ */
