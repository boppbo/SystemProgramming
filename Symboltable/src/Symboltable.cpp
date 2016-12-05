/*
 * Symboltable.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Symboltable.h"
#include "../includes/Info.h"

Symboltable::Symboltable(unsigned int tableSize)
: _tableSize(tableSize) {
}

Symboltable::~Symboltable() {
}

Information& Symboltable::getOrAdd(char const * const lexem) {
	return *new Info(lexem, Info::VarType::INT);
}

void Symboltable::initSymbols() {
}
