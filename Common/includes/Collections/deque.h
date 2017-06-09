/*
 * deque.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef DEQUE_H_
#define DEQUE_H_

#include <stdexcept>

template<typename T, bool isArr = false>
class deque {
public:
	deque() { }
	virtual ~deque() {
		while(this->_firstNode != nullptr) {
			Node *ptr = this->_firstNode;
			this->_firstNode = this->_firstNode->_next;

			delete ptr;
		}
	}
	deque(deque const &src) = delete;
	deque& operator= (deque const &src) = delete;

	unsigned int getSize() const {
		return this->_size;
	}
	virtual void push(T const * const newItem) {
		this->_lastNode = new Node(newItem, this->_lastNode);
		if (this->_firstNode == nullptr)
			this->_firstNode = this->_lastNode;
		this->_size++;
	}
	T const& operator[](unsigned int const index) const {
		using std::out_of_range;
		bool fromEnd = index > (this->_size / 2);

		Node* ptr = fromEnd ? this->_lastNode : this->_firstNode;
		for (unsigned int i = 0; (i < (fromEnd ? this->_size-index-1 : index)); i++) {
			if (ptr == nullptr)
				break;
			ptr = fromEnd ? ptr->_prev : ptr->_next;
		}

		if (ptr == nullptr)
			throw out_of_range("index");

		return *ptr->_data;
	}

protected:
	struct Node  {
		T const * const _data;
		Node *_next = nullptr, *_prev;

		Node(T const * const data, Node* const prev = nullptr)
		: _data(data), _prev(prev) {
			if (prev != nullptr)
				prev->_next = this;
		}
		Node(Node const &src) = delete;
		Node& operator= (Node const &src) = delete;
		virtual ~Node()
		{
			if (isArr)
				delete[] this->_data;
			else
				delete this->_data;
		}
	};

	Node* getLastNode() { return this->_lastNode; }

private:
	unsigned int _size = 0;
	Node *_firstNode = nullptr, *_lastNode = nullptr;
};

#endif /* DEQUE_H_ */
