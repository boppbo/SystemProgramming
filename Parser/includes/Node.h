#include "../../Scanner/includes/Scanner.h"
#include "ParseTree.h"
#include <vector>
using namespace std;

enum nodeType {
	Prog,
	Decls,
	Decl,
	DeclArray,
	DeclIdent,
	Array,
	Statements,
	StatementIdent,
	StatementWrite,
	StatementRead,
	StatementIf,
	StatementWhile,
	StatementBlock,
	Exp,
	Exp2,
	Exp2Ident,
	Exp2Int,
	Exp2Minus,
	Exp2Neg,
	Index,
	OpExp,
	Op,
	Nil,
	leaf
};

char const* const _nodeTypes[] = {
	"Prog",
	"Decls",
	"Decl",
	"DeclArray",
	"DeclIdent",
	"Array",
	"Statements",
	"StatementIdent",
	"StatementWrite",
	"StatementRead",
	"StatementIf",
	"StatementWhile",
	"StatementBlock",
	"Exp",
	"Exp2",
	"Exp2Ident",
	"Exp2Int",
	"Exp2Minus",
	"Exp2Neg",
	"Index",
	"OpExp",
	"Op",
	"Nil",
	"leaf"
};

class Node : public ParseTree{

public:
	nodeType _type;
	vector<Node*> _children;
	Node() {};
	Node(nodeType type);
	virtual void print(int indent = 0);

	virtual const char* getTypeAsString() const {
		return _nodeTypes[this->_type];
	}
};