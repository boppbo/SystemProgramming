#include "../includes/Leaf.h"
#include <iostream>
#include <iomanip>

Leaf::Leaf(Token* token, nodeType type) {
	this->_token = token;
	this->_type = type;
	if (this->_type == nodeType::Op) {
		switch (token->_type) {
			case TOKEN_PLUS: {	
				_opType = OpType::opPlus;
				break; 
			}
			case TOKEN_MINUS: {
				_opType = OpType::opMinus;
				break;
			}
			case TOKEN_STAR: {
				_opType = OpType::opMult;
				break; 
			}
			case TOKEN_COLON: {	
				_opType = OpType::opDiv;
				break;
			}
			case TOKEN_SMALLER: {	
				_opType = OpType::opLess;
				break;
			}
			case TOKEN_GREATER: {	
				_opType = OpType::opGreater;
				break; 
			}
			case TOKEN_EQUALS: {	
				_opType = OpType::opEqual;
				break; 
			}
			case TOKEN_ASSIGN2: {
				_opType = OpType::opUnEqual;
				break; 
			}
			case TOKEN_AND: {	
				_opType = OpType::opAnd;
				break; 
			}
		}
	}
}

void Leaf::print(int indent)
{
	cout << " " << setw(indent) << "Leaf ("<<  this->_token->getTypeAsString() << ") \n";
	for each(Node* child in this->_children) {
		if(child != nullptr)
			child->print(indent+4);
	}
}