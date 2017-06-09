/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../../Common/includes/cstring.h"
#include "../includes/Scanner.h"
#include <iostream>
#include <cerrno>
using namespace std;

Scanner::Scanner(char const* filename, Symboltable &st, unsigned int maxLexemLength)
: _buffer(filename), _st(st), _currLexem(new char[maxLexemLength+2]) , _maxLexemLength(maxLexemLength){
	if (maxLexemLength < 1)
		throw invalid_argument("maxLexemLength");
}

Token const* Scanner::nextToken() {
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
		auto *info = &this->_st.getOrAdd(this->_currLexem);
		this->makeToken(info->getTokenType());
		this->_returnToken->_info = info;
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
	strncpy(reason, "Symbol: ", 9);
	strncpy((reason+8), this->_currLexem, this->_currLexemPos+1);

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
