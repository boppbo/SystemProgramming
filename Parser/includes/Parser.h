/*
 * Parser.h
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#ifndef PARSER_INCLUDES_PARSER_H_
#define PARSER_INCLUDES_PARSER_H_

#include "Tree.h"
#include "../../Scanner/includes/Scanner.h"
#include "../../Symboltable/includes/Symboltable.h"

class Parser {
private:
	Scanner& _scanner;
public:
	Parser(Scanner& scanner);
	virtual ~Parser();

	virtual Tree* parse();
};

#endif /* PARSER_INCLUDES_PARSER_H_ */
