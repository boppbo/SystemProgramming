/*
 * deque.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../../includes/Collections/deque.h"
#include <stdexcept>

template<typename T, bool isArr>
T const& deque<T, isArr>::operator[](unsigned int const index) const {
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
