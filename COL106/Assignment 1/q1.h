#ifndef Stack_h
#define Stack_h

#include <exception>

template <typename Object>
class Stack
{
	public:
		Stack(Object);			//Constructs a stack with the element given
		int size();				//returns size of the stack
		bool isEmpty();			//Returns 1 or 0 depending on whether the stack is empty or no
		Object top();			//Returns the top of the stack
		void push(Object);		//Pushes and object into the stack
		Object pop();			//removes and element from a stack and returns it
		void display();			//Displays the stack
		void displayreverse();	//Displays the stack in reverse order

	private:
		int len;				//Contains the index from which the stack becomes empty
		int biglen;				//Contains the length of the array used for the stack
		Object *arr;			//points to the stack array
};

class StackEmptyException:		//Exception for Empty Stack
	public exception
{
	const char * wrong ;
	StackEmptyException(){};

public:
	StackEmptyException(const char* s)throw() : wrong(s){} 
	const char* what() const throw(){return wrong ;}
}
;

#endif
