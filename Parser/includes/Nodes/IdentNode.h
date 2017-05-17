/*
* ArrayNode.h
*
*  Created on: May 10, 2017
*      Author: Maksim Sunjajkin
*/


#ifndef PARSER_INCLUDES_IdentNode_H_
#define PARSER_INCLUDES_IdentNode_H_

#include "../Leaf.h"
#include "../../../Scanner/includes/Token.h"
#include "./Node.h"

class IdentNode : public Leaf {
public:
	IdentNode() {
		this->token = 0;
	}
	IdentNode(Token* token) {
		this->token = token;
	}
	virtual void accept(class TreeVisitor &visitor);
	virtual char getIdent() {
		return this->token->_info->getName;
	}
	virtual TType getType() {
		return this->token->_type;
	}
};

#endif /* PARSER_INCLUDES_IdentNode_H_ */


