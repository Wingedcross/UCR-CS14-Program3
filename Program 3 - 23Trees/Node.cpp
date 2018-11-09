#include "Node.h"

Node::Node(const string & keyS, Node * parent,  Node * left, Node * right) {

	middle = nullptr;

	this->parent = parent;
	this->left = left;
	this->right = right;

	small = keyS;
	large = "";
}