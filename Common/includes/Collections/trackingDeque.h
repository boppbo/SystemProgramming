/*
 * trackingDeque.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef TRACKINGDEQUE_H_
#define TRACKINGDEQUE_H_

#include "deque.h"

class trackingDeque : public deque<char, true> {
public:
	trackingDeque() { }
	virtual void push(char const * const newItem) override {
		deque<char, true>::push(newItem);
		this->setCurrentNode(*this->getLastNode());
	}

protected:
	void setCurrentNode(Node const &current) {
		this->_currentNode = &current;
		this->_currentPos = current._data;
	}
	Node const* getCurrentNode() const {
		return this->_currentNode;
	}
	char const*_currentPos = nullptr;

private:
	Node const *_currentNode = nullptr;
};

#endif /* TRACKINGDEQUE_H_ */
