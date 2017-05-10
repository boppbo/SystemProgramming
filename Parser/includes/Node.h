/*
 * Node.h
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#ifndef PARSER_INCLUDES_NODE_H_
#define PARSER_INCLUDES_NODE_H_

#include "Tree.h"

class Node: public Tree {
public:
	Node();
	virtual ~Node();

	void accept(TreeVisitor &visitor);
};

#endif /* PARSER_INCLUDES_NODE_H_ */
