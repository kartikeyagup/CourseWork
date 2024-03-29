//#include "DequeArray.h"

#include "DequeADT.h"

#include <deque>
#include <iostream>
#include <cstdlib>

using namespace std;

template <class T>
class DequeArray : public DequeADT<T> {
	private:
		int s;
		int arrsize;
		int front1;
		int rear;
		T* arr;

	public:
		DequeArray();
		void push_front (const T& val);//it pushes an element to the front of deque
		void push_back (const T& val); //it pushes an element to the front of deque	
		void clear();		       //clears the whole deque
		bool empty();		       //to check if the deque is empty
		T front();		       //returns the front element of deque
		T back();		       //returns the last element of deque
		T at(int index);	       //return the element at a given index in the deque
		void pop_front();	       //removes the front element of the deque
		void pop_back();	       //returns the size of the deque
		int size();
		//void print();

};

template <class T>
DequeArray<T>::DequeArray()
{
	s = 0;
	arrsize = 10;
	arr = new T[arrsize];
	front1 = -1;
	rear = -1;
}

template <class T>
void DequeArray<T>::push_front (const T& val)
{
	if (s == 0)
	{
		
		front1 = 0;
		rear = 0 ;
		arr[0] = val;
		s += 1;
	}
	else if ((s > 0) && (s < arrsize) && (front1==0))
	{
		arr[arrsize - 1] = val;
		front1 = arrsize - 1;
		s+=1;
	}
	else if ((s > 0) && (s < arrsize))
	{
		front1 = front1 - 1;
		arr[front1] = val;
		s+=1;
	}
	else
	{
		T *q = new T[arrsize+1];
		
		if (front1 <= rear)
		{
			q[0] = val;
			int z = 1;
			for (int i = front1; i <= rear; i++)
			{
				q[z] = arr[i];
				z++;
			}
			arr = new T[2 * arrsize];
			for (int j = 0; j <= arrsize; j++)
			{
				arr[j] = q[j];
			}
		}
		else
		{
			int a = 1;
			q[0] = val;
			for (int i = front1; i < arrsize; i++)
			{
				q[a] = arr[i];
				a++;
			}
			for (int j = 0; j <= rear; j++)
			{
				q[a] = arr[j];
				a++;
			}
			arr = new T[2 * arrsize];
			for (int z = 0; z <= arrsize; z++)
			{
				arr[z]=q[z];
			}
		}
		s += 1;
		rear = arrsize;
		front1 = 0;
		arrsize *= 2;
		
	}
}

template <class T>
void DequeArray<T>::push_back (const T& val)
{
	if (s == 0)
	{
		front1 = 0;
		rear = 0;
		arr[0] = val;
		s++;
	}
	else if ((rear == arrsize - 1) && (s < arrsize))
	{
		rear = 0;
		arr[0] = val;
		s++;
	}
	else if (s < arrsize)
	{
		rear++;
		arr[rear] = val;
		s++;
	}
	else 
	{
		T *w = new T[arrsize];
		if (front1 <= rear)
		{
			for (int i = front1; i <= rear; i++)
			{
				w[i] = arr[i];
			}
			arr = new T[2 * arrsize];
			for (int i = 0; i < arrsize; i++)
			{
				arr[i] = w[i];
			}
		}
		else
		{
			int x = 0;
			for (int p = front1; p < arrsize; p++)
			{
				w[x] = arr[p];
				x++;
			}
			for (int j = 0; j <= rear; j++)
			{
				w[x] = arr[j];
				x += 1;
			}
			arr = new T[2 * arrsize];
			for (int p = 0; p < arrsize; p++)
			{
				arr[p] = w[p];
			}
		}
		arr[s] = val;
		rear = arrsize;
		front1 = 0;
		s += 1;
		arrsize *= 2;

	}
}

template <class T>
void DequeArray<T>::clear()
{
	arrsize = 10;
	arr = new T[arrsize];
	front1 = -1;
	rear = -1;
	s = 0;
}
	
template <class T>
bool DequeArray<T>::empty()
{
	return (s == 0);
}
	
template <class T>
T DequeArray<T>::front()
{
	if (s==0) 
	{
		cout <<"Deque is empty, cannot give front\n";
		exit(1);
	}
	else
	{
		return arr[front1];
	}
}
	
template <class T>
T DequeArray<T>::back()
{
	if (s==0)
	{
		cout <<"Deque is empty, cannot give back\n";
		exit(1);
	}
	else
	{
		return arr[rear];
	}
}
	
template <class T>
T DequeArray<T>::at(int index)
{
	if (index >= s)
	{
		cout <<"index out of bounds\n";
		exit(1);
	}
	else
	{
		if ((front1 + index) < arrsize)
			return arr[front1 + index];
		else	
			return arr[front1 + index - arrsize];
	}
}
	
template <class T>
void DequeArray<T>::pop_front()
{
	if (s ==0) 
	{
		cout <<"Deque is empty, cannot pop front\n";
		exit(1);
	}
	else
	{
		if (s == 1)
		{
			front1 = -1;
			rear = -1;
			s -= 1;
		}
		else if (front1 == arrsize - 1)
		{
			front1 = 0;
			s -= 1;
		}
		else
		{
			front1 += 1;
			s -= 1;
		}
	}
}
	
template <class T>
void DequeArray<T>::pop_back()
{
	if (s==0) 
	{
		cout <<"Deque is empty, cannot pop back\n";
		exit(1);
	}
	else
	{
		if (s == 1)
		{
			front1 = -1;
			rear = -1;
			s -= 1;
		}
		else if (rear == 0)
		{
			rear = arrsize - 1;
			s -= 1;
		}
		else
		{
			rear -= 1;
			s -= 1;
		}
	}
}
	
template <class T>
int DequeArray<T>::size()
{
	return s;
}


//template <typename T>
//void DequeArray<T>::print()
//{
//	for(int i = 0; i < dq->size(); i++)
//	{
//		cout << dq->at(i) << endl;
//	}
//}
