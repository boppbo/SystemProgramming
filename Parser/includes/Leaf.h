/*
 * Leaf.h
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#ifndef LEAF_H
#define LEAF_H

#include "Tree.h"

class Leaf: public Tree {
public:
	Leaf();
	virtual ~Leaf();

	virtual void accept(TreeVisitor &visitor) override;

};

#endif /* PARSER_INCLUDES_LEAF_H_ */
