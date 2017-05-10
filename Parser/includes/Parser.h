/*
 * Parser.h
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#ifndef PARSER_INCLUDES_PARSER_H_
#define PARSER_INCLUDES_PARSER_H_

#include "../../Scanner/includes/Scanner.h"
#include "../includes/Node.h"

class Parser {
public:
	Parser(Scanner& scanner);
	virtual ~Parser();
	virtual Tree* parse();

private:
	Scanner& _scanner;
};

#endif /* PARSER_INCLUDES_PARSER_H_ */
