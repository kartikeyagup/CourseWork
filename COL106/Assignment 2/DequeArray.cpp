//#include "DequeArray.h"

#include "DequeADT.h"
//#include "misc.cpp"

#include <deque>
#include <iostream>
#include <cstdlib>

using namespace std;

template <class T>
class DequeArray : public DequeADT<T> {
	private:
		T *arr;
		int bigsize;
		int lenelem;
		int firstpost;

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
	bigsize=10;
	arr = new T[10];
	firstpost=1;
	lenelem=0;
}

template <class T>
void DequeArray<T>::push_front (const T& val)
{
	if (lenelem<bigsize)
	{
		firstpost=(firstpost + bigsize -1)%bigsize;
		arr[firstpost]=val;
		lenelem+=1;
	}
	else
	{
		T *big1= new T[2*bigsize];
		for (int i=0; i<bigsize; i++)
		{
			big1[i+1]=this->at(i);
		}
		firstpost=0;
		big1[0]=val;
		lenelem += 1;
		bigsize *= 2;
		arr=big1;
	}
}


template <class T>
void DequeArray<T>::push_back (const T& val)
{
	if (lenelem<bigsize)
	{
		arr[(firstpost+lenelem)%bigsize]=val;
		lenelem+=1;
	}
	else
	{
		T *big1= new T[2*bigsize];
		for (int i=0; i<bigsize; i++)
		{
				big1[i]=this->at(i);
		}
		firstpost=0;
		big1[bigsize]=val;
		lenelem += 1;
		bigsize *= 2;
		arr=big1;
	}
}

template <class T>
void DequeArray<T>::clear()
{
	lenelem=0;
	firstpost=1;
}


template <class T>
bool DequeArray<T>::empty()
{
	return (lenelem==0);
}

template <class T>
T DequeArray<T>::front()
{
	if (lenelem>0)
		return arr[firstpost];
	else
	{
		cout <<"Deque became empty\n";
		exit(1);
	}
}

template <class T>
T DequeArray<T>::back()
{
	if (lenelem>0)
		return arr[(firstpost + lenelem -1)%bigsize];
	else
	{
		cout <<"Deque became empty\n";
		exit(1);
	}
}

template <class T>
T DequeArray<T>::at(int index)
{
	if (index<lenelem)
		return arr[(firstpost+index)%bigsize];
	else
	{
		cout <<"Index not in bounds\n";
		exit(1);
	}
}


template <class T>
void DequeArray<T>::pop_front()
{
	if (lenelem>0)
	{
		firstpost=(firstpost+1)%bigsize;
		lenelem -=1;
	}
	else
	{
		cout <<"Deque is empty\n";
		exit(1);
	}
}

template <class T>
void DequeArray<T>::pop_back()
{
	if (lenelem>0)
		lenelem -=1;
    	else
	{
		cout <<"Deque is empty\n";
		exit(1); 
	}
}

template <class T>
int DequeArray<T>::size()
{
	return lenelem;
}


//template <typename T>
//void DequeArray<T>::print()
//{
	//for(int i = 0; i < this->size(); i++)
	//{
		////cout << this->at(i) << endl;
		//cout <<this->at(i) <<"\t";
	//}
	//cout <<"\n";
//}

//int main()
//{
	//DequeArray<int> *xyz1=new DequeArray<int>();
    	//xyz1->pop_back();
    	//xyz1->push_front(45);
	//xyz1->push_back(100);
	//xyz1->push_back(101);
	//xyz1->push_back(102);
	//xyz1->push_back(103);
	//xyz1->push_back(104);
	//xyz1->push_back(105);
	//xyz1->push_back(106);
	//xyz1->push_back(107);
	//xyz1->push_front(36);
	//xyz1->push_front(37);
	//xyz1->push_front(38);
	//xyz1->push_front(39);
	//xyz1->push_front(40);
	//xyz1->push_front(41);
	////xyz1->print();
	//cout <<xyz1->back();
	//xyz1->pop_back();
	////xyz1->print();
	//xyz1->pop_front();
	////xyz1->print();
	////xyz1->clear();
	//cout << "size of xyz1 :" <<xyz1->size() << "\n";
	//int k=0;
	//cin >> k;
	//return 0;
//}
