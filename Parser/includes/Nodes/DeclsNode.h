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
		this->decl = 0;
		this->nextDecls = 0;
	}
	virtual ~DeclsNode() {
		delete this->decl;
		delete this->nextDecls;
	}
	virtual void addChild(DeclsNode* newDecls) {
		this->nextDecls = newDecls;
	}
	virtual void addChild(DeclNode* newDecl) {
		this->decl = newDecl;
	}
	virtual void accept(class TreeVisitor &visitor);
};

#endif /* PARSER_INCLUDES_DeclsNode_H_ */