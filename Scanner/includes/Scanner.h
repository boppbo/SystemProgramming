/*
 * Scanner.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#include "../../Automat/includes/Automat.h"
#include "../../Buffer/includes/Buffer.h"
#include "../../Symboltable/includes/Symboltable.h"
#include "../../Symboltable/includes/Token.h"

class Scanner {

public:
	explicit Scanner(char const* filename, Symboltable& st, unsigned int maxLexemLength = 1024);
	virtual ~Scanner() { delete[] this->_currLexem; }
	Scanner(Scanner const &src) = delete;
	Scanner& operator= (Scanner const &src) = delete;

	Token* nextToken();
private:
	Automat _automat;
	Buffer _buffer;
	Symboltable& _st;

	char* _currLexem = nullptr;
	Token* _returnToken = nullptr;

	bool _tokenEndReached = false;
	char _currChar = '\0';
	int _currTokenCol = 1, _currCol = 1, _currLine = 1;
	unsigned int _currLexemPos = 0;
	unsigned int const _maxLexemLength;

	// Actions
	void nothing();
	void add_char();
	void add_token_integer();
	void add_token_identifier();
	void add_token_sign();
	void add_token_sign_ug0();
	void add_token_sign_ug2();
	void add_new_line();
	void add_token_unknown();
	void discard();
	void end();

	TType getSignType(char const* string) const;
	void makeToken(TType type, int unget = 1);
	void debugActions(char const* action) const;

	void(Scanner::*tansition_action[11])() = {
		&Scanner::nothing,
		&Scanner::add_char,
		&Scanner::add_token_integer,
		&Scanner::add_token_identifier,
		&Scanner::add_token_sign,
		&Scanner::add_token_sign_ug0,
		&Scanner::add_token_sign_ug2,
		&Scanner::add_new_line,
		&Scanner::add_token_unknown,
		&Scanner::discard,
		&Scanner::end
	};
};

#endif /* SCANNER_H_ */
