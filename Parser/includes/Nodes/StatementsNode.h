/*
* ProgNode.h
*
*  Created on: May 10, 2017
*      Author: Maksim Sunjajkin
*/


#ifndef PARSER_INCLUDES_StatementsNode_H_
#define PARSER_INCLUDES_StatementsNode_H_

#include "Node.h"

class StatementsNode : public Node {

	StatementNode* statement;
	StatementsNode* nextStatements;

public:
	StatementsNode() {
		this->statement = 0;
		this->nextStatements = 0;
	}
	virtual ~StatementsNode() {
		delete this->statement;
		delete this->nextStatements;
	}
	virtual void addChild(StatementNode* newStatement) {
		this->statement = newStatement;
	}
	virtual void addChild(StatementsNode* newStatements) {
		this->nextStatements = newStatements;
	}
	virtual void accept(class TreeVisitor &visitor);
};

#endif /* PARSER_INCLUDES_StatementsNode_H_ */