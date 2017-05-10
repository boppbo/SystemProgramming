/*
 * Leaf.cpp
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#include "../includes/Leaf.h"
#include "../includes/TreeVisitor.h"

Leaf::Leaf() {
	// TODO Auto-generated constructor stub

}

Leaf::~Leaf() {
	// TODO Auto-generated destructor stub
}

void Leaf::accept(TreeVisitor &visitor) {
	visitor.visit(this);
}
