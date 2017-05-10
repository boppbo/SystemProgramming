/*
* OpNode.h
*
*  Created on: May 10, 2017
*      Author: Maksim Sunjajkin
*/


#ifndef PARSER_INCLUDES_OpNode_H_
#define PARSER_INCLUDES_OpNode_H_

#include "../Leaf.h"
#include "../../../Scanner/includes/Token.h"

class OpNode : public Leaf {


public:
	OpNode(Token* token) {
		switch (token->_type)
		{
			case TOKEN_PLUS: {
				
				break;
			}
			case TOKEN_MINUS: {
				break;
			}
			case TOKEN_STAR: {
				break;
			}
			case TOKEN_COLON: {
				break;
			}
			case TOKEN_SMALLER: {
				break;
			}
			case TOKEN_GREATER: {
				break;
			}
			case TOKEN_EQUALS: {
				break;
			}
			case TOKEN_ASSIGN: {
				break;
			}
			case TOKEN_ASSIGN2: {
				break;
			}
			default: break;
		}
	}
	virtual ~OpNode();
	virtual void accept(class TreeVisitor &visitor) = 0;
};

#endif /* PARSER_INCLUDES_OpNode_H_ */
