#include "../includes/Scanner.h"
#include <iostream>
#include <iomanip>
using namespace std;

#define EVER ;;

int main(int argc, char *argv[]) {
	if (argc != 2)
		return EXIT_FAILURE;

	//disable debug messages.
	std::clog.setstate(std::ios_base::failbit);
	Scanner scanner(argv[1], 2048);

	for(EVER) {
		Token *t = scanner.nextToken();

		cout << "TType: " << left << setw(20) << t->getTypeAsString()
			<< " Line: " << t->_line
			<< "\t Column: " << t->_column << endl;

		if (t->_type != TOKEN_EOF)
			break;

		delete t;
	}

	return EXIT_SUCCESS;
}
