/*
* ProgNode.h
*
*  Created on: May 10, 2017
*      Author: Maksim Sunjajkin
*/


#ifndef PARSER_INCLUDES_Op_ExpNode_H_
#define PARSER_INCLUDES_Op_ExpNode_H_

#include "Node.h"

class Op_ExpNode : public Node {

	OpNode* op;
	ExpNode* exp;

public:
	Op_ExpNode() {
		this->exp = 0;
		this->op = 0;
	}
	virtual ~Op_ExpNode() {
		delete this->exp;
		delete this->op;
	}
	virtual void addChild(ExpNode* newExp) {
		this->exp = newExp;
	}
	virtual void addChild(OpNode* newOp) {
		this->op = newOp;
	}
	virtual void accept(class TreeVisitor &visitor);
};

#endif /* PARSER_INCLUDES_Op_ExpNode_H_ */

