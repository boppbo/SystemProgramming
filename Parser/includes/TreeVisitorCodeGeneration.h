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

protected:
	virtual void decl(Node *node);
	virtual void array(Node *node);
	virtual void statement(Node *node);
	virtual void statementIf(Node *node);
	virtual void statementWhile(Node *node);
	virtual void expression(Node *node);
	virtual void expression2(Node *node);
	virtual void index(Node *node);

	virtual void addCode(char const * code, bool newLine = false);
	virtual void addCommand(char const * command, char const * const arg = nullptr, bool newLine = true);
	virtual void addLabeledCommand(char const * const jumpLabel, char const * command, char const * const arg = nullptr, bool newLine = true);
	virtual char const * getNextLabel();
private:
	std::ostream& _code;
	int _labelId = 0;
};

#endif /* PARSER_INCLUDES_TREEVISITORCODEGENERATION_H_ */
