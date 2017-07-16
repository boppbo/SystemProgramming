/*
 * TreeVisitorTypeCheck.h
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#ifndef PARSER_INCLUDES_TREEVISITORTYPECHECK_H_
#define PARSER_INCLUDES_TREEVISITORTYPECHECK_H_

#include "TreeVisitor.h"

class TreeVisitorTypeCheck: public TreeVisitor {
public:
	TreeVisitorTypeCheck();
	virtual ~TreeVisitorTypeCheck();
	void check(Tree* tree);
	virtual bool isInt(Node* node, int index);
	virtual bool isArray(Node* node, int index);
	virtual int getLine(Node* node, int index);
	virtual int getColumn(Node* node, int index);
	virtual const Token getToken(Node* node,int index);
	virtual bool compType(Node* node,int index, NType type);

	virtual void visit(Node* node);
	virtual void visit(Leaf* leaf);
};

#endif /* PARSER_INCLUDES_TREEVISITORTYPECHECK_H_ */
