// YOU DO NOT NEED TO MODIFY THIS INSTRUCTOR-PROVIDED FILE.
// Your code should work properly with an unmodified version of this file.

#include "PriorityQueueADT.h"
#include "comparator.h"
#include "Point.h"

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class PriorityQueueSTL : public PriorityQueueADT {
	private:
		std::priority_queue<Point, vector<Point>, mycomparison> * pq;

	public:
		PriorityQueueSTL(Point *destination);

		void push (const Point& val);
		bool empty();
		Point top();
		void pop();
		int size();

};

PriorityQueueSTL::PriorityQueueSTL(Point *destination)
{
	pq = new priority_queue<Point, std::vector<Point>, mycomparison>(mycomparison(destination));
}


void PriorityQueueSTL::push (const Point& val)
{
	pq->push(val);
}
	
bool PriorityQueueSTL::empty()
{
	return pq->empty();
}
	
Point PriorityQueueSTL::top()
{
	return pq->top();
}
	
void PriorityQueueSTL::pop()
{
	pq->pop();
}
	
int PriorityQueueSTL::size()
{
	return pq->size();
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
