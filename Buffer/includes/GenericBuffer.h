/*
 * GenericBuffer.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef GENERICBUFFER_H_
#define GENERICBUFFER_H_

#include "../../Common/includes/Collections/trackingDeque.h"

class GenericBuffer : protected trackingDeque {
public:
	GenericBuffer() { }
	char getChar();
	char ungetChar(unsigned int count = 1);

protected:
	virtual char const* read() = 0;
	virtual bool isEof() const = 0;
};

#endif /* GENERICBUFFER_H_ */
