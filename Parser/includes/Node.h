/*
 * Node.h
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#ifndef NODE_H_
#define NODE_H_

#include "Tree.h"
#include "../../Common/includes/Collections/deque.h"

class Node : public Tree {
public:
	Node(NType nodeType);
	virtual void accept(TreeVisitor *visitor) override;

	virtual void addChild(Tree* child);
	virtual Tree* getChild(unsigned int index) const;
	virtual unsigned int getChildrenSize() const;

	virtual bool isEpsilon() const;
private:
	deque<Tree> _children;
};

#endif /* PARSER_INCLUDES_NODE_H_ */
