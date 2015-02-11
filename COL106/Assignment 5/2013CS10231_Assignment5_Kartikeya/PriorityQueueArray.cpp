#include "PriorityQueueADT.h"
#include "comparator.h"
#include "Point.h"

#include <iostream>

using namespace std;

class PriorityQueueArray : public PriorityQueueADT {
	private:
		int arrsize;
		int heaplen;
		Point* arr1;
		Point* dest;


	public:
		PriorityQueueArray(Point *destination);

		void push (const Point& val);
		bool empty();
		Point top();
		void pop();
		int size();
};


PriorityQueueArray::PriorityQueueArray(Point *destination)
{
	dest=destination;
	arr1=new Point[2];
	heaplen=1;
	arrsize=2;
}


void PriorityQueueArray::push (const Point& val)
{
	if (heaplen==arrsize)
	{
		arrsize=2*arrsize;
		Point* arr2=new Point[arrsize];
		for (int i=1; i<heaplen;i++)
		{
			arr2[i]=arr1[i];
		}
		arr2[heaplen]=val;
		arr1=arr2;
		heaplen++;
	}
	else
	{
		arr1[heaplen]=val;
		heaplen++;
	}
	bool done=false;
	int i=heaplen-1;
	while (i>1 && !done)
	{
		if (dest->distanceFrom(arr1[i])>=dest->distanceFrom(arr1[i/2]))
		{
			done=true;
		}	
		else
		{
			Point temp=arr1[i];
			arr1[i]=arr1[i/2];
			arr1[i/2]=temp;
			i=i/2;
		}
	}
}
	
bool PriorityQueueArray::empty()
{
	return (heaplen==1);
}
	
Point PriorityQueueArray::top()
{
	return arr1[1];
}
	
void PriorityQueueArray::pop()
{
	heaplen--;
	arr1[1]=arr1[heaplen];
	bool done=false;
	int i=1;
	while ((i<=(heaplen-1)/2) && !(done))
	{
		if (dest->distanceFrom(arr1[i])<dest->distanceFrom(arr1[2*i]))
		{
			if (dest->distanceFrom(arr1[i])<dest->distanceFrom(arr1[2*i+1]))
				done=true;
			else
			{
				Point temp=arr1[2*i+1];
				arr1[2*i+1]=arr1[i];
				arr1[i]=temp;
				i=2*i+1;
			}
		}
		else
		{
			if (dest->distanceFrom(arr1[2*i])<dest->distanceFrom(arr1[2*i+1]))
			{
				Point temp=arr1[2*i];
				arr1[2*i]=arr1[i];
				arr1[i]=temp;
				i=2*i;
			}
			else
			{
				Point temp=arr1[2*i+1];
				arr1[2*i+1]=arr1[i];
				arr1[i]=temp;
				i=2*i+1;	
			}
		}
	}
	if (!(done))
	{
		if (2*i==heaplen)
		{
			if (dest->distanceFrom(arr1[2*i])<=dest->distanceFrom(arr1[i]))
			{
				Point temp=arr1[2*i];
				arr1[2*i]=arr1[i];
				arr1[i]=temp;	
			}
		}
	}
}
	
int PriorityQueueArray::size()
{
	return heaplen-1;
	//TODO
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
