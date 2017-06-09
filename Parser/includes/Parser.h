/*
 * Parser.h
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#ifndef PARSER_INCLUDES_PARSER_H_
#define PARSER_INCLUDES_PARSER_H_

#include "../../Scanner/includes/Scanner.h"
#include "../includes/Node.h"

class Parser {
public:
	Parser(Scanner& scanner);
	virtual ~Parser();
	virtual Tree* parse();

protected:
	virtual Node* prog();
	virtual Node* decls();
	virtual Node* decl();
	virtual Node* array();
	virtual Node* statements();
	virtual Node* statement();
	virtual Node* statementIdent();
	virtual Node* statementWrite();
	virtual Node* statementRead();
	virtual Node* statementBlock();
	virtual Node* statementIf();
	virtual Node* statementWhile();
	virtual Node* expression();
	virtual Node* expression2();
	virtual Node* index();
	virtual Node* op_exp();
private:
	void addLeaf(Node* parent, TType expectedTokenType, NType nodeType);
	void addNode(Node* parent, Node* child, bool optional = false);
	void parseError();

	Scanner& _scanner;
	Token const* _currentToken = nullptr;
};

#endif /* PARSER_INCLUDES_PARSER_H_ */
