/*
* ArrayNode.h
*
*  Created on: May 10, 2017
*      Author: Maksim Sunjajkin
*/


#ifndef PARSER_INCLUDES_IntegerNode_H_
#define PARSER_INCLUDES_IntegerNode_H_

#include "../Leaf.h"
#include "../../../Scanner/includes/Token.h"

class IntegerNode : public Leaf {

	int value;


public:
	IntegerNode() {
		this->value = 0;
	}
	IntegerNode(Token* token) {
		this->value = token->_integerValue;
		this->token = token;
	}
	virtual void accept(class TreeVisitor &visitor);

	virtual int getValue() {
		return this->value;
	}
};

#endif /* PARSER_INCLUDES_IntegerNode_H_ */

