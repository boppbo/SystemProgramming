#include "../includes/Node.h"
#include <iostream>
#include <iomanip>

Node::Node(nodeType type) {
	this->_type = type;
}

void Node::print(int indent)
{
	cout << " " << setw(indent) << this->getTypeAsString() << " \n";
	for each(Node* child in this->_children) {
		if(child != nullptr)
			child->print(indent+4);
	}
}
