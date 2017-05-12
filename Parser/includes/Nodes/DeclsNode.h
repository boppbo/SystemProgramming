/*
* ProgNode.h
*
*  Created on: May 10, 2017
*      Author: Maksim Sunjajkin
*/


#ifndef PARSER_INCLUDES_DeclsNode_H_
#define PARSER_INCLUDES_DeclsNode_H_

#include "Node.h"

class DeclsNode : public Node {

	DeclNode* decl;
	DeclsNode* nextDecls;

public:
	DeclsNode() {
		decl = 0;
		nextDecls = 0;
	}
	virtual ~DeclsNode() {
		delete decl;
		delete nextDecls;
	}
	virtual void addChild(DeclsNode* newDecls) {
		nextDecls = newDecls;
	}
	virtual void addChild(DeclNode* newDecl) {
		decl = newDecl;
	}
	virtual void accept(class TreeVisitor &visitor) = 0;
};

#endif /* PARSER_INCLUDES_DeclsNode_H_ */