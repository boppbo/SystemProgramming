/*
 * Parser.cpp
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#include "../includes/Parser.h"
#include "../includes/Nodes/Node.h"

Parser::Parser(Scanner& scanner) : _scanner(scanner) {
	Tree* parseTree = new Tree(createProg());
	currentToken = NULL;
	lastToken = NULL;
}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

Tree* Parser::parse() {
	Tree* result = new Leaf();
	return result;
}

void Parser::getNextToken() {
	lastToken = currentToken;
	currentToken = _scanner.nextToken;
}

void Parser::compTokenType(TType type) {
	if (currentToken->_type == type) getNextToken();
	//TODO ELSE
}

ProgNode* Parser::createProg() {
	ProgNode* Prog = new ProgNode();
	Prog->addChild(createDecls());
	Prog->addChild(createStatements());
	return Prog;
}

DeclsNode* Parser::createDecls() {
	DeclsNode* decls = new DeclsNode();
	decls->addChild(createDecl());
	compTokenType(TType::TOKEN_SEMICOLON);
	decls->addChild(createDecls());
	return decls;
	//TODO EPS
}

DeclNode* Parser::createDecl() {
	DeclNode* decl = new DeclNode();
	compTokenType(TType::TOKEN_INT);
	decl->addChild(createArray());
}

ArrayNode* Parser::createArray() {
	ArrayNode* array = new ArrayNode();
	compTokenType(TType::TOKEN_BRACKETS2_OPEN);
	array->addChild(createInteger());
	compTokenType(TType::TOKEN_BRACKETS2_CLOSE);
	array->addChild(createIdent());
	return array;
	//TODO EPS
}

IntegerNode* Parser::createInteger() {
	IntegerNode* integer = new IntegerNode(currentToken);
	return integer;
}

IdentNode* Parser::createIdent() {
	IdentNode* ident = new IdentNode(currentToken);
	return ident;
}

StatementsNode* Parser::createStatements() {
	StatementsNode* statements = new StatementsNode();
	statements->addChild(createStatement());
	compTokenType(TType::TOKEN_SEMICOLON);
	statements->addChild(createStatements());
	return statements;
	//TODO EPS
}

StatementNode* Parser::createStatement() {
	StatementNode* statement = new StatementNode();
	switch (currentToken->_type)
	{
		case TType::TOKEN_IDENTIFIER: {
			statement->addChild(createIdent());
			statement->addChild(createIndex());
			compTokenType(TType::TOKEN_ASSIGN);
			statement->addChild(createExp());
			break;
		}
		case TType::TOKEN_WRITE: {
			compTokenType(TType::TOKEN_BRACKETS0_OPEN);
			statement->addChild(createExp());
			compTokenType(TType::TOKEN_BRACKETS0_CLOSE);
			break;
		}
		case TType::TOKEN_READ: {
			statement->addChild(createIdent());
			statement->addChild(createIndex());
		}
		case TType::TOKEN_BRACKETS1_OPEN: {
			statement->addChild(createStatements());
			compTokenType(TType::TOKEN_BRACKETS1_CLOSE);
		}
		case TType::TOKEN_IF: {
			compTokenType(TType::TOKEN_BRACKETS0_OPEN);
			statement->addChild(createExp());
			compTokenType(TType::TOKEN_BRACKETS0_CLOSE);
			statement->addChild(createStatement());
			compTokenType(TType::TOKEN_ELSE);
			statement->addChild(createStatement());	
		}
		case TType::TOKEN_WHILE: {
			compTokenType(TType::TOKEN_BRACKETS0_OPEN);
			statement->addChild(createExp());
			compTokenType(TType::TOKEN_BRACKETS0_CLOSE);
			statement->addChild(createStatement());
		}
	default:
		break;
	}
}

IndexNode* Parser::createIndex() {
	IndexNode* index = new IndexNode();
	compTokenType(TType::TOKEN_BRACKETS2_OPEN);
	index->addChild(createExp());
	compTokenType(TType::TOKEN_BRACKETS2_CLOSE);
	return index;
}

ExpNode* Parser::createExp() {
	ExpNode* exp = new ExpNode();
	exp->addChild(createExp2());
	exp->addChild(createOpExp());
	return exp;
}

Exp2Node* Parser::createExp2() {
	Exp2Node* exp_2 = new Exp2Node();
	switch (currentToken->_type)
	{
	case TType::TOKEN_BRACKETS0_OPEN: {
		exp_2->addChild(createExp());
		compTokenType(TType::TOKEN_BRACKETS0_CLOSE);
	}
	case TType::TOKEN_IDENTIFIER: {
		exp_2->addChild(createIdent());
		exp_2->addChild(createIndex());
	}
	case TType::TOKEN_INTEGER: {
		exp_2->addChild(createInteger());
	}
	case TType::TOKEN_MINUS: {
		exp_2->addChild(createExp2());
	}
	case TType::TOKEN_NOT: {
		exp_2->addChild(createExp2());
	}
	default:
		break;
	}
	return exp_2;
}

Op_ExpNode* Parser::createOpExp() {
	Op_ExpNode* opExp = new Op_ExpNode();
	opExp->addChild(createOp());
	opExp->addChild(createExp());
	return opExp;
	//TODO EPS
}

OpNode* Parser::createOp() {
	OpNode* op = new OpNode(currentToken);
	return op;
}