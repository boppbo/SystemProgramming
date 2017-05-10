/*
 * Node.h
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#ifndef NODE_H_
#define NODE_H_

#include "Tree.h"

class Node : public Tree {
public:
	Node();
	virtual void accept(TreeVisitor &visitor) override;

};

#endif /* PARSER_INCLUDES_NODE_H_ */
