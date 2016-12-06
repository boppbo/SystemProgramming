/*
 * searchableDeque.h
 *
 * A poor mans iterator
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SEARCHABLEDEQUE_H_
#define SEARCHABLEDEQUE_H_

#include "../../Common/includes/Collections/deque.h"
#include "Info.h"

class SearchableDeque : public deque<Info> {
public:
	SearchableDeque() { }

	Information* find(char const * const lexem) {
		auto result = this->getLastNode();
		while(result != nullptr && !result->_data->compareLex(lexem))
			result = result->_prev;

		return const_cast<Info *>( result->_data);
	}
};

#endif /* SEARCHABLEDEQUE_H_ */
