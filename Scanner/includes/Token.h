/*
* Token.h
*/

#ifndef TOKEN_H_
#define TOKEN_H_

#include "../../Symboltable/includes/Information.h"
#include "../../Common/includes/cstring.h"

enum TType {
	TOKEN_INTEGER,
	TOKEN_IDENTIFIER,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_COLON,
	TOKEN_SMALLER,
	TOKEN_GREATER,
	TOKEN_EQUALS,
	TOKEN_ASSIGN,
	TOKEN_ASSIGN2,
	TOKEN_NOT,
	TOKEN_AND,
	TOKEN_SEMICOLON,
	TOKEN_STAR,
	TOKEN_BRACKETS0_OPEN,
	TOKEN_BRACKETS0_CLOSE,
	TOKEN_BRACKETS1_OPEN,
	TOKEN_BRACKETS1_CLOSE,
	TOKEN_BRACKETS2_OPEN,
	TOKEN_BRACKETS2_CLOSE,
	TOKEN_IF,
	TOKEN_WHILE,
	TOKEN_UNKNOWN,
	TOKEN_EOF
};

class Token {
public:
	Token(TType type, int line, int column)
		: _type(type), _line(line), _column(column) { }

	virtual ~Token() {
		delete[] this->_unknownReason;
	}

	virtual const char* getTypeAsString() const {
		return this->_tokenTypes[this->_type];
	}

	TType const _type;
	int const _line;
	int const _column;

	Information const* _info = nullptr;
	int _integerValue = 0;

	void setUnknownReason(char const * const reason ) {
		delete[] this->_unknownReason;
		this->_unknownReason = __strdup(reason);
	}
	char const * getUnknownReason() {
		return this->_unknownReason;
	}
private:
	char const * _unknownReason = nullptr;
	static char const* const _tokenTypes[];
};

#endif /* TOKEN_H_ */
