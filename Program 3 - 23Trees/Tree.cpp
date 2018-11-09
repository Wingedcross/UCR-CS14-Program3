#include <string>
#include <iostream>
#include <fstream>
#include "Tree.h"
#include "Node.h"

using namespace std;


Tree::Tree() {
	root = nullptr;
}


 // Splits a full leaf creating a 2-node.
//void Tree::splitRoot(const string & key, Node *node) {
//
//	cout << "Splitting root\n";
//
//	// key is smaller than the smallest item in node.
//	if (key < node->small) {
//		node->left = new Node(key, node);
//		node->right = new Node(node->large, node);
//		node->large = "";
//	}
//	// key is smaller than node's largest item, but bigger than the smallest.
//	else if (key < node->large) {
//		node->left = new Node(node->small, node);
//		node->right = new Node(node->large, node);
//		node->small = key;
//		node->large = "";
//	}
//	// key is bigger than both items in our node.
//	else {
//		node->left = new Node(node->small, node);
//		node->right = new Node(key, node);
//		node->small = node->large;
//		node->large = "";
//	}
//}


//Node * Tree::split(const string & key, Node *node) {
//
//	// For safety
//	if (!node->isFull()) {
//		return nullptr;
//	}
//
//	Node *parent = nullptr;
//	string smallValue{""}, middleValue{""}, largeValue{""};
//
//
//	#pragma region Find the order of key, small, and large
//	if (key < node->small) {
//		smallValue = key;
//		middleValue = node->small;
//		largeValue = node->large;
//	}
//	else if (key < node->large) {
//		smallValue = node->small;
//		middleValue = key;
//		largeValue = node->large;
//	}
//	else {
//		smallValue = node->small;
//		middleValue = node->large;
//		largeValue = key;
//	}
//	#pragma endregion
//
//	if (node == root) {
//		parent = new Node(middleValue);
//
//		splitRoot()
//	}
//	else {
//		parent = node->parent;
//	}
//
//	// split
//	if (node == parent->right) {
//		parent->middle = node;
//		parent->right = new Node(largeValue, parent);
//		node->small = smallValue;
//		node->large = "";
//	}
//	else if (node == parent->left) {
//		parent->middle = node;
//		parent->left = new Node(smallValue, parent);
//		node->small = node->large;
//		node->large = "";
//	}
//
//	// The parent is a 3-node. split 3-node
//	else {
//		// TODO
//	}
//
//	pushUp(middleValue, parent);
//
//}


void Tree::pushUp(const string & key, Node *node) {

	// Keep a reference to our node's parent.
	Node *parent = node->parent;

	// The parent is a 2-node.
	if (parent->large == "") {

		if (key < parent->small) {
			parent->large = parent->small;

			parent->small = key;

			parent->left = node->left;
			parent->left->parent = parent;		// Fix left node's parent.

			parent->middle = node->right;
			parent->middle->parent = parent;		// Fix middle node's parent.

			// No dangling nodes.
			delete node;
			node = nullptr;
		}
		else {
			parent->large = node->small;

			parent->middle = node->left;
			parent->middle->parent = parent;		// Fix middle node's parent.

			parent->right = node->right;
			parent->right->parent = parent;		// Fix right node's parent.

			// No dangling nodes.
			delete node;
			node = nullptr;
		}
	}
	else {
		// This is a three node 
	}
}


void Tree::split(const string & key, Node *node) {

	// new Node's constructor accepts the following (small key, parent, left child, right child)


	if (key < node->small) {
		node->left = new Node(key, node);
		node->right = new Node(node->large, node);
		node->large = "";
	}
	else {
		if (key < node->large) {
			node->left = new Node(node->small, node);
			node->right = new Node(node->large, node);
			node->large = "";
			node->small = key;
		}
		else {
			node->left = new Node(node->small, node);
			node->right = new Node(key, node);
			node->small = node->large;
			node->large = "";

			//cout << "Split was called. The split node contains " << node->small << " and " << node->large
			//	<< " and has a left child " << node->left->small << " and a right child " << node->right->small
			//	<< " and its parent is " << node->parent->small << endl;

		}
	}

}


// Public.
void Tree::insert(const string & key) {

	// If node doesn't exist, create one.
	if (root == nullptr) {
		root = new Node(key);
	}
	else {
		insert(key, root);
	}
}


// Private. Allows the tree to travel down the leaves.
void Tree::insert(const string & key, Node *node) {

	if (node->containsKey(key)) {
		return; // No duplicates allowed.
	}

	// Node is a leaf
	if (node->isLeaf()) {

		//cout << "Node containing " << node->small << " and " << node->large << " is a leaf.\n";

		// Node has only one data
		if (!node->isFull()) {

			//cout << "Node containing " << node->small << " and " << node->large << " has 1 data.\n";

			if (key > node->small) {
				node->large = key;

				//cout << "Inserted " << key << " into the node already containing small " << node->small << endl;
			}
			else {
				node->large = node->small;
				node->small = key;
			}
		}

		// Node has two items and must be split
		else {
			//cout << "Node containing " << node->small << " and " << node->large << " must be split.\n";

			split(key, node);

			if (node->parent != nullptr) {
				pushUp(key, node);
			}
		}

		return;
	}

	// Not a leaf. Continue traveral.
	// If our key is smaller than node's smallest value, go left.
	if (key < node->small) {
		insert(key, node->left);
	}

	// This is a 2-node.
	// Our key is bigger. If large is empty, Go right.
	// Insertion only occurs at a leaf node. We do NOT insert to large here.
	else if (node->large == "") {
		insert(key, node->right);
	}

	// This is a 3-node.
	else {
		if (key < node->large) {
			insert(key, node->middle);
		}
		else {
			insert(key, node->right);
		}
	}

}


// Private. Find the minimum node all the way to the left.
Node * Tree::minValue(Node* node) {
	Node* curr = node;

	/* loop down to find the leftmost leaf */
	while (curr->left != nullptr) {
		curr = curr->left;
	}
	return curr;
}

// find inorder successor fxn
Node * Tree::inorderSuccessorNode(Node *node, const string & whichData) {

	// If the right subtree of node is not null,
	// then successor lies in the right subtree.
	// Go to right subtree and return the node with
	// minimum key value in the right subtree.
	Node *successor = nullptr;

	// 2-node
	if (!node->isFull()) {
		if (node->right != nullptr) {
			successor = minValue(node->right);
		}
	}

	// 3-node
	else {
		// Successor of node.small
		if (whichData == "small") {
			successor = minValue(node->middle);
		}
		// Successor of node.large
		else {
			successor = minValue(node->right);
		}
	}

	return successor;
}


Node * Tree::getLeftSibling(Node *child) {
	Node *parent = child->parent;


	// middle?

	if (parent->left != nullptr) {
		return parent->left;
	}

}


Node * Tree::getRightSibling(Node *child) {
	Node *parent = child->parent;


	// middle?

	if (parent->right != nullptr) {
		return parent->right;
	}
}


void Tree::fix(Node *node) {

	if (node == root) {

		if (node->left != nullptr) {
			root = node->left;
		}
		else {
			root = node->right;
		}

		delete node;
		node = nullptr;

		cout << "Outputting new root's data\n";
		cout << root->small << " and " << root->large << endl;

		return;
	}

	Node *parent = node->parent;
	Node *leftSibling = getLeftSibling(node);
	Node *rightSibling = getRightSibling(node);

	// if (some sibling of n has two items) then...

	// else merge

	if (leftSibling != nullptr) {

		leftSibling->large = parent->small;
		parent->small = "";

	}
	else if (rightSibling != nullptr) {
		// donno
	}

	delete node;
	node = nullptr;

	if (parent->isEmpty()) {

		fix(parent);
	}

}


// Public.
void Tree::remove(const string & key) {
	// Make sure our tree isn't empty.
	if (root == nullptr) {
		return;
	}

	// find the desired node that contains key and store it.
	Node *node = search(key);

	// If a node containing our key was found, call remove on that key and node.
	if (node != nullptr) {
		remove(key, node);
	}

}


// TODO
// Private
void Tree::remove(const string & key, Node *& node) {

	if (node == root && node->isLeaf() && !node->isFull()) {

		delete root;
		root = nullptr;

		return;
	}

	// node is a leaf and has two data, remove the key from node.
	// We're done.
	if (node->isLeaf() && node->isFull()) {

		if (node->small == key) {
			node->small = node->large;
			node->large = "";
		}
		else {
			node->large = "";
		}

		return;
	}

	// A leaf 2-node.
	if (node->isLeaf() && !node->isFull()) {
		// redist or merge

		node->small = "";

		fix(node);

		return;
	}

	// is an internal 3-node. Find inorder successor.
	// Replace node's data with the successor's. 
	if (!node->isLeaf() && node->isFull()) {
		if (key == node->small) {
			Node *successor = inorderSuccessorNode(node, "small");
		}
		else {
			Node *successor = inorderSuccessorNode(node, "large");
		}
		
		//TODO: complete

	}

	// is an internal 2-node.
	else if (!node->isLeaf() && !node->isFull()) {

		// Find inorder successor. We got right once, then all the way 
		// to the left.
		Node *successor = inorderSuccessorNode(node, "small");

		// Keep a reference to the current node.small
		string newSuccessorSmall = node->small;

		// node.small is now its successor's small.
		// successor's small is the old node.small.
		node->small = successor->small;
		successor->small = newSuccessorSmall;

		// Recurse remove on the successor node.
		remove(newSuccessorSmall, successor);
	}
	

}

// Private
Node * Tree::search(const string & key) {

	// For safety.
	if (root == nullptr) {
		return nullptr;
	}

	if (root->containsKey(key)) {
		return root;
	}

	Node *foundNode = nullptr;
	Node *curr = root;

	// While current does not contain our key...
	while (!curr->containsKey(key)) {
		if (key < curr->small) {
			curr = curr->left;
		}
		else if (key < curr->large) {
			curr = curr->middle;
		}
		else if (key > curr->large) {
			curr = curr->right;
		}

		// If this contains our key, store this node.
		if (curr->containsKey(key)) {
			foundNode = curr;

			break;
		}
	}

	// Returns nullptr if key wasn't found.
	return foundNode;
}

// Public.
void Tree::inOrder() const {
	if (root != nullptr) {
		inOrder(root);
	}

	cout << endl;
}


// Private recursive.
void Tree::inOrder(Node *node) const {
	if (node != nullptr) {
		inOrder(node->left);
		
		if (node->small != "") {
			cout << node->small << ", ";
		}

		inOrder(node->middle);

		if (node->large != "") {
			cout << node->large << ", ";
		}

		inOrder(node->right);
	}
}


// Public.
void Tree::postOrder() const {
	if (root != nullptr) {
		postOrder(root);
	}

	cout << endl;
}


// Private recursive.
void Tree::postOrder(Node *node) const {
	if (node != nullptr) {
		postOrder(node->left);
		postOrder(node->middle);

		if (node->small != "") {
			cout << node->small << ", ";
		}

		postOrder(node->right);

		if (node->large != "") {
			cout << node->large << ", ";
		}
	}
}


// Public.
void Tree::preOrder() const {
	if (root != nullptr) {
		preOrder(root);
	}

	cout << endl;
}


// Private recursive.
void Tree::preOrder(Node *node) const {
	if (node != nullptr) {
		if (node->small != "") {
			cout << node->small << ", ";
		}

		preOrder(node->left);

		if (node->large != "") {
			cout << node->large << ", ";
		}

		preOrder(node->middle);
		preOrder(node->right);
	}
}


//void Tree::visualizeTree(const string &outputFilename) {
//	ofstream outFS(outputFilename.c_str());
//
//	if (!outFS.is_open()) {
//		cout << "Error opening " << outputFilename << endl;
//		return;
//	}
//
//	outFS << "digraph G {" << endl;
//	visualizeTree(outFS, root);
//	outFS << "}";
//	outFS.close();
//
//	string jpgFilename = outputFilename.substr(0, outputFilename.size() - 4) + ".png";
//	string command = "dot -Tpng " + outputFilename + " -o " + jpgFilename;
//
//	system(command.c_str());
//}
//
//void Tree::visualizeTree(ofstream &outFS, Node *node) {
//	if (node == nullptr) {
//		return;
//	}
//
//	outFS << node->key << "[ label= \"" << node->data << "\"];" << endl;
//
//	if (node->left != nullptr) {
//		outFS << node->key << " -> " << node->left->key << ";" << endl;
//	}
//
//	if (node->right != nullptr) {
//		outFS << node->key << " -> " << node->right->key << ";" << endl;
//	}
//
//	visualizeTree(outFS, node->left);
//	visualizeTree(outFS, node->right);
//}