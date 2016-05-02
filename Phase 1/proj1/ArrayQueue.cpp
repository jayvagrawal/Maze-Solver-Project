#ifndef _ARRAYQUEUESOLN_CPP
#define _ARRAYQUEUESOLN_CPP

//ArrayQueueSoln.cpp

#include "ArrayQueue.hpp"
#include <cstdlib> //for NULL
#include <cassert>
#include <iostream>
using namespace std;

// 221 STUDENTS:
//
// This skeleton file (along with the .hpp) is
// here to help get you started, but you are
// free to change function signatures, etc.
// as long as ArrayQueue is some subtype
// of BagOfMazeStates
ArrayQueue::ArrayQueue() {
  // Constructor: initialize member variables
  //              and do any other initialization
  //              needed (if any)
  // TODO: implement constructor
	if (INIT_SIZE < 0) {
		capacity = 1;	
		array = new MazeState*[capacity];	
	} else {
		array = new MazeState*[INIT_SIZE];
		capacity = INIT_SIZE;
	}	
	head = 0;
	tail = 0;
}

void printArray(int head, int tail, int capacity) {
	
	cout << "Head: " << head << endl;
	cout << "Tail: " << tail << endl;
	cout << "Capacity: " << capacity << endl;	
	cout << "[";	
	while(head % capacity != tail){
		cout << head + ", ";
	head++;
	}
	cout << "]" << endl;
}

void ArrayQueue::add(MazeState *elem) {
  	// TODO: implement add method
	assert((head >= 0) && (tail >= 0));	
	if (elem != NULL) {
    		if ((tail + 1) % (capacity) == head) {
    			// queue is full
    			ensure_capacity(capacity+1); // ensure_capacity makes grows the array.
  		}
		// Your code goes here...
		array[tail] = elem;
		tail = (tail + 1) % capacity;
	} else {
		cout << "NULL was passed as an argument to function add. Hence, nothing was added." << endl;
	}
}

MazeState *ArrayQueue::remove() {
	// TODO: implement remove method
	assert(!is_empty());
	assert(head >= 0);
	MazeState *temp = array[head];
	head = (head + 1) % (capacity);
	return temp;
}


bool ArrayQueue::is_empty() {
	// TODO: implement is_empty method
	return (head==tail);
}

// TODO: implement ensure_capacity (but leave this to last.. just start with lots of capacity!)
void ArrayQueue::ensure_capacity(int n) {
	assert((head >= 0) && (tail >= 0));
	if (capacity < n) {
		// Make plenty of room.
		int target_capacity = (n > 2*capacity+1) ? n : (2*capacity+1);
		// TODO: Set the current array aside and make room for the new one.
		MazeState **oldarray = array;
		array = new MazeState*[target_capacity];

		// TODO: Copy each element of the old array over.
		// Update front carefully as you go!  Can you just use front++?
		int i = 0;
		while(((head + i) % capacity) != tail){
			array[i] = oldarray[(head + i) % capacity];
			i++; 
		}
		tail = i;
		head = 0;
		capacity = target_capacity;		
		delete [] oldarray;
		// TODO: Fix front and back and capacity so they correspond to the new array.
		// TODO: Delete the old array.
	}
}


ArrayQueue::~ArrayQueue()
{
  // TODO: implement the destructor
	delete [] array;
}


#endif
