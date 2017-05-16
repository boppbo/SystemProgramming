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
	Node* array();
	Node* statements();
	Node* statement();
	Node* statementIdent();
	Node* statementWrite();
	Node* statementRead();
	Node* statementIf();
	Node* statementWhile();
	Node* statementBlock();
	Node* index();
	Node* exp();
	Node* exp2();
	Node* op_exp();
	Node* op();
	Node* exp2Ident();
	Node* exp2Int();
	Node* exp2Minus();
	Node* exp2Neg();

private:
	Scanner* _scanner;
	Token* _prevToken = nullptr;
	Token* _currentToken;
	void addLeaf(Node* parent, TType expectedTokenType);
	void addNode(Node* parent, Node* child, bool optional = false);
	void parseError();

};