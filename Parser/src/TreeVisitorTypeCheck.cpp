/*
 * TreeVisitorTypeCheck.cpp
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#include "../includes/TreeVisitorTypeCheck.h"
#include <sstream>
#include <stdexcept>

//TODO comptype checks
void TreeVisitorTypeCheck::visit(Node* node) {
	switch (node->getType()) {
	case NType::Prog:
		node->getChild(0)->accept(this);
		node->getChild(1)->accept(this);
		break;
	case NType::Decls:
	case NType::Statements:
		if (node->isEpsilon())
			return;

		node->getChild(0)->accept(this);
		node->getChild(2)->accept(this);
		break;
	case NType::Decl: {
		auto arrayNode = static_cast<Node*>(node->getChild(1));
		arrayNode->accept(this);

		if (this->isDefined(node, 2)) {
			this->raiseError("identifier already defined", node, 2);
		}

		this->getToken(node, 2)._info->setIsArray(!arrayNode->isEpsilon());
		break;
	}
	case NType::Array:
		if (node->isEpsilon())
			return;

		if (getToken(node, 1)._integerValue < 1)
			this->raiseError("no valid dimension", node, 1);
		break;
	case NType::StatementIdent: {
		auto indexNode = static_cast<Node*>(node->getChild(1));

		node->getChild(3)->accept(this);
		indexNode->accept(this);

		if (!isDefined(node, 0))
			this->raiseError("identifier not defined", node, 0);
		else if (isInt(node, 0) && !indexNode->isEpsilon())
			this->raiseError("incompatible types. Declared as int", node, 0);
		else if (isArray(node, 0) && indexNode->isEpsilon())
			this->raiseError("incompatible types. Declared as int[]", node, 0);
		break;
	}
	case NType::StatementWrite:
		node->getChild(2)->accept(this);
		break;
	case NType::StatementRead: {
		auto indexNode = static_cast<Node*>(node->getChild(3));
		indexNode->accept(this);

		if (!isDefined(node, 2))
			this->raiseError("identifier not defined", node, 2);
		else if (isInt(node, 2) && !indexNode->isEpsilon())
			this->raiseError("incompatible types. Declared as int", node, 0);
		else if (isArray(node, 2) && indexNode->isEpsilon())
			this->raiseError("incompatible types. Declared as int[]", node, 0);
		break;
	}
	case NType::StatementBlock:
		node->getChild(1)->accept(this);
		break;
	case NType::StatementIf:
		node->getChild(2)->accept(this);
		node->getChild(4)->accept(this);
		node->getChild(6)->accept(this);
		break;
	case NType::StatementWhile:
		node->getChild(2)->accept(this);
		node->getChild(4)->accept(this);
		break;
	case NType::Index:
		if (node->isEpsilon())
			return;

		node->getChild(1)->accept(this);
		break;
	case NType::Exp:
		node->getChild(0)->accept(this);
		node->getChild(1)->accept(this);
		break;
	case NType::Exp2:
		// expect (
		// expect EXP
		// expect ")"
		node->getChild(1)->accept(this);
		break;
	case NType::Exp2Ident: {
		auto indexNode = static_cast<Node*>(node->getChild(1));
		indexNode->accept(this);

		if (!isDefined(node, 0))
			this->raiseError("identifier not defined", node, 0);
		else if (isInt(node, 0) && !indexNode->isEpsilon())
			this->raiseError("incompatible types. Declared as int", node, 0);
		else if (isArray(node, 0) && indexNode->isEpsilon())
			this->raiseError("no primitive Type in exp. incompatible types. Declared as int[] ", node, 0);
		break;
	}
	case NType::Exp2Int:
		break;
	case NType::Exp2Minus:
		node->getChild(1)->accept(this);
		break;
	case NType::Exp2Neg:
		node->getChild(1)->accept(this);
		break;
	case NType::OpExp:
		if (node->isEpsilon())
			return;

		node->getChild(0)->accept(this);
		node->getChild(1)->accept(this);
		break;
	default:
		break;
	}
}

void TreeVisitorTypeCheck::visit(Leaf* leaf) {
}
const Token TreeVisitorTypeCheck::getToken(Node* node,int index){
	return static_cast<Leaf*>(node->getChild(index))->getToken();
}
bool TreeVisitorTypeCheck::isDefined(Node* node, int index) {
    auto info = this->getToken(node, index)._info;
    return info->isInteger() || info->isArray();
}
bool TreeVisitorTypeCheck::isInt(Node* node, int index) {
	return getToken(node, index)._info->isInteger();
}

bool TreeVisitorTypeCheck::isArray(Node* node, int index) {
	return getToken(node, index)._info->isArray();
}

int TreeVisitorTypeCheck::getLine(Node* node, int index) {
	return getToken(node, index)._line;
}

int TreeVisitorTypeCheck::getColumn(Node* node, int index) {
	return getToken(node, index)._column;
}
void TreeVisitorTypeCheck::raiseError(char const * reason, Node* node, int index) {
	std::stringstream err;
	err << "Error in Line: " << this->getLine(node, index) << std::endl;
	err << "Error in Column: " << this->getColumn(node, index) << std::endl;
	err << reason;
	throw std::domain_error(err.str());
}
