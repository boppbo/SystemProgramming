/*
* Token.h
*/

#ifndef TOKEN_H_
#define TOKEN_H_

#include "../../Symboltable/includes/Information.h"

typedef enum {
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
} TType;

class Token {

public:
	TType _type;
	int _line;
	int _column;
	Information *_info;

	Token(TType type, int line, int column);
	virtual ~Token();
	const char* getTypeAsString();
private:
	static const char* const _tokenTypesArray[];
};

#endif /* TOKEN_H_ */
