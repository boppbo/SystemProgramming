#ifndef PARSER_INCLUDES_NODES_NodeTypes_H_
#define PARSER_INCLUDES_NODES_NodeTypes_H_

#include "Node.h"

enum NodeType {
	NoType = 0,				
	IntegerType,				
	IntArrayType,			
	ArrayType,					
	ErrorType,					
	PlusType,				
	MinusType,				
	CollonType,				
	StarType,			
	GreaterType,			
	SmallerType,			
	EqualsType,			
	AssigneType,			
	Assigne2Type,				

	ENUM_END_MARKER 
};

#endif /* PARSER_INCLUDES_NODES_NodeTypes_H_ */
