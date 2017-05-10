/*
 * Node.h
 *
 *  Created on: May 4, 2017
 *      Author: boris
 */

#ifndef PARSER_INCLUDES_NODE_H_
#define PARSER_INCLUDES_NODE_H_

#include "NodeTypes.h"

class Node{
public:
	Node();
	virtual ~Node();
	void accept(TreeVisitor &visitor);
	virtual NodeType getType();
	virtual void addChild(Node* node);
	virtual void setType(NodeType set);
private:
	NodeType type;
};


#include "ProgNode.h"

#include "DeclNode.h"
#include "DeclsNode.h"
#include "DeclsEpsNode.h"

#include "ArrayEpsNode.h"
#include "ArrayNode.h"

#include "StatementNode.h"
#include "StatementsNode.h"
#include "StatementsEpsNode.h"

#include "ExpNode.h"
#include "Exp2Node.h"
#include "IndexNode.h"
#include "IndexEpsNode.h"
#include "Op_ExpNode.h"
#include "Op_ExpEpsNode.h"
#include "OpNode.h"
#endif /* PARSER_INCLUDES_NODE_H_ */
