/*
 * Parser.cpp
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#include "../includes/Parser.h"
#include "../includes/Leaf.h"
#include <sstream>
using namespace std;

Parser::Parser(Scanner& scanner) : _scanner(scanner) {
}

Parser::~Parser() {
}

Tree* Parser::parse() {
	this->_currentToken = this->_scanner.nextToken();
	return prog();
}

Node* Parser::prog() {
	Node* progNode = new Node(NType::Prog);

	// optional DECLS
	addNode(progNode, Parser::decls(), true);
	// optional STATEMENTS
	addNode(progNode, Parser::statements(), true);

	return progNode;
}
Node* Parser::decls() {
	Node* decls = new Node(NType::Decls);
	Node* decl = Parser::decl();

	if (decl) {
		// DECL
		addNode(decls, decl);
		// expect ";"
		addLeaf(decls, TOKEN_SEMICOLON, NType::Keyword);
		// optional DECLS
		addNode(decls, Parser::decls(), true);
	} // else EPSILON

	return decls;
}
Node* Parser::decl() {
	if (this->_currentToken->_type != TOKEN_INT)
		return nullptr;

	Node* decl = new Node(NType::Decl);

	// expect "int"
	addLeaf(decl, TOKEN_INT, NType::Keyword);
	//optional array
	addNode(decl, Parser::array(), true);
	// expect Identifier
	addLeaf(decl, TOKEN_IDENTIFIER, NType::Identifier);

	return decl;
}
Node* Parser::array()
{
	Node* array = new Node(NType::Array);

	if (this->_currentToken->_type == TOKEN_BRACKETS2_OPEN) {
		// expect "["
		addLeaf(array, TOKEN_BRACKETS2_OPEN, NType::Keyword);
		// expect Integer
		addLeaf(array, TOKEN_INTEGER, NType::INTEGER);
		// expect "]"
		addLeaf(array, TOKEN_BRACKETS2_CLOSE, NType::Keyword);
	} // else EPSILON

	return array;
}
Node* Parser::statements() {
	Node* statements = new Node(NType::Statements);
	Node* statement = Parser::statement();

	if (statement) {
		// Statement
		addNode(statements, statement);
		// expect Semicolon
		addLeaf(statements, TOKEN_SEMICOLON, NType::Keyword);
		// optional STATEMENTS
		addNode(statements, Parser::statements(), true);
	} // else EPSILON

	return statements;
}
Node* Parser::statement() {
	switch (this->_currentToken->_type) {
		case TOKEN_IDENTIFIER:
			return statementIdent();
		case TOKEN_WRITE:
			return statementWrite();
		case TOKEN_READ:
			return statementRead();
		case TOKEN_BRACKETS1_OPEN:
			return statementBlock();
		case TOKEN_IF:
			return statementIf();
		case TOKEN_WHILE:
			return statementWhile();
		case TOKEN_BRACKETS1_CLOSE:
		case TOKEN_EOF:
			return nullptr;
		default:
			this->parseError();
			return nullptr;
	}
}
Node * Parser::statementIdent()
{
	Node* statementIdent = new Node(NType::StatementIdent);

	// expect Identifier
	addLeaf(statementIdent, TOKEN_IDENTIFIER, NType::Identifier);
	// optional INDEX
	addNode(statementIdent, Parser::index(), true);
	// expect ":="
	addLeaf(statementIdent, TOKEN_ASSIGN, NType::Keyword);
	// expect EXP
	addNode(statementIdent, Parser::expression());

	return statementIdent;
}
Node * Parser::statementWrite()
{
	Node* statementWrite = new Node(NType::StatementWrite);

	// expect "write"
	addLeaf(statementWrite, TOKEN_WRITE, NType::Keyword);
	// expect "("
	addLeaf(statementWrite, TOKEN_BRACKETS0_OPEN, NType::Keyword);
	// expect EXP
	addNode(statementWrite, Parser::expression());
	// expect ")"
	addLeaf(statementWrite, TOKEN_BRACKETS0_CLOSE, NType::Keyword);

	return statementWrite;
}
Node * Parser::statementRead()
{
	Node* statementRead = new Node(NType::StatementRead);

	// expect "read"
	addLeaf(statementRead, TOKEN_READ, NType::Keyword);
	// expect "("
	addLeaf(statementRead, TOKEN_BRACKETS0_OPEN, NType::Keyword);
	// expect Identifier
	addLeaf(statementRead, TOKEN_IDENTIFIER, NType::Identifier);
	// optional INDEX
	addNode(statementRead, Parser::index(), true);
	// expect ")"
	addLeaf(statementRead, TOKEN_BRACKETS0_CLOSE, NType::Keyword);

	return statementRead;
}
Node * Parser::statementBlock()
{
	Node* statementBlock = new Node(NType::StatementBlock);

	// expect "{"
	addLeaf(statementBlock, TOKEN_BRACKETS1_OPEN, NType::Keyword);
	// expect STATEMENTS
	addNode(statementBlock, Parser::statements(), true);
	// expect "}"
	addLeaf(statementBlock, TOKEN_BRACKETS1_CLOSE, NType::Keyword);

	return statementBlock;
}
Node * Parser::statementIf()
{
	Node* statementIf = new Node(NType::StatementIf);

	// expect "if"
	addLeaf(statementIf, TOKEN_IF, NType::Keyword);
	// expect "("
	addLeaf(statementIf, TOKEN_BRACKETS0_OPEN, NType::Keyword);
	// expect EXP
	addNode(statementIf, Parser::expression());
	// expect ")"
	addLeaf(statementIf, TOKEN_BRACKETS0_CLOSE, NType::Keyword);
	// expect STATEMENT
	addNode(statementIf, Parser::statement());
	// expect "else"
	addLeaf(statementIf, TOKEN_ELSE, NType::Keyword);
	// expect STATEMENT
	addNode(statementIf, Parser::statement());

	return statementIf;
}
Node * Parser::statementWhile()
{
	Node* statementWhile = new Node(NType::StatementWhile);

	// expect "while"
	addLeaf(statementWhile, TOKEN_WHILE, NType::Keyword);
	// expect "("
	addLeaf(statementWhile, TOKEN_BRACKETS0_OPEN, NType::Keyword);
	// expect EXP
	addNode(statementWhile, Parser::expression());
	// expect ")"
	addLeaf(statementWhile, TOKEN_BRACKETS0_CLOSE, NType::Keyword);
	// expect STATEMENT
	addNode(statementWhile, Parser::statement());

	return statementWhile;
}
Node * Parser::expression()
{
	Node* exp = new Node(NType::Exp);

	//expect EXP2
	addNode(exp, Parser::expression2());
	//optional OP_EXP
	addNode(exp, Parser::op_exp(), true);

	return exp;
}
Node * Parser::expression2()
{
	Node* n;

	switch (this->_currentToken->_type) {
		case TOKEN_BRACKETS0_OPEN:
			n = new Node(NType::Exp2);
			// expect (
			addLeaf(n, TOKEN_BRACKETS0_OPEN, NType::Keyword);
			// expect EXP
			addNode(n, Parser::expression());
			// expect ")"
			addLeaf(n, TOKEN_BRACKETS0_CLOSE, NType::Keyword);
			break;
		case TOKEN_IDENTIFIER:
			n = new Node(NType::Exp2Ident);
			// expect IDENTIFIER
			addLeaf(n, TOKEN_IDENTIFIER, NType::Identifier);
			//optional Index
			addNode(n, Parser::index(), true);
			break;
		case TOKEN_INTEGER:
			n = new Node(NType::Exp2Int);
			addLeaf(n, TOKEN_INTEGER, NType::INTEGER);
			break;
		case TOKEN_MINUS:
			n = new Node(NType::Exp2Minus);
			// expect "-"
			addLeaf(n, TOKEN_MINUS, NType::Keyword);
			// expect EXP2
			addNode(n, Parser::expression2());
			break;
		case TOKEN_NOT:
			n = new Node(NType::Exp2Neg);
			// expect "!"
			addLeaf(n, TOKEN_NOT, NType::Keyword);
			// expect EXP2
			addNode(n, Parser::expression2());
			break;
		default:
			parseError();
			return nullptr;
	}

	return n;
}
Node * Parser::index()
{
	Node* index = new Node(NType::Index);

	if (this->_currentToken->_type == TOKEN_BRACKETS2_OPEN) {
		// expect "["
		addLeaf(index, TOKEN_BRACKETS2_OPEN, NType::Keyword);
		// expect EXP
		addNode(index, Parser::expression());
		// expect "]"
		addLeaf(index, TOKEN_BRACKETS2_CLOSE, NType::Keyword);
	}

	return index;
}
Node * Parser::op_exp()
{
	Node* op_exp = new Node(NType::OpExp);
	Node* op;

	switch(this->_currentToken->_type)
	{
		case TOKEN_PLUS:
		case TOKEN_MINUS:
		case TOKEN_STAR:
		case TOKEN_COLON:
		case TOKEN_SMALLER:
		case TOKEN_GREATER:
		case TOKEN_EQUALS:
		case TOKEN_ASSIGN2:
		case TOKEN_AND:
			op = new Node(NType::Op);
			addLeaf(op, this->_currentToken->_type, NType::Op);
			op_exp->addChild(op);

			addNode(op_exp, Parser::expression());
			break;
		default:
			break;
	}

	return op_exp;
}

void Parser::addLeaf(Node* parent, TType expectedTokenType, NType nodeType) {
	if (this->_currentToken->_type != expectedTokenType)
		parseError();

	parent->addChild(new Leaf(this->_currentToken, nodeType));
	this->_currentToken = this->_scanner.nextToken();
}
void Parser::addNode(Node* parent, Node* child, bool optional) {
	if (parent == nullptr)
		throw invalid_argument("parent");
	if (child == nullptr)
		throw invalid_argument("child");
	if (!optional && child->isEpsilon())
		parseError();

	parent->addChild(child);
}
void Parser::parseError() {
	stringstream ss;
	ss << "unexpected Token Line: " << this->_currentToken->_line << " "
		<< "Column: " << this->_currentToken->_column << " "
		<< this->_currentToken->getTypeAsString();
	throw runtime_error(ss.str());
};
