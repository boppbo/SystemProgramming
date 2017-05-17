/*
* ProgNode.h
*
*  Created on: May 10, 2017
*      Author: Maksim Sunjajkin
*/


#ifndef PARSER_INCLUDES_Exp2Node_H_
#define PARSER_INCLUDES_Exp2Node_H_

#include "Node.h"

class Exp2Node : public Node {

	ExpNode* exp;
	IdentNode* ident;
	IndexNode* index;
	Exp2Node* exp2;
	IntegerNode* integer;

public:
	Exp2Node() {
		this->exp = 0;
		this->ident = 0;
		this->index = 0;
		this->exp2 = 0;
		this->integer = 0;
	}
	virtual ~Exp2Node() {
		delete this->exp;
		delete this->ident;
		delete this->index;
		delete this->exp2;
		delete this->integer;
	}
	virtual void addChild(Exp2Node* newExp2) {
		this->exp2 = newExp2;
	}
	virtual void addChild(ExpNode* newExp) {
		this->exp = newExp;
	}
	virtual void addChild(IdentNode* newIdent) {
		this->ident = newIdent;
	}
	virtual void addChild(IndexNode* newIndex) {
		this->index = newIndex;
	}
	virtual void addChild(IntegerNode* newInteger) {
		this->integer = newInteger;
	}
	virtual void accept(class TreeVisitor &visitor);
};

#endif /* PARSER_INCLUDES_Exp2Node_H_ */
#pragma once
