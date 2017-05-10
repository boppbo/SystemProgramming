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
	virtual ~TreeVisitorTypeCheck();

	void visit(Leaf* leaf);
	void visit(Node* node);
};

#endif /* PARSER_INCLUDES_TREEVISITORTYPECHECK_H_ */
