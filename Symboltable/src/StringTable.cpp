#include "../includes/StringTable.h"
#include "../../Common/includes/cstring.h"
#include <stdexcept>

char const * StringTable::add(char const * item) {
	auto len = strlen(item)+1;
	if (len > _nodeSize)
		throw std::invalid_argument("item");

	if (len > this->_spaceLeft)
		this->push(new char[this->_nodeSize]);

	char const * result = this->_currentPos;
	strncpy(const_cast<char *>(this->_currentPos), item, len);

	this->_currentPos += len;
	this->_spaceLeft -= len;

	return result;
}

void StringTable::push(char const * const newItem) {
	deque::push(newItem);
	this->_spaceLeft = this->_nodeSize;
}
