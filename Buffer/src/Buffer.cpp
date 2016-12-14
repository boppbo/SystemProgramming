/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Buffer.h"
#include <stdexcept>
using namespace std;

Buffer::Buffer(const char* const filePath, unsigned int size)
: _size(size), _stream(filePath) {
	//Need at least one char and '\'
	if (size < 2)
		throw invalid_argument("size");

	if (!this->_stream)
		throw invalid_argument("filePath");
}

char const* Buffer::read()
{
	auto result = new char[this->_size];

	this->_stream.read(result, this->_size-1);
	result[this->_stream.gcount()] = '\0';

	return result;
}

bool Buffer::isEof() const
{
	return this->_stream.eof();
}
