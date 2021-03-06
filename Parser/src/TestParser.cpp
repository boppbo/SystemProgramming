/*
 * TestParser.cpp
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#include "../includes/Parser.h"
#include "../includes/TreeVisitorPrintTree.h"
#include "../includes/TreeVisitorTypeCheck.h"
#include "../includes/TreeVisitorCodeGeneration.h"
#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 4) {
		cerr << "Invalid arguments! Usage: " << argv[0] << " source.txt -c source.code" << endl;
		return EXIT_FAILURE;
	}

#ifndef DEBUG
	//disable debug messages for release.
	clog.setstate(std::ios_base::failbit);
#endif

	Symboltable st;
	Scanner scanner(argv[1], st);
	Parser parser(scanner);
	TreeVisitorPrintTree printTree = TreeVisitorPrintTree();
	TreeVisitorTypeCheck checkType = TreeVisitorTypeCheck();
	auto codeOutStream = ofstream(argv[3]);
	TreeVisitorCodeGeneration codeGeneration = TreeVisitorCodeGeneration(codeOutStream);


	try {
		Tree* t = parser.parse();
#ifdef DEBUG
		//print tree only for debug
		t->accept(&printTree);
#endif
		t->accept(&checkType);
		t->accept(&codeGeneration);
	}
	catch(exception& e) {
		cerr << e.what() << endl
			 << "stop" << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
