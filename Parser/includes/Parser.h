/*
 * Parser.h
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#ifndef PARSER_INCLUDES_PARSER_H_
#define PARSER_INCLUDES_PARSER_H_

#include "Tree.h"
#include "../../Scanner/includes/Scanner.h"
#include "../../Symboltable/includes/Symboltable.h"

class Parser {
private:
	Scanner* scanner;
	Token* currentToken;
	Token* lastToken;
	void Parser::getNextToken();
	Scanner& _scanner;
	void Parser::compTokenType(TType type);
	ProgNode* Parser::createProg();
	DeclsNode* Parser::createDecls();
	DeclNode* Parser::createDecl();
	ArrayNode* Parser::createArray();
	IntegerNode* Parser::createInteger();
	IdentNode* Parser::createIdent();
	StatementsNode* Parser::createStatements();
	StatementNode* Parser::createStatement();
	IndexNode* Parser::createIndex();
	ExpNode* Parser::createExp();
	Exp2Node* Parser::createExp2();
	Op_ExpNode* Parser::createOpExp();
	OpNode* Parser::createOp();
public:
	Parser(Scanner& scanner);
	virtual ~Parser();

	virtual Tree* parse();
};

#endif /* PARSER_INCLUDES_PARSER_H_ */
