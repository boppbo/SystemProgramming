/*
 * Node.cpp
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#include "../includes/Node.h"
#include "../includes/TreeVisitor.h"
#include <stdexcept>

Node::Node(NType nodeType) : Tree(nodeType) {
}

void Node::accept(TreeVisitor *visitor) {
	visitor->visit(this);
}

void Node::addChild(Tree* child) {
	if (child == nullptr)
		throw std::invalid_argument("child");

	this->_children.push(child);
}

Tree* Node::getChild(unsigned int index) const {
	return const_cast<Tree*>(&this->_children[index]);
}

unsigned int Node::getChildrenSize() const {
	return this->_children.getSize();
}

bool Node::isEpsilon() const {
	return this->_children.getSize() == 0;
}
