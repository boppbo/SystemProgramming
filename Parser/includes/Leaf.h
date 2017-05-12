/*
 * Leaf.h
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#ifndef PARSER_INCLUDES_LEAF_H_
#define PARSER_INCLUDES_LEAF_H_

#include "Tree.h"
#include "../../Scanner/includes/Token.h"

class Leaf: public Node {
public:
	Leaf();
	virtual ~Leaf();
	void accept(TreeVisitor &visitor);

private:

	Token* token;
	Leaf();
};

#endif /* PARSER_INCLUDES_LEAF_H_ */
