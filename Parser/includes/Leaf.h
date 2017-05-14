#include "../../Scanner/includes/Scanner.h"
#include "Node.h"


class Leaf : public Node {

public:
	Leaf(Token* token);
	Token* _token;
	void print(int indent = 0);
private:
	
};