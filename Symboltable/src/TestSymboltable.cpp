#include "../includes/Symboltable.h"
#include <iostream>
using namespace std;

int main() {

	Symboltable symboltable;
	cout << symboltable.getOrAdd("foo").getName() << endl;
	cout << symboltable.getOrAdd("bar").getName() << endl;
}
