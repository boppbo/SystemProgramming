#include "../../Scanner/includes/Scanner.h"
#include "Node.h"


class Leaf : public Node {

public:
	Leaf(Token* token, nodeType type);
	Token* _token;
	nodeType _type;
	OpType _opType;
	virtual void print(int indent = 0) /*override*/;
	virtual void accept(Visitor* visitor) {
		visitor->visit(this);
	}

private:
	
};