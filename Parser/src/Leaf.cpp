#include "../includes/Leaf.h"
#include <iostream>
#include <iomanip>

Leaf::Leaf(Token* token) {
	this->_token = token;
	this->_type = leaf;
}

void Leaf::print(int indent)
{
	cout << " " << setw(indent) << "Leaf ("<<  this->_token->getTypeAsString() << ") \n";
	for each(Node* child in this->_children) {
		if(child != nullptr)
			child->print(indent+4);
	}
}