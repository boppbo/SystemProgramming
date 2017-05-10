/*
 * Parser.cpp
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#include "../includes/Parser.h"
#include "../includes/Leaf.h"

Parser::Parser(Scanner& scanner) : _scanner(scanner) {
	// TODO Auto-generated constructor stub
}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

Tree* Parser::parse() {
	Tree* result = new Leaf();
	return result;
}
