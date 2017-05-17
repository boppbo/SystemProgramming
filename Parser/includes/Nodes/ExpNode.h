/*
* ProgNode.h
*
*  Created on: May 10, 2017
*      Author: Maksim Sunjajkin
*/


#ifndef PARSER_INCLUDES_ExpNode_H_
#define PARSER_INCLUDES_ExpNode_H_

#include "Node.h"

class ExpNode : public Node {

	Exp2Node* exp2;
	Op_ExpNode* opExp;

public:
	ExpNode() {
		this->exp2 = 0;
		this->opExp = 0;
	}
	virtual ~ExpNode() {
		delete this->exp2;
		delete this->opExp;
	}
	virtual void addChild(Exp2Node* newExp2) {
		this->exp2 = newExp2;
	}
	virtual void addChild(Op_ExpNode* newOpExp) {
		this->opExp = newOpExp;
	}
	virtual void accept(class TreeVisitor &visitor);
};

#endif /* PARSER_INCLUDES_DeclNode_H_ */

