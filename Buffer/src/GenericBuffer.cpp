/*
 * GenericBuffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/GenericBuffer.h"
#include "../../Common/includes/cstring.h"
using namespace std;

char GenericBuffer::getChar() {
	Node const* curr = this->getCurrentNode();
	//Do we have to switch nodes?
	if (curr == nullptr	|| *this->_currentPos == '\0') {
		if (curr == nullptr || curr->_next == nullptr) {
			// We need to read from disk (first or last node)
			if (this->isEof())
				return '\0';

			this->push(this->read());
		}
		else
			// Data already in memory
			this->setCurrentNode(*curr->_next);
	}

	// Set to next position after retrieving.
	return (*this->_currentPos == '\0')
			? *this->_currentPos
			: *this->_currentPos++;
}
char GenericBuffer::ungetChar(unsigned int count) {
	//currentPos points to the next character,
	//so we have always to go back at least one position
	for (unsigned int i = 0; i <= count; i++)
	{
		Node const* curr = this->getCurrentNode();
		if (curr == nullptr)
			return '\0';

		if (this->_currentPos == curr->_data) {
			// At the position of first character in node
			if (curr->_prev == nullptr)
				//First node, so we can't go further back
				return '\0';

			// Switch to the last character in previous node
			this->setCurrentNode(*curr->_prev);
			this->_currentPos += __strlen(curr->_prev->_data) - 1;
		}
		else
		{
			this->_currentPos--;
		}
	}
	// Ensure getChar still works as expected.
	return *this->_currentPos++;
}
