/*
 * Tree.cpp
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#include "../includes/Tree.h"

Tree::Tree(NType nodeType) : _nodeType(nodeType) {
}

char const * Tree::getTypeAsString() const {
	return _nodeTypes[this->_nodeType];
}

char const* const Tree::_nodeTypes[] = {
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
