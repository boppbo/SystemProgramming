/*
* ArrayNode.h
*
*  Created on: May 10, 2017
*      Author: Maksim Sunjajkin
*/


#ifndef PARSER_INCLUDES_IndexNode_H_
#define PARSER_INCLUDES_IndexNode_H_

#include "Node.h"

class IndexNode : public Node {

	ExpNode* exp;


public:
	IndexNode() {
		this->exp = 0;
	}
	virtual ~IndexNode() {
		delete this->exp;
	}
	virtual void addChild(ExpNode* newExp) {
		this->exp = newExp;
	}
	virtual void accept(class TreeVisitor &visitor);
};

#endif /* PARSER_INCLUDES_ArrayNode_H_ */

