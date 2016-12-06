#include "../includes/cstring.h"
#include "../includes/Collections/trackingDeque.h"
#include <iostream>
using namespace std;

int main() {
	cout << strlen("");
	cout << "Hello World" << strlen("Hello World") << endl;

	trackingDeque foo;
	foo.push("foo");
	foo.push("bar");
}
