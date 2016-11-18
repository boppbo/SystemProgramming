/*
 * Buffer.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include "GenericBuffer.h"
#include <fstream>

class Buffer : public GenericBuffer {
public:
	Buffer(const char* const filePath, unsigned int size = 1024);
protected:
	virtual bool isEof() const override;
	virtual char const* read() override;
private:
	int _size;
	std::ifstream _stream;
};


#endif /* BUFFER_H_ */
