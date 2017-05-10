/*
 * Node.cpp
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#include "../includes/Node.h"
#include "../includes/TreeVisitor.h"

Node::Node() {
	// TODO Auto-generated constructor stub

}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

void Node::accept(TreeVisitor &visitor) {
	visitor.visit(this);
}
