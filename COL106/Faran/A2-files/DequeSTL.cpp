// YOU DO NOT NEED TO MODIFY THIS INSTRUCTOR-PROVIDED FILE.
// Your code should work properly with an unmodified version of this file.

//#include "DequeSTL.h"

#include "DequeADT.h"

#include <deque>
#include <iostream>

using namespace std;

template <class T>
class DequeSTL : public DequeADT<T> {
	private:
		std::deque<T> * dq;

	public:
		DequeSTL();

		void push_front (const T& val);
		void push_back (const T& val);	
		void clear();
		bool empty();	
		T front();	
		T back();	
		T at(int index);	
		void pop_front();	
		void pop_back();	
		int size();
		//void print();

};

template <class T>
DequeSTL<T>::DequeSTL()
{
	dq = new std::deque<T>();
}

template <class T>
void DequeSTL<T>::push_front (const T& val)
{
	dq->push_front(val);
}

template <class T>
void DequeSTL<T>::push_back (const T& val)
{
	dq->push_back(val);
}

template <class T>
void DequeSTL<T>::clear()
{
	dq->clear();
}
	
template <class T>
bool DequeSTL<T>::empty()
{
	return dq->empty();
}
	
template <class T>
T DequeSTL<T>::front()
{
	return dq->front();
}
	
template <class T>
T DequeSTL<T>::back()
{
	return dq->back();
}
	
template <class T>
T DequeSTL<T>::at(int index)
{
	return dq->at(index);
}
	
template <class T>
void DequeSTL<T>::pop_front()
{
	dq->pop_front();
}
	
template <class T>
void DequeSTL<T>::pop_back()
{
	dq->pop_back();
}
	
template <class T>
int DequeSTL<T>::size()
{
	return dq->size();
}

/*
template <typename T>
void DequeSTL<T>::print()
{
	for(int i = 0; i < dq->size(); i++)
	{
		cout << dq->at(i) << endl;
	}
}*/
