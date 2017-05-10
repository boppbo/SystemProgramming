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
	

public:
	ProgNode();
	virtual ~ProgNode();
	virtual ProgNode getProgNote();
	virtual void accept(class TreeVisitor &visitor) = 0;
};

#endif /* PARSER_INCLUDES_ProgNode_H_ */
