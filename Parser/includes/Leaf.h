/*
 * Leaf.h
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#ifndef PARSER_INCLUDES_LEAF_H_
#define PARSER_INCLUDES_LEAF_H_

#include "Tree.h"

class Leaf: public Tree {
public:
	Leaf();
	virtual ~Leaf();

	void accept(TreeVisitor &visitor);
};

#endif /* PARSER_INCLUDES_LEAF_H_ */
