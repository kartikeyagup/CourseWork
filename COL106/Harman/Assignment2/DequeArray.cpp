//#include "DequeArray.h"

#include "DequeADT.h"
#include <cstdlib>
#include <deque>
#include <iostream>



using namespace std;

template <class T>
class DequeArray : public DequeADT<T> {
	private:
		int start,end,size1;
		T *a;
		int elem;

	public:
		DequeArray();

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
DequeArray<T>::DequeArray()
{
	size1=10;
	start=0;
	end=0;
	a=new T[size1];
	elem=0;
}

template <class T>
void DequeArray<T>::push_front (const T& val)
{
		if(elem==size1)
		{

			T*temp=new T[2*size1];
			int count=0;
			for(int i=start;count<elem;i=((i+1)%size1),count++)
			{
				temp[count+1]=a[i];
			}
			end=size1;
			a=temp;
			size1*=2;
			start=0;
			a[start]=val;
			elem++;
		}

		else if(elem==0)
		{
			a[start]=val;
			elem++;
		}

		else
		{
			if(start==0)
			{
				start=size1-1;
				a[start]=val;
			}

			else
			{
				start--;
				a[start]=val;
			}

			elem++;
		}

}

template <class T>
void DequeArray<T>::push_back (const T& val)
{
	if(elem==size1)
	{

		T*temp=new T[2*size1];
		int count=0;
		for(int i=start;count<elem;i=((i+1)%size1),count++)
		{
			temp[count]=a[i];
		}

		start=0;
		end=size1-1;
		delete a;
		a=temp;
		size1*=2;
		end++;
		a[end]=val;
		elem++;
	}

	else if(elem==0)
	{
		a[end]=val;
		elem++;
	}

	else
	{
		end=((end+1)%size1);
		a[end]=val;
		elem++;
	}
}

template <class T>
void DequeArray<T>::clear()
{
	start=0;
	end=0;
	elem=0;
}

template <class T>
bool DequeArray<T>::empty()
{
     return (elem==0);
}

template <class T>
T DequeArray<T>::front()
{
	if(elem==0)
	{
		cout<<"The queue is empty !!!!"<<endl;
		exit(1);
	}

	else
	{
		return a[start];
	}
}

template <class T>
T DequeArray<T>::back()
{
	if(elem==0)
	{
		cout<<"The queue is empty !!!!"<<endl;
		exit(1);	
	}
	else
	{
		return a[end];
	}
}

template <class T>
T DequeArray<T>::at(int index)
{
	if (index>=elem)
	{	
		cout << "The queue is empty !!!!" <<endl;
		exit(1);
	}
	else 
		return a[(start+index)%size1];
	
/*	if(elem==0)
	{
		cout<<"The queue is empty !!!!"<<endl; 					// throw empty exception
	}
	else
	{
		if(start==end)
		{
				if(index==start)
				{
					return a[start];
				}
				else
				{
					// Throw not existing exception
				}
		}
		if(start<end)
		{
			if((index>=start)&&(index<=end))
			{
				return a[index];
			}
			else
			{
				// throw not existing exception
			}
		}
		if(start>end)
		{
			if((index>=start)||(index<=end))
			{
				return a[index];
			}
			else
			{
				// throw not existing exception
			}
		}
	}
*/
}


template <class T>
void DequeArray<T>::pop_front()
{
	if(elem==0)
	{
		cout <<"The Queue is empty !!!!" <<endl;
		exit(1);	
	}
	else
	{
		if(elem>1)
		{
			start=((start+1)%size1);
		}
		elem--;
	}
}

template <class T>
void DequeArray<T>::pop_back()
{
	if(elem==0)
	{
		cout <<"The Queue is empty !!!!" <<endl;
		exit(1);	
	}

	else
	{
		if(elem>1)
		{
			end--;
		}

		if(end<0)
		{
			end=size1-1;
		}
		elem--;
	}
}

template <class T>
int DequeArray<T>::size()
{
	return elem;
}
/*
template <typename T>
void DequeArray<T>::print()
{
	for(int i = 0; i < dq->size(); i++)
	{
		cout << dq->at(i) << endl;
	}
}*/
