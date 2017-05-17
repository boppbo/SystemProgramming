/*
 * Tree.cpp
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#include "../includes/Tree.h"

Tree::Tree(ProgNode* ProgNode) {
	this->prog = prog;
}

Tree::~Tree() {
	delete this->prog;
}

