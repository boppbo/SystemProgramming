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
	explicit Info(char const * name, bool isKeyword = false)
	: name(__strdup(name)), _varType(isKeyword ? VarType::KEYWORD : VarType::INT) { }

	virtual ~Info() {
		delete[] this->name;
	}
	virtual bool compareLex(char const * lexem) const override {
		return __strcmp(lexem, this->name) == 0;
	}
	virtual char* getName() const override{
		return __strdup(this->name);
	}

	virtual bool isArray() const override {
		return this->_varType == VarType::INTARR;
	}
	virtual bool isInteger() const override {
		return this->_varType == VarType::INT;
	}
	virtual bool isKeyword() const override {
		return this->_varType == VarType::KEYWORD;
	}

	virtual void setIsArray(bool isArray) override {
		if (this->_varType == VarType::KEYWORD)
			throw std::domain_error("Invalid operation for keywords!");

		this->_varType = isArray ? VarType::INTARR : VarType::INT;
	}

private:
	enum class VarType : char { INT, INTARR, KEYWORD };
	char* const name;
	VarType _varType;
};

#endif /* INFORMATION_H_ */
