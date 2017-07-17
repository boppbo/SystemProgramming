/*
 * TreeVisitorCodeGeneration.cpp
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#include "../includes/TreeVisitorCodeGeneration.h"
#include "../../Common/includes/cstring.h"
#include <stdexcept>
#include <stdio.h>

TreeVisitorCodeGeneration::TreeVisitorCodeGeneration(std::ostream& codeOut) : _code(codeOut) {
}

TreeVisitorCodeGeneration::~TreeVisitorCodeGeneration() {
}

void TreeVisitorCodeGeneration::visit(Leaf *leaf) {
	switch(leaf->getToken()._type) {
		case TType::TOKEN_IDENTIFIER:
			this->addCode("$", false);
			this->addCode(leaf->getToken()._info->getName());
			break;
		case TType::TOKEN_INTEGER:
			this->addCode(std::to_string(leaf->getToken()._integerValue).c_str());
			break;
		case TType::TOKEN_PLUS:
			this->addCommand("ADD");
			break;
		case TType::TOKEN_MINUS:
			this->addCommand("SUB");
			break;
		case TType::TOKEN_STAR:
			this->addCommand("MUL");
			break;
		case TType::TOKEN_COLON:
			this->addCommand("DIV");
			break;
		case TType::TOKEN_SMALLER:
			this->addCommand("LES");
			break;
		case TType::TOKEN_GREATER:
			break;
		case TType::TOKEN_EQUALS:
		case TType::TOKEN_ASSIGN2:
			this->addCommand("EQU");
			break;
		case TType::TOKEN_AND:
			this->addCommand("AND");
			break;
		default:
			throw std::domain_error(leaf->getTypeAsString());
	}
}

void TreeVisitorCodeGeneration::visit(Node *node) {
	switch(node->getType()) {
		case NType::Prog:
			// optional DECLS
			node->getChild(0)->accept(this);
			// optional STATEMENTS
			node->getChild(1)->accept(this);

			this->addCode("STP", true);
			break;
		case NType::Decls:
		case NType::Statements:
			if (node->isEpsilon())
				return;

			// expect DECL / STATEMENT
			node->getChild(0)->accept(this);
			// optional DECLS / STATEMENTS
			node->getChild(2)->accept(this);
			break;
		case NType::Decl:
			this->decl(node);
			break;
		case NType::StatementIdent:
		case NType::StatementWrite:
		case NType::StatementRead:
		case NType::StatementBlock:
			this->statement(node);
			break;
		case NType::StatementIf:
			this->statementIf(node);
			break;
		case NType::StatementWhile:
			this->statementWhile(node);
			break;
		case NType::Array:
			this->array(node);
			break;
		case NType::Exp:
			this->expression(node);
			break;
		case NType::Exp2:
		case NType::Exp2Ident:
		case NType::Exp2Int:
		case NType::Exp2Minus:
		case NType::Exp2Neg:
			this->expression2(node);
			break;
		case NType::Index:
			this->index(node);
			break;
		case NType::OpExp:
			if (node->isEpsilon())
				return;

			node->getChild(1)->accept(this);
			node->getChild(0)->accept(this);
			break;
		case NType::Op:
			node->getChild(0)->accept(this);
			break;
		default:
			throw std::domain_error(node->getTypeAsString());
	}
}

void TreeVisitorCodeGeneration::decl(Node *node) {
	// expect int
	// optional array
	// expect Identifier
	// =>
	// DS $identifier size

	this->addCode("DS ");
	node->getChild(2)->accept(this);
	this->addCode(" ");
	node->getChild(1)->accept(this);
}

void TreeVisitorCodeGeneration::array(Node *node)
{
	if (node->isEpsilon())
		this->addCode("1", true);
	else {
		// expect "["
		// expect Integer
		// expect "]"
		node->getChild(1)->accept(this);
		this->addCode("", true);
	}
}

void TreeVisitorCodeGeneration::statement(Node *node) {
	switch (node->getType()) {
		case NType::StatementIdent:
			// expect Identifier
			// optional INDEX
			// expect ":="
			// expect EXP
			// =>
			// EXP
			// LA $var INDEX
			// STR
			node->getChild(3)->accept(this);

			this->addCode("LA ");
			node->getChild(0)->accept(this);
			this->addCode(" ", false);
			node->getChild(1)->accept(this);
			this->addCode("", true);
			this->addCommand("STR");
			break;
		case NType::StatementWrite:
			// expect write
			// expect "("
			// expect EXP
			// expect ")"
			node->getChild(2)->accept(this);
			this->addCommand("PRI");
			break;
		case NType::StatementRead:
			// expect read
			// expect "("
			// expect Identifier
			// optional INDEX
			// expect ")"
			this->addCommand("REA");
			this->addCode("LA ");
			node->getChild(2)->accept(this);
			this->addCode(" ");
			node->getChild(3)->accept(this);
			this->addCommand("STR");
			break;
		case NType::StatementBlock:
			// expect "{"
			// expect STATEMENTS
			// expect "}"
			node->getChild(1)->accept(this);
			break;
		default:
			throw std::domain_error(node->getTypeAsString());
	}
}

void TreeVisitorCodeGeneration::statementIf(Node *node) {
	// expect "if"
	// expect "("
	// expect EXP
	// expect ")"
	// expect STATEMENT
	// expect "else"
	// expect STATEMENT
	node->getChild(2)->accept(this);

	auto elseLabel = this->getNextLabel();
	auto endLabel = this->getNextLabel();

	this->addCommand("JIN", elseLabel);

	node->getChild(4)->accept(this);
	this->addCommand("JMP", endLabel);

	this->addLabeledCommand(elseLabel, "NOP");
	node->getChild(6)->accept(this);

	this->addLabeledCommand(endLabel, "NOP");
}
void TreeVisitorCodeGeneration::statementWhile(Node *node) {
	// expect "while"
	// expect "("
	// expect EXP
	// expect ")"
	// expect STATEMENT
	auto startLabel = this->getNextLabel();
	auto endLabel = this->getNextLabel();

	this->addLabeledCommand(startLabel, "NOP");
	node->getChild(2)->accept(this);
	this->addCommand("JIN", endLabel);
	node->getChild(4)->accept(this);
	this->addCommand("JMP", startLabel);
	this->addLabeledCommand(endLabel, "NOP");
}

void TreeVisitorCodeGeneration::expression(Node *node)
{
	//expect EXP2
	//optional OP_EXP
	auto op_exp = static_cast<Node*>(node->getChild(1));

	if (op_exp->isEpsilon()) {
		node->getChild(0)->accept(this);
	} else {
		auto opNode = static_cast<Node*>(op_exp->getChild(0));
		auto opLeaf = static_cast<Leaf*>(opNode->getChild(0));

		if (opLeaf->getToken()._type == TType::TOKEN_GREATER) {
			node->getChild(1)->accept(this);
			node->getChild(0)->accept(this);
			this->addCommand("LES");
		} else if (opLeaf->getToken()._type == TType::TOKEN_ASSIGN2) {
			node->getChild(0)->accept(this);
			node->getChild(1)->accept(this);
			this->addCommand("NOT");
		} else {
			node->getChild(0)->accept(this);
			node->getChild(1)->accept(this);
		}
	}
}

void TreeVisitorCodeGeneration::expression2(Node *node)
{
	switch (node->getType()) {
		case NType::Exp2:
			// expect (
			// expect EXP
			// expect ")"
			node->getChild(1)->accept(this);
			break;
		case NType::Exp2Ident:
			// expect IDENTIFIER
			// optional Index
			this->addCode("LA ");
			node->getChild(0)->accept(this);
			this->addCode("", true);
			node->getChild(1)->accept(this);
			this->addCommand("LV");
			break;
		case NType::Exp2Int:
			// expect integer
			this->addCode("LC ");
			node->getChild(0)->accept(this);
			this->addCode("", true);
			break;
		case NType::Exp2Minus:
			// expect "-"
			// expect EXP2
			this->addCommand("LC", "0");
			node->getChild(1)->accept(this);
			this->addCommand("SUB");
			break;
		case NType::Exp2Neg:
			// expect "!"
			// expect EXP2
			node->getChild(1)->accept(this);
			this->addCommand("NOT");
			break;
		default:
			throw std::domain_error(node->getTypeAsString());
	}
}

void TreeVisitorCodeGeneration::index(Node *node)
{
	// expect "["
	// expect EXP
	// expect "]"
	if (node->isEpsilon())
		return;

	node->getChild(1)->accept(this);
	this->addCode("", true);
	this->addCommand("ADD");
}

void TreeVisitorCodeGeneration::addCode(char const * code, bool newLine) {
	if (code == nullptr)
		code = "";

	this->_code << code;
	if (newLine)
		this->_code << std::endl;
}

void TreeVisitorCodeGeneration::addCommand(char const * const command, char const * const arg, bool newLine) {
	this->addCode(command, false);
	if (arg != nullptr)
		this->addCode(" ", false);
	this->addCode(arg, newLine);
}

void TreeVisitorCodeGeneration::addLabeledCommand(char const * const jumpLabel, char const * const command, char const * const arg, bool newLine) {
	if (jumpLabel != nullptr) {
		this->addCode(jumpLabel, false);
		this->addCode(" ", false);
	}
	this->addCommand(command, arg, newLine);
}

char const * TreeVisitorCodeGeneration::getNextLabel() {
	return ("#label" + std::to_string(this->_labelId++)).c_str();
}
