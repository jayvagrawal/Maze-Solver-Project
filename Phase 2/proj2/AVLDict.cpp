#ifndef _AVLDICT_CPP
#define _AVLDICT_CPP

//AVLDict.cpp
#include "AVLDict.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>
#include <unistd.h>

// An implementation of a dictionary ADT as an AVL tree
//
AVLDict::AVLDict() {
  root = NULL;

  // Initialize array of counters for depth statistics
  depth_stats = new int[MAX_STATS]();
}

void AVLDict::destructor_helper(node * x) {
  if (x == NULL) return; // Nothing to destroy.
  destructor_helper(x->left);
  destructor_helper(x->right);
  delete x->key;
  delete x;
}

AVLDict::~AVLDict() {
  // Clean up the tree.
  // This is most easily done recursively.
  destructor_helper(root);

  // It's not good style to put this into a destructor,
  // but it's convenient for this assignment...
  cout << "Depth Statistics for find():\n";
  for (int i=0; i<MAX_STATS-1; i++)
    cout << i << ": " << depth_stats[i] << endl;
  cout << "More: " << depth_stats[MAX_STATS-1] << endl;
  delete [] depth_stats;
}

// 221 Students:  DO NOT CHANGE THIS FUNCTION
// You need to call this function from your find (or from a helper function).
// Pass in the depth in the tree that the find stopped at.
// E.g., you'd call record_stats(0) if the entire dictionary were
// a NULL tree and you did a find on it.
// You'd call record_stats(1) if the entire dictionary were a single
// node, and you did a find on that dictionary, successful or not.
// (Another way to understand this is the number of nodes on the chain
// from the root to the node where the find succeeded,
// or to a leaf if the find didn't succeed.)
void AVLDict::record_stats(int depth) {
  if (depth > MAX_STATS-1) depth = MAX_STATS-1;
  depth_stats[depth]++;
}


bool AVLDict::find_helper(string keyID, node *root, MazeState *&pred, int depth) {
	if (root == NULL) {
		record_stats(depth);
		return false;
	} else if(keyID == root->key->getUniqId()) {
		record_stats(depth + 1);	
		pred = root->data;
		return true;
	} else if(keyID > root->key->getUniqId()) {
		return find_helper(keyID, root->right, pred, depth + 1);
	} else {
		return find_helper(keyID, root->left, pred, depth + 1);
	}
}

bool AVLDict::find(MazeState *key, MazeState *&pred) {
  // TODO:  Write this function!
	assert (key != NULL);
	return find_helper(key->getUniqId(), root, pred, 0);
}

bool AVLDict::update_height( node * x ) {
  // TODO:  Write this function!	
	if (x == NULL)
		return false;

	int m = std::max(height(x->left), height(x->right)) + 1;

	if (x->height != m) {
		x->height = m;
		return true;
	}

	return false;
}

void AVLDict::rotate_left( node *& a ) {
  // "rotates" the subtree rooted at a to the left (counter-clockwise)

// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
std::cout << "Rotate Left: " << a->getUniqId() << std::endl;
#endif
// End of "DO NOT CHANGE" Block

  // TODO:  Write this function!
	assert(a != NULL);
	assert(a->right != NULL);
	node* temp = a->right;
	a->right = temp->left;
	temp->left = a;
	update_height(a);
	update_height(temp);
	a = temp;
}

void AVLDict::rotate_right( node *& b ) {
  // "rotates" the subtree rooted at b to the right (clockwise)

// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
cout << "Rotate Right: " << b->getUniqId() << endl;
#endif
// End of "DO NOT CHANGE" Block

  // TODO:  Write this function!
	assert(b != NULL);
	assert(b->left != NULL);
	node* temp = b->left;
	b->left = temp->right;
  	temp->right = b;
  	update_height(b);
  	update_height(temp);
  	b = temp;
}

void AVLDict::double_rotate_left(node *&a) {
	assert(a != NULL);
	rotate_right(a->right);
  	rotate_left(a);
}

void AVLDict::double_rotate_right(node *&a) {
	assert(a != NULL);
  	rotate_left(a->left);
  	rotate_right(a);
}

void AVLDict::balance(node *&x) {
	assert (x != NULL);
	int leftHeight = height(x->left);
	int rightHeight = height(x->right);
	int diff = leftHeight - rightHeight;
	
	if (diff > 1) {
		if (height(x->left->left) - height(x->left->right) < 0) {
			double_rotate_right(x);
		} else {
			rotate_right(x);
		}
	}

	if (diff < -1) {
		if (height(x->right->left) - height(x->right->right) > 0) {
			double_rotate_left(x);
		} else {
			rotate_left(x);
		}
	} 
	
}

AVLDict::node* AVLDict::createNode(MazeState* key, MazeState* pred) {
	node* result = new node;
	result->key = key;
	result->data = pred;
	result->height = 0;
	result->left = NULL;
	result->right = NULL;
	return result;
}

void AVLDict::insert(MazeState* key, MazeState* pred, node *&root) {
	if (root == NULL) {
		root = createNode(key, pred);
		return;
	} else if (key->getUniqId() > root->key->getUniqId()) {
		insert(key, pred, root->right);
	} else if (key->getUniqId() < root->key->getUniqId()) {
		insert(key, pred, root->left);
	} if (update_height(root)) {
		balance(root);
	}
}

// You may assume that no duplicate MazeState is ever added.
void AVLDict::add(MazeState *key, MazeState *pred) {
  // TODO:  Write this function!
	assert(key != NULL);
	insert(key, pred, root);
}

#endif 
