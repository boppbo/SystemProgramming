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
	TreeVisitorTypeCheck() { }
	virtual ~TreeVisitorTypeCheck() { }
	virtual void visit(Node* node) override;
	virtual void visit(Leaf* leaf) override;
protected:
	virtual bool isInt(Node* node, int index);
	virtual bool isDefined(Node* node, int index);
	virtual bool isArray(Node* node, int index);
	virtual int getLine(Node* node, int index);
	virtual int getColumn(Node* node, int index);
	virtual const Token getToken(Node* node,int index);
	virtual void raiseError(char const * reason, Node* node, int index);
};

#endif /* PARSER_INCLUDES_TREEVISITORTYPECHECK_H_ */
