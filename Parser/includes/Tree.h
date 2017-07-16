/*
 * Tree.h
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#ifndef PARSER_INCLUDES_TREE_H_
#define PARSER_INCLUDES_TREE_H_


enum NType {
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

class Tree {
public:
	Tree(NType nodeType);
	virtual ~Tree() {}
	virtual void accept(class TreeVisitor* visitor) = 0;
	virtual char const * getTypeAsString() const;
	virtual NType getType() const;
	virtual void setType(NType type){
		this->_nodeType = type;
	};

private:
	static char const* const _nodeTypes[];
	NType _nodeType;
};

#endif /* PARSER_INCLUDES_TREE_H_ */
