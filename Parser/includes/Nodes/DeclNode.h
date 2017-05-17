/*
* ProgNode.h
*
*  Created on: May 10, 2017
*      Author: Maksim Sunjajkin
*/


#ifndef PARSER_INCLUDES_DeclNode_H_
#define PARSER_INCLUDES_DeclNode_H_

#include "Node.h"

class DeclNode : public Node {

	ArrayNode* array;
	IdentNode* ident;

public:
	DeclNode() {
		this->array = 0;
	}
	virtual ~DeclNode() {
		delete this->array;
	}
	virtual void addChild(ArrayNode* newArray) {
		this->array = newArray;
	}
	virtual void addChild(IdentNode* newIdent) {
		this->ident = newIdent;
	}
	virtual void accept(class TreeVisitor &visitor)
};

#endif /* PARSER_INCLUDES_DeclNode_H_ */
