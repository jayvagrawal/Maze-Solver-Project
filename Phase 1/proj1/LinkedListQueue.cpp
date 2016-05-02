//LinkedListQueue.cpp
#ifndef _LINKEDLISTQUEUE_CPP
#define _LINKEDLISTQUEUE_CPP

#include "LinkedListQueue.hpp"
#include <cstdlib> //for NULL
#include <cassert>
#include <iostream>
LinkedListQueue::LinkedListQueue() {
  // TODO:  Initialize any member variables as needed in the constructor.
	head = NULL;
	tail = NULL;
	size = 0;
}

void LinkedListQueue::add(MazeState *elem) {
	// TODO:  Implement this.
	if (elem != NULL) {
		if (head == NULL) {
			size++;
			head = new node;
			head->data = elem;
			head->next = NULL;
			tail = head;
		} else {
			size++;
			tail->next = new node;
			tail->next->data = elem;
			tail->next->next = NULL;
			tail = tail->next;
		}
	} else {
		cout << "NULL was passed as an argument to function add. Hence, nothing was added." << endl;
	}
}

MazeState *LinkedListQueue::remove() {
	// TODO:  Implement this.
	assert(!is_empty());
	size--;
	MazeState* ret = head->data;
	node* temp = head;
	head = head->next;
	delete temp;
	return ret;
}

bool LinkedListQueue::is_empty() {
	// TODO:  Implement this.
	return (head == NULL);
}

LinkedListQueue::~LinkedListQueue() {
	// TODO:  Implement the destructor.  Be sure to delete everything.
	while(!is_empty()) {
		remove();
	}	
}

#endif

