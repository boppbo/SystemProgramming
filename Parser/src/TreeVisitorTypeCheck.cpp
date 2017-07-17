/*
 * TreeVisitorTypeCheck.cpp
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#include "../includes/TreeVisitorTypeCheck.h"
#include "iostream"
#include <stdexcept>

TreeVisitorTypeCheck::TreeVisitorTypeCheck() {

}

TreeVisitorTypeCheck::~TreeVisitorTypeCheck() {

}

void TreeVisitorTypeCheck::check(Tree* tree) {
	tree->accept(this);
}

void TreeVisitorTypeCheck::visit(Node* node) {
	switch (node->getType()) {
	case NType::Prog: {
		//std::cout << "Prog" << std::endl;
		if (!node->isEpsilon()) {
			node->getChild(0)->accept(this);
			node->getChild(1)->accept(this);
		}
		node->setType(NType::NoType);
		break;
	}
	case NType::Decls: {
		//std::cout << "Decls" << std::endl;
		if (!node->isEpsilon()) {
			node->getChild(0)->accept(this);
			//std::cout << "DeclsC0" << std::endl;
			node->getChild(2)->accept(this);
			//std::cout << "DeclsC1" << std::endl;
		}
		node->setType(NType::NoType);
		break;
	}
	case NType::Decl: {
		//std::cout << "Decl" << std::endl;
		node->getChild(1)->accept(this);
		if (node->getChild(1)->getType() == NType::arrayType) {
			if (isArray(node, 2) || isInt(node, 2)) {
				node->setType(NType::ERROR);
				std::cerr << "Error in Line: " << getLine(node, 2) << std::endl;
				std::cerr << "Error in Column: " << getColumn(node, 2) << std::endl;
				throw std::domain_error("identifier already defined");
			} else {
				dynamic_cast<Leaf*>(node->getChild(2))->getToken()._info->setIsArray(true);
				node->setType(NType::NoType);
			}
		} else if (node->getChild(1)->getType() == NType::ERROR) {
			node->setType(NType::ERROR);
		} else {
			node->setType(NType::NoType);
			dynamic_cast<Leaf*>(node->getChild(2))->getToken()._info->setIsArray(false);
		}
		break;
	}
	case NType::Array: {
		//std::cout << "Array" << std::endl;
		if (!node->isEpsilon()) {
			if (getToken(node, 1)._integerValue > 0) {
				node->setType(NType::arrayType);
			} else {
				node->setType(NType::ERROR);
				std::cout << "Error in Line: " << getLine(node, 1) << std::endl;
				std::cout << "Error in Column: " << (getColumn(node, 1)) << std::endl;
				throw std::domain_error("no valid dimension");
			}

		} else {
			node->setType(NType::NoType);
		}
		break;
	}
	case NType::Statements: {
		//std::cout << "Statements" << std::endl;
		if (!node->isEpsilon()) {
			node->getChild(0)->accept(this);
			node->getChild(2)->accept(this);
		}
		node->setType(NType::NoType);
		break;
	}
	case NType::StatementIdent: {
		//std::cout << "StatementIdent" << std::endl;
		node->getChild(3)->accept(this);
		node->getChild(1)->accept(this);
		if (!isInt(node, 0) && !isArray(node, 0)) {
			std::cout << "Error in Line: " << getLine(node, 0) << std::endl;
			std::cout << "Error in Column: " << getColumn(node, 0) << std::endl;
			node->setType(NType::ERROR);
			throw std::domain_error("identifier not defined");

		} else if (compType(node, 3, NType::intType) && (
						(isInt(node, 0) && compType(node, 1, NType::NoType))
						|| (isArray(node, 0) && compType(node, 1, NType::arrayType)))) {
			node->setType(NType::NoType);
		} else {
			std::cout << "Error in Line: " << getLine(node, 0) << std::endl;
			std::cout << "Error in Column: " << getColumn(node, 0) << std::endl;
			std::cout << "Type: " << (isInt(node, 0) ? "Int" : "-")
					<< std::endl;
			node->setType(NType::ERROR);
			throw std::domain_error("incompatible types");

		}
		break;
	}
	case NType::StatementWrite: {
		//std::cout << "StatementWrite" << std::endl;
		node->getChild(2)->accept(this);
		node->setType(NType::NoType);
		break;
	}
	case NType::StatementRead: {
		//std::cout << "StatementRead" << std::endl;
		node->getChild(3)->accept(this);

		if (!isInt(node, 2) && !isArray(node, 2)) {
			std::cout << "Error in Line: " << getLine(node, 2) << std::endl;
			std::cout << "Error in Column: " << getColumn(node, 2) << std::endl;
			throw std::domain_error("identifier not defined");
			node->setType(NType::ERROR);
		} else if ((isInt(node, 2) && compType(node, 3, NType::NoType))
						|| (isArray(node, 2) && compType(node, 3, NType::arrayType))) {
			node->setType(NType::NoType);
		} else {
			std::cout << "Error in Line: "
					<< getLine(node, 2) << std::endl;
			std::cout << "Error in Column: "
					<< getColumn(node, 2)
					<< std::endl;
			throw std::domain_error("incompatible types");
			node->setType(NType::ERROR);
		}
		break;
	}
	case NType::StatementBlock: {
		//std::cout << "StatementBlock" << std::endl;
		node->getChild(1)->accept(this);
		node->setType(NType::NoType);
		break;
	}
	case NType::StatementIf: {
		//std::cout << "StatementIf" << std::endl;
		node->getChild(2)->accept(this);
		node->getChild(4)->accept(this);
		node->getChild(6)->accept(this);
		if (compType(node, 2, NType::ERROR)) {
			node->setType(NType::ERROR);
		} else {
			node->setType(NType::NoType);
		}
		break;
	}
	case NType::StatementWhile: {
		//std::cout << "StatementWhile" << std::endl;
		node->getChild(2)->accept(this);
		node->getChild(4)->accept(this);
		if (compType(node, 2, NType::ERROR)) {
			node->setType(NType::ERROR);
		} else {
			node->setType(NType::NoType);
		}
		break;
	}
	case NType::Index: {
		//std::cout << "Index" << std::endl;
		if (!node->isEpsilon()) {
			node->getChild(1)->accept(this);
			if (compType(node, 1, NType::ERROR)) {
				node->setType(NType::ERROR);
			} else {
				node->setType(NType::arrayType);
			}
		} else {
			node->setType(NType::NoType);
		}
		break;
	}
	case NType::Exp: {
		//std::cout << "Exp" << std::endl;
		node->getChild(0)->accept(this);
		node->getChild(1)->accept(this);
		if (compType(node, 1, NType::NoType)) {
			node->setType(node->getChild(0)->getType());
		} else if (!(compType(node, 0, node->getChild(1)->getType()))) {
			node->setType(NType::ERROR);
		} else {
			node->setType(node->getChild(0)->getType());
		}
		break;
	}
	case NType::Exp2: {
		//std::cout << "Exp2" << std::endl;
		node->getChild(1)->accept(this);
		node->setType(node->getChild(1)->getType());
		break;
	}
	case NType::Exp2Ident: {
		//std::cout << "Exp2Ident" << std::endl;
		node->getChild(1)->accept(this);
		if (!isInt(node, 0) && !isArray(node, 0)) {
			std::cout << "Error in Line: " << getLine(node, 0) << std::endl;
			std::cout << "Error in Column: " << getColumn(node, 0) << std::endl;
			throw std::domain_error("identifier not defined");
			node->setType(NType::ERROR);
		} else if (isInt(node, 0) && compType(node, 1, NType::NoType)) {
			node->setType(NType::intType);
		} else if (isArray(node, 0) && compType(node, 1, NType::arrayType)) {
			node->setType(NType::intType);
		} else {
			std::cout << "Error in Line: " << getLine(node, 0) << std::endl;
			std::cout << "Error in Column: " << getColumn(node, 0) << std::endl;
			throw std::domain_error("no primitive Type");
			node->setType(NType::ERROR);
		}
		break;
	}
	case NType::Exp2Int: {
		//std::cout << "Exp2Int" << std::endl;
		node->setType(NType::intType);
		break;
	}
	case NType::Exp2Minus: {
		//std::cout << "Exp2Minus" << std::endl;
		node->getChild(1)->accept(this);
		node->setType(node->getChild(1)->getType());
		break;
	}
	case NType::Exp2Neg: {
		//std::cout << "Exp2Neg" << std::endl;
		node->getChild(1)->accept(this);
		if (!compType(node, 1, NType::intType)) {
			node->setType(NType::ERROR);
		} else {
			node->setType(NType::intType);
		}
		break;
	}
	case NType::OpExp: {
		//std::cout << "OpExp" << std::endl;
		if (!node->isEpsilon()) {
			node->getChild(0)->accept(this);
			node->getChild(1)->accept(this);
			node->setType(node->getChild(1)->getType());
		} else {
			node->setType(NType::NoType);
		}
		break;
	}
	case NType::Op: {
		break;
	}
	default:{
		break;
	}
	}
}

void TreeVisitorTypeCheck::visit(Leaf* leaf) {
}
bool TreeVisitorTypeCheck::compType(Node* node,int index, NType type) {
	return node->getChild(index)->getType() == type;
}
const Token TreeVisitorTypeCheck::getToken(Node* node,int index){
	return dynamic_cast<Leaf*>(node->getChild(index))->getToken();
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
