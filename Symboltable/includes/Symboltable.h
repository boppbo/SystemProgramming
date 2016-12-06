/*
 * Symboltable.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include "Information.h"
#include "SearchableDeque.h"
#include "StringTable.h"

class Symboltable {
public:
	explicit Symboltable(unsigned int bucketSize = 256);
	virtual ~Symboltable();
	Information& getOrAdd(char const *const lexem);

protected:
	unsigned int getHashCode(char const * lexem) const;

private:
	void initSymbols();
	void addKeyword(char const * const lexem);

	SearchableDeque* const _buckets;
	unsigned int const _bucketSize;
	StringTable _strings;
};

#endif /* SYMBOLTABLE_H_ */
