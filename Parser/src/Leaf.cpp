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
}

Leaf::~Leaf() {
	delete this->_token;
}

void Leaf::accept(TreeVisitor *visitor) {
	visitor->visit(this);
}

Token const& Leaf::getToken() const {
	return *this->_token;
}
