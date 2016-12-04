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
#include "../includes/Token.h"

class Scanner {

public:
	Scanner(char const* filename, int bufferSize, int stdLexemLenght, bool debug);
	virtual ~Scanner();
	Token* nextToken();
	int _currentTokenColumn;
	int _currentColumn = 1;
private:
	bool _tokenEndReached = false;
	bool _debug = false;
	char _currentChar;
	char* _currentLexem;
	int _currentLexemPtr;
	int _stdLexemLenght;
	int _currentLine = 1;

	Token* _returnToken;
	Buffer* _buffer;
	Automat* _automat;
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
	TType getSignType(char* string);
	void makeToken(TType type, int unget = 1);
	void debugActions(char const* action);

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
