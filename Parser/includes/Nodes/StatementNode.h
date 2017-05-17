/*
* ProgNode.h
*
*  Created on: May 10, 2017
*      Author: Maksim Sunjajkin
*/


#ifndef PARSER_INCLUDES_Statement_H_
#define PARSER_INCLUDES_Statement_H_

#include "Node.h"

class StatementNode : public Node {

	StatementsNode* statements;
	IdentNode* ident;
	IndexNode* index;
	ExpNode* exp;
	StatementNode* statement1;
	StatementNode* statement2;
	bool st2 = false;

public:
	StatementNode() {
		this->statements = 0;
		this->ident = 0;
		this->index = 0;
		this->exp = 0;
		this->statement1 = 0;
		this->statement2 = 0;
	}
	virtual ~StatementNode() {
		delete this->statements;
		delete this->ident;
		delete this->index;
		delete this->exp;
		delete this->statement1;
		delete this->statement2;
	}
	virtual void addChild(IdentNode* newIdent) {
		this->ident = newIdent;
	}
	virtual void addChild(StatementsNode* newStatments) {
		this->statements = newStatments;
	}
	virtual void addChild(IndexNode* newIndex) {
		this->index = newIndex;
	}
	virtual void addChild(ExpNode* newExp) {
		this->exp = newExp;
	}
	virtual void addChild(StatementNode* newStatement) {
		if (!st2) {
			this->statement1 = newStatement;
			st2 = !st2;
		}
		else {
			this->statement2 = newStatement;
		}
	}
	virtual void accept(class TreeVisitor &visitor);
};

#endif /* PARSER_INCLUDES_Statement_H_ */

