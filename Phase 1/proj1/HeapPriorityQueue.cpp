//HeapPriorityQueue.cpp
#ifndef _HEAPPRIORITYQUEUE_CPP
#define _HEAPPRIORITYQUEUE_CPP

#include "HeapPriorityQueue.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>
#include <unistd.h>

HeapPriorityQueue::HeapPriorityQueue() {
  // Empty... nothing needs to be done.
}

HeapPriorityQueue::~HeapPriorityQueue() {
  // no clean-up to do, since the heap is not dynamically allocated
}


// THE FOLLOWING COMMENTED OUT CODE ARE ADD AND REMOVE WITHOUT HELPER FUNCTIONS
/*void HeapPriorityQueue::add(MazeState *elem) {
	// TODO:  Implement this!
	if (elem != NULL) {
		cout << "ADDING ELEMENT WITH BADNESS:" << elem->getBadness() << endl;
		print();
		heap.push_back(elem);
		int hole = heap.size() - 1;
		MazeState *parentHole = heap[parent(hole)];
		while (hole > 0 && (elem->getBadness() < parentHole->getBadness())) {
			heap[hole] = parentHole;
			heap[parent(hole)] = elem;
			hole = parent(hole);
			parentHole = heap[parent(hole)];
		}
		cout << "FINISHED ELEMENT WITH BADNESS:" << elem->getBadness() << endl;
		print();
	}
}

MazeState * HeapPriorityQueue::remove() {
	// TODO:  Implement this!
	cout << "DELETING ELEMENT WITH BADNESS:" << elem->getBadness() << endl;
	print();
	assert(!is_empty());
	if (heap.size() < 1)
		return (MazeState *)NULL;	
	int hole = 0;
	MazeState* ret = heap[hole];
	int size = heap.size() - 1;
	MazeState *last = heap[size];
	int target = 0;
	while (first_child(hole) < size) {
		int left = first_child(hole);
		int right = left + 1;
		if (right < size && (heap[right]->getBadness() < heap[left]->getBadness())) {
			target = right;
		} else { 
			target = left;
		}
		if (heap[target]->getBadness() < last->getBadness()) {
			heap[hole] = heap[target];
			hole = target;
		} else
			break;
	}
	heap[hole] = last;
	heap.erase(heap.begin() + heap.size() - 1);
	cout << "FINISHED DELETING ELEMENT WITH BADNESS:" << elem->getBadness() << endl;
	print();	
	return ret;
}*/

int HeapPriorityQueue::percolateUp(int hole, MazeState* val){
  	while (hole > 0 && val->getBadness() < heap[parent(hole)]->getBadness()){
    		heap[hole] = heap[parent(hole)];
    		heap[parent(hole)] = val;
    		hole = parent(hole);
  	}
  	return hole;
}

void HeapPriorityQueue::add(MazeState *elem) {
  	// TODO:  Implement this!
	if (elem != NULL) {
		//cout << "ADDING ELEMENT WITH BADNESS:" << elem->getBadness() << endl;
		//print();
	  	heap.push_back(elem);
	  	int hole = (int)heap.size() - 1;
	  	int newPos = percolateUp(hole, elem);
		assert(newPos >= 0);
	  	heap[newPos] = elem;
		//cout << "FINISHED ADDING ELEMENT WITH BADNESS:" << elem->getBadness() << endl;
		//print();
	}
	else {
		cout << "NULL was passed as an argument to function add. Hence, nothing was added." << endl;
	}
}

int HeapPriorityQueue::percolateDown(int hole, MazeState* val) {
	int target;
  	while (first_child(hole) < ((int)heap.size() - 1)){
    		int left = first_child(hole);
    		int right = left + 1;
    		if (right < ((int)heap.size() - 1) && (heap[right]->getBadness() < heap[left]->getBadness())) {
      			target = right;
    		} else {
      			target = left;
    		} if (heap[target]->getBadness() < val->getBadness()) {
      			heap[hole] = heap[target];
      			hole = target;
    		} else break;
  	}
	return hole;
}


MazeState * HeapPriorityQueue::remove() {
	// TODO:  Implement this!
  	assert(!is_empty());
	//cout << "DELETING ELEMENT WITH BADNESS:" << endl;
	//print();
  	MazeState* returnVal = heap[0];
  	int hole = 0;
	int newPos = percolateDown(hole, heap[(int)heap.size() - 1]);
	assert(newPos >= 0);
  	heap[newPos] = heap[heap.size() - 1];
  	heap.pop_back();
	//cout << "FINISHED DELETING ELEMENT WITH BADNESS:" << endl;
	//print();
  	return returnVal;
}
  
bool HeapPriorityQueue::is_empty() {
  	// TODO:  Implement this!
	return (heap.size() == 0);
}

// You might find these helper functions helpful...
int HeapPriorityQueue::parent(int index) {
  return (index - 1) / 2;
}

int HeapPriorityQueue::first_child(int index) {
  return 2 * index + 1;
}

bool HeapPriorityQueue::is_root(int index) {
  return index == 0;
}

bool HeapPriorityQueue::is_leaf(int index) {
  return num_children(index) == 0;
}

int HeapPriorityQueue::num_children(int index) {
  int fchild = first_child(index);
  return max(0, min(2, (int)heap.size() - fchild));
}

// The following print function prints the heap with each MazeState*'s associated Badness Level.
void HeapPriorityQueue::print(){
	cout<< "[";
	for(int i = 0; i < (int)heap.size(); i++){
		cout << heap[i]->getBadness() << ", ";	
	}
	cout << "]" << endl;
	usleep(1000000);
}

#endif
