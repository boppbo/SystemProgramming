#include "..//includes/SemanticCheck.h"
#include "iostream"

SemanticCheck::SemanticCheck() {

}

SemanticCheck::~SemanticCheck() {

}

void SemanticCheck::check(ParseTree* tree) {
	tree->getProg->accept(this);
}

void SemanticCheck::visit(Node* node) {
	switch (node->_type) {
		case nodeType::Prog: {
			node->_children[0]->accept(this);
			node->_children[1]->accept(this);
			node->_type = nodeType::NoType;
			break;
		}
		case nodeType::Decls: {
			node->_children[0]->accept(this);
			node->_children[2]->accept(this);
			node->_type = nodeType::NoType;
			break;
		}
		case nodeType::Decl: {
			node->_children[1]->accept(this);
			if (node->_children[2]->_type != nodeType::Identifier) {
				cerr << "Error in Line: " << ((Leaf*)node)->_token->_line << endl;
				cerr << "Error in Column: " << ((Leaf*)node)->_token->_column << endl;
				cerr << "Error : identifier already defined "<< endl;
				node->_children[2]->_type = nodeType::ERROR;
			}
			else if (node->_children[1]->_type == nodeType::ERROR) {
				node->_type = nodeType::ERROR;
			}
			else {
				node->_type = nodeType::NoType;
				if (node->_children[1]->_type == nodeType::arrayType) {
					node->_children[2]->_type = nodeType::intArrayType;
				}
				else {
					node->_children[2]->_type = nodeType::intType;
				}
			}
			break;
		}
		case nodeType::Array: {
			for each(Leaf* leaf in node->_children) {
				if (leaf->_type == nodeType::INTEGER) {
					if (leaf->_token->_integerValue > 0) {
						node->_type = nodeType::arrayType;
					}
					else {
						node->_type = nodeType::ERROR;
						cerr << "Error in Line: " << leaf->_token->_line << endl;
						cerr << "Error in Column: " << leaf->_token->_column << endl;
						cerr << "Error : no valid dimension" << endl;
					}
				}
			}
			break;
		}
		case nodeType::Statements: {
			node->_children[0]->accept(this);
			node->_children[2]->accept(this);
			node->_type = nodeType::NoType;
			break;
		}
		case nodeType::StatementIdent: {
			node->_children[3]->accept(this);
			node->_children[1]->accept(this);
			if (node->_children[0]->_type == nodeType::Identifier) {
				cerr << "Error in Line: " << ((Leaf*)node->_children[0])->_token->_line << endl;
				cerr << "Error in Column: " << ((Leaf*)node->_children[0])->_token->_column << endl;
				cerr << "Error : identifier not defined" << endl;
				node->_type = nodeType::ERROR;
			}
			else if (node->_children[3]->_type == nodeType::intType && ((node->_children[0]->_type == nodeType::intType && node->_children[1]->_type == nodeType::NoType) ||
				(node->_children[0]->_type == nodeType::intArrayType && node->_children[1]->_type == nodeType::arrayType))) {
				node->_type = nodeType::NoType;
			}
			else {
				cerr << "Error in Line: " << ((Leaf*)node->_children[0])->_token->_line << endl;
				cerr << "Error in Column: " << ((Leaf*)node->_children[0])->_token->_column << endl;
				cerr << "Error : incompatible types" << endl;
				node->_type = nodeType::ERROR;
			}
			break;
		}
		case nodeType::StatementWrite: {
			node->_children[2]->accept(this);
			node->_type = nodeType::NoType;
			break;
		}
		case nodeType::StatementRead: {
			node->_children[3]->accept(this);
			if (node->_children[2]->_type == nodeType::Identifier) {
				cerr << "Error in Line: " << ((Leaf*)node->_children[2])->_token->_line << endl;
				cerr << "Error in Column: " << ((Leaf*)node->_children[2])->_token->_column << endl;
				cerr << "Error : identifier not defined" << endl;
				node->_type = nodeType::ERROR;
			}
			else if (((node->_children[2]->_type == nodeType::intType) && (node->_children[3]->_type == nodeType::NoType)) ||
					((node->_children[2]->_type == nodeType::intArrayType) && (node->_children[3]->_type == nodeType::arrayType))) {
				node->_type = nodeType::NoType;
			} 
			else {
				cerr << "Error in Line: " << ((Leaf*)node->_children[2])->_token->_line << endl;
				cerr << "Error in Column: " << ((Leaf*)node->_children[2])->_token->_column << endl;
				cerr << "Error : incompatible types" << endl;
				node->_type = nodeType::ERROR;
			}
			break;
		}
		case nodeType::StatementBlock: {
			node->_children[1]->accept(this);
			node->_type = nodeType::NoType;
			break;
		}
		case nodeType::StatementIf: {
			node->_children[2]->accept(this);
			node->_children[4]->accept(this);
			node->_children[6]->accept(this);
			if (node->_children[2]->_type == nodeType::ERROR) {
				node->_type = nodeType::ERROR;
			}
			else {
				node->_type = nodeType::NoType;
			}
			break;
		}
		case nodeType::StatementWhile: {
			node->_children[2]->accept(this);
			node->_children[4]->accept(this);
			if (node->_children[2]->_type == nodeType::ERROR) {
				node->_type = nodeType::ERROR;
			}
			else {
				node->_type = nodeType::NoType;
			}
			break;
		}
		case nodeType::Index: {
			node->_children[1]->accept(this);
			if (node->_children[1]->_type == nodeType::ERROR) {
				node->_type = nodeType::ERROR;
			}
			else {
				node->_type = nodeType::arrayType;
			}
			break;
		}
		case nodeType::Exp: {
			node->_children[0]->accept(this);
			node->_children[1]->accept(this);
			if (node->_children[1]->_type == nodeType::NoType) {
				node->_type = nodeType::Exp2;
			}
			else if (node->_children[0]->_type != node->_children[1]->_type) {
				node->_type = nodeType::ERROR;
			}
			else {
				node->_type = nodeType::Exp2;
			}
			break;
		}
		case nodeType::Exp2: {
			node->_children[0]->accept(this);
			node->_type = nodeType::Exp;
			break;
		}
		case nodeType::Exp2Ident: {
			node->_children[1]->accept(this);
			if (node->_children[0]->_type == nodeType::Identifier) {
				cerr << "Error in Line: " << ((Leaf*)node->_children[0])->_token->_line << endl;
				cerr << "Error in Column: " << ((Leaf*)node->_children[0])->_token->_column << endl;
				cerr << "Error : identifier not defined" << endl;
				node->_type = nodeType::ERROR;
			}
			else if (node->_children[0]->_type == nodeType::intType && node->_children[1]->_type == nodeType::NoType) {
				node->_type = node->_children[0]->_type;
			}
			else if (node->_children[0]->_type == nodeType::intArrayType && node->_children[1]->_type == nodeType::arrayType) {
				node->_type = nodeType::intType;
			}
			else {
				cerr << "Error in Line: " << ((Leaf*)node->_children[0])->_token->_line << endl;
				cerr << "Error in Column: " << ((Leaf*)node->_children[0])->_token->_column << endl;
				cerr << "Error : no primitive Type" << endl;
				node->_type = nodeType::ERROR;
			}
			break;
		}
		case nodeType::Exp2Int: {
			node->_type = nodeType::intType;
			break;
		}
		case nodeType::Exp2Minus: {
			node->_type = nodeType::Exp2;
			break;
		}
		case nodeType::Exp2Neg: {
			if (node->_type != nodeType::intType) {
				node->_type = nodeType::ERROR;
			}
			else {
				node->_type = nodeType::intType;
			}
			break;
		}
		case nodeType::OpExp: {
			node->_children[0]->accept(this);
			node->_children[1]->accept(this);
			node->_type = nodeType::Exp;
			break;
		}
	}
}

void SemanticCheck::visit(Leaf* leaf) {
	
}

void 