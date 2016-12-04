/*
* Automat.cpp
*
*/

#include "../includes/Token.h"
#include <ctype.h>
#include <iostream>

const char* const Token::_tokenTypesArray[] = {
	"Integer", "Identifier", "Plus", "Minus",
	"Colon", "Smaller", "Greater",
	"Equals", "Assign", "Assign2 (=:=)", "Not",
	"And", "Semicolon", "Star",  "Bracket '('", "Bracket ')'",
	"Bracket '{'", "Bracket '}'", "Bracket '['", "Bracket ']'",
	"If", "While", "Unknown", "EOF" };

Token::Token(TType type, int line, int column) {
	this->_type = type;
	this->_line = line;
	this->_column = column;
	// TODO ADD information / lexem

}

Token::~Token() {
	// TODO Auto-generated destructor stub
}

const char* Token::getTypeAsString() {
	return this->_tokenTypesArray[this->_type];
}
