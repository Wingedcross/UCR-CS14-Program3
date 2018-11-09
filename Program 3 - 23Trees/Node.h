#pragma once
#ifndef __NODE_H
#define __NODE_H

#include <string>

using namespace std;

class Node {

	friend class Tree;

private:
	Node(const string &, Node * = nullptr, Node * left = nullptr, Node * right = nullptr);

	string small;
	string large;

	Node *left;
	Node *middle;
	Node *right;
	Node *parent;

	// Returns true if either small or large equal the key argument.
	bool containsKey(const string &key) { return (small == key || large == key) ? true : false; };

	// True if both small and large have chars in them.
	bool isFull() { return (small != "" && large != "") ? true : false; }

	// True if this node has no children.
	bool isLeaf() { return (left == nullptr && right == nullptr && middle == nullptr) ? true : false; }

	// True is has no data.
	bool isEmpty() { return (small == "" && large == "") ? true : false; }

	// NO Node * or string variables.

};

#endif