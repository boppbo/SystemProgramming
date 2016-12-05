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

class Info : public Information {
public:
	enum class VarType : char { INT, INTARR, KEYWORD };

	explicit Info(char const * name, VarType const varType)
	: name(strdup(name)), _varType(varType) { }

	virtual ~Info() {
		delete[] this->name;
	}
	virtual bool compareLex(char const * lexem) const override {
		return strcmp(lexem, this->name) == 0;
	}
	virtual char* getName() const override{
		return strdup(this->name);
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

private:
	char* const name;
	VarType const _varType;
};

#endif /* INFORMATION_H_ */
