/*
* ProgNode.h
*
*  Created on: May 10, 2017
*      Author: Maksim Sunjajkin
*/


#ifndef PARSER_INCLUDES_ProgNode_H_
#define PARSER_INCLUDES_ProgNode_H_

#include "Nodes\Node.h"

class ProgNode : public Node {
	
	DeclsNode* decls;
	StatementsNode* statements;

public:
	ProgNode() {
		this->decls = 0;
		this->statements = 0;
	}
	virtual ~ProgNode();
	virtual void addChild(DeclsNode* newDecls) {
		this->decls = newDecls;
	}
	virtual void addChild(StatementsNode* newStatements) {
		this->statements = newStatements;
	}
	virtual void accept(class TreeVisitor &visitor);
};

#endif /* PARSER_INCLUDES_ProgNode_H_ */
