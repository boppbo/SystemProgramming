#include "../includes/Parser.h"
#include <sstream>
#include <string>

Parser::Parser(Scanner* scanner) {
	this->_scanner = scanner;
}

Node* Parser::parse() {
	ParseTree* ProgTree = new ParseTree(prog());
	return prog();
}

Node* Parser::prog() {	
	Node* progNode = new Node(nodeType::Prog);
	this->_currentToken = this->_scanner->nextToken();

	// optinal DECLS
	addNode(progNode, Parser::decls(), true);
	// optinal statements
	addNode(progNode, Parser::statements(), true);

	return progNode;
}

Node* Parser::decls() {

	Node* decls = new Node(nodeType::Decls);

	Node* decl = Parser::decl();
	if (decl == nullptr)	// Epsilon �bergang
		return nullptr;
	addNode(decls, decl);
	// expect Semicolon
	addLeaf(decls, TOKEN_SEMICOLON, nodeType::Keyword);
	// optional DECLS
	addNode(decls, Parser::decls(), true);

	return decls;
}

Node* Parser::decl() {
	if (this->_currentToken->_type != TOKEN_INT)
		return nullptr;
	
	Node* decl = new Node(nodeType::Decl);
	// expect int
	addLeaf(decl, TOKEN_INT, nodeType::Keyword);
	//optional array
	addNode(decl, Parser::array(), true);
	// expect Identifier
	addLeaf(decl, TOKEN_IDENTIFIER, nodeType::Identifier);

	return decl;
}

Node* Parser::array()
{
	if (this->_currentToken->_type != TOKEN_BRACKETS2_OPEN)
		return nullptr;

	Node* array = new Node(nodeType::Array);
	// exprect "["
	addLeaf(array, TOKEN_BRACKETS2_OPEN, nodeType::Keyword);
	// erwate Integer
	addLeaf(array, TOKEN_INTEGER, nodeType::INTEGER);
	// erwarte "]"
	addLeaf(array, TOKEN_BRACKETS2_CLOSE, nodeType::Keyword);

	return array;
}

Node* Parser::statements() {
	
	Node* statements = new Node(nodeType::Statements);

	Node* statement = Parser::statement();
	if (statement == nullptr)	// Epsilon �bergang
		return nullptr;
	statements->_children.push_back(statement);
	// expect Semicolon
	addLeaf(statements, TOKEN_SEMICOLON, nodeType::Keyword);

	Node* followingStatements = Parser::statements();
	if (followingStatements != nullptr)
		statements->_children.push_back(followingStatements);

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
			return statementIf();
		case TOKEN_IF:
			return statementWhile();
		case TOKEN_WHILE:
			return statementBlock();
		default:
			return nullptr;
	}
}

Node * Parser::statementIdent()
{
	Node* statementIdent = new Node(nodeType::StatementIdent);
	addLeaf(statementIdent, TOKEN_IDENTIFIER, nodeType::Identifier);

	// optional INDEX
	addNode(statementIdent, Parser::index(), true);
	// Erwarte ":="
	addLeaf(statementIdent, TOKEN_ASSIGN, nodeType::Keyword);
	// expect EXP
	addNode(statementIdent, Parser::exp());

	return statementIdent;
}

Node * Parser::statementWrite()
{
	Node* statementWrite = new Node(nodeType::StatementWrite);
	addLeaf(statementWrite, TOKEN_WRITE, nodeType::Keyword);

	// Erwarte "("
	addLeaf(statementWrite, TOKEN_BRACKETS0_OPEN, nodeType::Keyword);
	// Erwarte EXP
	addNode(statementWrite, Parser::exp());
	// Erwarte ")"
	addLeaf(statementWrite, TOKEN_BRACKETS0_CLOSE, nodeType::Keyword);

	return statementWrite;
}

Node * Parser::statementRead()
{
	Node* statementRead = new Node(nodeType::StatementWrite);
	addLeaf(statementRead, TOKEN_READ, nodeType::Keyword);
	// expect "("
	addLeaf(statementRead, TOKEN_BRACKETS0_OPEN, nodeType::Keyword);
	// expect Identifier
	addLeaf(statementRead, TOKEN_IDENTIFIER, nodeType::Identifier);
	// optional INDEX
	addNode(statementRead, Parser::index(), true);
	// expect ")"
	addLeaf(statementRead, TOKEN_BRACKETS0_CLOSE, nodeType::Keyword);

	return statementRead;
}

Node * Parser::statementIf()
{
	Node* statementIf = new Node(nodeType::StatementIf);
	addLeaf(statementIf, TOKEN_IF, nodeType::Keyword);

	// Erwarte "("
	addLeaf(statementIf, TOKEN_BRACKETS0_OPEN, nodeType::Keyword);
	// Erwarte EXP
	Node* exp = Parser::exp();
	if (exp == nullptr)
		parseError();
	statementIf->_children.push_back(exp);
	// Erwarte ")"
	addLeaf(statementIf, TOKEN_BRACKETS0_CLOSE, nodeType::Keyword);
	// Erwarte STATEMENT
	addNode(statementIf, Parser::statement());
	// Erwarte "ELSE"
	addLeaf(statementIf, TOKEN_ELSE, nodeType::Keyword);
	// Erwarte STATEMENT
	addNode(statementIf, Parser::statement());

	return statementIf;
}

Node * Parser::statementWhile()
{
	Node* statementWhile = new Node(nodeType::StatementWrite);
	addLeaf(statementWhile, TOKEN_WHILE, nodeType::Keyword);

	// expect "("
	addLeaf(statementWhile, TOKEN_BRACKETS0_OPEN, nodeType::Keyword);
	// expect EXP
	Node* exp = Parser::exp();
	if (exp == nullptr)
		parseError();
	statementWhile->_children.push_back(exp);
	// expect ")"
	addLeaf(statementWhile, TOKEN_BRACKETS0_CLOSE, nodeType::Keyword);
	// expect STATEMENT
	addNode(statementWhile, Parser::statement());

	return statementWhile;
}

Node * Parser::statementBlock()
{
	Node* statementWrite = new Node(nodeType::StatementWrite);
	addLeaf(statementWrite, TOKEN_BRACKETS1_OPEN, nodeType::Keyword);
	// expect STATEMENTS
	addNode(statementWrite, Parser::statements());
	// exprec "}"
	addLeaf(statementWrite, TOKEN_BRACKETS1_CLOSE, nodeType::Keyword);

	return statementWrite;
}

Node * Parser::index()
{
	if (this->_currentToken->_type != TOKEN_BRACKETS2_OPEN)
		return nullptr;
	
	Node* index = new Node(nodeType::Index);
	// exprect "["
	addLeaf(index, TOKEN_BRACKETS2_OPEN, nodeType::Keyword);
	// expect EXP
	addNode(index, Parser::exp());
	// exprect "]"
	addLeaf(index, TOKEN_BRACKETS2_CLOSE, nodeType::Keyword);
	
	return index;
}

Node * Parser::exp()
{
	Node* exp = new Node(nodeType::Exp);
	//expect EXP2
	addNode(exp, Parser::exp2());
	//optional OP_EXP
	addNode(exp, op_exp(), true);

	return exp;
}

Node * Parser::exp2()
{
	switch (this->_currentToken->_type) {
	case TOKEN_BRACKETS0_OPEN:
	{
		Node* exp2exp = new Node(nodeType::Exp2);
		addLeaf(exp2exp, TOKEN_BRACKETS0_OPEN, nodeType::Keyword);
		// expect EXP
		addNode(exp2exp, Parser::exp());
		// expect ")"
		addLeaf(exp2exp, TOKEN_BRACKETS0_CLOSE, nodeType::Keyword);

		return exp2exp;
	}
	case TOKEN_IDENTIFIER:
		return exp2Ident();
	case TOKEN_INTEGER:
		return exp2Int();
	case TOKEN_MINUS:
		return exp2Minus();
	case TOKEN_NOT:
		return exp2Neg();
	default:
		return nullptr;
	}
	
	return nullptr;
}

Node * Parser::op_exp()
{
	Node* op_exp = new Node(nodeType::OpExp);
	
	Node* op = Parser::op();
	if(op == nullptr)
		return nullptr;

	addNode(op_exp, op);
	// expect EXP
	addNode(op_exp, Parser::exp());
	return op_exp;
}

Node * Parser::op()
{
	if(! this->_currentToken->isOperator())
		return nullptr;

	Node* op = new Node(nodeType::Op);
	addLeaf(op, this->_currentToken->_type, nodeType::Op);

	return op;
}

Node * Parser::exp2Ident()
{
	Node* exp2Ident = new Node(nodeType::Exp2Ident);
	addLeaf(exp2Ident, TOKEN_IDENTIFIER, nodeType::Identifier);
	// optional INDEX
	addNode(exp2Ident, Parser::index(), true);

	return exp2Ident;
}

Node * Parser::exp2Int()
{
	Node* exp2Integer = new Node(nodeType::Exp2Int);
	addLeaf(exp2Integer, TOKEN_INTEGER, nodeType::INTEGER);

	return exp2Integer;
}

Node * Parser::exp2Minus()
{
	Node* exp2Minus = new Node(nodeType::Exp2Minus);
	addLeaf(exp2Minus, TOKEN_MINUS, nodeType::Keyword);
	// expect EXP2
	addNode(exp2Minus, Parser::exp2());
	return exp2Minus;
}

Node * Parser::exp2Neg()
{
	Node* exp2Neg = new Node(nodeType::Exp2Neg);
	addLeaf(exp2Neg, TOKEN_NOT, nodeType::Keyword);
	// expect EXP2
	addNode(exp2Neg, Parser::exp2());
	return exp2Neg;
}








void Parser::parseError() {
	stringstream ss;
	ss << "unexpected Token Line: " << this->_currentToken->_line << " "
		<< "Column: " << this->_currentToken->_column << " " 
		<< this->_currentToken->getTypeAsString();

	throw runtime_error(ss.str());
};

void Parser::addNode(Node* parent, Node* child, bool optional) {
	if (child == nullptr && !optional)
		parseError();
	if(child != nullptr)
		parent->_children.push_back(child);
}

void Parser::addLeaf(Node* parent, TType expectedTokenType, nodeType nodeType) {
	if (this->_currentToken->_type != expectedTokenType)
		parseError();

	parent->_children.push_back((Leaf*) new Leaf(this->_currentToken, nodeType));
	this->_currentToken = this->_scanner->nextToken();
}