#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>

#include "Point.h"
#include "Maze.h"
#include "PriorityQueueADT.h"
#include "PriorityQueueSTL.cpp"
#include "PriorityQueueArray.cpp"

using namespace std;


int main(int argc, char **argv)
{
	Point * destination = new Point(0,0);
	PriorityQueueADT * pq;
	if(atoi(argv[1]) == 0)
		pq = new PriorityQueueSTL(destination);
	else
		pq = new PriorityQueueArray(destination);

	printf("\n\npushing 3 elements : ");
	pq->push(Point(2,2));
	pq->push(Point(3,4));
	pq->push(Point(4,3));
	printf("\n\nsize = %d", pq->size());
	printf("\n\ntop() = "); pq->top().print();
	printf("\n\npushing 7 elements : ");
	pq->push(Point(5,6));
	pq->push(Point(1,2));
	pq->push(Point(8,3));
	pq->push(Point(4,5));
	pq->push(Point(6,7));
	pq->push(Point(3,1));
	pq->push(Point(3,2));
	printf("\n\nsize = %d", pq->size());
	printf("\n\nisEmpty() = %d", pq->empty());
	printf("\n\ntop() = "); pq->top().print();
	printf("\n\n----------------------------\n\n");
	printf("popping all elements :\n\n");
	while(!pq->empty())
	{
		pq->top().print();
		pq->pop();
	}
	printf("\n\nsize = %d", pq->size());
	printf("\n\nisEmpty() = %d\n\n", pq->empty());

	return 0;
}


