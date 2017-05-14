#include "../includes/Parser.h"


Parser::Parser(Scanner* scanner) {
	this->_scanner = scanner;
}

Node* Parser::parse() {
	return prog();
}

Node* Parser::prog() {	
	Node* progNode = new Node(Prog);
	this->_currentToken = this->_scanner->nextToken();

	Node* decls = Parser::decls();
	if(decls != nullptr)
		progNode->_children.push_back(decls);

	Node* statements = Parser::statements();
	if(statements != nullptr)
		progNode->_children.push_back(statements);

	return progNode;
}

Node* Parser::decls() {

	Node* decls = new Node(Decls);

	Node* decl = Parser::decl();
	if (decl == nullptr)	// Epsilon übergang
		return nullptr;
	decls->_children.push_back(decl);

	// kein Epsilon übergang. Erwarte Semicolon
	if (this->_currentToken->_type != TOKEN_SEMICOLON)
		throw - 1;
	
	addLeaf(decls);

	Node* followingDecls = Parser::decls();
	if (followingDecls != nullptr)
		decls->_children.push_back(followingDecls);

	return decls;
}

Node* Parser::decl() {

	if (this->_currentToken->_type != TOKEN_INT)
		return nullptr;
	
	Node* decl = new Node(Decl);

	addLeaf(decl);

	Node* array = Parser::array();
	if (array != nullptr)
		decl->_children.push_back(array);

	// erwate Identifier
	if (this->_currentToken->_type != TOKEN_IDENTIFIER)
		throw - 1;

	addLeaf(decl);

	return decl;
}

Node* Parser::array()
{
	if (this->_currentToken->_type != TOKEN_BRACKETS2_OPEN)
		return nullptr;

	Node* array = new Node(Array);
	addLeaf(array);
	
	// erwate Integer
	if (this->_currentToken->_type != TOKEN_INTEGER)
		throw - 1;
	addLeaf(array);

	// erwarte "]"
	if (this->_currentToken->_type != TOKEN_BRACKETS2_CLOSE)
		throw - 1;
	addLeaf(array);

	return array;
}

Node* Parser::statements() {
	
	
	
	return nullptr;
}








int Parser::addLeaf(Node* parent) {
	parent->_children.push_back((Leaf*) new Leaf(this->_currentToken));
	this->_currentToken = this->_scanner->nextToken();
	return 1;
}