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
#include "Nodes\Node.h"

class Leaf: public Node {
protected:
	Token* token;
	Leaf();
public:
	virtual ~Leaf();
	virtual void accept(class TreeVisitor &visitor);

};

#endif /* PARSER_INCLUDES_LEAF_H_ */
