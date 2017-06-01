#ifndef NODE_H_
#define NODE_H_


#include "../../Scanner/includes/Scanner.h"
#include <vector>

#include "Visitor.h"

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
	leaf,
	Keyword,
	INTEGER,
	Identifier,
	IdentifierUsed,
	NoType,

	intType,
	intArrayType,
	arrayType,
	ERROR
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
	"leaf",
	"Keyword",
	"INTEGER",
	"Identifier",
	"IdentifierUsed",
	"NOTYPE",
	"ERROR"
};

enum OpType {
	opPlus,
	opMinus,
	opMult,
	opDiv,
	opLess,
	opGreater,
	opEqual,
	opUnEqual,
	opAnd
};

class Node {

public:
	bool _isEps = true;
	nodeType _type;
	OpType _opType;
	vector<Node*> _children;
	Node() {};
	Node(nodeType type);
	virtual void print(int indent = 0);

	virtual const char* getTypeAsString() const {
		return _nodeTypes[this->_type];
	}
	virtual void accept(Visitor* visitor) {
		visitor->visit(this);
	}
};

#endif