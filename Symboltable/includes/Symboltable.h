/*
 * Symboltable.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include "Information.h"
#include "StringTable.h"

class Symboltable {
public:
	explicit Symboltable(unsigned int tableSize = 256);
	virtual ~Symboltable();
	Information& getOrAdd(char const *const lexem);

private:
	void initSymbols();
	unsigned int _tableSize;
};

#endif /* SYMBOLTABLE_H_ */
