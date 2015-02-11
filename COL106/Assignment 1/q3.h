#ifndef ququest_h
#define queuest_h

#include "q1.h"								//Included to include the properties and fucntions of the class Stack
#include <exception> 

template <typename Object>
class Queuest								//New class for Queue implemented using 2 stacks
{
public:
	Queuest(Object);						//Constructor for creating a new queue by stack with given input

	int size();								//Returns the size of the queue
	bool isEmpty();							//Returns 0 or 1 based on whether the queue is empty or not
	Object front();							//Returns the front element of the queue
	void enqueue(Object);					//Adds the given element to the queue
	Object dequeue();						//Removes the first element from the queue and returns it
	
	void display();

private:
	Stack<Object> *instack;					//Stack for incoming objects
	Stack<Object> *outstack;				//Stack for dequeue operation

	void moveStack();						//A fucntion to move elements from instack to outstack when the outstack becomes empty
};

class QueueStEmptyException:				//Exception for when the queue becomes empty
	public exception
{
	const char * wrong ;
	QueueStEmptyException(){};

public:
	QueueStEmptyException(const char* s)throw() : wrong(s){} 
	const char* what() const throw(){return wrong ;}
}
;


#endif