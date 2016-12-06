/*
 * trackingdeque.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../../includes/Collections/trackingDeque.h"

void trackingDeque::push(char const * const newItem) {
	deque<char, true>::push(newItem);
	this->setCurrentNode(*this->getLastNode());
}
