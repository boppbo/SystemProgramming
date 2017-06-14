/*
 * TreeVisitorCodeGeneration.cpp
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#include "../includes/TreeVisitorPrintTree.h"

#include <iostream>
#include <iomanip>
using namespace std;

TreeVisitorPrintTree::TreeVisitorPrintTree() {
}

TreeVisitorPrintTree::~TreeVisitorPrintTree() {
}

void TreeVisitorPrintTree::visit(Leaf *leaf) {
	this->print(leaf);
}

void TreeVisitorPrintTree::visit(Node *node) {
	this->print(node);

	indent += 4;
	for(unsigned int i = 0; i < node->getChildrenSize(); i++) {
		node->getChild(i)->accept(this);
	}
	indent -= 4;
}

void TreeVisitorPrintTree::print(Tree* node) {
	clog << left << setw(indent) << " ";
	auto asLeaf = dynamic_cast<Leaf*>(node);
	auto asNode = dynamic_cast<Node*>(node);

	if (asLeaf)
		clog << "Leaf (";

	if(asNode && asNode->isEpsilon())
		clog << "(eps)";
	clog << node->getTypeAsString();

	if (asLeaf)
		clog << "): " << asLeaf->getToken().getTypeAsString();

	clog << endl;
}
