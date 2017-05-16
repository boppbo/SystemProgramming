#include "../../Scanner/includes/Scanner.h"
#include "../includes/Parser.h"
#include <iostream>
#include <iomanip>
using namespace std;

#define EVER ;;

int main(int argc, char *argv[]) {
	if (argc != 3)
		return EXIT_FAILURE;

	// disable debug messages.
	clog.setstate(std::ios_base::failbit);

	Symboltable st;
	Scanner* scanner = new Scanner(argv[1], st);
	ofstream out(argv[2]);
	Parser parser(scanner);

	cout << "parsing ... \n";
	try {
		Node* pt = parser.parse();
		pt->print();
	}
	catch (exception e) {
		cout << e.what() << "\n" << "stop";
	}
}