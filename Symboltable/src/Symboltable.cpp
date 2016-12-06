/*
 * Symboltable.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Symboltable.h"
#include "../includes/Info.h"

Symboltable::Symboltable(unsigned int bucketSize)
: _buckets(new SearchableDeque[bucketSize]()), _bucketSize(bucketSize) {
	this->initSymbols();
}

Symboltable::~Symboltable() {
	delete[] this->_buckets;
}

Information& Symboltable::getOrAdd(char const * const lexem) {
	auto hash = this->getHashCode(lexem);

	auto buck = &this->_buckets[hash];
	auto result = buck->find(lexem);

	if (result == nullptr)
		buck->push(
				static_cast<Info*>(
						result = new Info(this->_strings.add(lexem))));

	return *result;
}

unsigned int Symboltable::getHashCode(char const * lexem) const {
    int c, hash1 = 5381, hash2 = 5381;
    while ((c = lexem[0]) != 0) {
        hash1 = ((hash1 << 5) + hash1) ^ c;
        c = lexem[1];
        if (c == 0)
            break;
        hash2 = ((hash2 << 5) + hash2) ^ c;
        lexem += 2;
    }
    return (hash1 + (hash2 * 1566083941)) % this->_bucketSize;
}

void Symboltable::initSymbols() {
	this->addKeyword("int");

	this->addKeyword("if");
	this->addKeyword("IF");
	this->addKeyword("else");
	this->addKeyword("ELSE");
	this->addKeyword("while");
	this->addKeyword("WHILE");

	this->addKeyword("read");
	this->addKeyword("write");
}

void Symboltable::addKeyword(char const * const lexem) {
	this->_buckets[this->getHashCode(lexem)]
	//no need for string table as keywords are already in non-volatile memory;
	.push(new Info(lexem, true));
}
