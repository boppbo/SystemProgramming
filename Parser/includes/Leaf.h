/*
 * Leaf.h
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#ifndef LEAF_H
#define LEAF_H

#include "Tree.h"
#include "../../Symboltable/includes/Token.h"

enum OpType {
	opPlus,
	opMinus,
	opMult,
	opDiv,
	opLess,
	opGreater,
	opEqual,
	opUnEqual,
	opAnd,
	INVALID
};

class Leaf: public Tree {
public:
	Leaf(Token const* token, NType nodeType);
	virtual ~Leaf();
	Leaf(Leaf const &src) = delete;
	Leaf& operator= (Leaf const &src) = delete;

	virtual void accept(TreeVisitor *visitor) override;

private:
	void setOperationTypeFromToken();
	OpType _opType = OpType::INVALID;
	Token const* _token;
};

#endif /* LEAF_H */
