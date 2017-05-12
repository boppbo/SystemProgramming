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
				type = PlusType;
				break;
			}
			case TOKEN_MINUS: {
				type = MinusType;
				break;
			}
			case TOKEN_STAR: {
				type = StarType;
				break;
			}
			case TOKEN_COLON: {
				type = CollonType;
				break;
			}
			case TOKEN_SMALLER: {
				type = SmallerType;
				break;
			}
			case TOKEN_GREATER: {
				type = GreaterType;
				break;
			}
			case TOKEN_EQUALS: {
				type = EqualsType;
				break;
			}
			case TOKEN_ASSIGN: {
				type = AssigneType;
				break;
			}
			case TOKEN_ASSIGN2: {
				type = Assigne2Type;
				break;
			}
			default: {
				type = ErrorType;
				break;
			}
		}
	}
	virtual ~OpNode();
	virtual void accept(class TreeVisitor &visitor) = 0;
};

#endif /* PARSER_INCLUDES_OpNode_H_ */
