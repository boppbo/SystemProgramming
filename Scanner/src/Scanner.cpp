/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#define _CRT_SECURE_NO_WARNINGS

#include "../includes/Scanner.h"
#include "../../Common/includes/cstring.h"
#include <iostream>
#include <cerrno>
using namespace std;

Scanner::Scanner(char const* filename, Symboltable &st, unsigned int maxLexemLength)
: _buffer(filename), _st(st), _currLexem(new char[maxLexemLength+2]) , _maxLexemLength(maxLexemLength){
	if (maxLexemLength < 1)
		throw invalid_argument("maxLexemLength");
}

Token* Scanner::nextToken() {
	this->_tokenEndReached = false;
	this->_currLexemPos = 0;
	this->_currLexem[0] = '\0';
	this->_currTokenCol = this->_currCol;

	while(!this->_tokenEndReached) {
		this->_currChar = this->_buffer.getChar();

		clog << "read char: '" << this->_currChar << "'"<< endl;

		(this->*tansition_action[this->_automat.charEval(this->_currChar)])();

		this->_currCol++;
	}
	return this->_returnToken;
}

// ####  ACTIONS ######
void Scanner::nothing() {
	this->debugActions("NOTHING");
	this->_currTokenCol = this->_currCol + 1;
}
void Scanner::add_char() {
	if (this->_currLexemPos <= this->_maxLexemLength) {
		this->_currLexem[this->_currLexemPos++] = this->_currChar;
		this->_currLexem[this->_currLexemPos] = '\0';
	}
	this->debugActions("ADD_CHAR");
}
void Scanner::add_token_integer() {
	this->debugActions("ADD_TOKEN_INTEGER");

	errno = 0;
	auto val = strtol(this->_currLexem, nullptr, 10);

	if (errno) {
		this->makeToken(TOKEN_UNKNOWN);
		this->_returnToken->setUnknownReason("Integer out of range!");
	}
	else {
		this->makeToken(TOKEN_INTEGER);
		this->_returnToken->_integerValue = val;
	}
}
void Scanner::add_token_identifier() {
	this->debugActions("ADD_TOKEN_IDENTIFIER");

	if (this->_currLexemPos > this->_maxLexemLength) {
		this->makeToken(TOKEN_UNKNOWN);
		this->_returnToken->setUnknownReason("Identifier too long.");
	}
	else {
		auto type = TOKEN_IDENTIFIER;
		// auf Keywords prüfen
		if (isIF(this->_currLexem)) type = TOKEN_IF;
		if (isWHILE(this->_currLexem)) type = TOKEN_WHILE;
		if (isINT(this->_currLexem)) type = TOKEN_INT;
		if (isELSE(this->_currLexem)) type = TOKEN_ELSE;
		if (isREAD(this->_currLexem)) type = TOKEN_READ;
		if (isWRITE(this->_currLexem)) type = TOKEN_WRITE;

		this->makeToken(type);
		//Identifiers AND Keywords get added to the symbol table
		this->_returnToken->_info = &this->_st.getOrAdd(this->_currLexem);
	}
}
void Scanner::add_token_sign() {
	this->debugActions("ADD_TOKEN_SIGN");

	this->makeToken(this->getSignType(this->_currLexem));
}
void Scanner::add_token_sign_ug0() {
	this->debugActions("ADD_TOKEN_SIGN_UG0");

	this->add_char();
	this->makeToken(this->getSignType(this->_currLexem), 0);
}
void Scanner::add_token_sign_ug2() {
	this->debugActions("ADD_TOKEN_SIGN_UG2");

	this->_currLexem[this->_currLexemPos-1] = '\0';
	this->makeToken(this->getSignType(this->_currLexem), 2);
}
void Scanner::add_new_line() {
	this->debugActions("ADD_NEW_LINE");

	this->_currLine++;
	// wird in nextToken() auf 1 erhöht
	this->_currCol = 0;
	this->_currTokenCol = 1;
}
void Scanner::add_token_unknown() {
	this->debugActions("ADD_TOKEN_SIGN_UNKONWN");

	this->makeToken(TOKEN_UNKNOWN);
	char* reason = new char[this->_currLexemPos+9];
	__strncpy(reason, "Symbol: ", 9);
	__strncpy((reason+8), this->_currLexem, this->_currLexemPos+1);

	this->_returnToken->setUnknownReason(reason);
	delete[] reason;
}
void Scanner::discard() {
	this->debugActions("DISCARD");

	this->_currLexemPos = 0;
	this->_currLexem[0] = '\0';
}
void Scanner::end() {
	this->debugActions("END");

	this->makeToken(TOKEN_EOF);
}
// ####  END ACTIONS ######

void Scanner::makeToken(TType type, int unget) {
	this->_currCol -= unget;
	this->_buffer.ungetChar(unget);
	this->_returnToken = new Token(
			type,
			this->_currLine,
			this->_currTokenCol);
	this->_tokenEndReached = true;
}

void Scanner::debugActions(char const * action) const {
	clog << "Action: " << action << " | " << "Lexem: " << this->_currLexem << " | " << "State: " << this->_automat.getCurrentState() << endl;
}

TType Scanner::getSignType(char const * const string) const {
	if (__strcmp(string, "+") == 0) return TOKEN_PLUS;
	if (__strcmp(string, "-") == 0) return TOKEN_MINUS;
	if (__strcmp(string, ":") == 0) return TOKEN_COLON;
	if (__strcmp(string, ";") == 0) return TOKEN_SEMICOLON;
	if (__strcmp(string, "<") == 0) return TOKEN_SMALLER;
	if (__strcmp(string, ">") == 0) return TOKEN_GREATER;
	if (__strcmp(string, "=") == 0) return TOKEN_EQUALS;
	if (__strcmp(string, "*") == 0) return TOKEN_STAR;
	if (__strcmp(string, ":=") == 0) return TOKEN_ASSIGN;
	if (__strcmp(string, "=:=") == 0) return TOKEN_ASSIGN2;
	if (__strcmp(string, "!") == 0) return TOKEN_NOT;
	if (__strcmp(string, "&&") == 0) return TOKEN_AND;
	if (__strcmp(string, "(") == 0) return TOKEN_BRACKETS0_OPEN;
	if (__strcmp(string, ")") == 0) return TOKEN_BRACKETS0_CLOSE;
	if (__strcmp(string, "{") == 0) return TOKEN_BRACKETS1_OPEN;
	if (__strcmp(string, "}") == 0) return TOKEN_BRACKETS1_CLOSE;
	if (__strcmp(string, "[") == 0) return TOKEN_BRACKETS2_OPEN;
	if (__strcmp(string, "]") == 0) return TOKEN_BRACKETS2_CLOSE;
	return TOKEN_UNKNOWN;

}

bool Scanner::isIF(char const * const string) const {

	if(__strcmp(string, "IF") == 0)
		return true;

	if (__strcmp(string, "if") == 0)
			return true;

	return false;
}

bool Scanner::isWHILE(char const * const string) const {

	if (__strcmp(string, "WHILE") == 0)
		return true;

	if (__strcmp(string, "while") == 0)
		return true;
	return false;
}

bool Scanner::isINT(char const * const string) const {
	if (__strcmp(string, "int") == 0)
		return true;
	return false;
}

bool Scanner::isELSE(char const * const string) const {

	if (__strcmp(string, "ELSE") == 0)
		return true;

	if (__strcmp(string, "else") == 0)
		return true;
	return false;
}

bool Scanner::isREAD(char const * const string) const {
	if (__strcmp(string, "read") == 0)
		return true;
	return false;
}

bool Scanner::isWRITE(char const * const string) const {
	if (__strcmp(string, "write") == 0)
		return true;
	return false;
}
