/*
 * TreeVisitorTypeCheck.h
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#ifndef PARSER_INCLUDES_TREEVISITORTYPECHECK_H_
#define PARSER_INCLUDES_TREEVISITORTYPECHECK_H_

#include "TreeVisitor.h"
#include "TreeVisitorTypeCheckResult.h"

class TreeVisitorTypeCheck: public TreeVisitor {
private:
	TreeVisitorTypeCheckResult _result;
public:
	TreeVisitorTypeCheck(TreeVisitorTypeCheckResult result) : _result(result) { }
	virtual ~TreeVisitorTypeCheck();

	void visit(Leaf* leaf);
	void visit(Node* node);
};

#endif /* PARSER_INCLUDES_TREEVISITORTYPECHECK_H_ */
