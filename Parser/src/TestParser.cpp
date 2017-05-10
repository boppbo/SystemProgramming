/*
 * TestParser.cpp
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#include "../includes/Parser.h"
#include "../includes/TreeVisitorTypeCheck.h"
#include "../includes/TreeVisitorCodeGeneration.h"
#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 3)
		return EXIT_FAILURE;

#ifndef DEBUG
	//disable debug messages for release.
	clog.setstate(std::ios_base::failbit);
#endif

	Symboltable st;
	Scanner scanner(argv[1], st);
	Parser parser(scanner);
	TreeVisitorTypeCheckResult tcRes;
	TreeVisitorTypeCheck tc(tcRes);
	TreeVisitorCodeGeneration cg;
	Tree* t = parser.parse();

	if (t == nullptr)
		return EXIT_FAILURE;

	t->accept(tc);
	if (tcRes.isFailed())
		return EXIT_FAILURE;

	t->accept(cg);

	return EXIT_SUCCESS;
}
