/*
 * StringTable.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef STRINGTABLE_H_
#define STRINGTABLE_H_

#include "../../Common/includes/Collections/deque.h"

class StringTable : protected deque {
public:
	StringTable(unsigned int nodeSize = 4096) : _nodeSize(nodeSize) { }
	char const * add (char const * const item);
protected:
	void push(char const * const newItem) override;

private:
	unsigned int _spaceLeft = 0;
	unsigned int const _nodeSize;
};

#endif /* STRINGTABLE_H_ */
