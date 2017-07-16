/*
* Token.h
*/

#ifndef TOKEN_H_
#define TOKEN_H_

#include "../../Common/includes/cstring.h"
#include "Information.h"

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

	Information* _info = nullptr;
	int _integerValue = 0;

	void setUnknownReason(char const * const reason ) {
		delete[] this->_unknownReason;
		this->_unknownReason = strdup(reason);
	}
	char const * getUnknownReason() const {
		return this->_unknownReason;
	}
	int getIntValue(){
		return _integerValue;
	}
private:
	char const * _unknownReason = nullptr;
	static char const* const _tokenTypes[];
};

#endif /* TOKEN_H_ */
