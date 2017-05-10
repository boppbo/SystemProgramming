/*
 * TreeVisitorCodeGeneration.h
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#ifndef PARSER_INCLUDES_TREEVISITORCODEGENERATION_H_
#define PARSER_INCLUDES_TREEVISITORCODEGENERATION_H_

#include "TreeVisitor.h"
#include <iostream>

class TreeVisitorCodeGeneration : public TreeVisitor {
public:
	TreeVisitorCodeGeneration(std::ostream& codeOut);
	virtual ~TreeVisitorCodeGeneration();

	virtual void visit(Leaf* leaf) override;
	virtual void visit(Node* node) override;
private:
	std::ostream& _out;
};

#endif /* PARSER_INCLUDES_TREEVISITORCODEGENERATION_H_ */
