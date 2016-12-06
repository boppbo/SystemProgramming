/*
 * Information.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef INFORMATION_H_
#define INFORMATION_H_

class Information {
public:
	virtual ~Information() { }
	virtual bool compareLex(char const * const lexem) const = 0;
	virtual char* getName() const = 0;

	virtual bool isArray() const = 0;
	virtual bool isInteger() const = 0;
	virtual bool isKeyword() const = 0;

	virtual void setIsArray(bool isArray) = 0;
};

#endif /* INFORMATION_H_ */
