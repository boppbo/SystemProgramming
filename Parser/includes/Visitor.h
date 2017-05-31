#ifndef VISITOR_H
#define VISITOR_H

class Node;
class Leaf;

class Visitor {
	public:
		virtual void visit(Node* node) = 0;
		virtual void visit(Leaf* leaf) = 0;
};

#endif /* VISITOR_H */
