/*
 * Tree.h
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#ifndef PARSER_INCLUDES_TREE_H_
#define PARSER_INCLUDES_TREE_H_

#include "Nodes\Node.h"

class Tree {
public:
	Tree(ProgNode* ProgNode);
	virtual ~Tree();

	virtual void accept(class TreeVisitor &visitor) = 0;
};

#endif /* PARSER_INCLUDES_TREE_H_ */
