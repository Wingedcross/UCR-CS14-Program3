#pragma once
#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
	Node * root;

public:
	Tree();
	//~Tree();

	void insert(const string &);
	
	void preOrder() const;
	void inOrder() const;
	void postOrder() const;
	void remove(const string &);

	//bool search(const string &) const;

private:

	void insert(const string &, Node *);
	Node * minValue(Node *);
	Node * search(const string &);
	void split(const string &, Node *);
	void preOrder(Node *) const;
	// void visualizeTree(const string & outputFilename);
	// void visualizeTree(ofstream & outFS, Node * leaf);
	void inOrder(Node *) const;
	void postOrder(Node *) const;
	Node * inorderSuccessorNode(Node *, const string &);
	Node * getLeftSibling(Node *);
	Node * getRightSibling(Node *);
	void fix(Node *);
	void remove(const string &, Node *&);
	void pushUp(const string & key, Node *);
};

#endif