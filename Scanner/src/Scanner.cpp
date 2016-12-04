/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Scanner.h"
#include "../../Common/includes/cstring.h"
#include <iostream>
using namespace std;

bool isIF(char* string);
bool isWHILE(char* string);

Scanner::Scanner(char const* filename, int bufferSize = 1024, int stdLexemLenght = 1024, bool debug = false) {
	// TODO Auto-generated constructor stub
	this->_automat = new Automat();
	this->_buffer = new Buffer(filename, bufferSize);
	this->_stdLexemLenght = stdLexemLenght;
	this->_debug = debug;
}

Scanner::~Scanner() {
	// TODO Auto-generated destructor stub
}

Token* Scanner::nextToken() {

	this->_tokenEndReached = false;
	//free(this->_currentLexem);
	this->_currentLexem = (char*)malloc(this->_stdLexemLenght * sizeof(char));
	this->_currentLexemPtr = 0;
	this->_currentLexem[0] = '\0';
	this->_currentTokenColumn = this->_currentColumn;

	while(! this->_tokenEndReached) {
		this->_currentChar = this->_buffer->getChar();

		if(this->_debug)
			cout << "read char: '" << this->_currentChar << "'"<< endl;

		(this->*tansition_action[this->_automat->charEval(this->_currentChar)])();

		this->_currentColumn++;
	}
	return this->_returnToken;
}

// ####  ACTIONS ######
void Scanner::nothing() {
	this->debugActions("NOTHING");

	this->_currentTokenColumn = this->_currentColumn + 1;
}
void Scanner::add_char() {

	this->_currentLexem[this->_currentLexemPtr] = this->_currentChar;
	this->_currentLexem[this->_currentLexemPtr + 1] = '\0';
	this->_currentLexemPtr++;

	this->debugActions("ADD_CHAR");
}
void Scanner::add_token_integer() {
	this->debugActions("ADD_TOKEN_INTEGER");

	this->makeToken(TOKEN_INTEGER);
}
void Scanner::add_token_identifier() {
	this->debugActions("ADD_TOKEN_IDENTIFIER");

	TType type = TOKEN_IDENTIFIER;

	if (isIF(this->_currentLexem) )
		type = TOKEN_IF;
	if (isWHILE(this->_currentLexem))
		type = TOKEN_WHILE;

	this->makeToken(type);
}
void Scanner::add_token_sign() {
	this->debugActions("ADD_TOKEN_SIGN");

	this->makeToken(this->getSignType(this->_currentLexem));
}
void Scanner::add_token_sign_ug0() {
	this->debugActions("ADD_TOKEN_SIGN_UG0");

	this->add_char();
	this->makeToken(this->getSignType(this->_currentLexem), 0);
}
void Scanner::add_token_sign_ug2() {
	this->debugActions("ADD_TOKEN_SIGN_UG2");

	this->_currentLexem[this->_currentLexemPtr - 2] = '\0';
	this->_currentLexemPtr -= 2;

	this->makeToken(this->getSignType(this->_currentLexem), 2);
}
void Scanner::add_new_line() {
	this->debugActions("ADD_NEW_LINE");

	this->_currentLine++;
	this->_currentColumn = 0; // wird in nextToken() auf 1 erhöht
	this->_currentTokenColumn = 1;
}
void Scanner::add_token_unknown() {
	this->debugActions("ADD_TOKEN_SIGN_UNKONWN");

	this->makeToken(TOKEN_UNKNOWN);
}
void Scanner::discard() {
	this->debugActions("DISCARD");

	this->_currentLexemPtr = 0;
	this->_currentLexem[0] = '\0';
}
void Scanner::end() {
	this->debugActions("END");

	this->makeToken(TOKEN_EOF);
}

void Scanner::makeToken(TType type, int unget) {
	// TODO insert Lexem in Symbol-Tab and add information to Token
	this->_currentColumn -= unget;
	this->_buffer->ungetChar(unget);
	this->_returnToken = new Token(type, this->_currentLine, this->_currentTokenColumn);
	this->_tokenEndReached = true;
}

void Scanner::debugActions(char const * action) {
	if(this->_debug)
		cout << "Action: " << action << " | " << "Lexem: " << this->_currentLexem << " | " << "State: " << this->_automat->_currentState << endl;
}

TType Scanner::getSignType(char * string) {

	if (strcmp(string, "+") == 0) return TOKEN_PLUS;
	if (strcmp(string, "-") == 0) return TOKEN_MINUS;
	if (strcmp(string, ":") == 0) return TOKEN_COLON;
	if (strcmp(string, ";") == 0) return TOKEN_SEMICOLON;
	if (strcmp(string, "<") == 0) return TOKEN_SMALLER;
	if (strcmp(string, ">") == 0) return TOKEN_GREATER;
	if (strcmp(string, "=") == 0) return TOKEN_EQUALS;
	if (strcmp(string, "*") == 0) return TOKEN_STAR;
	if (strcmp(string, ":=") == 0) return TOKEN_ASSIGN;
	if (strcmp(string, "=:=") == 0) return TOKEN_ASSIGN2;
	if (strcmp(string, "!") == 0) return TOKEN_NOT;
	if (strcmp(string, "&&") == 0) return TOKEN_AND;
	if (strcmp(string, "(") == 0) return TOKEN_BRACKETS0_OPEN;
	if (strcmp(string, ")") == 0) return TOKEN_BRACKETS0_CLOSE;
	if (strcmp(string, "{") == 0) return TOKEN_BRACKETS1_OPEN;
	if (strcmp(string, "}") == 0) return TOKEN_BRACKETS1_CLOSE;
	if (strcmp(string, "[") == 0) return TOKEN_BRACKETS2_OPEN;
	if (strcmp(string, "]") == 0) return TOKEN_BRACKETS2_CLOSE;
	return TOKEN_UNKNOWN;

}

bool isIF(char* string) {

	if(strcmp(string, "IF") == 0)
		return true;

	if (strcmp(string, "if") == 0)
			return true;

	return false;
}

bool isWHILE(char* string) {

	if (strcmp(string, "WHILE") == 0)
		return true;

	if (strcmp(string, "while") == 0)
		return true;
	return false;
}
