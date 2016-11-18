/*
 * deque.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../../includes/Collections/deque.h"
#include <stdexcept>

deque::~deque()
{
	while(this->_firstNode != nullptr) {
		Node *ptr = this->_firstNode;
		this->_firstNode = this->_firstNode->_next;

		delete ptr;
	}
}

void deque::push(char const * const newItem) {
	this->_lastNode = new Node(newItem, this->_lastNode);
	if (this->_firstNode == nullptr)
		this->_firstNode = this->_lastNode;
	this->_size++;

	this->setCurrentNode(*this->_lastNode);
}

char const& deque::operator[](unsigned int const index) const {
	using std::out_of_range;
	bool fromEnd = index > (this->_size / 2);

	Node* ptr = fromEnd ? this->_lastNode : this->_firstNode;
	for (unsigned int i = 0; i < fromEnd ? this->_size-index-1 : index; i++) {
		if (ptr == nullptr)
			break;
		ptr = fromEnd ? ptr->_prev : ptr->_next;
	}

	if (ptr == nullptr)
		throw out_of_range("index");

	return *ptr->_data;
}
