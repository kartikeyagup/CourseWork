#ifndef queue_h
#define queue_h

#include <exception>

template <typename Object>
class Node							//The class node.
{
public:
	Node(Object);					//Constructor for the node
	Object getData();				//Returns the data stored in the node

	Node* next;						//Pointer to another node
	Object data;					//Data of type object stored in a node
};

template <typename Object>
class Queue
{
public:
	Queue(Object);					//Constructor for a queue having given element
	
	int size();						//Returns the size of the Queue
	bool isEmpty();					//Returns 1 or 0 depending on wheather the queue is empty or not
	Object front();					//Returns the front element of the Queue
	void enqueue(Object);			//Adds an object to the queue
	Object dequeue();				//Removes element from the queue and returns it

	void display();					//Displays the queue

private:
	Node<Object> *ending;			//A node pointer which points to the end of the circular list
	int num;						//Number of elements in the queue
}
;

class QueueEmptyException:			//Exception if the queue is empty
	public exception
{
	const char * wrong ;
	QueueEmptyException(){};

public:
	QueueEmptyException(const char* s)throw() : wrong(s){} 
	const char* what() const throw(){return wrong ;}
}
;

#endif


