/*
 * Leaf.cpp
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#include "../includes/Leaf.h"
#include "../includes/TreeVisitor.h"
#include "../../Common/includes/cstring.h"
#include <stdexcept>

Leaf::Leaf(Token const* token, NType nodeType) : Tree(nodeType), _token(token) {
	if (nodeType == NType::Op) {
		this->setOperationTypeFromToken();
	}
}

Leaf::~Leaf() {
	delete this->_token;
}

void Leaf::accept(TreeVisitor *visitor) {
	visitor->visit(this);
}

void Leaf::setOperationTypeFromToken() {
	switch (this->_token->_type) {
				case TOKEN_PLUS:
					this->_opType = OpType::opPlus;
					break;
				case TOKEN_MINUS:
					this->_opType = OpType::opMinus;
					break;
				case TOKEN_STAR:
					this->_opType = OpType::opMult;
					break;
				case TOKEN_COLON:
					this->_opType = OpType::opDiv;
					break;
				case TOKEN_SMALLER:
					this->_opType = OpType::opLess;
					break;
				case TOKEN_GREATER:
					this->_opType = OpType::opGreater;
					break;
				case TOKEN_EQUALS:
					this->_opType = OpType::opEqual;
					break;
				case TOKEN_ASSIGN2:
					this->_opType = OpType::opUnEqual;
					break;
				case TOKEN_AND:
					this->_opType = OpType::opAnd;
					break;
				default:
					throw std::domain_error(strcat("Invalid operation: ", this->_token->getTypeAsString()));
			}
}
