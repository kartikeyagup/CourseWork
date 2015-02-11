#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>

#include "Point.h"
#include "Maze.h"
#include "DequeADT.h"
//#include "DequeSTL.h"
#include "DequeSTL.cpp"
#include "DequeArray.cpp"
//#include "MazeSolver.cpp"

using namespace std;

void printStringDeque(DequeADT<string>* deque)
{
	cout << "deque size = " << deque->size() << endl;
	for(int i = 0; i < deque->size(); i++)
	{
		cout << deque->at(i) << endl;
	}
	cout << endl;
}

// Tests the addLast method.
void testAddLast(DequeADT<string>* deque) {
	cout << "--------------------------------------------------------------------------------------------------------------" << endl;
	cout << "push_back:" << endl;
	deque->push_back("seven");
	printStringDeque(deque);
	deque->push_back("years");
	printStringDeque(deque);
	deque->push_back("ago");
	printStringDeque(deque);
}
	
// Tests the removeLast method.
void testRemoveLast(DequeADT<string>* deque) {
	cout << "--------------------------------------------------------------------------------------------------------------" << endl;
	cout << "pop_back:" << endl;
	cout << "element removed : " << deque->back() << endl;
	deque->pop_back();
	printStringDeque(deque);
	cout << "element removed : " << deque->back() << endl;
	deque->pop_back();
	printStringDeque(deque);
	cout << "element removed : " << deque->back() << endl;
	deque->pop_back();
	printStringDeque(deque);
}

// Tests the isEmpty and size methods.
void testIsEmptySize(DequeADT<string>* deque) {
	cout << "--------------------------------------------------------------------------------------------------------------" << endl;
	cout << "isEmpty / size:" << endl;
	cout << deque->empty() << " / " << deque->size() << endl;
	deque->push_back("seven");
	cout << deque->empty() << " / " << deque->size() << endl;
	deque->push_back("years");
	cout << deque->empty() << " / " << deque->size() << endl;
	deque->push_back("ago");
	cout << deque->empty() << " / " << deque->size() << endl;
	while (!deque->empty()) {
		deque->pop_back();
		cout << deque->empty() << " / " << deque->size() << endl;
	}
}

// Tests the clear method.
void testClear(DequeADT<string>* deque) {
	cout << "--------------------------------------------------------------------------------------------------------------" << endl;
	cout << "clear:" << endl;
	deque->push_back("four");
	deque->push_back("score");
	deque->push_back("and");
	deque->push_back("seven");
	deque->push_back("years");
	deque->push_back("ago");
	printStringDeque(deque);
	deque->clear();
	printStringDeque(deque);
}

// Tests the addFirst method.
void testAddFirst(DequeADT<string>* deque) {
	cout << "--------------------------------------------------------------------------------------------------------------" << endl;
	cout << "push_front:" << endl;
	deque->push_front("and");
	printStringDeque(deque);
	deque->push_front("score");
	printStringDeque(deque);
	deque->push_front("four");
	printStringDeque(deque);

	deque->push_back("seven");
	printStringDeque(deque);
	deque->push_back("years");
	printStringDeque(deque);
	deque->push_back("ago");
	printStringDeque(deque);
}

// Tests the removeFirst method.
void testRemoveFirst(DequeADT<string>* deque) {
	cout << "--------------------------------------------------------------------------------------------------------------" << endl;
	cout << "pop_front:" << endl;
	while (!deque->empty()) {
		cout << "element removed : " << deque->front() << endl;
		deque->pop_front();
		printStringDeque(deque);
	}
}

// Tests the addFirst, addLast, removeFirst, and removeLast methods together.
void testAddRemove(DequeADT<string>* deque) {
	cout << "--------------------------------------------------------------------------------------------------------------" << endl;
	cout << "add/remove-Front/Back together:" << endl;
	deque->push_front("and");
	deque->push_back("seven");
	deque->push_front("score");
	deque->push_back("years");
	deque->push_front("four");
	deque->push_back("ago");
	printStringDeque(deque);
	while (!deque->empty()) {
		cout << "element removed : " << deque->back() << endl;
		deque->pop_back();
		printStringDeque(deque);
		cout << "element removed : " << deque->front() << endl;
		deque->pop_front();
		printStringDeque(deque);
	}
}

int main(int argc, char **argv)
{
	DequeADT<string> * deque;
	if(argc == 0) //|| atoi(argv[1]) == 0)
		deque = new DequeSTL<string>();
	else
		deque = new DequeArray<string>();
	testAddLast(deque);
	testRemoveLast(deque);
	testIsEmptySize(deque);
	testClear(deque);
	
	testAddFirst(deque);
	testRemoveFirst(deque);
	testAddRemove(deque);
}
