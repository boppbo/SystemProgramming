#include "../../Scanner/includes/Scanner.h"
#include "ParseTree.h"
#include "Leaf.h"


class Parser {

public:
	Parser(Scanner* scanner);
	Node* parse();
	Node* prog();
	Node* decls();
	Node* decl();
	Node* declsArray();
	Node* declsIdent();
	Node* array();
	Node* statements();

private:
	Scanner* _scanner;
	Token* _prevToken = nullptr;
	Token* _currentToken;
	int addLeaf(Node* parent);

};