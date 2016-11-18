/*
 * Buffer.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef DEQUE_H_
#define DEQUE_H_

class deque {
public:
	deque() { }
	virtual ~deque();
	deque(deque const &src) = delete;
	deque& operator= (deque const &src) = delete;

	virtual void push(char const * const newItem);
	char const& operator[](unsigned int const index) const;

protected:
	struct Node  {
		char const * const _data;
		Node *_next = nullptr, *_prev;

		Node(char const * const data, Node* const prev = nullptr)
		: _data(data), _prev(prev) {
			if (prev != nullptr)
				prev->_next = this;
		}
		Node(deque const &src) = delete;
		Node& operator= (Node const &src) = delete;
		virtual ~Node()
		{
			delete[] this->_data;
		}
	};

	virtual void setCurrentNode(Node &current) {
		this->_currentNode = &current;
		this->_currentPos = current._data;
	}
	virtual Node const* getCurrentNode() { return this->_currentNode; }
	unsigned int getSize() { return this->_size; }
	char const*_currentPos = nullptr;

private:
	unsigned int _size = 0;
	Node *_currentNode = nullptr, *_firstNode = nullptr, *_lastNode = nullptr;
};

#endif /* DEQUE_H_ */
