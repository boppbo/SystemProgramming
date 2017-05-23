/*
 * Info.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef INFO_H_
#define INFO_H_

#include "../../Common/includes/cstring.h"
#include "Information.h"
#include <stdexcept>

class Info : public Information {
public:
	explicit Info(char const * name, TType tokenType = TOKEN_IDENTIFIER)
	: _name(strdup(name)), _tokenType(tokenType), _varType(VarType::UNKNOWN) { }

	virtual ~Info() {
		delete[] this->_name;
	}
	virtual bool compareLex(char const * lexem) const override {
		return strcmp(lexem, this->_name) == 0;
	}
	virtual char* getName() const override {
		return strdup(this->_name);
	}
	virtual TType getTokenType() const override {
		return this->_tokenType;
	}

	virtual bool isArray() const override {
		return this->_varType == VarType::INTARR;
	}
	virtual bool isInteger() const override {
		return this->_varType == VarType::INT;
	}

	virtual void setIsArray(bool isArray) override {
		if (this->_tokenType != TOKEN_IDENTIFIER)
			throw std::domain_error("Invalid operation for keywords!");
		if (this->_varType != VarType::UNKNOWN)
			throw std::domain_error(strcat("Identifier already declared: ", this->_name));

		this->_varType = isArray ? VarType::INTARR : VarType::INT;
	}

protected:
	enum class VarType : char { INT, INTARR, UNKNOWN };

private:
	char* const _name;
	TType _tokenType;
	VarType _varType;
};

#endif /* INFORMATION_H_ */
