/*
* ArrayNode.h
*
*  Created on: May 10, 2017
*      Author: Maksim Sunjajkin
*/


#ifndef PARSER_INCLUDES_ArrayNode_H_
#define PARSER_INCLUDES_ArrayNode_H_

#include "Node.h"

class ArrayNode: public Node {

	IntegerNode* integer;
	IdentNode* ident;

public:
	ArrayNode() {
		integer = 0;
		ident = 0;
	}
	virtual ~ArrayNode() {
		delete integer;
	}
	virtual void addChild(IntegerNode* newInteger) {
		integer = newInteger;
	}
	virtual void addChild(IdentNode* newIdent) {
		ident = newIdent;
	}
	virtual void accept(class TreeVisitor &visitor)
};

#endif /* PARSER_INCLUDES_ArrayNode_H_ */

