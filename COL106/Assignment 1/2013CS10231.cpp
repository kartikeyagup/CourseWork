#include <iostream>
using namespace std;
#include "q1.h"
#include "q2.h"
#include "q3.h"

template <typename Object>
Stack<Object>::Stack(Object input)
{
	len=0;
	biglen= 1;
	arr= new Object[1];
	arr[0]=input;
}

template <typename Object>
int Stack<Object>::size()
{
	if (this==NULL)
		return 0;
	else
		return len+1;
}

template <typename Object>
bool Stack<Object>::isEmpty()
{
	return (len+1==0);
}

template <typename Object>
Object Stack<Object>::top()
{
	if (len +1==0)
	{
		try
		{
			throw StackEmptyException("Stack is Empty");
		}
		catch (exception & e)
		{
			cout <<e.what() << "\n";
		}
	}
	else
		return arr[len-1];
}

template <typename Object>
void Stack<Object>::push(Object x1)
{
	if (len+1==biglen)
	{
		Object *c1= new Object[biglen];
		for (int p=0; p<biglen; p++)
			c1[p]=arr[p];
		arr= new Object[2*biglen];
		for (int p=0; p<biglen; p++)
			arr[p]=c1[p];
		len +=1;
		biglen *=2;
		arr[len]=x1;
	}
	else
	{
		len+=1;
		arr[len]=x1;
	}
}

template <typename Object>
Object Stack<Object>::pop()
{
	if (len+1==0)
	{
		try
		{
				throw StackEmptyException("Stack is Empty");
		}
		catch (exception & e)
		{
			cout <<e.what() << "\n";
		}
	}
	else
	{
		Object answer=arr[len];
		len-=1;
		return answer;
	}
}

template <typename Object>
void Stack<Object>::display()
{
	for (int t=0;t<=len; t++)
	{
		cout<<arr[t]<<"\t";
	}
}

template <typename Object>
void Stack<Object>::displayreverse()
{
	if (this==NULL)
	{
		cout << "";
	}
	else
	{
		for (int t=len;t>=0; t--)
		{
			cout<<arr[t]<<"\t";
		}
	}
}

template <typename Object>
Node<Object>::Node(Object x)
{
	data=x;
	next=NULL;
}

template <typename Object>
Object Node<Object>::getData()
{
	return this->data;
}

template <typename Object>
Queue<Object>::Queue(Object input)
{
	num=1;
	Node<Object> *x1= new Node<Object>(input);
	x1->next=x1;
	ending=x1;
}

template <typename Object>
int Queue<Object>::size()
{
	return num;
}	

template <typename Object>
void Queue<Object>::enqueue(Object x)
{
	if (num==0)
	{
		Node<Object> *x1= new Node<Object>(x);
		x1->next=x1;
		ending=x1;
		num +=1;
	}
	else
	{
		Node<Object> *point= ending->next;
		Node<Object> *x1= new Node<Object>(x);
		x1->next=this->ending->next;
		this->ending->next=x1;
		this->ending=x1;
		num +=1;
	}
}

template <typename Object>
bool Queue<Object>::isEmpty()
{
	return (num==0);
}

template <typename Object>
Object Queue<Object>::front()
{
	if (num==0)
	{
		try
		{
			throw QueueEmptyException("Queue is Empty");
		}
		catch (exception & e)
		{
			cout <<e.what() << "\n";
		}
	}
	else
	{
		Object ans=this->ending->next->getData();
		return ans;
	}
}

template <typename Object>
Object Queue<Object>::dequeue()
{
	if (num==0)
	{
		try
		{
			throw QueueEmptyException("Queue is Empty");
		}
		catch (exception & e)
		{
			cout <<e.what() << "\n";
		}
	}
	else
	{
		if (num >1)
		{
			Object answer;
			answer= this->ending->next->getData();
			this->ending->next = this->ending->next->next;
			num-=1;
			return answer;
		}
		else
		{
			Object answer=this->ending->getData();
			num-=1;
			return answer;
		}
	}
}

template <typename Object>
void Queue<Object>::display()
{
	int limt= this->size();
	ending=ending->next;
	for (int i=0; i<limt ; i++)
	{
		cout << ending->getData() << "\t";
		ending=ending->next;
	}
	cout << "\n" ;
}


template <typename Object>
Queuest<Object>::Queuest(Object o)
{
	instack=new Stack<Object>(o);
	outstack=NULL;
}

template <typename Object>
int Queuest<Object>::size()
{
	int lenin,lenout;
	if (this->outstack ==NULL)
		lenout=0;
	else
		lenout=this->outstack->size();
	lenin=this->instack->size();
	return (lenin+lenout);
}

template <typename Object>
void Queuest<Object>::enqueue(Object x)
{
	this->instack->push(x);
	// Amortized run time = O(1)
}

template <typename Object>
void Queuest<Object>::moveStack()
{
	if (this->outstack==NULL)
	{
		Object x= this->instack->pop();
		outstack=new Stack<Object>(x);
	}
	else
	{
		Object x= this->instack->pop();
		outstack->push(x);
	}
	int limt=this->instack->size();
	for (int count=0; count<limt; count ++)
	{
		Object newelem=this->instack->pop();
		this->outstack->push(newelem);
	}
}

template <typename Object>
bool Queuest<Object>::isEmpty()
{
	return (this->size()==0);
}

template <typename Object>
Object Queuest<Object>::front()
{
	if (this->outstack->size()>0)
	{
		return this->outstack->top();
	}
	else
	{
		if (this->size()==0)
		{
				throw QueueStEmptyException("Queue is Empty");	//Raise exception
		}
		else
		{
			moveStack();
			return this->outstack->top();
		}
	}
}

template <typename Object>
void Queuest<Object>::display()
{
	this->outstack->displayreverse();
	this->instack->display();
	cout << "\n";
}

template <typename Object>
Object Queuest<Object>::dequeue()
{
if (this->outstack->size()>0)
	{
		return this->outstack->pop();
	}
	else
	{
		if (this->size() ==0)
		{
				throw QueueStEmptyException("Queue is Empty") ;//return 0;		//Raise exception
		}
		else
		{
			moveStack();
			return this->outstack->pop();
		}
	}
	// Amortized run time = O(1)
}

int main()
{
	int d;
	//Stack testing
	cout<< "Testing stack implementation by growable array \n \n";
	Stack<int> *st1=new Stack<int>(10);
	st1->pop();
	st1->top();
	st1->pop();
	st1->push(13); 
	st1->display();
	cout << "\n";
	st1->push(1);
	st1->display();
	cout << "\n";
	st1->push(10);
	st1->display();
	cout << "\n";
	st1->push(100);
	st1->display();
	cout << "\n";
	//cout << "printing reverse \n";
	st1->displayreverse();
	cout << "\n";
	cout<< st1->size()<<"\n";
	cout<<	st1->top()<<"\n";
	cout<< st1->pop()<< "\n";
	st1->display();
	cout << "\n";
	
	// Queue testing
	cout<<"\nTesting the queue implementation by linked list \n \n";
	Queue<int> *q1= new Queue<int>(25);
	Queue<int> *q2 = new Queue<int>(100);
	q2->dequeue();
	q2->front();
	q1->enqueue(34);
	cout << q1->size() << "\n";
	q1->enqueue(345);
	cout << q1->size() << "\n";
	cout << q1->front() << "\n";
	q1->display();
	cout << q1->dequeue() << "\n";
	cout << q1->size() << "\n";
	cout << q1->dequeue() << "\n";
	cout << q1->size() << "\n";

	//Queue by stack testing
	cout<<"\n Testing the queue by stack implementation \n \n";
	Queuest<int> *qst1= new Queuest<int>(25);
	Queuest<int> *qst2= new Queuest<int>(37); 
	try
	{
		cout << qst2->dequeue() << "\n";
		cout << qst2->size() << "\n";
		cout << qst2->front() << "\n";
	}
	catch (exception & e)
	{
		cout <<e.what() << "\n";
	}
	cout << qst1->size() << "\n";
	qst1->enqueue(34);
	qst1->enqueue(345);
	cout << qst1->size() << "\n";
	cout << qst1->front() << "\n";
	cout << "Displaying the queue by stack: ";
	qst1->display();
	qst1->enqueue(456);
	cout << "Displaying the queue by stack: ";
	qst1->display();
	cout << qst1->dequeue() << "\n";
	cout << "Displaying the queue by stack: ";
	qst1->display();
	cout << qst1->size() << "\n";
	cin >> d;
	return d;
}
