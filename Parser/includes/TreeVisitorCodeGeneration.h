/*
 * TreeVisitorCodeGeneration.h
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#ifndef PARSER_INCLUDES_TREEVISITORCODEGENERATION_H_
#define PARSER_INCLUDES_TREEVISITORCODEGENERATION_H_

#include "TreeVisitor.h"


class TreeVisitorCodeGeneration : public TreeVisitor {
public:
	TreeVisitorCodeGeneration();
	virtual ~TreeVisitorCodeGeneration();

	void visit(Leaf* leaf);
	void visit(Node* node);
};

#endif /* PARSER_INCLUDES_TREEVISITORCODEGENERATION_H_ */
